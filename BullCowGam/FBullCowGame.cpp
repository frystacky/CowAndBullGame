//Games main class
#pragma once
#include "FBullCowGame.h"
#include <map>
#define TMap std::map // to make syntax unreal friendly
 
using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); } // default constructor


int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

//maps the ammount of tries, (word length, tries)
int32 FBullCowGame::GetMaxTries() const 
{ 
	TMap<int32, int32> WordLengthToMaxTries{ {3,4}, {4,7}, {5,10}, {6,15}, {7,20} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset()
{
	
	const FString HIDDEN_WORD = "ants"; //The isogram used in game
	MyHiddenWord = HIDDEN_WORD;
	
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

//checks for errors when the user enters a word.
EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess))//if the guess isn't an isogram
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess)) //if the guess isn't all lowercase
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength()) // if the guess length is wrong
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}

}

// receives a VALID guess, incriments  turns and returns count.
FBullCowCount FBullCowGame::SumitValidGuess(FString Guess)
{

	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); // assumes same lenght as game

											  // look through all letters in the guess

	for (int32 i = 0; i < WordLength; i++) {
		// compare letters agains all hidden word
		for (int32 j = 0; j < WordLength; j++) {
			// if they match then
			if (Guess[j] == MyHiddenWord[i]) {
				if (i == j) { // if they're in the same place

					BullCowCount.Bulls++; // incriments bulls
				}
				else {
					BullCowCount.Cows++; // incriments cow
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength) {
		bGameIsWon = true;
	}
	else {
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// reat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }

	TMap <char, bool> LetterSeen;
	for (auto Letter : Word) // for all letters of the word  // *auto* compiler will decide the type
	{
		Letter = tolower(Letter); //this will handle mix cases
		if (LetterSeen[Letter]) { // if the letter is in the map
			return false; // we do not have an isogram
		}
		else { 
			LetterSeen[Letter] = true; // add the letter to the map as seen
		}		
	}
	return true;  // for example in case where /0 is entered 
				  // can change to false, but change in functio from not(!)
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word)  // each letter in the word
	{
		if (!islower(Letter)) // if statement for to check for lowercase letter
		{
		return false;
	    }
	}
	return true;
}
