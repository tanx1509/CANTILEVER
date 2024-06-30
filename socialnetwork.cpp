#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

// Function to generate a timestamp
string getTimestamp() {
  time_t now = time(0);
  char buffer[80];
  strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", localtime(&now));
  return string(buffer);
}

// User class to store user information and friend management
class User {
public:
  string username;
  string name;
  string password; // Hashed password (implementation omitted for simplicity)
  vector<string> friends;

  // Load user data from file
  bool loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
      return false;
    }
    getline(file, name);
    getline(file, password);
    string friendName;
    while (getline(file, friendName)) {
      friends.push_back(friendName);
    }
    file.close();
    return true;
  }

  // Save user data to file
  void saveToFile(const string& filename) {
    ofstream file(filename);
    file << name << endl;
    file << password << endl;
    for (const string& friendName : friends) {
      file << friendName << endl;
    }
    file.close();
  }

  // Send friend request to another user (for demonstration)
  bool sendFriendRequest(const string& username) {
    cout << "Friend request functionality not implemented yet." << endl;
    return false;
  }

  // Add a friend to user's list (for demonstration)
  void addFriend(const string& friendName) {
    friends.push_back(friendName);
  }

  // Post a message
  void postMessage(const string& message) {
    string filename = "messages_" + username + ".txt";
    ofstream file(filename, ios::app);
    file << getTimestamp() << ": " << message << endl;
    file.close();
    cout << "Message posted successfully!" << endl;
  }

  // View user profile (including friends list)
  void viewProfile() {
    cout << "Username: " << username << endl;
    cout << "Name: " << name << endl;
    if (friends.empty()) {
      cout << "No friends yet." << endl;
    } else {
      cout << "Friends:" << endl;
      for (const string& friendName : friends) {
        cout << "- " << friendName << endl;
      }
    }
  }
};

// Function to perform user registration
bool registerUser(const string& username, const string& name, const string& password) {
  string filename = "users/" + username + ".txt";
  ifstream file(filename);
  if (file.is_open()) {
    cout << "Username already exists!" << endl;
    return false;
  }
  ofstream newFile(filename);
  newFile << name << endl;
  // Hash and store password (implementation omitted)
  newFile << password << endl;
  newFile.close();
  cout << "Registration successful!" << endl;
  return true;
}

// Function to perform user login
User loginUser(const string& username, const string& password) {
  unordered_map<string, User> users;
  // Load user data from files into the map for efficient lookup (replace with actual data loading)
  for (const string& filename : {"users/user1.txt", "users/user2.txt"}) {
    User user;
    if (user.loadFromFile(filename)) {
      users[user.username] = user;
    }
  }

  if (users.count(username) == 0) {
    cout << "Invalid username!" << endl;
    return User(); // Return empty user on failure
  }

  User user = users[username];
  // Verify password (use hashed password comparison)
  if (password != user.password) {
    cout << "Invalid password!" << endl;
    return User();
  }

  cout << "Login successful!" << endl;
  return user;
}

int main() {
  int choice, subChoice;
  User currentUser;

  while (true) {
    cout << "\nSimple Social Network" << endl;
    cout << "1. Register" << endl;
    cout << "2. Login" << endl;
    cout << "3. Exit" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
      case 1: {
        string username, name, password;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter name: ";
        cin.ignore(); // Consume newline character from previous input
        getline(cin, name);
        cout << "Enter password: ";
        cin >> password;
        if (registerUser(username, name, password)) {
          currentUser.username = username; // Update current user for potential future login
        }
        break;
      }
      case 2: {
        string username, password;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        currentUser = loginUser(username, password);
        if (!currentUser.username.empty()) {
          // User logged in successfully, show additional options
          while (true) {
            cout << "\nLogged in as: " << currentUser.username << endl;
            cout << "1. View profile" << endl;
            cout << "2. Post message" << endl;
            cout << "3. Logout" << endl;
            cout << "Enter your choice: ";
            cin >> subChoice;

            switch (subChoice) {
              case 1:
                currentUser.viewProfile();
                break;
              case 2: {
                string message;
                cout << "Enter your message: ";
                cin.ignore(); // Consume newline character
                getline(cin, message);
                currentUser.postMessage(message);
                break;
              }
              case 3:
                currentUser = User(); // Reset current user
                cout << "Logged out successfully!" << endl;
                break;
              default:
                cout << "Invalid choice!" << endl;
            }
            if (subChoice == 3) {
              break; // Exit inner loop on logout
            }
          }
        }
        break;
      }
      case 3:
        cout << "Exiting..." << endl;
        return 0;
      default:
        cout << "Invalid choice!" << endl;
    }
  }
  return 0;
}

