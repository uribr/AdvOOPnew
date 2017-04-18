#ifndef HW1_PLAYER_H
#define HW1_PLAYER_H

#include <queue>
#include <cctype>
#include "IBattleshipGameAlgo.h"
#include "Ship.h"

using namespace std;

#define ROW_SIZE 10
#define COL_SIZE 10
#define DEFAULT_SHIPS_COUNT 5

class Player : IBattleshipGameAlgo
{
protected:
    char board[ROW_SIZE][COL_SIZE] = {{0}};
    std::queue<std::pair<int, int>> movesQueue;
    std::vector<Ship> shipsList;
    int shipsCount = DEFAULT_SHIPS_COUNT; // number of living ships - starting from DEFAULT_SHIPS_COUNT
	int playerNum;
    //int score = 0;


public:
    virtual void setBoard(int player, const char **board, int numRows, int numCols) override; // called once to notify player on his board
    virtual std::pair<int, int> attack() override; // ask player for his move
	virtual bool init(const std::string& path) override;
    virtual void notifyOnAttackResult(int player, int row, int col, AttackResult result) override; // notify on last move result
    void setMoves(vector<pair<int,int>> moves);
    bool registerHit(std::pair<int,int> coords, eShipType shipType, AttackResult& res); //Updates the ship that got hit (or sank).
    bool hasMoves(); // checks if the player has more moves to play
    bool hasShips(); // checks if the player has more living ships
    void initShipsList();

    //char ** getBoard();
};


#endif //HW1_PLAYER_H
