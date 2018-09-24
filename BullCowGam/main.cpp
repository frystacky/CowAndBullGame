/* This is the console executable, that makes use of the BullCow Class
This acts as the view in a MVC pattern, and is responsiable for all
user interaction. For game logic see FBullCowGame class.
*/
#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

// to make syntax unreal friendly
using FText = std::string;
using int32 = int;

// functions 
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; // instantiate a new game

int main()
{
	bool PlayAgain = false;
	do
	{
		PrintIntro();
		PlayGame();
		PlayAgain = AskToPlayAgain();
	} while (PlayAgain);


	return 0;
}


void PrintIntro()
{
	//introduction of the game   //Borrowed ASCII art from udemy website

	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}

// function used to play the game to completion
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();



	// loops for number of guesses enterd by the user.

	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
		//repeats(prints) the guess back to the player
		FText Guess = GetValidGuess();

		//this will sumit a valid guess to the game
		FBullCowCount BullCowCount = BCGame.SumitValidGuess(Guess);
		//print number of bulls and cows in game

		std::cout << "Bulls =  " << BullCowCount.Bulls;
		std::cout << ". Cows =  " << BullCowCount.Cows << "\n\n";
	}

	PrintGameSummary();
	return;
}

// will keep looping untill user gives a valid input
FText GetValidGuess()
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::invalde_Status;
	do {
		//gets a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries();
		std::cout << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		// checks status for validity and returns feed back if invalid
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) {
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please a word without repeating letters.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lower case letters.\n\n";
			break;
		default:
			// is here to assume guess is valid
			break;
		}

	} while (Status != EGuessStatus::OK); //keeps looping untill useers inputs are valid
	return Guess;


}


bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same hidden word (y/n)?  ";
	FText Response = "";
	std::getline(std::cin, Response);



	return (Response[0] == 'y') || (Response[0] == 'Y');
}

// displays in game if the user won or lost.
void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "Congratulations, you won!\n";
		std::cout << std::endl;
		
	}
	else
	{
		std::cout << "Sorry, but you lost!\n";
	}

}