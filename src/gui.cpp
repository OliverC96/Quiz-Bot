#include "gui.h"
#include <curl/curl.h>

/**
 * @brief Initializes the Wt GUI for the QuizBot application
 * @param env the Wt environment
 * @author Oliver Clennan
 */
GUI::GUI(const Wt::WEnvironment &env): WApplication(env) {

    // NOTE: the following attributes are currently hardcoded for testing purposes
    // Will change later once other features have been implemented and integrated with the GUI class
    answerKey = new QASet("nature", "easy");
    userAnswers = new QASet("geography", "hard");
    currentQuestionID = 1;
    currentUser = new User("userid", "userpass", 200, 1);

    quizQuestions = {
            QA(1, "What is the capital city of France?", "Paris", "easy", "random"),
            QA(2, "How many days are there in a year?", "365", "easy", "random"),
            QA(3, "What is the world's longest river called?", "The Nile", "easy", "random"),
            QA(4, "Which house was Harry Potter almost sorted into?", "Slytherin", "easy", "random"),
            QA(5, "What planet is closest to Earth?", "Venus", "easy", "random")
    };

    // Configure metadata
    setTitle("QuizBot");
    useStyleSheet("src/styles.css");

    // Initialize a stack-based widget to store the different pages of the application
    pages = root()->addWidget(std::make_unique<Wt::WStackedWidget>());

    // Initialize the primary pages of the application
    this->initializeMainPage();
    this->initializeLeaderboardPage();
    this->initializeDifficultyPage();
    this->initializeQuestionPage();

    // Display the main page
    pages->setCurrentIndex(0);

}

GUI::~GUI() {}

/**
 * @brief Display the user profile page.
 */
void GUI::displayUserProfile() {
    // Implementation for displaying the user profile page
}

/**
 * @brief Displays the question page
 */
void GUI::displayQuestionPage() {
    currentQuestionID = 1;
    this->updateQuestionPage();
    pages->setCurrentIndex(3);
}

/**
 * @brief Displays the difficulty page
 */
void GUI::displayDifficultyPage() {
    pages->setCurrentIndex(2);
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

    // TODO - analyze the answer, and assign an appropriate score

    currentQuestionID++;
    // Update the question page GUI to reflect the next question in the quiz
    this->updateQuestionPage();

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
    titleContainer->clicked().connect(this, &GUI::displayMainPage);

    return navBar;

}

/**
 * @brief Updates the question page with the information relevant to the next question in the quiz
 * @author Oliver Clennan
 */
void GUI::updateQuestionPage() {

    // Access the next question in the quiz
    QA newQuestion = quizQuestions[currentQuestionID - 1];
    bool isLastQuestion = currentQuestionID == quizQuestions.size();

    std::string buttonText = isLastQuestion ? "Submit" : "Next";
    std::string questionText = newQuestion.getQuestionText();
    std::string currentProgress = std::to_string(currentQuestionID) + "/" + std::to_string(quizQuestions.size());

    // Update the relevant elements in the GUI to reflect the new question
    questionInput->setPlaceholderText(questionText);
    answerArea->setText("");
    submitButton->setText(buttonText);
    questionProgress->setText(currentProgress);

    // Redirect to the leaderboard after the last question has been answered
    if (isLastQuestion) {
        submitButton->clicked().connect(this, &GUI::displayLeaderboard);
        answerArea->enterPressed().connect(this, &GUI::displayLeaderboard);
    }

}

/**
 * @brief Initializes the question page (where the user can view and answer a question in the quiz)
 * @author Oliver Clennan
 */
