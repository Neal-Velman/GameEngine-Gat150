#pragma once
#include <string>
#include <iostream>

namespace nu {
	inline std::string ToLower(const std::string& str) {
		std::string lower = str;
		for (auto& c : lower) {
			c = std::tolower(c);
		}
		return lower;
	}

	inline std::string ToUpper(const std::string& str) {
		std::string upper = str;
		for (auto& c : upper) {
			c = std::toupper(c);
		}
		return upper;
	}

	inline bool EqualsIgnoreCase(const std::string& strA, const std::string& strB) {
		if (strA.size() != strB.size()) {
			return false;
		}
		return ToLower(strA) == ToLower(strB);
	}
}