Instructions to Run the GUI:
1. Ensure you are in the root of the QuizBot directory
2. Execute the command [make gui] to build/compile the application
3. Execute the command [./gui --docroot . --http-listen 0.0.0.0:8080]
4. Go into your browser and type localhost:8080 to view the GUI

Note - if frequently testing GUI-related changes, make an alias to speed up the re-building process:
1. alias gui='make gui && ./gui --docroot . --http-listen 0.0.0.0:8080'
Note - if CSS changes are not updating properly in the browser, clear your browsers cache and try again