/* This is the console executable, that makes use of the BullCow  class. 
This acts as the view in an MVC pattern, and is responsible for all user 
interaction. For game logic see the FBullCowGame class. 
*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int; 

void PrintIntro();
void PlayGame();
FText GetGuess();
bool PlayAgain(); 

FBullCowGame BCGame; // instantiate a new game

// entry point for our application 
int main()
{
	bool bPlayAgain = false;
	do
	{
		PrintIntro();
		PlayGame();
		bPlayAgain = PlayAgain();
	}
	while (bPlayAgain);
	return 0; // exit the application
}
 

// introduce the game 
void PrintIntro()
{
	std::cout << "Welcome to Bulls and Cows, a fun word game\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?\n"; 
	return;
}


void PlayGame()
{
	BCGame.Reset(); 
	int32 MaxTries = BCGame.GetMaxTries();

	// loop for the number of turns asking for guesses
	// TODO change from FOR to WHILE loop once we are validating guesses
	for (int32 CurrentTry = 1; CurrentTry <= MaxTries; CurrentTry++)
	{
		FText Guess = GetGuess(); // TODO make loop check for valid guess

		// Submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SumbitGuess(Guess);
		// Print number of bulls and cows
		std::cout << "Bulls = " << BullCowCount.Bulls; 
		std::cout << ". Cows = " << BullCowCount.Cows << std::endl; 
		
		std::cout << std::endl;
	}
	// TODO summarize game
}


FText GetGuess()
{
	int32 CurrentTry = BCGame.GetCurrentTry();
	// get a guess from the player
	FText Guess = "";
	std::cout << std::endl << "Try #" << CurrentTry << ". Enter your guess: ";
	std::getline(std::cin, Guess);

	return Guess; 
} 

bool PlayAgain()
{
	std::cout << "Do you want to play again? (y/n) ";
	FText Response = ""; 
	std::getline(std::cin, Response); 
	return (Response[0] == 'y') || (Response[0] == 'Y');
}