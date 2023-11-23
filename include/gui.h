#ifndef GUI_H
#define GUI_H

#include "qa.h"
#include "qaSet.h"
#include "user.h"
#include "voice.h"
#include <vector>
#include <tuple>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include <Wt/WStackedWidget.h>
#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WWidget.h>
#include <Wt/WGridLayout.h>
#include <Wt/WLayoutItem.h>
#include <Wt/WLineEdit.h>
#include <Wt/WTextArea.h>
#include <Wt/WPushButton.h>
#include <Wt/WImage.h>
#include <Wt/WText.h>
#include <Wt/WTable.h>
#include <Wt/WTableRow.h>
#include <Wt/WSignal.h>

/**
 * @class GUI
 * @brief A class representing the graphical user interface for a quiz application.
 */
class GUI : public Wt::WApplication{
public:

    /**
     * @brief Constructor to initialize the GUI
     * @param env
     */
    GUI(const Wt::WEnvironment &env);

    /**
     * @brief Destructor
     */
    ~GUI(void);

    /**
     * @brief Generates a navigation bar component
     * @param showPrivatePages used to customize the navbar links to reflect the user's current status (logged-in or anonymous)
     * @return The navbar widget
     */
    std::unique_ptr<Wt::WContainerWidget> generateNavBar(bool showPrivatePages);

    /**
     * @brief Initializes the main page of the application
     */
    void initializeMainPage(void);

    /**
     * @brief Initializes the login page
     */
    void initializeLoginPage(void);

    /**
     * @brief Initializes the register page
     */
    void initializeRegisterPage(void);

    /**
     * @brief Initializes the leaderboard page
     */
    void initializeLeaderboardPage(void);

    /**
     * @brief Initializes the difficulty page
     */
    void initializeDifficultyPage(void);

    /**
     * @brief Initializes the question page
     */
    void initializeQuestionPage(void);

    /**
     * @brief Initializes the profile page containing all information relevant to the currently logged in user
     */
    void initializeProfilePage(void);

    /**
     * @brief Fetches the current leaderboard data from the specified file
     * @param filePath
     */
    void loadLeaderboard(std::string filePath);

    /**
     * @brief Display the question page.
     */
    void displayQuestionPage();

    /**
     * @brief Updates the question page.
     */
    void updateQuestionPage();

    /**
     * @brief Display the difficulty page.
     */
    void displayDifficultyPage();

    /**
     * @brief Display the user profile page.
     */
    void displayUserProfile();

    /**
     * @brief Display the leaderboard page.
     */
    void displayLeaderboard();

    /**
     * @brief Display the main/welcome page.
     */
    void displayMainPage();

    /**
     * @brief Display the login page.
     */
    void displayLoginPage();

    /**
     * @brief Display the register page.
     */
    void displayRegisterPage();

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

    // High-level application objects/components
    QASet *answerKey; /**< The answer key for questions. */
    QASet *userAnswers; /**< The user's answers. */
    User *currentUser; /**< The currently logged-in user. */
    Wt::WStackedWidget* pages; /**< Stores references to the various application pages. */
    std::vector<std::tuple<std::string, int, std::string, std::string>> leaderboard; /**< The leaderboard data. */

    // Additional attributes critical to the game logic
    int currentQuestionID; /**< The current question being displayed. */
    int finalScore; /**< The user's final score. */

    // Containers representing the various pages of the application
    std::unique_ptr<Wt::WContainerWidget> loginPage;
    std::unique_ptr<Wt::WContainerWidget> registerPage;
    std::unique_ptr<Wt::WContainerWidget> mainPage;
    std::unique_ptr<Wt::WContainerWidget> difficultyPage;
    std::unique_ptr<Wt::WContainerWidget> profilePage;
    std::unique_ptr<Wt::WContainerWidget> leaderboardPage;
    std::unique_ptr<Wt::WContainerWidget> questionPage;

    /*
     * Maintaining references to specific elements of the GUI to allow for them to be dynamically updated as necessary
     */
    Wt::WLineEdit* questionInput;
    Wt::WTextArea* answerArea;
    Wt::WPushButton* submitButton;
    Wt::WText* questionProgress;
    Wt::Signals::connection enterConn;

    //being used for testing reigstration SUNG
    Wt::WLineEdit* usernameField;
    Wt::WLineEdit* passwordField;
    Wt::WLineEdit* loginUsernameField;
    Wt::WLineEdit* loginPasswordField;
    Wt::WLineEdit* confirmPasswordField;
    Wt::WText* loginErrorMessage;
    Wt::WText* registerErrorMessage;

    std::vector<QA> quizQuestions; // ONLY for testing purposes - will change later to QASet

};

#endif
