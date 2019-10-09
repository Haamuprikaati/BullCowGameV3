// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    
	SetupGame();


	//Prompt player for guess
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();
	if (bGameOver == true)
	{
		SetupGame();
		return;
	}

	//Check if isogram
	//Prompt to guess again
	//Check if right length
	//Prompt to guess again

	//Check if correct word
	
	
	//Check if lives > 0
	//Check if correct length
	if (Input.Len() == HiddenWord.Len())
	{	//Check if correct word
		if (Input == HiddenWord)
		{	
			PrintLine(TEXT("Your guess was correct! You won!\n"));
			PrintLine(TEXT(" Press Enter to play again."));
		}
		else if (!IsIsogram(Input))
		{
			PrintLine(TEXT("The word cannot have repeating letters!\n"), Lives);
			PrintLine(TEXT("Guess again."));
			return;
		}
		else if (Lives > 1)
		{
			Lives -= 1;
			PrintLine(TEXT("Wrong. You have %i guesses left!\n"), Lives);
			PrintLine(TEXT("Guess again."));
			return;
		}
		else
		{
			Lives -= 1;
			EndGame();
		}
	}
	else
	{
		PrintLine(FString::Printf(TEXT("You need to enter a %i letter word!"), HiddenWord.Len()));
		PrintLine(TEXT("Guess again."));
		return;
	}

	
	//If yes GuessAgain
	//If no Show Game Over and hidden word
	//Prompt to play again, Press Enter to play again
	//Check user input
	//Play again or quit
}

void UBullCowCartridge::SetupGame()
{
	FilterIsograms(FilterLength(Words));
	HiddenWord = TEXT("Unreali");
	Lives = HiddenWord.Len();
	//Welcoming the player
	PrintLine(TEXT("Welcome to Bulls & Cows!"));
	PrintLine(TEXT("Try guess the %i letter word...\n"), HiddenWord.Len());
	PrintLine(TEXT("You have %i guesses."), Lives);

}

void UBullCowCartridge::EndGame()
{
	bGameOver = true;
	PrintLine(TEXT("You Lost! The hidden word was: %s \n"), *HiddenWord);
	PrintLine(TEXT(" Press Enter to try again."));
}

bool UBullCowCartridge::IsIsogram(FString Word) const
{
	int32 Index = 0;
	int32 Comparison = Index + 1;

	for (Index = 0; Index < Word.Len(); Index++)
	{
		for (Comparison = Index + 1; Comparison < Word.Len(); Comparison++)
			if (Word[Index] == Word[Comparison])
			{
				return false;
			}
	}

	return true;
}

TArray<FString> UBullCowCartridge::FilterLength(TArray<FString> WordList) const
{
	TArray<FString> RightLength;

	for (int32 Index = 0; Index < WordList.Num(); Index++)
	{
		if (WordList[Index].Len() >= 4 && WordList[Index].Len() <= 8)
		{
			RightLength.Emplace(WordList[Index]);
		}
	}
	return RightLength;
}

TArray<FString> UBullCowCartridge::FilterIsograms(TArray<FString> RightLengthWords) const
{
	TArray<FString> ValidWords;

	for (int32 Index = 0; Index < RightLengthWords.Num(); Index++)
	{
		if (IsIsogram(RightLengthWords[Index]))
		{
			ValidWords.Emplace(RightLengthWords[Index]);
		}
	}

	PrintLine(TEXT("ValidWords list size is: %i"), ValidWords.Num());
	return ValidWords;
}