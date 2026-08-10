#include "pch.h"
#include "Json.h"
#include "File.h"

#include <rapidjson/istreamwrapper.h>
#include <rapidjson/error/en.h>
#include <iostream>

namespace nu::json
{
    bool Load(const std::string& filename, rapidjson::Document& document)
    {
        // read the file into a string
        std::string buffer;
        if (!ReadTextFile(filename, buffer))
        {
            std::cerr << "Could not read file:" << filename << std::endl;
            return false;
        }

        // convert the string into a json stream
        std::stringstream stream(buffer);
        rapidjson::IStreamWrapper istream(stream);

        // set the json document from the stream
        document.ParseStream(istream);

        // check if the parse was successful
        if (document.HasParseError())
        {
            std::cerr << "Could not parse JSON: " << filename << std::endl;
            std::cerr << "Error: " << rapidjson::GetParseError_En(document.GetParseError()) << std::endl;

            return false;
        }

        // check that the root value is an object, not an array/string/number/etc.
        if (!document.IsObject())
        {
            std::cerr << "JSON root is not an object: " << filename << std::endl;
            return false;
        }

        return true;
    }

    bool Read(const rapidjson::Value& value, const std::string& name, int& data)
    {
        // check if the value has the "<name>" and the correct data type
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsInt())
        {
            std::cerr << "Could not read JSON value (int):" << name << std::endl;
            return false;
        }

        // get the data
        data = value[name.c_str()].GetInt();

        return true;
    }
}