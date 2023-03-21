import random

def play_hangman():
    word_list = ["python", "java", "javascript", "html", "css"]
    # randomly select a word from the list
    word = random.choice(word_list)
    # use a set to store the letters that have been guessed
    correct_letters = set()
    # use a set to store the letters that have been guessed incorrectly
    incorrect_letters = set()
    # number of wrong guesses the player is allowed
    max_wrong_guesses = 6
    # initialize the number of wrong guesses to zero
    num_wrong_guesses = 0

    while num_wrong_guesses < max_wrong_guesses:
        # display the current state of the game
        display_hangman(num_wrong_guesses)
        print("Word: " + get_display_word(word, correct_letters))
        print("Incorrect Guesses: ", end="")
        print(" ".join(incorrect_letters))
        print("Correct Guesses: ", end="")
        print(" ".join(correct_letters))
        # get the player's next guess
        guess = get_next_guess(correct_letters, incorrect_letters)
        if guess in word:
            correct_letters.add(guess)
            # check if the player has won
            if all(letter in correct_letters for letter in word):
                print("Congratulations! You won!")
                print("The word was: " + word)
                return
        else:
            incorrect_letters.add(guess)
            num_wrong_guesses += 1
    # the player has lost
    print("You have run out of guesses! Better luck next time.")
    print("The word was: " + word)

def display_hangman(num_wrong_guesses):
    stages = [  # initial empty state
                """
                   --------
                   |      |
                   |      
                   |    
                   |      
                   |     
                   -
                """,
                # head
                """
                   --------
                   |      |
                   |      O
                   |    
                   |      
                   |     
                   -
                """,
                # head and torso
                """
                   --------
                   |      |
                   |      O
                   |      |
                   |      |
                   |     
                   -
                """,
                # head, torso, and one arm
                """
                   --------
                   |      |
                   |      O
                   |     \\|
                   |      |
                   |     
                   -
                """,
                # head, torso, and both arms
                """
                   --------
                   |      |
                   |      O
                   |     \\|/
                   |      |
                   |      
                   -
                """,
                # head, torso, both arms, and one leg
                """
                   --------
                   |      |
                   |      O
                   |     \\|/
                   |      |
                   |     / 
                   -
                """,
                # final state: head, torso, both arms, and both legs
                """
                   --------
                   |      |
                   |      O
                   |     \\|/
                   |      |
                   |     / \\
                   -
                """,
            ]
    print(stages[num_wrong_guesses])


def get_display_word(word, correct_letters):
    # return the word with underscores for letters that have not been guessed yet
    display_word = ""
    for letter in word:
        if letter in correct_letters:
            display_word += letter
        else:
            display_word += "_"
    return display_word

def get_next_guess(correct_letters, incorrect_letters):
    # get the player's next guess
    while True:
        next_guess = input("Please enter your next guess: ").lower()
        if len(next_guess) != 1:
            print("Please enter a single letter.")
        elif not next_guess.isalpha():
            print("Please enter a letter.")
        elif next_guess in correct_letters or next_guess in incorrect_letters:
            print("You have already guessed that letter. Please try again.")
        else:
            return next_guess

# start the game
print("Welcome to Hangman!")
play_hangman()

