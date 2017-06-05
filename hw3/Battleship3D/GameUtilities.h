﻿#pragma once
#include "CommonUtilities.h"
#include "Game.h"
#include "GameResultsTable.h"
#include "PlayerGameResults.h"
#include "AlgorithmLoader.h"
#include "MyBoardData.h"

using namespace std;
using namespace CommonUtilities;

namespace GameUtilities
{
	/* input argument for setting the amount of threads */
	const std::string PARAM_THREADS("-threads");
	const std::string BOARD_FILE_SUFFIX(".sboard");
	const std::string LIB_FILE_SUFFIX(".dll");
	const std::string BAD_STRING("!@#"); // for getDirPath validation
	const int MAX_PATH_LEN = 1024;

	

	/* initializing the game attributes, player boards and paths for the different files */
/*	int initGameBoardsAndPaths(int argc, char **argv, std::string(&board)[ROW_SIZE], char **boardA, char* *boardB,
		std::string& dirPath, std::string& dllPathA, std::string& dllPathB);*/

	int processInputArguments(int argc, char** argv, std::string& dirPath, int& numThreads);
	

	/* prints the final results of the game */
	//void printGameResults(PlayerAttributes playerAttributesArr[]);

/*	/* player initialization #1#
	bool initPlayer(IBattleshipGameAlgo*& pPlayer, int playerNum, const char** board, const string dirPath, const string dllPath, 
					PlayerAttributes playerAttributesArr[], AlgorithmLoader& dllMngr);*/

	/* the main function of the game itself! */
	//int playTheGame(IBattleshipGameAlgo* A, IBattleshipGameAlgo* B, PlayerAttributes playerAttributesArr[], const std::string* board);

	/* prints the various error encountered on the board (if any)*/
	int printBoardErrors(std::bitset<4>& errShipsA, std::bitset<4>& errShipsB, int shipCountA, int shipCountB, int adjCheck);

	/* helper functions for printBoardErrors */
	void printWrongSizeOrShapeError(std::bitset<4>& errShips, int& ret, const std::string player);
	void printBadShipsCountError(int shipCountA, int shipCountB);

	/* changes the given dirPath (relative or absolute) to its full path representation */
	int convertToFullPath(std::string& dirPath);

	/* returns an absolute path to the current working directory */
	std::string getDirPath();

	/* helper function - initializes the ship list in the given PlayerAttribute struct, according to the given board*/
	//void initPlayerShipsList(const char** board, int numOfRows, int numOfCols, PlayerAttributes& playerAttributes);

	/* a helper function to the initPlayerShipsList method */
	Ship handleShipDiscovery(int iOrig, int jOrig, int numOfRows, int numOfCols, const char** board);

	/* given a vector of paths to sboard files, loads only the valid ones into vector<MyBoardData> boards */
	void initBoards3D(const std::vector<std::string>& boardPaths, std::vector<MyBoardData>& boards);

	/* parses the dimension line (first line in .sboard file) into rows, columns and depth */
	int getDims(const string& line, int& rows, int& cols, int& depth);

	/* checks if the ship's shape starting at board[i][j][k] is valid */
	int checkShape3D(MyBoardData& board, const int size, int i, int j, int k);

	/* registers the ship starting at board[i][j][k] to the passed board 
	 * kDir, iDir, jDir indicates the "direction vector" of the ship
	 * i.e if kDir = 0, iDir = 1, jDir = 0, the ship orientation is vertrical
	 */
	void registerShip(MyBoardData& board, const int size, int i, int j, int k, int iDir, int jDir, int kDir);

	/* checks if the passed board is valid */
	int checkBoard3D(MyBoardData& board);
}