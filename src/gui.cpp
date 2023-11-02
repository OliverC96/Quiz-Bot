#include "../include/gui.h"

/**
 * @brief Initializes the Wt GUI for the QuizBot application
 * @param env the Wt environment
 * @author Oliver Clennan
 */
GUI::GUI(const Wt::WEnvironment &env): WApplication(env) {

    answerKey = new QASet("nature", "easy");
    userAnswers = new QASet("geography", "hard");
    currentQuestion = new QA(1, "question", "answer", "difficulty", "category");
    currentUser = new User("userid", "userpass", 200, 1);

    // Configure metadata
    setTitle("QuizBot");
    useStyleSheet("src/styles.css");

    // Initialize a stack-based widget to store the different pages of the application
    pages = root()->addWidget(std::make_unique<Wt::WStackedWidget>());

    // Initialize the primary pages of the application
    this->initializeMainPage();
    this->initializeLeaderboardPage();

    // Display the main page
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
    pages->setCurrentIndex(1);
}

void GUI::displayMainPage() {
    pages->setCurrentIndex(0);
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
    std::tuple<std::string, int, std::string, std::string> newEntry = make_tuple(currentUser->getID(), this->finalScore, answerKey->getCategory(), answerKey->getDifficultyLevel());
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
 * @brief Fetches the current leaderboard data from the specified file
 * @param filePath
 * @author Oliver Clennan
 */
void GUI::loadLeaderboard(std::string filePath) {

    // Opens the provided file for reading
    std::ifstream dataFile(filePath);
    if (!dataFile.is_open()) {
        std::cerr << "Error - failed to locate the leaderboard data file." << std::endl;
        return;
    }
    std::vector<std::string> currRow;
    std::string currLine, currToken;

    // Iterate through all lines (i.e., leaderboard entries) contained in the file
    while (std::getline(dataFile, currLine)) {
        currRow.clear();
        std::stringstream ss(currLine);
        while (std::getline(ss, currToken, ',')) {
            currRow.push_back(currToken);
        }
        // Add each leaderboard entry to the leaderboard collection
        std::tuple<std::string, int, std::string, std::string> newEntry = make_tuple(currRow[0], std::stoi(currRow[1]), currRow[2], currRow[3]);
        leaderboard.push_back(newEntry);
    }

}

/**
 * Creates a navigation bar component (allows for the easy reuse of the navbar across all pages in the application)
 * Note: this method is necessary because Wt does not directly support the sharing of widgets (due to unique pointers)
 * @return The navbar widget
 * @author Oliver Clennan
 */
std::unique_ptr<Wt::WContainerWidget> GUI::generateNavBar() {

    std::unique_ptr<Wt::WContainerWidget> navBar = std::make_unique<Wt::WContainerWidget>();
    navBar->setStyleClass("nav-bar");

    // Add two wrapper containers for the title/logo and navbar items
    Wt::WContainerWidget* titleContainer = navBar->addWidget(std::make_unique<Wt::WContainerWidget>());
    Wt::WContainerWidget* navItems = navBar->addWidget(std::make_unique<Wt::WContainerWidget>());

    // Define the application name and logo
    Wt::WText* appTitle = titleContainer->addWidget(std::make_unique<Wt::WText>("QuizBot"));
    Wt::WImage* appIcon = titleContainer->addWidget(std::make_unique<Wt::WImage>("src/appIcon.png"));

    // Add additional styling for the elements in the navbar
    appTitle->setStyleClass("title");
    titleContainer->setStyleClass("title-container");
    navItems->setStyleClass("nav-items");

    // Define the navbar items (i.e., links to the various pages of the application)
    Wt::WPushButton* homeButton = navItems->addWidget(std::make_unique<Wt::WPushButton>("Home"));
    Wt::WPushButton* profileButton = navItems->addWidget(std::make_unique<Wt::WPushButton>("Profile"));
    Wt::WPushButton* leaderboardButton = navItems->addWidget(std::make_unique<Wt::WPushButton>("Leaderboard"));

    // Make the links functional
    leaderboardButton->clicked().connect(this, &GUI::displayLeaderboard);
    //profileButton->clicked().connect(this, &GUI::displayUserProfile);
    homeButton->clicked().connect(this, &GUI::displayMainPage);

    return navBar;

}

/**
 * @brief Initializes the leaderboard page
 * @author Oliver Clennan
 */
void GUI::initializeLeaderboardPage() {

    // Load the leaderboard data and add the navbar to the leaderboard widget
    this->loadLeaderboard("src/leaderboardData.txt");
    leaderboardPage = std::make_unique<Wt::WContainerWidget>();
    leaderboardPage->addWidget(this->generateNavBar());

    Wt::WContainerWidget* pageContent = leaderboardPage->addWidget(std::make_unique<Wt::WContainerWidget>());
    pageContent->setStyleClass("leaderboard");

    Wt::WText* leaderboardTitle = pageContent->addWidget(std::make_unique<Wt::WText>("Leaderboard"));
    leaderboardTitle->setStyleClass("leaderboard-title");
    Wt::WTable* leaderboardTable = pageContent->addWidget(std::make_unique<Wt::WTable>());

    // Attach all entries to the leaderboard
    for (int i = 0; i < leaderboard.size(); i++) {
        Wt::WTableRow* leaderboardEntry = leaderboardTable->insertRow(i, std::make_unique<Wt::WTableRow>());
        leaderboardEntry->setStyleClass("leaderboard-entry");
        leaderboardEntry->elementAt(0)->addWidget(std::make_unique<Wt::WText>(std::to_string(i + 1)));
        leaderboardEntry->elementAt(1)->addWidget(std::make_unique<Wt::WText>(std::get<0>(leaderboard[i])));
        leaderboardEntry->elementAt(2)->addWidget(std::make_unique<Wt::WText>(std::to_string(std::get<1>(leaderboard[i]))));
        leaderboardEntry->elementAt(3)->addWidget(std::make_unique<Wt::WText>(std::get<2>(leaderboard[i])));
        leaderboardEntry->elementAt(4)->addWidget(std::make_unique<Wt::WText>(std::get<3>(leaderboard[i])));
    }

    pages->addWidget(std::move(leaderboardPage));

}

/**
 * @brief Initializes the main page of the GUI
 * @author Oliver Clennan
 */
void GUI::initializeMainPage() {

    // Defining the welcome messages to be displayed on the page
    const std::vector<std::string> WELCOME_MESSAGES = {
            "Welcome to QuizBot, your go-to destination for trivia fun and excitement! Our web application is designed with trivia enthusiasts in mind, offering a seamless and enjoyable experience for users of all levels. With a sleek and user-friendly interface, QuizBot opens the door to a world of trivia quizzes spanning a wide range of categories, ensuring there's something for everyone.",
            "What sets QuizBot apart is its commitment to accessibility and engagement. We believe that trivia should be a delightful experience for all, and that's why we provide both text input and speech recognition options for answering questions. Whether you prefer typing out your answers or speaking them aloud, QuizBot has you covered.",
            "At the heart of QuizBot is our mission to make trivia enjoyable and hassle-free. You can easily browse and select quiz categories that pique your interest, dive into quizzes, and keep track of your scores. With an extensive and diverse database of trivia questions meticulously organized by topics, finding quizzes that match your interests has never been easier.",
            "Join us on a journey of knowledge, fun, and friendly competition with QuizBot. Let's get started!"
    };

    // Defining the image and name of each category supported by the application
    const std::vector<std::tuple<std::string, std::string>> CATEGORIES = {
            std::make_tuple("https://placehold.co/150x100/AEB4BF/FAF9F9", "Category 1"),
            std::make_tuple("https://placehold.co/150x100/AEB4BF/FAF9F9", "Category 2"),
            std::make_tuple("https://placehold.co/150x100/AEB4BF/FAF9F9", "Category 3"),
            std::make_tuple("https://placehold.co/150x100/AEB4BF/FAF9F9", "Category 4"),
            std::make_tuple("https://placehold.co/150x100/AEB4BF/FAF9F9", "Category 5"),
            std::make_tuple("https://placehold.co/150x100/AEB4BF/FAF9F9", "Category 6"),
    };

    // Attach the navbar to the main page
    mainPage = std::make_unique<Wt::WContainerWidget>();
    mainPage->addWidget(this->generateNavBar());
    Wt::WContainerWidget* pageContent = mainPage->addWidget(std::make_unique<Wt::WContainerWidget>());
    pageContent->setStyleClass("wrapper");

    Wt::WContainerWidget* welcomeText = pageContent->addWidget(std::make_unique<Wt::WContainerWidget>());
    welcomeText->setStyleClass("welcome-text");

    // Attach the welcome messages
    for (int i = 0; i < WELCOME_MESSAGES.size(); i++) {
        welcomeText->addWidget(std::make_unique<Wt::WText>(WELCOME_MESSAGES[i]));
    }

    // Attach the start quiz button
    Wt::WPushButton* startButton = pageContent->addWidget(std::make_unique<Wt::WPushButton>("Start Quiz"));
    startButton->setStyleClass("start-button");

    // Create and style the category grid
    Wt::WContainerWidget* categoryGrid = pageContent->addWidget(std::make_unique<Wt::WContainerWidget>());
    categoryGrid->setStyleClass("category-grid");

    // Define the category options
    for (int i = 0; i < CATEGORIES.size(); i++) {
        Wt::WContainerWidget* categoryWrapper = categoryGrid->addWidget(std::make_unique<Wt::WContainerWidget>());
        Wt::WContainerWidget* category = categoryWrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
        category->addWidget(std::make_unique<Wt::WContainerWidget>());
        category->addWidget(std::make_unique<Wt::WImage>(std::get<0>(CATEGORIES[i])));
        category->addWidget(std::make_unique<Wt::WText>(std::get<1>(CATEGORIES[i])));
    }

    pages->addWidget(std::move(mainPage));

}
