/*

Master Mind 

By Kim Moltved 
Date 3/9-2019

As a C++ example for Widex don in 24h

Main file

*/


#include <iostream>
#include "Game.h"


MMGame* MM;				// Object with the main game object as a state machine
QuestionPieces* PC;		// Use for user input to the game

int main()
{
	char charind[MMsize+10];
	
	MM = new MMGame;	// init the game

	MM->NewGame();		// start a new game

	// Loop for handel user input
	while (1) {
		// wait for user input
		std::cin.getline(&charind[0],(MMsize+1), '\n');

		// is it 'n' then trigger a new game i not running
		if ((charind[0] == 'n') || (charind[0] == 'N')){
			MM->NewGame();
		} else

		// if in a game then trigger a give up of the game		
		if ((charind[0] == 'g') || (charind[0] == 'G')) {
			MM->GiveUp();
		}
		else {
			// test if it is a question input (4 digis)
			bool Question = true;
			for (int i = 0; i < MMsize; i++) {
				if (!((charind[i] >= '0') && (charind[i] <= '6'))) {
					Question = false;
				}
			}
			if (Question) {
				PC = new QuestionPieces;
				for (int i = 0; i < MMsize; i++) {
					PC->color[i] = (int)charind[i] - 48;
				}
				MM->AddQuestions(PC);
			}
		}
	}
}