void GUI::initializeQuestionPage() {

    // Access the first question in the quiz
    QA firstQuestion = quizQuestions[currentQuestionID - 1];

    // Creating the question page, and generating/attaching the navbar
    questionPage = std::make_unique<Wt::WContainerWidget>();
    questionPage->addWidget(this->generateNavBar());

    Wt::WContainerWidget* pageContent = questionPage->addWidget(std::make_unique<Wt::WContainerWidget>());
    pageContent->setStyleClass("question");

    // Configuring the question label and input
    Wt::WContainerWidget* questionWrapper = pageContent->addWidget(std::make_unique<Wt::WContainerWidget>());
    questionWrapper->setStyleClass("question-wrapper");
    Wt::WText* questionLabel = questionWrapper->addWidget(std::make_unique<Wt::WText>("Question"));
    questionInput = questionWrapper->addWidget(std::make_unique<Wt::WLineEdit>());
    questionInput->setPlaceholderText(firstQuestion.getQuestionText());
    questionInput->setDisabled(true);

    // Configuring the answer label and textarea
    Wt::WContainerWidget* answerWrapper = pageContent->addWidget(std::make_unique<Wt::WContainerWidget>());
    answerWrapper->setStyleClass("answer-wrapper");
    Wt::WText* answerLabel = answerWrapper->addWidget(std::make_unique<Wt::WText>("Answer"));
    answerArea = answerWrapper->addWidget(std::make_unique<Wt::WTextArea>());
    enterConn = answerArea->enterPressed().connect(this, &GUI::processCurrAnswer);

    // Configuring the submit button
    Wt::WContainerWidget* buttonWrapper = pageContent->addWidget(std::make_unique<Wt::WContainerWidget>());
    buttonWrapper->setStyleClass("button-wrapper");
    submitButton = buttonWrapper->addWidget(std::make_unique<Wt::WPushButton>("Next"));
    submitButton->clicked().connect(this, &GUI::processCurrAnswer);

    // Attaching the mute and unmute icons
    Wt::WContainerWidget* iconWrapper = buttonWrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
    iconWrapper->setStyleClass("icon-wrapper");
    Wt::WImage* startRecordingIcon = iconWrapper->addWidget(std::make_unique<Wt::WImage>("src/start-recording.png"));
    Wt::WImage* stopRecordingIcon = iconWrapper->addWidget(std::make_unique<Wt::WImage>("src/stop-recording.png"));

    // Attaching the current question number to illustrate the users progress through the quiz
    questionProgress = pageContent->addWidget(std::make_unique<Wt::WText>(std::to_string(currentQuestionID) + "/" + std::to_string(quizQuestions.size())));
    questionProgress->setObjectName("questionProgress");
    questionProgress->setStyleClass("question-progress");

    pages->addWidget(std::move(questionPage));

}

/**
 * @brief Initializes the difficulty page (where the user selects a difficulty level for the quiz)
 * @author Oliver Clennan
 */
void GUI::initializeDifficultyPage() {

    // Defining the page content
    const std::string SECTION_HEADER = "Select your preferred difficulty level, and let the games begin!";
    const std::string SECTION_NOTE = "Note: you can always change the difficulty level later on, in case you want to try something more challenging, or more relaxed.";
    const std::vector<std::string> DIFFICULTY_LEVELS = {"Easy", "Medium", "Hard"};

    // Creating the difficulty page, and generating/attaching the navbar
    difficultyPage = std::make_unique<Wt::WContainerWidget>();
    difficultyPage->addWidget(this->generateNavBar());

    Wt::WContainerWidget* pageContent = difficultyPage->addWidget(std::make_unique<Wt::WContainerWidget>());
    pageContent->setStyleClass("difficulty");

    // Defining the page header
    Wt::WText* sectionHeader = pageContent->addWidget(std::make_unique<Wt::WText>(SECTION_HEADER));
    sectionHeader->setStyleClass("difficulty-header");

    Wt::WContainerWidget* levelsWrapper = pageContent->addWidget(std::make_unique<Wt::WContainerWidget>());
    levelsWrapper->setStyleClass("levels-wrapper");

    // Attach all buttons (one per difficulty level)
    for (int i = 0; i < DIFFICULTY_LEVELS.size(); i++) {
        Wt::WPushButton* difficultyButton = levelsWrapper->addWidget(std::make_unique<Wt::WPushButton>(DIFFICULTY_LEVELS[i]));
        difficultyButton->setStyleClass("primary-button");
        difficultyButton->clicked().connect(this, &GUI::displayQuestionPage);
    }

    // Defining the side note
    Wt::WText* sideNote = pageContent->addWidget(std::make_unique<Wt::WText>(SECTION_NOTE));

    pages->addWidget(std::move(difficultyPage));

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

    // Attach the start quiz button, and make it functional (redirect to the difficult page when clicked)
    Wt::WPushButton* startButton = pageContent->addWidget(std::make_unique<Wt::WPushButton>("Start Quiz"));
    startButton->setStyleClass("primary-button");
    startButton->clicked().connect(this, &GUI::displayDifficultyPage);

    // Create and style the category grid
    Wt::WContainerWidget* categoryGrid = pageContent->addWidget(std::make_unique<Wt::WContainerWidget>());
    categoryGrid->setStyleClass("category-grid");

    // Defining the category options
    // When a category is clicked/selected, it will redirect the user to the difficulty page
    for (int i = 0; i < CATEGORIES.size(); i++) {
        Wt::WContainerWidget* categoryWrapper = categoryGrid->addWidget(std::make_unique<Wt::WContainerWidget>());
        Wt::WContainerWidget* category = categoryWrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
        category->addWidget(std::make_unique<Wt::WContainerWidget>());
        category->addWidget(std::make_unique<Wt::WImage>(std::get<0>(CATEGORIES[i])));
        category->addWidget(std::make_unique<Wt::WText>(std::get<1>(CATEGORIES[i])));
        category->clicked().connect(this, &GUI::displayDifficultyPage);
    }

    pages->addWidget(std::move(mainPage));

}
