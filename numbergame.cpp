#include <iostream>
#include <random>
#include <ctime>

using namespace std;

int main() {
  int randomNumber, guess, difficulty;
  int tries = 0;

  // Seed the random number generator
  srand(time(0));

  // Get difficulty level from user
  cout << "Choose difficulty level (1 - Easy, 2 - Medium, 3 - Hard): ";
  cin >> difficulty;

  // Set random number range based on difficulty
  int min = 1, max = 100;
  switch (difficulty) {
    case 1:
      max = 20;
      break;
    case 2:
      max = 50;
      break;
    case 3:
      break; // Default range for hard
  }

  // Generate random number
  randomNumber = rand() % (max - min + 1) + min;

  // Start the guessing game
  cout << "Guess a number between " << min << " and " << max << endl;
  while (guess != randomNumber) {
    cin >> guess;
    tries++;

    if (guess < randomNumber) {
      cout << "Too low! Try again." << endl;
    } else if (guess > randomNumber) {
      cout << "Too high! Try again." << endl;
    }
  }

  cout << "Congratulations! You guessed the number in " << tries << " tries." << endl;

  return 0;
}
