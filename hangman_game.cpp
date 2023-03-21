#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <iostream>
#include <string>

void display_hangman(int num_wrong_guesses) {
    std::string stages[] = {  // initial empty state
                              "--------\n"
                              "|      |\n"
                              "|      \n"
                              "|     \n"
                              "|      \n"
                              "|     \n"
                              "-\n",
                              // head
                              "--------\n"
                              "|      |\n"
                              "|      O\n"
                              "|     \n"
                              "|      \n"
                              "|     \n"
                              "-\n",
                              // head and torso
                              "--------\n"
                              "|      |\n"
                              "|      O\n"
                              "|      |\n"
                              "|      |\n"
                              "|     \n"
                              "-\n",
                              // head, torso, and one arm
                              "--------\n"
                              "|      |\n"
                              "|      O\n"
                              "|     \\|\n"
                              "|      |\n"
                              "|     \n"
                              "-\n",
                              // head, torso, and both arms
                              "--------\n"
                              "|      |\n"
                              "|      O\n"
                              "|     \\|/\n"
                              "|      |\n"
                              "|     \n"
                              "-\n",
                              // head, torso, both arms, and one leg
                              "--------\n"
                              "|      |\n"
                              "|      O\n"
                              "|     \\|/\n"
                              "|      |\n"
                              "|     /\n"
                              "-\n",
                              // final state: head, torso, both arms, and both legs
                              "--------\n"
                              "|      |\n"
                              "|      O\n"
                              "|     \\|/\n"
                              "|      |\n"
                              "|     / \\\n"
                              "-\n",
                          };
    std::cout << stages[num_wrong_guesses];
}

std::string get_display_word(const std::string& word, const std::set<char>& correct_letters) {
    // return the word with underscores for letters that have not been guessed yet
    std::string display_word;
    for (char letter : word) {
        if (correct_letters.count(letter)) {
            display_word += letter;
        } else {
            display_word += "_";
        }
    }
    return display_word;
}

char get_next_guess(const std::set<char>& correct_letters, const std::set<char>& incorrect_letters) {
    // get the player's next guess
    while (true) {
        std::cout << "Please enter your next guess: ";
        std::string next_guess;
        std::cin >> next_guess;
        if (next_guess.length() != 1) {
            std::cout << "Please enter a single letter." << std::endl;
        } else if (!isalpha(next_guess[0])) {
            std::cout << "Please enter a letter." << std::endl;
        } else if (correct_letters.count(next_guess[0]) || incorrect_letters.count(next_guess[0])) {
            std::cout << "You have already guessed that letter. Please try again." << std::endl;
        } else {
            return next_guess[0];
        }
    }
}

void play_hangman() {
    std::vector<std::string> word_list = {"python", "java", "javascript", "html", "css"};
    // randomly select a word from the list
    std::string word = word_list[rand() % word_list.size()];
    // use a set to store the letters that have been guessed
    std::set<char> correct_letters;
    // use a set to store the letters that have been guessed incorrectly
    std::set<char> incorrect_letters;
    // number of wrong guesses the player is allowed
    int max_wrong_guesses = 6;
    // initialize the number of wrong guesses to zero
    int num_wrong_guesses = 0;

    while (num_wrong_guesses < max_wrong_guesses) {
        // display the current state of the game
        display_hangman(num_wrong_guesses);
        std::cout << "Word: " << get_display_word(word, correct_letters) << std::endl;
        std::cout << "Incorrect Guesses: ";
        for (char letter : incorrect_letters) {
            std::cout << letter << " ";
        }
        std::cout << std::endl;
        std::cout << "Correct Guesses: ";
        for (char letter : correct_letters) {
            std::cout << letter << " ";
        }
        std::cout << std::endl;
        // get the player's next guess
        char guess = get_next_guess(correct_letters, incorrect_letters);
        if (word.find(guess) != std::string::npos) {
            correct_letters.insert(guess);
            // check if the player has won
            bool all_correct = true;
			for (char letter : word) {
			    if (!correct_letters.count(letter)) {
			        all_correct = false;
			        break;
			    }
			}
			if (all_correct) {
			   std::cout << "Congratulations! You won!" << std::endl;
                std::cout << "The word was: " << word << std::endl;
                return;
            }
        } else {
            incorrect_letters.insert(guess);
            num_wrong_guesses++;
        }
    }
    // the player has lost
    std::cout << "You have run out of guesses! Better luck next time." << std::endl;
    std::cout << "The word was: " << word << std::endl;
}

int main() {
    // start the game
    std::cout << "Welcome to Hangman!" << std::endl;
    play_hangman();
    return 0;
}
