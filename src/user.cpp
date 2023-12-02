#include "user.h"

/**
 * @brief Constructor for the User class.
 */
User::User(const std::string& userID, const std::string& userPW, int ranking, std::vector<std::tuple<int, std::string, std::string>> scoreHistory) : userID(userID), userPW(userPW), ranking(ranking), scoreHistory(scoreHistory) {
    // Constructor code here
}

/**
 * @brief Get the user's ID.
 */
std::string User::getID() const {
    return userID;
}

/**
 * @brief Get the user's password.
 */
std::string User::getPW() const {
    return userPW;
}

/**
 * @brief Set the user's password.
 * @param newPassword The new password to set.
 */
void User::setPW(const std::string& newPassword) {
    userPW = newPassword;
}

/**
 * @brief Set the user's ID.
 * @param newID The new user ID to set.
 */
void User::setID(const std::string& newID) {
    userID = newID;
}

/**
 * @brief Get the user's score.
 */
int User::getUserScore() const {
    return userScore;
}

/**
 * @brief Set the user's score.
 * @param newScore The new score to set.
 */
void User::setUserScore(int newScore) {
    userScore = newScore;
}

/**
 * @brief Retrieves a comprehensive history of the user's scores on previous quizzes
 * @return A collection of scores
 */
std::vector<std::tuple<int, std::string, std::string>> User::getScoreHistory() const {
    return this->scoreHistory;
}

/**
 * @brief Updates the score history with the user's current score, and the provided arguments
 * @param category The category of the quiz in which this score was attained
 * @param difficulty The difficulty level of the quiz in which this score was attained
 */
void User::updateScoreHistory(std::string category, std::string difficulty) {
    std::tuple<int, std::string, std::string> newScore = std::make_tuple(this->userScore, category, difficulty);
    this->scoreHistory.insert(scoreHistory.begin(), newScore);
}

/**
 * @brief Saves all user data to the user's file
 */
void User::saveUserData() const {

    // Open the user's file for writing
    std::string filePath = "user/" + this->userID + ".txt";
    std::ofstream userFile(filePath);

    if (!userFile.is_open()) {
        std::cerr << "Error - failed to locate user file for: " << this->userID << std::endl;
        return;
    }

    // Write out all user data to their file
    userFile << this->userID << "," << this->userPW << "," << this->ranking << std::endl;

    for (int i = 0; i < scoreHistory.size(); i++) {
        std::tuple<int, std::string, std::string> currScore = this->scoreHistory[i];
        userFile << std::get<0>(currScore) << "," << std::get<1>(currScore) << "," << std::get<2>(currScore);
        if (i != scoreHistory.size() - 1) {
            userFile << std::endl;
        }
    }

    // Close the user file
    userFile.close();
}

/**
 * @brief Retrieve the highest leaderboard rank associated with this user
 * @return The highest rank
 */
int User::getUserRank() const {
    return ranking;
}

/**
 * @brief Update the user's ranking with the specified rank
 * @param newRank
 */
void User::setUserRank(int newRank) {
    ranking = newRank;
}