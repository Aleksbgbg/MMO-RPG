#include "Json.h"

#include <fstream>

using nlohmann::json;

json read_json(const std::string& filename)
{
	std::ifstream input{ filename };

	return json::parse(input);
}