#include "FBullCowGame.h"

FBullCowGame::FBullCowGame()
{
	Reset(); 
}

int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 8; 
	MyMaxTries = MAX_TRIES; 

	const FString HIDDEN_WORD = "planet"; 
	MyHiddenWord = HIDDEN_WORD; 
	MyCurrentTry = 1;
	bGameIsWon = false; 
	return;
}


EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	// if the guess isnt an isogram
	if (false)
	{
		return EGuessStatus::Not_Isogram; 
	}
	// if the guess isnt all lowercase
	else if (false)
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

