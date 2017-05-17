#include "Puntuador.h"

Puntuador::Puntuador(int Categoria)
{
	categoria = Categoria;
	puntuacion = 0;
	truePuntuacion = 0;
	Puntuador::setLastCategoria(Categoria);
}
Puntuador::~Puntuador()
{
}

int Puntuador::getPuntuacion()
{
	if (puntuacion == -truePuntuacion)
		return truePuntuacion;
	else
		return -1;
}
void Puntuador::addPuntuacion()
{
	puntuacion--;
	truePuntuacion++;
}
int Puntuador::getLastPuntuacion()
{
	char str[100] = { 0 };
	sprintf(str, "lastPuntuacion%d", getLastCategoria());

	char trueStr[100] = { 0 };
	sprintf(trueStr, "trueLastPuntuacion%d", getLastCategoria());

	int pun = UserDefault::getInstance()->getIntegerForKey(str, 0);
	int truePun = UserDefault::getInstance()->getIntegerForKey(trueStr, 0);
	if (pun == -truePun)
		return truePun;
	else
		return -1;
}
void Puntuador::setLastPuntuacion()
{
	char str[100] = { 0 };
	sprintf(str, "lastPuntuacion%d", categoria);

	char trueStr[100] = { 0 };
	sprintf(trueStr, "trueLastPuntuacion%d", categoria);
	if (puntuacion == -truePuntuacion)
	{
		UserDefault::getInstance()->setIntegerForKey(str, puntuacion);
		UserDefault::getInstance()->setIntegerForKey(trueStr, truePuntuacion);

		int coinsAct = UserDefault::getInstance()->getIntegerForKey("trueTotales",0);
		int coinsFet = UserDefault::getInstance()->getIntegerForKey("totales", 0)/3;

		UserDefault::getInstance()->setIntegerForKey("trueTotales", coinsAct + truePuntuacion);
		UserDefault::getInstance()->setIntegerForKey("totales", (coinsFet + puntuacion)*3);
	}
	else
	{
		UserDefault::getInstance()->setIntegerForKey(str, -1);
		UserDefault::getInstance()->setIntegerForKey(trueStr, -1);

		UserDefault::getInstance()->setIntegerForKey("trueTotales", 0);
		UserDefault::getInstance()->setIntegerForKey("totales", 0);
	}
}
int Puntuador::getTotalCoins()
{
	if (UserDefault::getInstance()->getIntegerForKey("trueTotales", 0) == -UserDefault::getInstance()->getIntegerForKey("totales", 0) / 3)
	{
		return UserDefault::getInstance()->getIntegerForKey("trueTotales", 0);
	}
	else
	{
		return -1;
	}
}
void Puntuador::setTotalCoins(int total)
{
	UserDefault::getInstance()->setIntegerForKey("trueTotales", total);
	UserDefault::getInstance()->setIntegerForKey("totales", -total*3);
}
int Puntuador::getHighPuntuacion()
{
	char str[100] = { 0 };
	sprintf(str, "highPuntuacion%d", getLastCategoria());

	char trueStr[100] = { 0 };
	sprintf(trueStr, "trueHighPuntuacion%d", getLastCategoria());

	int pun = UserDefault::getInstance()->getIntegerForKey(str, 0);
	int truePun = UserDefault::getInstance()->getIntegerForKey(trueStr, 0);

	if (pun == -truePun)
		return truePun;
	else
		return -1;
}
int Puntuador::getLastCategoria()
{
	return UserDefault::getInstance()->getIntegerForKey("lastCategoria",1);
}
void Puntuador::setLastCategoria(int categoria)
{
	UserDefault::getInstance()->setIntegerForKey("lastCategoria", categoria);
}
void Puntuador::setHighPuntuacion()
{
	int ultima = getLastPuntuacion();
	char str[100] = { 0 };
	sprintf(str, "highPuntuacion%d", getLastCategoria());
	UserDefault::getInstance()->setIntegerForKey(str, -ultima);
	char truestr[100] = { 0 };
	sprintf(truestr, "trueHighPuntuacion%d", getLastCategoria());
	UserDefault::getInstance()->setIntegerForKey(truestr, ultima);
}