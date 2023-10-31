#include "../include/qa.h"

/**
 * @brief Constructor for the QA class.
 */
QA::QA(int questionId, const std::string& questionText, const std::string& answerText, const std::string& difficultyLevel, const std::string& category) {
    _questionId = questionId;
    _questionText = questionText;
    _answerText = answerText;
    _difficultyLevel = difficultyLevel;
    _category = category;
}

/**
 * @brief Get the question ID.
 */
int QA::getQuestionId() const {
    return _questionId;
}

/**
 * @brief Get the text of the question.
 */
std::string QA::getQuestionText() const {
    return _questionText;
}

/**
 * @brief Get the text of the answer.
 */
std::string QA::getAnswerText() const {
    return _answerText;
}

/**
 * @brief Get the difficulty level of the question.
 */
std::string QA::getDifficultyLevel() const {
    return _difficultyLevel;
}

/**
 * @brief Get the category to which the question belongs.
 */
std::string QA::getCategory() const {
    return _category;
}
