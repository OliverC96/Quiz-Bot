#include "../include/gui.h"
#include <unistd.h>
// #include <curl/curl.h>

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
    this->initializeLoginPage();
    this->initializeRegisterPage();
    this->initializeMainPage();
    this->initializeLeaderboardPage();
    this->initializeDifficultyPage();
    this->initializeQuestionPage();

    // Display the login/register page
    pages->setCurrentIndex(0);
}

GUI::~GUI() {}


/**
 * @brief Display the current question's answer.
 * @author Taegyun Kim
 */
void GUI::displayAnswer() {
    for (int i = 0; i < quizQuestions.size(); i++) {
        if (quizQuestions.at(i).getQuestionId() == currentQuestionID){
            answerButton->setText(quizQuestions.at(i).getAnswerText());
            submitButton->show();
            break;
        }
    }

}

/**
 * @brief Display the user profile page.
 */
void GUI::displayUserProfile() {
    pages->setCurrentIndex(6);
}

/**
 * @brief Displays the question page
 */
void GUI::displayQuestionPage() {
    currentQuestionID = 1;
    this->updateQuestionPage();
    pages->setCurrentIndex(5);
}

/**
 * @brief Displays the difficulty page
 */
void GUI::displayDifficultyPage() {
    pages->setCurrentIndex(4);
}

/**
 * @brief Display the leaderboard page.
 */
void GUI::displayLeaderboard() {
    pages->setCurrentIndex(3);
}

/**
 * @brief Display the main/welcome page.
 */
void GUI::displayMainPage() {
    pages->setCurrentIndex(2);
}

/**
 * @brief Display the register page.
 */
void GUI::displayRegisterPage() {
    pages->setCurrentIndex(1);
}


/**
 * @brief Display the login page.
 */
