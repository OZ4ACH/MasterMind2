
#include <iostream>
#include "Game.h"

#include <random>
#include <functional>

std::default_random_engine generator;
std::uniform_int_distribution<int> distribution(1, MMcolors);

std::function<int()> getrandcolor = std::bind(distribution, generator);





Pieces::Pieces() {
	DEBUG_MSG("Pieces Init\n");

	for (int i = 0; i < MMsize; i++) {
		color[i] = 0;
	}
}



void QuestionPieces::Count(MasterPieces* mp) {
	DEBUG_MSG("QuestionPieces count\n");

	bool colorused[MMtrys];

	PlaceRight = 0;
	ColorRight = 0;
	for (int i = 0; i < MMsize; i++) {
		if (color[i] == mp->color[i]) {
			PlaceRight++;
		}
		colorused[i] = false;
	}

	for (int i = 0; i < MMsize; i++) {
		for (int j = 0; j < MMsize; j++) {
			if ((color[i] == mp->color[j]) && (colorused[j] == false)) {
				ColorRight++;
				colorused[j] = true;
				break;
			}
		}
	}

	ColorRight = ColorRight - PlaceRight;
}

void Pieces::ShowColor() {
	for (int i = 0; i < MMsize; i++) {
		std::cout << color[i];
		//std::cout << ", ";
	}
	std::cout << "\n";
}

void QuestionPieces::ShowRights() {
	std::cout << "Color at the right place: ";
	std::cout << PlaceRight;
	std::cout << "\n";

	std::cout << "Right color but at the wrong place: ";
	std::cout << ColorRight;
	std::cout << "\n";
}


MasterPieces::MasterPieces() {
	DEBUG_MSG("MasterPieces Init\n");

	for (int i = 0; i < MMsize; i++) {
		color[i] = getrandcolor();
	}
}

void MasterPieces::ShowColor() {
	std::cout << "Master: ";
	for (int i = 0; i < MMsize; i++) {
		std::cout << color[i];
		//std::cout << ", ";
	}
	std::cout << "\n";
}





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



void MMState::NewGame(MMGame*) {}
void MMState::AddQuestions(MMGame*, QuestionPieces* PC) {
	DEBUG_MSG("MMState AddQuestions\n");

	delete PC;
}
void MMState::GiveUp(MMGame*) {}



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



MMWaitQuestions::MMWaitQuestions(MMGame* context) : _context(context) {};

void MMWaitQuestions::AddQuestions(MMGame* t, QuestionPieces* PC) {
	DEBUG_MSG("MMWaitQuestions AddQuestions\n");

#ifdef DEBUG
	PC->ShowColor();
#endif

	t->trys++;

	PC->Count(t->mastercolor);
	PC->ShowRights();

	if (PC->PlaceRight == MMsize) {
		std::cout << "\nWin!!!\n\n";
		std::cout << "Type 'N' New Game\n";
		_context->ChangeState(new MMGenerateTest(_context));
	} 
	else 
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


void MMWaitQuestions::GiveUp(MMGame* t) {
	DEBUG_MSG("MMWaitQuestions GiveUp\n");

	std::cout << "You giveup\n";
	t->mastercolor->ShowColor();
	std::cout << "\nType 'N' New Game\n";

	_context->ChangeState(new MMGenerateTest(_context));
}

