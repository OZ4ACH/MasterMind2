#pragma once


//#define DEBUG

#ifdef DEBUG
#define DEBUG_MSG(str) do { std::cout << str ; } while( false )
#else
#define DEBUG_MSG(str) do { } while ( false )
#endif

class MMState;

#define MMsize 4
#define MMcolors 6
#define MMtrys 10


class Pieces {
public:
	Pieces();
	void ShowColor();

	int color[MMsize];
};

class MasterPieces : public Pieces {
public:
	MasterPieces();
	void ShowColor();
};

class QuestionPieces : public Pieces {
public:
	void Count(MasterPieces* mp);
	void ShowRights();

	int PlaceRight = 0;
	int ColorRight = 0;
};







class PieceColors {
public:
	int color[MMsize];

};


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



class MMState {
public:
	virtual void NewGame(MMGame*);
	virtual void AddQuestions(MMGame*, QuestionPieces* PC);
	virtual void GiveUp(MMGame*);

};


class MMGenerateTest : public MMState {
public:
	MMGenerateTest(MMGame* context);

	virtual void NewGame(MMGame*);

private:
	MMGame* _context;
};



class MMWaitQuestions : public MMState {
public:
	MMWaitQuestions(MMGame* context);

	virtual void AddQuestions(MMGame*, QuestionPieces* PC);
	virtual void GiveUp(MMGame*);

private:
	MMGame* _context;
};

/*
class MMWinGame : public MMState {
public:
	MMWinGame(MMGame* context);

	virtual void NewGame(MMGame*);

private:
	MMGame* _context;
};



class MMLossGame : public MMState {
public:
	MMLossGame(MMGame* context);

	virtual void NewGame(MMGame*);

private:
	MMGame* _context;
};



class MMGiveUp : public MMState {
public:
	MMGiveUp(MMGame* context);

	virtual void NewGame(MMGame*);

private:
	MMGame* _context;
};
*/