#ifndef WEBINTERSINGLETON_H
#define WEBINTERSINGLETON_H
#include "webinter.h"

class WebInterSingleton {
public:
    static WebInter& Instance() {
        static WebInter wb;
        return wb;
    }
private:
    WebInterSingleton() {}
    ~WebInterSingleton() {}

    WebInterSingleton(WebInterSingleton const&) = delete;
    WebInterSingleton& operator = (WebInterSingleton const&) = delete;
};

#endif // WEBINTERSINGLETON_H
