#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class PresetNave
{
public:
	PresetNave(int Num, int valueCoins);
	~PresetNave();

	int Numero;
	int valorCoins;
	bool isAvailable();
	void buy();
};

class Naves
{
public:
	static const int numNaves = 14;
	static PresetNave naves[numNaves];
	Naves();
	~Naves() {}
};
