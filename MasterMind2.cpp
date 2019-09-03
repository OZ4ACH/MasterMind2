// MasterMind2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Game.h"


MMGame* MM;
QuestionPieces* PC;

int main()
{
	char charind[MMsize+10];
	
	MM = new MMGame;

	MM->NewGame();

	while (1) {
		std::cin.getline(&charind[0],(MMsize+1), '\n');

		if ((charind[0] == 'n') || (charind[0] == 'N')){
			MM->NewGame();
		} else

		if ((charind[0] == 'g') || (charind[0] == 'G')) {
			MM->GiveUp();
		}
		else {
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
