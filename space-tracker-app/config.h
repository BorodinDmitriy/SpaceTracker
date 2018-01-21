#ifndef CONFIG_H
#define CONFIG_H

#define DirectoryDataBase "D:/QtVit/Qt5.1.0/Tools/QtCreator/bin/TEST/build-untitled-Desktop-Debug/database/dbfile"
#define FILENAME "file"

#define LOGIN_URL "https://www.space-track.org/ajaxauth/login"
#define LOGIN_PARAMETERS "identity=catkiller95@gmail.com&password=catkiller19950214"
#define COOKIE_JAR "cookie"
#define COOKIE_TYPE "cookie"
#define CURL_AGENT "libcurl-agent/1.0"
#define CURL_CERT_TYPE "PEM"
#define CURL_CERT_PATH "D:/QtVit/Qt5.1.0/Tools/QtCreator/bin/TEST/bookingcar.pem"
#define LOAD_TLE_URL "https://www.space-track.org/basicspacedata/query/class/tle_publish/PUBLISH_EPOCH/"
#define LIMIT_LOAD_TLE_STRING "/orderby/PUBLISH_EPOCH%20asc/limit/10/format/tle/metadata/false"
#define WEB_INTER_ERR_MESSAGE "<html>\n<body>\n\t\n\t\t<p><p>You must be logged in to complete this action</p></p>\n\n</body>\n</html>"

#define SELECT_BY_DATE "SELECT * FROM TLE WHERE (DATE = "
#endif // CONFIG_H
