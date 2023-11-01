#include "../include/gui.h"

/**
 * @brief Initializes the Wt GUI for the QuizBot application
 * @param env the Wt environment
 * @author Oliver Clennan
 */
GUI::GUI(const Wt::WEnvironment &env): WApplication(env) {

    currentQuestion = new QA(1, "question", "answer", "difficulty", "category");
    currentUser = new User("userid", "userpass", 200, 1);

    // Configure metadata
    setTitle("QuizBot");
    useStyleSheet("src/styles.css");

    // Initialize a stack-based widget to store the different pages of the application
    pages = root()->addWidget(std::make_unique<Wt::WStackedWidget>());

    // Initialize the main page
    this->initializeMainPage();

    // Display the main page
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

/**
 * @brief Initializes the main page of the GUI
 * @author Oliver Clennan
 * @todo  Make navbar a reusable component since it must be shown on all pages
 *        Add for loops to simplify the method (if possible)
 */
void GUI::initializeMainPage() {
    mainPage = std::make_unique<Wt::WContainerWidget>();

    Wt::WContainerWidget* navBar = mainPage->addWidget(std::make_unique<Wt::WContainerWidget>());
    Wt::WContainerWidget* pageContent = mainPage->addWidget(std::make_unique<Wt::WContainerWidget>());

    navBar->setStyleClass("nav-bar");
    pageContent->setStyleClass("wrapper");

    Wt::WContainerWidget* titleContainer = navBar->addWidget(std::make_unique<Wt::WContainerWidget>());
    Wt::WContainerWidget* navItems = navBar->addWidget(std::make_unique<Wt::WContainerWidget>());

    Wt::WText* appTitle = titleContainer->addWidget(std::make_unique<Wt::WText>("QuizBot"));
    Wt::WImage* appIcon = titleContainer->addWidget(std::make_unique<Wt::WImage>("src/appIcon.png"));

    appTitle->setStyleClass("title");
    titleContainer->setStyleClass("title-container");
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

    Wt::WContainerWidget* categoryGrid = pageContent->addWidget(std::make_unique<Wt::WContainerWidget>());
    categoryGrid->setStyleClass("category-grid");

    Wt::WContainerWidget* cat1Wrapper = categoryGrid->addWidget(std::make_unique<Wt::WContainerWidget>());
    Wt::WContainerWidget* cat2Wrapper = categoryGrid->addWidget(std::make_unique<Wt::WContainerWidget>());
    Wt::WContainerWidget* cat3Wrapper = categoryGrid->addWidget(std::make_unique<Wt::WContainerWidget>());
    Wt::WContainerWidget* cat4Wrapper = categoryGrid->addWidget(std::make_unique<Wt::WContainerWidget>());
    Wt::WContainerWidget* cat5Wrapper = categoryGrid->addWidget(std::make_unique<Wt::WContainerWidget>());
    Wt::WContainerWidget* cat6Wrapper = categoryGrid->addWidget(std::make_unique<Wt::WContainerWidget>());

    Wt::WContainerWidget* cat1 = cat1Wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
    Wt::WContainerWidget* cat2 = cat2Wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
    Wt::WContainerWidget* cat3 = cat3Wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
    Wt::WContainerWidget* cat4 = cat4Wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
    Wt::WContainerWidget* cat5 = cat5Wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
    Wt::WContainerWidget* cat6 = cat6Wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());

    Wt::WContainerWidget* overlay1 = cat1->addWidget(std::make_unique<Wt::WContainerWidget>());
    Wt::WContainerWidget* overlay2 = cat2->addWidget(std::make_unique<Wt::WContainerWidget>());
    Wt::WContainerWidget* overlay3 = cat3->addWidget(std::make_unique<Wt::WContainerWidget>());
    Wt::WContainerWidget* overlay4 = cat4->addWidget(std::make_unique<Wt::WContainerWidget>());
    Wt::WContainerWidget* overlay5 = cat5->addWidget(std::make_unique<Wt::WContainerWidget>());
    Wt::WContainerWidget* overlay6 = cat6->addWidget(std::make_unique<Wt::WContainerWidget>());

    Wt::WImage* image1 = cat1->addWidget(std::make_unique<Wt::WImage>("https://placehold.co/150x100/AEB4BF/FAF9F9"));
    Wt::WImage* image2 = cat2->addWidget(std::make_unique<Wt::WImage>("https://placehold.co/150x100/AEB4BF/FAF9F9"));
    Wt::WImage* image3 = cat3->addWidget(std::make_unique<Wt::WImage>("https://placehold.co/150x100/AEB4BF/FAF9F9"));
    Wt::WImage* image4 = cat4->addWidget(std::make_unique<Wt::WImage>("https://placehold.co/150x100/AEB4BF/FAF9F9"));
    Wt::WImage* image5 = cat5->addWidget(std::make_unique<Wt::WImage>("https://placehold.co/150x100/AEB4BF/FAF9F9"));
    Wt::WImage* image6 = cat6->addWidget(std::make_unique<Wt::WImage>("https://placehold.co/150x100/AEB4BF/FAF9F9"));

    Wt::WText* text1 = cat1->addWidget(std::make_unique<Wt::WText>("Category 1"));
    Wt::WText* text2 = cat2->addWidget(std::make_unique<Wt::WText>("Category 2"));
    Wt::WText* text3 = cat3->addWidget(std::make_unique<Wt::WText>("Category 3"));
    Wt::WText* text4 = cat4->addWidget(std::make_unique<Wt::WText>("Category 4"));
    Wt::WText* text5 = cat5->addWidget(std::make_unique<Wt::WText>("Category 5"));
    Wt::WText* text6 = cat6->addWidget(std::make_unique<Wt::WText>("Category 6"));
}
