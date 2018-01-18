#include "../space-tracker-lib/curl/curl.h"

// curl instance - singleton
class CurlInstance {
public:
	CurlInstance();
	~CurlInstance();

	void query(std::string query);
}