#include <string>
using namespace std;

class quizapi {
    string difficulty;
    string category;
    string questionNumber;

    string urlTemplate = "https://opentdb.com/api.php?amount=%s&category=%s&difficulty=%s", questionNumber, category, difficulty;

    //NOT SURE. TESTING. IF USING CURL LIBRARY, NEED TO ADD EXTERNAL. DO NOT USE
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s) {
        size_t newLength = size*nmemb;
        size_t oldLength = s->size();
        try {
            s->resize(oldLength + newLength);
        }
        catch(std::bad_alloc &e) {
            return 0;
        }
    }

    /* ????????????? AGAIN FOR CURL LIB. DO NOT USE YET. TESTING
    curl_global_init(CURL_GLOBAL_DEFAULT);
        curl = curl_easy_init();
        if(curl) {
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            res = curl_easy_perform(curl);

            if(res != CURLE_OK) {
                fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            }

            curl_easy_cleanup(curl);
        }

        curl_global_cleanup();

        // TODO: Parse the JSON response stored in 'readBuffer' and add the questions to the 'questions' vector
    */

};