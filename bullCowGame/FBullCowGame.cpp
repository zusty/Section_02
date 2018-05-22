#include "FBullCowGame.h"

FBullCowGame::FBullCowGame()
{
	Reset(); 
}

int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }

void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 8; 
	MyMaxTries = MAX_TRIES; 

	const FString HIDDEN_WORD = "planet"; 
	MyHiddenWord = HIDDEN_WORD; 

	MyCurrentTry = 1;
	return;
}

bool FBullCowGame::IsGameWon() const
{
	return false;
}

EWordStatus FBullCowGame::CheckGuessValidity(FString) const
{
	return EWordStatus::OK; // TODO make an actual error 
}

// Receives a valid guess, increments turn, returns count
FBullCowCount FBullCowGame::SumbitGuess(FString Guess)
{
	// increment the turn number 
	MyCurrentTry++; 

	// setup a return variable
	FBullCowCount BullCowCount; 

	// loop through all letters in the guess
	int32 HiddenWordLength = MyHiddenWord.length(); 
	for (int32 MHWChar = 0; MHWChar < HiddenWordLength; MHWChar++)
	{
		// compare letters against the hidden word 
		for (int32 GChar = 0; GChar < HiddenWordLength; GChar++)
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
	return BullCowCount;
}

