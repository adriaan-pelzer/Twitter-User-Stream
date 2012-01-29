#include <curl/curl.h>

#ifndef _FT_CURL_H_
#define _FT_CURL_H_

#define C_KEY "pKEdIYPZ8KUvU6bilTVebw"
#define C_SECRET "HyollEZ4tbEdpnCsZsp1LKHgEE3Io1YG57M4eMSpNUA"
#define T_KEY "169026281-xkZp4FAMwIOPfZv7qIDlSAF3GtIi6mY55g19hWbd"
#define T_SECRET "7LWGVo1PCtYNzetWYOk83ZFBaugugabhJ2BPUT58"

struct MemoryStruct {
    CURL *curl_handle; /* HTTP Connection handle */
    char glob_init; /* Indicates if Connection handle has been initialised */
    char *req_url; /* OAuth signed Twitter API URL */
    char *memory; /* scratch memory for streamed content received */
    size_t size; /* Size of scratch memory */
};

CURLcode curl_connect();

#endif
