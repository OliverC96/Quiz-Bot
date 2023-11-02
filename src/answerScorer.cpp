#include "answerScorer.h"

/**
 * @brief Calculate the score for a user's answer based on keyword matching.
 *
 * This function calculates a score for the user's answer based on keyword matching.
 *
 * @param userAnswer The user's answer represented as a QA object.
 * @param keywords The set of keywords for the question.
 * @return The calculated score as a percentage.
 */
double AnswerScorer::calculateAnswerScore(const QA& userAnswer, const std::unordered_set<std::string>& keywords) {
    // Tokenize the user's answer.
    std::vector<std::string> userTokens = tokenize(userAnswer.getAnswerText());

    // Initialize variables to keep track of found and total keywords.
    int foundKeywords = 0;
    int totalKeywords = keywords.size();

    // Iterate through user's tokens and check if they match any of the question keywords.
    for (const std::string& token : userTokens) {
        if (keywords.count(token) > 0) {
            foundKeywords++;
        }
    }

    // Calculate the score as a percentage based on the number of found keywords.
    double score = (static_cast<double>(foundKeywords) / totalKeywords) * 100.0;

    return score;
}

/**
 * @brief Tokenize a string into words.
 *
 * This function splits a string into individual words using space as a delimiter, and removes punctuation.
 *
 * @param input The input string to tokenize.
 * @return A vector of tokens.
 */
std::vector<std::string> AnswerScorer::tokenize(const std::string& input) {
    std::vector<std::string> tokens;
    std::istringstream tokenStream(input);
    std::string token;
    while (std::getline(tokenStream, token, ' ')) {
        tokens.push_back(removePunctuation(token));
    }
    return tokens;
}

/**
 * @brief Remove punctuation from a string.
 *
 * This function removes punctuation characters from a string.
 *
 * @param str The input string.
 * @return The input string with punctuation characters removed.
 */
std::string AnswerScorer::removePunctuation(const std::string& str) {
    std::string result;
    for (char ch : str) {
        if (!std::ispunct(ch)) {
            result += ch;
        }
    }
    return result;
}