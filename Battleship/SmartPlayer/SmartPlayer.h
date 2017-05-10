#pragma once
#include "AbstractPlayer.h"
#include <set>
#include <deque>


enum Direction
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
	EMPTY = 'O',
	SHIP = 'S',
	DESTROYED = 'D',
	SUNK = 'X',
	UNKNOWN = ' '
};

class SmartPlayer :	public AbstractPlayer
{
protected:
	static const int NUMBER_OF_DIRECTIONS = 4;
	set<pair<int, int>>  mMyCoords;			// A set for the coordinates of the player's ships
	set<pair<int, int>>  mEnemyAttackCoords;	// A set for keeping track of where enemy attacks land.
	queue<pair<int, int>> mHighPriorityQueue;				// A queue for high priority (follow up) attacks
	queue<pair<int, int>> mMediumPriorityQueue; // A queue for medium priority (follow up) attacks
	void analyzeEnemy(pair<int, int> hitPoint, AttackResult result);	// Try to figue out if we're up agains the file player or not. If not, then we should try to outline the areas he doesn't attack! those would be his own ships!!
	///Returns whether the coordinates are valid.
	bool  isPointValid(int row, int col);
	///Replaces the old_char with new_char and we return true. if the square did not hold old_char nothing happens and we return false. Assumes coordinates are valid.
	///If reverse = true the char will be replaced only if it is NOT equal to old_char.
	bool replaceChar(int row, int col, char old_char, char new_char, bool reverse = false);
	/// Adds the coordinates to the attack queue if they are unknown or searches for the first unknown coordinates in the direction dir points.
	void addTarget(int row, int col, queue<pair<int,int>> attackQueue, Direction dir = NONE);
	///Returns a pair of booleans, the first is true iff the point is a valid point and the second is true iff these coordinates contain the char c.
	pair<bool, bool> verifyChar(int row, int col, char c);
	///Returns whether this square is adjacent to a ship. Does not assumes coordinates are valid.
	bool isNearChar(int row, int col, eSign s, Direction* dir = NULL);
	pair<int, int> attackFromPriorityQuque(queue<pair<int, int>> priorityQueue);
	void reLabelTheBoard();
	void analyzeAttackResult();
	//Direction scanTheVicinity(int row, int col);		// Scan the nearby blocks for two hits in a row to determine the ship's orientation
	void outlineEnemyShips(int row, int col);			// Mark the area around a sunken ship as eSight::Empty so it won't be targeted.
	//void debugBoard();

public:
	SmartPlayer(){}
	~SmartPlayer(){}
	void setBoard(int player, const char **board, int numRows, int numCols) override; // called once to notify player on his board
	bool init(const string& path) override;
	void notifyOnAttackResult(int player, int row, int col, AttackResult result) override; // notify on last move result
	pair<int, int> attack() override; // ask player for his move
};