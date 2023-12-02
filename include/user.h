#ifndef USER_H
#define USER_H

#include <string>
#include <iostream>
#include <fstream>

/**
 * @class User
 * @brief A class representing a user in the application.
 */
class User {
public:
    /**
     * @brief Constructor for the User class.
     * @param userID The user's ID.
     * @param userPW The user's password.
     * @param ranking The user's ranking.
     * @param scoreHistory A comprehensive record of the user's scores in previous quizzes.
     */
    User(const std::string& userID, const std::string& userPW, int ranking, std::vector<std::tuple<int, std::string, std::string>> scoreHistory);

    /**
     * @brief Get the user's ID.
     * @return The user's ID.
     */
    std::string getID() const;

    /**
     * @brief Get the user's password.
     * @return The user's password.
     */
    std::string getPW() const;

    /**
     * @brief Set the user's password.
     * @param newPassword The new password to set.
     */
    void setPW(const std::string& newPassword);

    /**
     * @brief Set the user's ID.
     * @param newID The new user ID to set.
     */
    void setID(const std::string& newID);

    /**
     * @brief Get the user's score for the current session
     * @return The user's score.
     */
    int getUserScore() const;

    /**
     * @brief Set the user's score for the current session
     * @param newScore The new score to set.
     */
    void setUserScore(int newScore);

    /**
     * @brief Retrieves a comprehensive history of the user's scores on previous quizzes
     * @return A collection of scores
     */
    std::vector<std::tuple<int, std::string, std::string>> getScoreHistory() const;

    /**
     * @brief Updates the score history with the user's current score, and the provided arguments
     * @param category The category of the quiz in which this score was attained
     * @param difficulty The difficulty level of the quiz in which this score was attained
     */
    void updateScoreHistory(std::string category, std::string difficulty);

    /**
     * @brief Saves all user data to the user's file
     */
    void saveUserData(void) const;

    /**
     * @brief Get the user's rank.
     * @return The user's rank.
     */
    int getUserRank() const;

    /**
     * @brief Set the user's rank.
     * @param newRank The new rank to set.
     */
    void setUserRank(int newRank);

private:
    std::vector<std::tuple<int, std::string, std::string>> scoreHistory;
    std::string userID; /**< The user's ID. */
    std::string userPW; /**< The user's password. */
    int userScore; /**< The user's score. */
    int ranking; /**< The user's ranking. */
};

#endif
