/* This is the console executable, that makes use of the BullCow  class. 
This acts as the view in an MVC pattern, and is responsible for all user 
interaction. For game logic see the FBullCowGame class. 
*/
#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

// to make syntax Unreal friendly 
using FText = std::string;
using int32 = int; 

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool PlayAgain(); 
void PrintGameSummary(); 

FBullCowGame BCGame; // instantiate a new game thats re-used globaly

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
 
 
void PrintIntro()
{
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?\n"; 
	return;
}


void PlayGame()
{
	BCGame.Reset(); 
	int32 MaxTries = BCGame.GetMaxTries();

	// loop asking for guesses while game is NOT won and there are still tries remaining 
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess();

		// Submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SumbitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls; 
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n"; 
	}
	PrintGameSummary(); 
	return; 
}

// Loop continually until the user gives a valid guess
FText GetValidGuess()
{
	FText Guess = ""; 
	EGuessStatus Status = EGuessStatus::Invalid_Status; 
	do 
	{
		// get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << std::endl << "Try " << CurrentTry << " of " << BCGame.GetMaxTries() << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter your guess in all lowercase.\n\n";
			break;
		default:
			// assuming the guess is valid 
			break;
		}
	} while (Status != EGuessStatus::OK); // Keep looping until we get no errors 
	return Guess;
} 

bool PlayAgain()
{
	std::cout << "Do you want to play again with the same hidden word? (y/n) ";
	FText Response = ""; 
	std::getline(std::cin, Response); 
	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "Congratulations! You win!\n";
	} 
	else
	{
		std::cout << "Sorry better luck next time!\n"; 
	}
}
