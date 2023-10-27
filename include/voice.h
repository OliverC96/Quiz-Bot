#ifndef VOICE_H
#define VOICE_H

#include <string>

/**
 * @class Voice
 * @brief A class for handling voice-related operations.
 */
class Voice {
public:
    /**
     * @brief Constructor for the Voice class.
     * @param userInputText The user input text.
     */
    Voice(const std::string& userInputText);

    /**
     * @brief Initialize the Voice API.
     */
    void initializeVoiceAPI();

    /**
     * @brief End the Voice API.
     */
    void endVoiceAPI();

    /**
     * @brief Convert speech to text.
     * @return The text converted from speech.
     */
    std::string convertSpeechToText();

private:
    std::string userInputText; /**< The user input text. */
};

#endif
