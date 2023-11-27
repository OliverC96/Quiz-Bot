#include "answerScorer.h"

std::unordered_set<std::string> AnswerScorer::extractKeywords(const std::string& text) {
    std::vector<std::string> tokens = tokenize(text);
    std::unordered_set<std::string> keywords;

    std::unordered_set<std::string> stopWords = {"a", "an", "the", "and", "or", "this", "that", "is", "of"};// add more?

    for (const std::string& token : tokens) {
        if (stopWords.count(token) == 0) {
            keywords.insert(token);
        }
    }

    return keywords;
}

/**
 * @brief Calculate the score for a user's answer based on keyword matching.
 *
 * This function calculates a score for the user's answer based on keyword matching.
 *
 * @param userAnswer The user's answer represented as a QA object.
 * @param correctAnswer The correct answer and the question.
 * @return The calculated score as a percentage.
 */
double AnswerScorer::calculateAnswerScore(std::string userAnswer, const QA& correctAnswer) {

    // Extract keywords from the user's and correct answers.
    std::unordered_set<std::string> userKeywords = extractKeywords(userAnswer);
    std::unordered_set<std::string> correctKeywords = extractKeywords(correctAnswer.getAnswerText());

    // Calculate the score based on the intersection of user and correct answer keywords.
    std::unordered_set<std::string> commonKeywords;
    for (const std::string& keyword : userKeywords) {
        if (correctKeywords.count(keyword) > 0) {
            commonKeywords.insert(keyword);
        }
    }

    // Calculate the score as a percentage based on the number of common keywords.
    double score = (static_cast<double>(commonKeywords.size()) / correctKeywords.size()) * 100.0;

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