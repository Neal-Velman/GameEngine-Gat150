#pragma once
#include <rapidjson/document.h>
#include <string>

namespace nu::json
{
	bool Load(const std::string& filename, rapidjson::Document& document);

	// read json data
	bool Read(const rapidjson::Value& value, const std::string& name, int& data);
}