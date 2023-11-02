#ifndef ANSWER_SCORER_H
#define ANSWER_SCORER_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <locale>
#include "qa.h"

/**
 * @class AnswerScorer
 * @brief A class for scoring user answers based on keyword comparison.
 */
class AnswerScorer {
public:
    /**
     * @brief Calculate the score for a user's answer based on keyword matching.
     *
     * This function calculates a score for the user's answer based on keyword matching.
     *
     * @param userAnswer The user's answer represented as a QA object.
     * @param keywords The set of keywords for the question.
     * @return The calculated score as a percentage.
     */
    double calculateAnswerScore(const QA& userAnswer, const std::unordered_set<std::string>& keywords);
private:
    /**
     * @brief Tokenize a string into words and remove punctuation.
     *
     * This function splits a string into individual words using space as a delimiter and removes punctuation.
     *
     * @param input The input string to tokenize.
     * @return A vector of tokens with punctuation removed.
     */
    std::vector<std::string> tokenize(const std::string& input);

    /**
     * @brief Remove punctuation from a string.
     *
     * This function removes punctuation characters from a string.
     *
     * @param str The input string.
     * @return The input string with punctuation characters removed.
     */
    std::string removePunctuation(const std::string& str);
};

#endif
