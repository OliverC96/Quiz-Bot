#include "qaSet.h"

/**
 * @brief Get a specific question by its ID.
 */
QA QASet::getQuestion(int id) {
    // Check if the question ID exists in the map
    auto it = questions.find(id);
    if (it != questions.end()) {
        return it->second; // Return the QA object for the specified ID
    } else {
        // Return an empty QA object if the ID is not found
        return QA(0, "", "", "", "");
    }
}
