#include "Json.h"

#include <fstream>

using nlohmann::json;

json read_json(const std::string& filename)
{
	std::ifstream input{ filename };

	if (!input.is_open())
	{
		throw std::runtime_error{ "Could not open JSON file." };
	}

	return json::parse(input);
}