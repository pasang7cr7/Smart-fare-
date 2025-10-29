# Smart Fare Project Progress Tracker

## Project Overview
This is a C++-based smart fare system for public transport, managing user cards, rides, balances, and admin functionalities. The project uses CSV files for data storage (card.csv, Ride_History.csv).

## Completed Features
- [x] **Main Menu System** (main.cpp): User interface with options for registration, top-up, ride start, details, history, admin, and utilities.
- [x] **Card Registration** (card.cpp): Supports normal, student (with code validation), and elder citizen (age >=60) cards. Generates unique IDs, sets expiry (1 year from registration), saves to card.csv.
- [x] **Top-up Card** (card.cpp): Allows balance recharge with password "kacbit". Updates card.csv.
- [x] **Start Ride** (card.cpp): Validates card, checks balance, calculates fare based on stops and card type (discounts for student/elder), deducts fare, saves ride history to Ride_History.csv.
- [x] **Card Details** (card.cpp): Displays card info by ID.
- [x] **Ride History** (utils.cpp): Views ride history for a card ID from Ride_History.csv.
- [x] **Admin Login** (admin.cpp): Simple username/password authentication.
- [x] **Admin Panel** (admin.cpp): Menu for viewing all cards, searching cards, updating balance, blocking/unblocking cards.
- [x] **Utility Functions** (utils.cpp): Number validation, fare calculation (Rs. 5/stop with discounts), save/view ride history.
- [x] **Time Functions** (time.cpp): Get current date and date with time.
- [x] **Data Storage**: Uses CSV files for persistence (card.csv for cards, Ride_History.csv for rides).
- [x] **Executables**: Multiple compiled versions (smartfare.exe, etc.) indicate successful builds.

## Partially Completed or Pending Features
- [ ] **View All Ride History in Admin** (admin.cpp): Function `viewAllRideHistory()` is declared but not implemented (empty body). Needs to read and display all rides from Ride_History.csv.
- [ ] **Error Handling**: Some functions lack robust error handling (e.g., file I/O failures, invalid inputs beyond basic checks).
- [ ] **Security**: Passwords are hardcoded (e.g., "kacbit" for top-up, "admin"/"admin123" for admin). Consider encryption or better auth.
- [ ] **Input Validation**: Limited validation (e.g., no check for duplicate names or invalid expiry dates).
- [ ] **UI Improvements**: Console-based; could add better formatting or clear screen usage.
- [ ] **Testing**: No visible unit tests; manual testing assumed.
- [ ] **Documentation**: Basic README and file structure; could expand with usage instructions.
- [ ] **Features Missing**: No logout for admin, no bulk operations, no reports.

## Overall Progress
- **Completion Level**: ~80-85% functional for core features.
- **Strengths**: Core logic implemented, data persistence works, modular code structure.
- **Weaknesses**: Incomplete admin features, lack of advanced validation/security.
- **Next Steps**: Implement missing admin ride history view, add error handling, improve security.

## Recommendations
- Complete `viewAllRideHistory()` in admin.cpp.
- Add try-catch for file operations.
- Consider adding more card types or features like refunds.
- Test edge cases (e.g., invalid stops, insufficient balance).

Last Updated: [Current Date/Time]
