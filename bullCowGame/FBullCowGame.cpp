#pragma once

#include "FBullCowGame.h"
#include <map>
#define TMap std::map // to make syntax Unreal friendly 

FBullCowGame::FBullCowGame() // default constructor
{
	Reset(); 
}

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const 
{ 
	TMap <int32, int32> WordLengthToMaxTries{ {3,4}, {4,7}, {5,10}, {6,15}, {7,20} };
	return WordLengthToMaxTries[MyHiddenWord.length()]; 
}


void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "planet"; // this MUST be an isogram
	MyHiddenWord = HIDDEN_WORD; 
	MyCurrentTry = 1;
	bGameIsWon = false; 
	return;
}


EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	// if the guess isnt an isogram
	if (!IsIsogram(Guess))
	{
		return EGuessStatus::Not_Isogram; 
	}
	// if the guess isnt all lowercase
	else if (!IsLowercase(Guess))
	{
		return EGuessStatus::Not_Lowercase; 
	}
	// the the guess length is wrong
	else if (Guess.length() != GetHiddenWordLength())
	{
		return EGuessStatus::Wrong_Length; 
	}
	// otherwise return ok 
	else
	{
		return EGuessStatus::OK; 
	}
}


// Receives a valid guess, increments turn, returns count
FBullCowCount FBullCowGame::SumbitValidGuess(FString Guess)
{ 
	MyCurrentTry++; 
	FBullCowCount BullCowCount; 
	int32 WordLength = MyHiddenWord.length();  // assuming the same length as guess
	
    // loop through all letters in the hidden word
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)
	{
		// compare letters against the guess 
		for (int32 GChar = 0; GChar < WordLength; GChar++)
		{
			// if they math then 
			if (Guess[GChar] == MyHiddenWord[MHWChar])
			{
				if (MHWChar == GChar)
				{
					// increment bulls if they're in the same place 
					BullCowCount.Bulls++;
				}
				else
				{
					// increment cows if not 
					BullCowCount.Cows++;
				}
			} 
		} 
	}
	if (BullCowCount.Bulls == WordLength)
	{
		bGameIsWon = true; 
	}
	else
	{
		bGameIsWon = false; 
	}
	return BullCowCount;
}


bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen; 
	for (auto Letter : Word) // for all letters of the word
	{
		Letter = tolower(Letter); // handle mixed case
		if (LetterSeen[Letter]) { return false; }
		else { LetterSeen[Letter] = true; }
	}
	return true; 
}


bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter)) { return false; }
		else { return true; }
	}
}