#pragma once

#include <string>

class TmxObjectProperty
{
public:
	TmxObjectProperty(const std::string name, const std::string type, const std::string value);
	~TmxObjectProperty();

	std::string name;
	std::string type;
	std::string value;
};