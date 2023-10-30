#include "gui.h"

/**
 * @brief Display the question page.
 */
void GUI::displayQuestionPage() {
    // Implementation for displaying the question page
}

/**
 * @brief Display the user profile page.
 */
void GUI::displayUserProfile() {
    // Implementation for displaying the user profile page
}

/**
 * @brief Display the leaderboard page.
 */
void GUI::displayLeaderboard() {
    // Implementation for displaying the leaderboard page
}

/**
 * @brief Display the login page.
 */
void GUI::displayLoginPage() {
    // Implementation for displaying the login page
}

/**
 * @author Oliver Clennan
 * @brief Updates the leaderboard with the current user's score
 */
void GUI::updateLeaderboard() {
    std::tuple<std::string, int> newEntry = make_tuple(currentUser.userID, finalScore);
    leaderboard.push_back(newEntry);
}

/**
 * @brief Update the user's score.
 */
void GUI::updateScore() {
    // Implementation for updating the user's score
}

/**
 * @brief Store the user's score.
 */
void GUI::storeUserScore() {
    // Implementation for storing the user's score
}

/**
 * @brief Get the leaderboard data.
 * @return A vector of tuples containing userID and userRanking.
 */
std::vector<std::tuple<std::string, int>> GUI::getLeaderboardData() {
    // Implementation for getting leaderboard data
    std::vector<std::tuple<std::string, int>> leaderboardData;
    // Populate leaderboardData with actual data
    return leaderboardData;
}

/**
 * @brief Show the answer button on the question page.
 */
void GUI::showAnswerButton() {
    // Implementation for showing the answer button
}

/**
 * @brief Hide the answer button on the question page.
 */
void GUI::hideAnswerButton() {
    // Implementation for hiding the answer button
}

/**
 * @brief Process the current answer submitted by the user.
 */
void GUI::processCurrAnswer() {
    // Implementation for processing the current answer
}

/**
 * @brief Log in the user.
 */
void GUI::loginUser() {
    // Implementation for user login
}

/**
 * @brief Log out the user.
 */
void GUI::logoutUser() {
    // Implementation for user logout
}

/**
 * @brief Register a new user.
 */
void GUI::registerUser() {
    // Implementation for user registration
}
