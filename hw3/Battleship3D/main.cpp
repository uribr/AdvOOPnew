#include "GameUtilities.h"
#include <string>
#include "MyBoardData.h"
#include "CompetitionManager.h"
#include "InitUtilities.h"


using namespace std;
using namespace CommonUtilities;
using namespace InitUtilities;

int main(int argc, char** argv)
{
	vector<MyBoardData> boards;
	vector<GetAlgoFuncType> players;
	vector<string> dirFiles, boardFiles, dllFiles, playerNames;	
	string dirPath;
	int numThreads = CompetitionManager::DEFAULT_NUM_THREADS;

	if (processInputArguments(argc, argv, dirPath, numThreads) < 0)
	{
		return EXIT_FAILURE;
	}
	
	// intialize logger only after there is a valid path
	shared_ptr<Logger> pLogger = make_shared<Logger>(dirPath);

	if (getDirectoryFileList(dirPath, dirFiles, pLogger) < 0)
	{
		return EXIT_FAILURE;
	}
	filterDirFiles(dirFiles, boardFiles, dllFiles, dirPath);
	if (checkMinBoardsAndPlayersCount(boardFiles.size(), dllFiles.size(), dirPath, false, pLogger) < 0)
	{
		return EXIT_FAILURE;
	}
	initBoards3D(boardFiles, boards);
	AlgorithmLoader algoLoader(pLogger);
	algoLoader.loadLibs(dllFiles, players, playerNames, dirPath);

	//TODO - exit if no valid players/board?
	// here we know that we have valid boards and players
	pLogger->writeToLog("Number of legal players: " + to_string(players.size()), true);
	pLogger->writeToLog("Number of legal boards: " + to_string(boards.size()), true);
	if (checkMinBoardsAndPlayersCount(boards.size(), players.size(), dirPath, true, pLogger) < 0)
	{
		return EXIT_FAILURE;
	}
	CompetitionManager tournamentMngr(boards, players, playerNames, pLogger, numThreads);
	tournamentMngr.runCompetition();
	pLogger->writeToLog("", false, Logger::eLogType::LOG_END);
	return EXIT_SUCCESS;
}