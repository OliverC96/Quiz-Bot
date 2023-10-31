#include "../include/gui.h"

/**
 * Initializes a Wt application
 * @param env the Wt environment
 */
GUI::GUI(const Wt::WEnvironment &env): WApplication(env) {

    currentQuestion = new QA(1, "question", "answer", "difficulty", "category");
    currentUser = new User("userid", "userpass", 200, 1);

    setTitle("QuizBot");


//    // Linking an external stylesheet to the application
//    useStyleSheet("./resources/styles.css");
//
//    // Configuring the wrapper (highest-level container element)
//    wrapper_ = root()->addWidget(std::make_unique<Wt::WContainerWidget>());
//    wrapper_->setStyleClass("wrapper");
//
//    // Configuring the title header
//    titleHeader_ = wrapper_->addWidget(std::make_unique<Wt::WText>("Wordle"));
//    titleHeader_->setStyleClass("title");
//
//    // Configuring the wordle grid
//    gridContainer_ = wrapper_->addWidget(std::make_unique<Wt::WContainerWidget>());
//    gridContainer_->setStyleClass("grid");
//    guessGrid_ = gridContainer_->setLayout(std::make_unique<Wt::WGridLayout>());
//
//    // Configuring the input area (composed of the status message and input field)
//    inputArea_ = wrapper_->addWidget(std::make_unique<Wt::WContainerWidget>());
//    inputArea_->setStyleClass("input-area");
//
//    // Configuring the components of the input area
//    statusText_ = inputArea_->addWidget(std::make_unique<Wt::WText>());
//    guessInput_ = inputArea_->addWidget(std::make_unique<Wt::WLineEdit>());
//    guessInput_->setStyleClass("guess-input");
//    guessInput_->enterPressed().connect(this, &Wordle::checkGuess);
//
//    // Configuring the status button
//    statusButton_ = wrapper_->addWidget(std::make_unique<Wt::WPushButton>());
//    statusButton_->setStyleClass("status-btn");
//
//    // Read in all the words contained within the word bank file
//    parseWords("./resources/word_bank.txt");
//
//    // Initialize a new game
//    initializeGame();

}

GUI::~GUI() {}

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
 * @brief Update the leaderboard.
 */
void GUI::updateLeaderboard() {
    // Implementation for updating the leaderboard
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
