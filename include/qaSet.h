#ifndef QASET_H
#define QASET_H

#include "qa.h"
#include <map>

/**
 * @class QASet
 * @brief A class to manage a set of questions and their answers.
 */
class QASet {
public:
    /**
     * @brief Get a specific question by its ID.
     * @param id The ID of the question to retrieve.
     * @return The QA object for the specified question ID. Returns an empty QA object if the question ID is not found.
     */
    QA getQuestion(int id);

private:
    std::map<int, QA> questions; /**< A map of question IDs to QA objects. */
};

#endif
