#pragma once
#include "AbstractPlayer.h"
#include <set>
#include <deque>


enum class Direction
{
	UP,
	DOWN,
	RIGHT,
	LEFT,
	VERTICAL,
	HORIZONAL,
	NONE
};

enum eSign : char
{
	EMPTY  = 'O',
	DESTROYED = 'X'
};

class SmartPlayer :	public AbstractPlayer
{
protected:
	bool mAttackMode;
	bool mIsFilePlayer;
	Direction mDir;										// The orientaiton of our current target. Initially set to Direction::None.
	static const int NUMBER_OF_DIRECTIONS = 4;
	set<pair<int, int>>  mMyCoords;			// A set for the coordinates of the player's ships
	set<pair<int, int>>  mEnemyAttackCoords;	// A set for keeping track of where enemy attacks land.
	deque<pair<int, int>> mSmartMoveQueue;				// A deque for attacks
	void analyzeEnemy(pair<int, int> hitPoint, AttackResult result);	// Try to figue out if we're up agains the file player or not. If not, then we should try to outline the areas he doesn't attack! those would be his own ships!!
	bool isShip(int row, int col);
	bool isPointValid(int row, int col);
	bool putChar(int row, int col, char new_char);
	bool replaceChar(int row, int col, char old_char, char new_char);
	bool addTarget(int row, int col);
	/*Returns whether this square holds char c. Assumes coordinates are valid.*/
	bool verifyChar(int row, int col, char c);
	bool isShipOutline(int row, int col);
	Direction scanTheVicinity(int row, int col);		// Scan the nearby blocks for two hits in a row to determine the ship's orientation
	void outlineSunkenEnemyShip(int row, int col, int row_mod = 0, int col_mod = 0);			// Mark the area around a sunken ship as eSight::Empty so it won't be targeted.

public:
	SmartPlayer() : mAttackMode(false), mIsFilePlayer(false), mDir(Direction::NONE) {}
	~SmartPlayer(){}
	void setBoard(int player, const char **board, int numRows, int numCols) override; // called once to notify player on his board
	bool init(const string& path) override;
	void notifyOnAttackResult(int player, int row, int col, AttackResult result) override; // notify on last move result
	pair<int, int> attack() override; // ask player for his move
};