#include "../include/gui.h"

/**
 * @brief Initializes the Wt GUI for the QuizBot application
 * @param env the Wt environment
 * @author Oliver Clennan
 */
GUI::GUI(const Wt::WEnvironment &env): WApplication(env) {

    currentQuestion = new QA(1, "question", "answer", "difficulty", "category");
    currentUser = new User("userid", "userpass", 200, 1);

    setTitle("QuizBot");
    useStyleSheet("src/styles.css");

    pages = root()->addWidget(std::make_unique<Wt::WStackedWidget>());
    std::unique_ptr<Wt::WContainerWidget> mainPage = std::make_unique<Wt::WContainerWidget>();

    Wt::WContainerWidget* navBar = mainPage->addWidget(std::make_unique<Wt::WContainerWidget>());
    Wt::WContainerWidget* pageContent = mainPage->addWidget(std::make_unique<Wt::WContainerWidget>());

    navBar->setStyleClass("nav-bar");
    pageContent->setStyleClass("wrapper");

    Wt::WText* appTitle = navBar->addWidget(std::make_unique<Wt::WText>("QuizBot"));
    Wt::WContainerWidget* navItems = navBar->addWidget(std::make_unique<Wt::WContainerWidget>());

    appTitle->setStyleClass("title");
    navItems->setStyleClass("nav-items");

    Wt::WPushButton* homeButton = navItems->addWidget(std::make_unique<Wt::WPushButton>("Home"));
    Wt::WPushButton* profileButton = navItems->addWidget(std::make_unique<Wt::WPushButton>("Profile"));
    Wt::WPushButton* leaderboardButton = navItems->addWidget(std::make_unique<Wt::WPushButton>("Leaderboard"));

    Wt::WContainerWidget* welcomeText = pageContent->addWidget(std::make_unique<Wt::WContainerWidget>());
    welcomeText->setStyleClass("welcome-text");

    Wt::WText* firstSection = welcomeText->addWidget(std::make_unique<Wt::WText>("Welcome to QuizBot, your go-to destination for trivia fun and excitement! Our web application is designed with trivia enthusiasts in mind, offering a seamless and enjoyable experience for users of all levels. With a sleek and user-friendly interface, QuizBot opens the door to a world of trivia quizzes spanning a wide range of categories, ensuring there's something for everyone."));
    Wt::WText* secondSection = welcomeText->addWidget(std::make_unique<Wt::WText>("What sets QuizBot apart is its commitment to accessibility and engagement. We believe that trivia should be a delightful experience for all, and that's why we provide both text input and speech recognition options for answering questions. Whether you prefer typing out your answers or speaking them aloud, QuizBot has you covered."));
    Wt::WText* thirdSection = welcomeText->addWidget(std::make_unique<Wt::WText>("At the heart of QuizBot is our mission to make trivia enjoyable and hassle-free. You can easily browse and select quiz categories that pique your interest, dive into quizzes, and keep track of your scores. With an extensive and diverse database of trivia questions meticulously organized by topics, finding quizzes that match your interests has never been easier."));
    Wt::WText* fourthSection = welcomeText->addWidget(std::make_unique<Wt::WText>("Join us on a journey of knowledge, fun, and friendly competition with QuizBot. Let's get started!"));

    Wt::WPushButton* startButton = pageContent->addWidget(std::make_unique<Wt::WPushButton>("Start Quiz"));
    startButton->setStyleClass("start-button");

    pages->addWidget(std::move(mainPage));
    pages->setCurrentIndex(0);

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
