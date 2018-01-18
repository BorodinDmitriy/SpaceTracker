#include "models.h"

class Parser {
public:
	Parser();
	~Parser();

	std::string parseDate(std::string datetime);
	const tle parseTleJson(std::string tleJson);
	const object_info parseObjectInfoJson(std::string objectInfoJson);
}