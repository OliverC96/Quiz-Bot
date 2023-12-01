<h1> Welcome to QuizBot! </h1>

<h2> Overview </h2>
<p>QuizBot is an interactive trivia platform which allows users to test their knowledge in a variety of categories, and at multiple difficulty levels. The following are the primary features supported by QuizBot:</p>
<ul>
    <li> Users can register an account to take quizzes, and save their results across multiple sessions</li>
    <li> Users can take quizzes spanning seven categories (science, geography, politics, culture, history, sports, and random), and three difficulty levels (easy, medium, and hard) </li>
    <li> User answers are analyzed by QuizBot, and assigned a score based on their relevance and quality </li>
    <li> Feedback (i.e., missing keywords) is provided after each question to help the user understand exactly where they went wrong</li>
    <li> High scores and rankings are displayed on a leaderboard allowing users to compare their performance against other users</li>
    <li> Users can access a personalized profile page containing a breakdown of their previous scores </li>
</ul>

<h2> Compilation Instructions </h2>
<p> Follow these steps to build and run the application:</p>
<ol>
    <li> Ensure you are in the root of the QuizBot directory </li>
    <li> Execute the command <b>[make gui]</b> to build/compile the application </li>
    <li> Execute the command <b>[./gui --docroot . --http-listen 0.0.0.0:8080]</b> </li>
    <li> Go into your browser and type <b>localhost:8080</b> to view the GUI </li>
</ol>
<p>Or, simply make an alias:</p> 
<b> alias gui='make gui && ./gui --docroot . --http-listen 0.0.0.0:8080' </b>