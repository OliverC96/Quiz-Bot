#ifndef GUI_H
#define GUI_H

#include "qa.h"
#include "qaSet.h"
#include "user.h"
#include "voice.h"
#include <vector>
#include <tuple>
#include <string>

#include <Wt/WStackedWidget.h>
#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WWidget.h>
#include <Wt/WGridLayout.h>
#include <Wt/WLayoutItem.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/WSignal.h>

/**
 * @class GUI
 * @brief A class representing the graphical user interface for a quiz application.
 */
class GUI : public Wt::WApplication{
public:
    GUI(const Wt::WEnvironment &env);
    ~GUI(void);
    /**
     * @brief Display the question page.
     */
    void displayQuestionPage();

    /**
     * @brief Display the user profile page.
     */
    void displayUserProfile();

    /**
     * @brief Display the leaderboard page.
     */
    void displayLeaderboard();

    /**
     * @brief Display the login page.
     */
    void displayLoginPage();

    /**
     * @brief Update the leaderboard.
     */
    void updateLeaderboard();

    /**
     * @brief Update the user's score.
     */
    void updateScore();

    /**
     * @brief Store the user's score.
     */
    void storeUserScore();

    /**
     * @brief Get the leaderboard data.
     * @return A vector of tuples containing userID and userRanking.
     */
    std::vector<std::tuple<std::string, int>> getLeaderboardData();

    /**
     * @brief Show the answer button on the question page.
     */
    void showAnswerButton();

    /**
     * @brief Hide the answer button on the question page.
     */
    void hideAnswerButton();

    /**
     * @brief Process the current answer submitted by the user.
     */
    void processCurrAnswer();

    /**
     * @brief Log in the user.
     */
    void loginUser();

    /**
     * @brief Log out the user.
     */
    void logoutUser();

    /**
     * @brief Register a new user.
     */
    void registerUser();

private:
    QASet answerKey; /**< The answer key for questions. */
    QASet userAnswers; /**< The user's answers. */
    QA *currentQuestion; /**< The current question being displayed. */
    User *currentUser; /**< The currently logged-in user. */
    int finalScore; /**< The user's final score. */
    Wt::WStackedWidget* pages;
    std::vector<std::tuple<std::string, int>> leaderboard; /**< The leaderboard data. */
};

#endif
