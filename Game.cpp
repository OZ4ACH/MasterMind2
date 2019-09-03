/*

Master Mind

By Kim Moltved
Date 3/9-2019

As a C++ example for Widex don in 24h

The game 

*/


#include <iostream>
#include "Game.h"

#include <random>
#include <functional>

// handling of the radnom
std::default_random_engine generator;
std::uniform_int_distribution<int> distribution(1, MMcolors);

std::function<int()> getrandcolor = std::bind(distribution, generator);


// Init of Color pieces 
Pieces::Pieces() {
	DEBUG_MSG("Pieces Init\n");

	for (int i = 0; i < MMsize; i++) {
		color[i] = 0;
	}
}


// Compare and count of the color pieces to the master
void QuestionPieces::Count(MasterPieces* mp) {
	DEBUG_MSG("QuestionPieces count\n");

	bool colorused[MMtrys];

	PlaceRight = 0;
	ColorRight = 0;

	// Count right color 
	for (int i = 0; i < MMsize; i++) {
		if (color[i] == mp->color[i]) {
			PlaceRight++;
		}
		colorused[i] = false;
	}

	// Count right color but wrong or right place
	for (int i = 0; i < MMsize; i++) {
		for (int j = 0; j < MMsize; j++) {
			if ((color[i] == mp->color[j]) && (colorused[j] == false)) {
				ColorRight++;
				colorused[j] = true;
				break;
			}
		}
	}

	// Calculate right color but wrong place
	ColorRight = ColorRight - PlaceRight;
}


// Show the color on the ui
void Pieces::ShowColor() {
	for (int i = 0; i < MMsize; i++) {
		std::cout << color[i];
		//std::cout << ", ";
	}
	std::cout << "\n";
}

// Show Right place and Color on the ui
void QuestionPieces::ShowRights() {
	std::cout << "Color at the right place: ";
	std::cout << PlaceRight;
	std::cout << "\n";

	std::cout << "Right color but at the wrong place: ";
	std::cout << ColorRight;
	std::cout << "\n";
}


// Init a new game generating random color pieces
MasterPieces::MasterPieces() {
	DEBUG_MSG("MasterPieces Init\n");

	for (int i = 0; i < MMsize; i++) {
		color[i] = getrandcolor();
	}
}

// Show master color pieces
void MasterPieces::ShowColor() {
	std::cout << "Master: ";
	for (int i = 0; i < MMsize; i++) {
		std::cout << color[i];
		//std::cout << ", ";
	}
	std::cout << "\n";
}




// State handling
MMGame::MMGame() {
	DEBUG_MSG("MMGame Init\n");
	_state = new MMGenerateTest(this);
}

void MMGame::NewGame() {
	DEBUG_MSG("MMGame NewGame\n");
	_state->NewGame(this);
}

void MMGame::AddQuestions(QuestionPieces* PC) {
	DEBUG_MSG("MmGame AddQuestions\n");
	_state->AddQuestions(this, PC);
}

void MMGame::GiveUp() {
	DEBUG_MSG("MmGame GiveUp\n");
	_state->GiveUp(this);
}

void MMGame::ChangeState(MMState* s) {
	DEBUG_MSG("MMGame ChangeState\n");
	_state = s;
}


// init a new game default 
void MMState::NewGame(MMGame*) {}
void MMState::AddQuestions(MMGame*, QuestionPieces* PC) {
	DEBUG_MSG("MMState AddQuestions\n");

	delete PC;
}
void MMState::GiveUp(MMGame*) {}


// generat e new game
MMGenerateTest::MMGenerateTest(MMGame* context) : _context(context) {};

void MMGenerateTest::NewGame(MMGame* t) {
	DEBUG_MSG("MMGenerateTest NewGame\n");

	t->trys = 0;

	std::cout << "\n";
	std::cout << "-------------------------------------\n";
	std::cout << "Welcom to MasteMind\n";
	std::cout << "-------------------------------------\n";
	std::cout << "New game ready!\n";
	std::cout << "-------------------------------------\n";
	std::cout << "The colors is repensated by the number 1 to 6\n";
	std::cout << "And 0 is non color placed\n";
	std::cout << "Type 4 digits from 0 to 6 ex. 1224 to make a question\n";
	std::cout << "Type 'G' Give Up\n";
	std::cout << "-------------------------------------\n";
	std::cout << "Type your suggestions (" << (t->trys+1) <<") : ";

	t->mastercolor = new MasterPieces();

#ifdef DEBUG
	t->mastercolor->ShowColor();
#endif

	_context->ChangeState(new MMWaitQuestions(_context));
}


// Test for question of color pieces 
MMWaitQuestions::MMWaitQuestions(MMGame* context) : _context(context) {};

void MMWaitQuestions::AddQuestions(MMGame* t, QuestionPieces* PC) {
	DEBUG_MSG("MMWaitQuestions AddQuestions\n");

#ifdef DEBUG
	PC->ShowColor();
#endif

	t->trys++;

	PC->Count(t->mastercolor);
	PC->ShowRights();

	// Test if it is a winner
	if (PC->PlaceRight == MMsize) {
		std::cout << "\nWin!!!\n\n";
		std::cout << "Type 'N' New Game\n";
		_context->ChangeState(new MMGenerateTest(_context));
	} 
	else 
		// test if there is used to many trys
		if (t->trys >= MMtrys) {
			std::cout << "\nFail!!! to many trys\n\n";
			t->mastercolor->ShowColor();
			std::cout << "\nType 'N' New Game\n";
			_context->ChangeState(new MMGenerateTest(_context));
		}
		else {
			std::cout << "Type your new suggestions (" << (t->trys + 1) << ") : ";
		}

	delete PC;
}


// Show give up and show master color pieces
void MMWaitQuestions::GiveUp(MMGame* t) {
	DEBUG_MSG("MMWaitQuestions GiveUp\n");

	std::cout << "You giveup\n";
	t->mastercolor->ShowColor();
	std::cout << "\nType 'N' New Game\n";

	_context->ChangeState(new MMGenerateTest(_context));
}

