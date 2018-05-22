#pragma once
#include <string>

using FString = std::string; 
using int32 = int; 

// all values initialized to zero 
struct FBullCowCount 
{
	int32 Bulls = 0; 
	int32 Cows = 0; 
};

enum class EWordStatus 
{
	OK, 
	Not_Isogram, 
	Wrong_Length, 
	Not_Lowercase
};

class FBullCowGame 
{
public:
	FBullCowGame(); // Constructor

	int32 GetMaxTries() const; 
	int32 GetCurrentTry() const; 
	int32 GetHiddenWordLength() const; 

	bool IsGameWon() const; 
	EWordStatus CheckGuessValidity(FString) const; // TODO make a more rich return value 

	void Reset(); // TODO make a more rich return value
	FBullCowCount SumbitGuess(FString Guess); 

private:
	// See constructor for initialization 
	int32 MyCurrentTry; 
	int32 MyMaxTries;
	FString MyHiddenWord; 
};