#include <zed.h>

#define CURL_STATICLIB
#include <curl/curl.h>
#pragma comment( lib, "libcurl.lib" )
#pragma comment( lib, "zlib.lib" )

#pragma comment( lib, "advapi32.lib" )
#pragma comment( lib, "crypt32.lib" )
#pragma comment( lib, "normaliz.lib" )
#pragma comment( lib, "wldap32.lib" )
#pragma comment( lib, "ws2_32.lib" )

// #include "vend/rapid-json/document.h"
// #include "vend/rapid-json/writer.h"
// #include "vend/rapid-json/stringbuffer.h"

#include <string>
#include <memory>

struct curl_t {
	handle curl;
} curl;

void zed_curl_init() {
	curl.curl = (handle)curl_easy_init();
    curl_easy_setopt( curl.curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4 );
    curl_easy_setopt( curl.curl, CURLOPT_TIMEOUT, 10 );
    curl_easy_setopt( curl.curl, CURLOPT_FOLLOWLOCATION, 1L );
}

size_t curl_cb( const char* in, size_t size, size_t count, std::string* out ) {
    size_t total = size * count;
    out->append( in, total );
    return total;
}

void zed_curl_get( string url, string auth ) {
	curl_easy_setopt( curl.curl, CURLOPT_URL, url );

    curl_slist *headers = 0;
    headers = curl_slist_append( headers, "Content-Type: application/json" );
    char temp[64]; sprintf( temp, "Authorization: Bearer %s", auth );
    headers = curl_slist_append( headers, temp );
    curl_easy_setopt( curl.curl, CURLOPT_HTTPHEADER, headers );

	//

    int code;
    handle data;

    curl_easy_setopt( curl.curl, CURLOPT_WRITEFUNCTION, curl_cb );
    curl_easy_setopt( curl.curl, CURLOPT_WRITEDATA, &data );

	//

    curl_easy_perform( curl.curl );
    curl_easy_getinfo( curl.curl, CURLINFO_RESPONSE_CODE, &code );
    curl_easy_cleanup( curl.curl );

    switch ( code ) {
        case 200: {
            printf( "\nGot successful response from %s\n", url );

            // Response looks good - done using Curl now.  Try to parse the results and print them out.
            // Json::Value jsonData;
            // Json::Reader jsonReader;

            // if (jsonReader.parse(*httpData.get(), jsonData))
            // {
                // std::cout << "Successfully parsed JSON data" << std::endl;
                // std::cout << "\nJSON data received:" << std::endl;
                // std::cout << jsonData.toStyledString() << std::endl;

                // const std::string dateString(jsonData["date"].asString());
                // const std::size_t unixTimeMs( jsonData["milliseconds_since_epoch"].asUInt64());
                // const std::string timeString(jsonData["time"].asString());

                // std::cout << "Natively parsed:" << std::endl;
                // std::cout << "\tDate string: " << dateString << std::endl;
                // std::cout << "\tUnix timeMs: " << unixTimeMs << std::endl;
                // std::cout << "\tTime string: " << timeString << std::endl;
                // std::cout << std::endl;
            // }
            // else
            // {
            //     std::cout << "Could not parse HTTP data as JSON" << std::endl;
            //     std::cout << "HTTP data was:\n" << *httpData.get() << std::endl;
            //     return 1;
            // }

            break;
        }

        default: {
            printf( "Couldn't GET from %s\n", url );
        }
    }
}
