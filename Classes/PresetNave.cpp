#include "PresetNave.h"
#include "Puntuador.h"

PresetNave::PresetNave(int Num, int valueCoins)
{
	Numero = Num;
	valorCoins = valueCoins;
}
PresetNave::~PresetNave()
{
}
bool PresetNave::isAvailable()
{
	if (Numero == 0)
		return true;
	char titulo[100] = { 0 };
	sprintf(titulo, "NaveAvailable%i", Numero);
	return UserDefault::getInstance()->getBoolForKey(titulo,false);
}
void PresetNave::buy()
{
	if (Puntuador::getTotalCoins() >= valorCoins)
	{
		char titulo[100] = { 0 };
		sprintf(titulo, "NaveAvailable%i", Numero);
		UserDefault::getInstance()->setBoolForKey(titulo, true);
		Puntuador::setTotalCoins(Puntuador::getTotalCoins() - valorCoins);
	}
}

Naves::Naves()
{
}
PresetNave Naves::naves[Naves::numNaves] =
{
	PresetNave(0,0),
	PresetNave(1,20),
	PresetNave(2,50),
	PresetNave(3,100),
	PresetNave(4,1100),
	PresetNave(5,500),
	PresetNave(6,800),
	PresetNave(7,1000),
	PresetNave(8,400),
	PresetNave(9,5000),
	PresetNave(10,2000),
	PresetNave(11,300),
	PresetNave(12,1500),
	PresetNave(13,10000)

};