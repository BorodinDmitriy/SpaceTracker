// модель объекта tle

struct tle {
	int norad_cat_id; // идентификатор летающего объекта в каталоге
	std::string msg_epoch; // время фиксации сообщения о данных объекта 
	std::string direction; // траектория - ascending/descending
	float latitude; // широта
	float longitude; // долгота
	float inclination; // наклон
	int id; // непосредственный идентифактор tle в базе апишной
};

struct object_info {
	int norad_cat_id; // идентификатор летающего объекта в каталоге
	std::string object_type; // тип летающего объекта
	std::string satellite_name; // название спутника
	std::string country; // код страны/запускателя
	std::string launch_date; // дата запуска
	float period; // период вращения вокруг земли
	float inclination; // наклон
	float apogee; // апогей - дальняя точка от поверхности земли
	float perigee; // перигей - самая ближняя точка от поверхности земли
	std::string comment; // комментарий к объекту
	std::string object_size_type; // тип размера объекта
	int launch_year; // год запуска (для краткости)
	std::string object_id; // идентификатор объекта во внутренней базе
}