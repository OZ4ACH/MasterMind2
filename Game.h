#pragma once
/*

Master Mind

By Kim Moltved
Date 3/9-2019

As a C++ example for Widex don in 24h

Header file for the game part

*/


//#define DEBUG

#ifdef DEBUG
#define DEBUG_MSG(str) do { std::cout << str ; } while( false )
#else
#define DEBUG_MSG(str) do { } while ( false )
#endif

class MMState;

// define for setting the width size, the count of colors and who many trys there is
#define MMsize 4
#define MMcolors 6
#define MMtrys 10


// Object for color pieces
class Pieces {
public:
	Pieces();
	void ShowColor();

	int color[MMsize];
};

// Object for the master color pieces
class MasterPieces : public Pieces {
public:
	MasterPieces();
	void ShowColor();
};

// Object for question color pieces (from the user input)
class QuestionPieces : public Pieces {
public:
	void Count(MasterPieces* mp);
	void ShowRights();

	int PlaceRight = 0;
	int ColorRight = 0;
};


// The entry to the game state machine
class MMGame {
public:
	MMGame();

	void NewGame();
	void AddQuestions(QuestionPieces* PC);
	void GiveUp();
	void ChangeState(MMState*);

	MasterPieces* mastercolor;
	int trys = 0;
	
private:
	friend class MMState;
	friend class PieceColors;

private:
	MMState* _state;

};


// The diffrent game state
class MMState {
public:
	virtual void NewGame(MMGame*);
	virtual void AddQuestions(MMGame*, QuestionPieces* PC);
	virtual void GiveUp(MMGame*);
};


// State for generating new game color pieces
class MMGenerateTest : public MMState {
public:
	MMGenerateTest(MMGame* context);

	virtual void NewGame(MMGame*);

private:
	MMGame* _context;
};


// state for testing user input
class MMWaitQuestions : public MMState {
public:
	MMWaitQuestions(MMGame* context);

	virtual void AddQuestions(MMGame*, QuestionPieces* PC);
	virtual void GiveUp(MMGame*);

private:
	MMGame* _context;
};

