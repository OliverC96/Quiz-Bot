#include "voice.h"
#include <iostream>
#include <string>
//#include "curl/curl.h"
using namespace std;

/**
 * @Class Voice - Class for voice-to-text API
 *        Allow the user to record their voice by pressing a key/button on the quiz site
 * @param userInputText - user's speech, converted in text/String, from the API
 * @author Taegyun Kim
 */


/**
 * @brief Constructor for the Voice class.
 */
Voice::Voice(const std::string& userInputText) : userInputText(userInputText) {
    // Constructor code here

}

/**
 * @brief Initialize the Voice API.
 */
void Voice::initializeVoiceAPI() {
    // Code to initialize the Voice API
}

/**
 * @brief End the Voice API.
 */
void Voice::endVoiceAPI() {
    // Code to end the Voice API
}

/**
 * @brief Convert speech to text.
 * @return The text converted from speech.
 */
std::string Voice::convertSpeechToText() {
    // Code to convert speech to text
    return ""; // Placeholder return, actual implementation needed
}

/**
 * main method for this class
 * to test speech-to-text etc.
 * @return
 */
int Voice::main(){
    string s = "This is a string var";
    cout << s << endl;

    return 0;
}