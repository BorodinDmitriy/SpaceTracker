#include "models.h"

// класс загрузчика данных с space-track.org

class SpaceTrackDataRetriever {
public:
	CurlInstance *curl;
	Parser *parser;

	SpaceTrackDataRetriever();
	~SpaceTrackDataRetriever();

	void authorize(std::string login, std::string password);

	const tle* getSatellitesPositions(long norad_cat_id);
	const tle* getSatellitesPositions(std::string datetime);

	const tle getSatellitePosition(long norad_cat_id);

	const object_info* getSatellitesInfo(long norad_cat_id);
	const object_info* getSatellitesInfo(std::string datetime);
}