void GUI::displayLoginPage() {
    pages->setCurrentIndex(0);
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
 * @author Taegyun Kim
 */
void GUI::updateScore() {

    // Implementation for updating the user's score
}

/**
 * @brief Store the user's score.
 * @author Taegyun Kim
 */
void GUI::storeUserScore() {
    finalScore = currentUser->getUserScore();
    // Implementation for storing the user's score
}

/**
 * @brief Show the answer button on the question page
 *         after n seconds.
 * @author Taegyun Kim
 */
void GUI::showAnswerButton() {
    int second = 0;
    clock_t start = clock();
    clock_t end = clock();

    while (true) {
        end = clock();
        if (double(end - start) / CLOCKS_PER_SEC == second) {
            break;
        }
    }
    std::cout << "Timer done" << std::endl;
    answerButton->show();
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
    answerButton->show();
    answerButton->setText("Check Answer");
    answerButton->clicked().connect(this, &GUI::displayAnswer);
    currentQuestionID++;
    // Update the question page GUI to reflect the next question in the quiz
    this->updateQuestionPage();

}

/**
 * @brief Log in the user.
 * @author Sung Kim
 */
void GUI::loginUser() {
    //Taking in the values from registration page
    bool loginOK = false;
    std::string username = loginUsernameField->text().toUTF8();
    std::string password = loginPasswordField->text().toUTF8();
    int score;
    int rank;

    std::string filename = "user/" + username + ".txt";
    std::fstream file;
    file.open(filename.c_str(), std::ios::in | std::ios::out);
    if(!file) {
        std::cout << "Error: user does not exist" << std::endl;
        loginErrorMessage->setText("Username or Password does not exist");
    } else {
        std::string file_line;
        std::getline(file, file_line);
        std::vector<std::string> tokens;
        std::stringstream ss(file_line);
        std::string token;

        while (std::getline(ss, token, ',')) {
            token.erase(0, token.find_first_not_of(' ')); // leading spaces
            token.erase(token.find_last_not_of(' ') + 1); // trailing spaces
            tokens.push_back(token);
        }

        if (tokens.size() >= 2 && tokens[1] == password) {
            score = std::stoi(tokens[2]);
            rank = std::stoi(tokens[3]);
            loginOK = true;
        } else {
            loginOK = false;
            std::cout << "Error: password does not match" << std::endl;
            loginErrorMessage->setText("Username or Password does not exist");
        }
    }

    // Implementation for user login
    // If log in successful
    if (loginOK == true) {
        currentUser = new User(username, password, score, rank);
        this->initializeProfilePage();
        this->displayMainPage();
    }
}

/**
 * @brief Log out the user.
 */
void GUI::logoutUser() {
    // Implementation for user logout
    std::cout << "User successfully logged out of the application." << std::endl;
    currentUser = nullptr;
    this->displayLoginPage();
}

/**
 * @brief Register a new user.
 * @author Sung Kim
 */
void GUI::registerUser() {
    //Taking in the values from registration page
    bool registerOK = false;
    std::string username = usernameField->text().toUTF8();
    std::string password = passwordField->text().toUTF8();
    std::string confirmPassword = confirmPasswordField->text().toUTF8();

    std::string filename = "user/" + username + ".txt";
    std::fstream file;
    file.open(filename.c_str(), std::ios::in | std::ios::out);
    if(!file) {
        std::cout << "Username available." << std::endl;
        if (confirmPassword == password) {
            registerOK = true;
            registerErrorMessage->setText("");
        } else {
            std::cout << "Error: Password does not match" << std::endl;
            registerErrorMessage->setText("Error: Password does not match");
        }
    } else {
        std::cout << "Error: Username already taken." << std::endl;
        registerErrorMessage->setText("Error: Username already taken.");
        registerOK = false; // set regOK to false if username exists
    }
    file.close();


    // Implementation for user registration
    // If registration successful
    if (registerOK == true) {
        currentUser = new User(username, password, 0, 0);
        this->initializeProfilePage();
        this->displayMainPage();

        // Create a text file in the 'user' directory
        std::string filename = "user/" + currentUser->getID() + ".txt";
        std::ofstream outfile(filename);

        // Write user details to the file
        outfile << currentUser->getID() << ", " << currentUser->getPW() << ", " << currentUser->getUserScore() << ", " << currentUser->getUserRank();
        outfile.close();

    }
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
 * @param showPrivatePages used to customize the navbar links to reflect the user's current status (logged-in or anonymous)
 *
 * Public pages:  Login Register
 * Private pages: Home Profile Leaderboard Logout
 *
 * @return The resulting navbar widget
 * @author Oliver Clennan
 */
std::unique_ptr<Wt::WContainerWidget> GUI::generateNavBar(bool showPrivatePages) {

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

    // Provide links only to the pages accessible to anonymous users (i.e., public pages)
    if (!showPrivatePages) {

        // Define the appropriate page links
        Wt::WPushButton* loginButton = navItems->addWidget(std::make_unique<Wt::WPushButton>("Login"));
        Wt::WPushButton* registerButton = navItems->addWidget(std::make_unique<Wt::WPushButton>("Register"));

        // Make the links functional
        loginButton->clicked().connect(this, &GUI::displayLoginPage);
        registerButton->clicked().connect(this, &GUI::displayRegisterPage);

    }

    // Provide links to all pages accessible to logged-in users (i.e., private pages)
    else {

        // Define the appropriate page links
        Wt::WPushButton* homeButton = navItems->addWidget(std::make_unique<Wt::WPushButton>("Home"));
        Wt::WPushButton* profileButton = navItems->addWidget(std::make_unique<Wt::WPushButton>("Profile"));
        Wt::WPushButton* leaderboardButton = navItems->addWidget(std::make_unique<Wt::WPushButton>("Leaderboard"));
        Wt::WPushButton* logoutButton = navItems->addWidget(std::make_unique<Wt::WPushButton>("Logout"));

        // Make the links functional
        homeButton->clicked().connect(this, &GUI::displayMainPage);
        profileButton->clicked().connect(this, &GUI::displayUserProfile);
        leaderboardButton->clicked().connect(this, &GUI::displayLeaderboard);
        logoutButton->clicked().connect(this, &GUI::logoutUser);
        titleContainer->clicked().connect(this, &GUI::displayMainPage);

    }

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
    submitButton->hide();
    questionProgress->setText(currentProgress);


    // Redirect to the leaderboard after the last question has been answered
    if (isLastQuestion) {
        submitButton->clicked().connect(this, &GUI::displayLeaderboard);
        answerArea->enterPressed().connect(this, &GUI::displayLeaderboard);
        answerButton->clicked().connect(this, &GUI::displayAnswer);
        answerButton->show();
    }

}

/**
 * @todo Jiho - Design GUI for the user's profile page
 */
void GUI::initializeProfilePage() {

    profilePage = std::make_unique<Wt::WContainerWidget>();
    profilePage->addWidget(this->generateNavBar(true));

    Wt::WContainerWidget* pageContent = profilePage->addWidget(std::make_unique<Wt::WContainerWidget>());
    pageContent->setStyleClass("profile");

    // Add elements to the pageContent container


    pages->addWidget(std::move(profilePage));

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
    questionPage->addWidget(this->generateNavBar(true));

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
    submitButton->hide();

    // Configuring the answer button
    Wt::WContainerWidget* answerButtonWrapper = pageContent->addWidget(std::make_unique<Wt::WContainerWidget>());
    answerButtonWrapper->setStyleClass("button-wrapper");
    answerButton = answerButtonWrapper->addWidget(std::make_unique<Wt::WPushButton>("Check Answer"));
    answerButton->clicked().connect(this, &GUI::displayAnswer);
    answerButton->show();

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
    difficultyPage->addWidget(this->generateNavBar(true));

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
    leaderboardPage->addWidget(this->generateNavBar(true));

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
    mainPage->addWidget(this->generateNavBar(true));
    Wt::WContainerWidget* pageContent = mainPage->addWidget(std::make_unique<Wt::WContainerWidget>());
    pageContent->setStyleClass("main");

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

/**
 * @brief Initializes the register page
 * @author Oliver Clennan, Sung Kim
 */
void GUI::initializeRegisterPage() {

    registerPage = std::make_unique<Wt::WContainerWidget>();
    registerPage->addWidget(this->generateNavBar(false));

    Wt::WContainerWidget* pageContent = registerPage->addWidget(std::make_unique<Wt::WContainerWidget>());
    pageContent->setStyleClass("form-wrapper");

    Wt::WContainerWidget* registerForm = pageContent->addWidget(std::make_unique<Wt::WContainerWidget>());
    registerForm->setStyleClass("form");

    Wt::WText* registerHeader = registerForm->addWidget(std::make_unique<Wt::WText>("Create Account"));
    registerHeader->setStyleClass("form-header");

    //being tested by sung. Original altered so the values can be passed on
    usernameField = registerForm->addWidget(std::make_unique<Wt::WLineEdit>());
    usernameField->setPlaceholderText("Username");
    passwordField = registerForm->addWidget(std::make_unique<Wt::WLineEdit>());
    passwordField->setPlaceholderText("Password");
    confirmPasswordField = registerForm->addWidget(std::make_unique<Wt::WLineEdit>());
    confirmPasswordField->setPlaceholderText("Password");

    //error message for registration error being tested
    registerErrorMessage = registerForm->addWidget(std::make_unique<Wt::WText>());
    registerErrorMessage->setStyleClass("form-errormessage");

    Wt::WPushButton* registerButton = registerForm->addWidget(std::make_unique<Wt::WPushButton>("Register"));
    registerButton->clicked().connect(this, &GUI::registerUser);

    Wt::WContainerWidget* redirectWrapper = registerForm->addWidget(std::make_unique<Wt::WContainerWidget>());
    redirectWrapper->setStyleClass("form-redirect");
    Wt::WText* redirectMessage = redirectWrapper->addWidget(std::make_unique<Wt::WText>("Already have an account?"));
    Wt::WPushButton* redirectLink = redirectWrapper->addWidget(std::make_unique<Wt::WPushButton>("Login"));
    redirectLink->clicked().connect(this, &GUI::displayLoginPage);

    pages->addWidget(std::move(registerPage));

}

/**
 * @brief Initializes the login page
 * @author Oliver Clennan, Sung Kim, Taegyun Kim
 */
void GUI::initializeLoginPage() {

    loginPage = std::make_unique<Wt::WContainerWidget>();
    loginPage->addWidget(this->generateNavBar(false));

    Wt::WContainerWidget* pageContent = loginPage->addWidget(std::make_unique<Wt::WContainerWidget>());
    pageContent->setStyleClass("form-wrapper");

    Wt::WContainerWidget* loginForm = pageContent->addWidget(std::make_unique<Wt::WContainerWidget>());
    loginForm->setStyleClass("form");

    Wt::WText* loginHeader = loginForm->addWidget(std::make_unique<Wt::WText>("Login"));
    loginHeader->setStyleClass("form-header");

    loginUsernameField = loginForm->addWidget(std::make_unique<Wt::WLineEdit>());
    loginUsernameField->setPlaceholderText("Username");
    loginPasswordField = loginForm->addWidget(std::make_unique<Wt::WLineEdit>());
    loginPasswordField->setPlaceholderText("Password");

    //error message for login error being tested
    loginErrorMessage = loginForm->addWidget(std::make_unique<Wt::WText>());
    loginErrorMessage->setStyleClass("form-errormessage");

    Wt::WPushButton* loginButton = loginForm->addWidget(std::make_unique<Wt::WPushButton>("Login"));
    loginButton->clicked().connect(this, &GUI::loginUser);
    loginPasswordField->enterPressed().connect(this, &GUI::loginUser);

    Wt::WContainerWidget* redirectWrapper = loginForm->addWidget(std::make_unique<Wt::WContainerWidget>());
    redirectWrapper->setStyleClass("form-redirect");
    Wt::WText* redirectMessage = redirectWrapper->addWidget(std::make_unique<Wt::WText>("Don't have an account?"));
    Wt::WPushButton* redirectLink = redirectWrapper->addWidget(std::make_unique<Wt::WPushButton>("Register"));
    redirectLink->clicked().connect(this, &GUI::displayRegisterPage);

    pages->addWidget(std::move(loginPage));

}
