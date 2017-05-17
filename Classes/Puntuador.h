#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class Puntuador
{
public:
	Puntuador(int Categoria);
	~Puntuador();
	int getPuntuacion();
	void setLastPuntuacion();
	void addPuntuacion();
	static int getLastPuntuacion();
	static int getHighPuntuacion();
	static int getLastCategoria();
	static void setHighPuntuacion();
	static void setLastCategoria(int categoria);
	static int getTotalCoins();
	static void setTotalCoins(int total);
private:
	int categoria;
	int puntuacion;
	int truePuntuacion;
};

