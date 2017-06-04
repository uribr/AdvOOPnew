﻿#pragma once
#include "IBattleshipGameAlgo.h"
#include <vector>
#include <tuple>
#include <windows.h>

typedef IBattleshipGameAlgo *(*GetAlgoFuncType)();

class AlgorithmLoader
{
	//data members
	std::vector<std::tuple<std::string, HINSTANCE, GetAlgoFuncType>> libs;

public:
	AlgorithmLoader(){}
	~AlgorithmLoader();
	// blocking copy ctor & assignment operator (rule of three)
	AlgorithmLoader(const AlgorithmLoader& dllMngr) = delete;
	AlgorithmLoader& operator=(const AlgorithmLoader& dllMngr) = delete;

	void loadLibs(const std::vector<std::string> dlls);
	IBattleshipGameAlgo* loadAlgo(int n);
	const int size();

private:
	int loadDLL(const std::string path);
};