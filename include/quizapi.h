#ifndef QUIZAPI_H
#define QUIZAPI_H
#include <string>
using namespace std;

class QuizAPI {
public:
    //constructor
    QuizAPI(string& url);

    string getApi();
    string setCategory();
    string setDifficulty();
    string setQuestionAmount();
private:

};

#endif