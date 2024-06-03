#include <iostream>
#include <string>
#include <curl/curl.h>
#include "../colors.hpp"

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

int main() {
    CURL *curl;
    CURLcode res;
    std::string readBuffer;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if(curl) {
        std::string ip;
        std::cout << br_blue << "Enter IP address:" << RESET_COLOR << " ";
        std::cin >> ip;

        std::string url = "http://ip-api.com/json/" + ip;

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if(res != CURLE_OK) {
            std::cerr << "Error: " << curl_easy_strerror(res) << std::endl;
            return 1;
        }

        std::cout << readBuffer << std::endl;

    } else {
        std::cerr << red << "[!] ERROR" << RESET_COLOR << std::endl;
        return 1;
    }

    curl_global_cleanup();

    return 0;
}