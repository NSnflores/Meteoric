#pragma once
#include "cocos2d.h"
#include "AudioEngine.h"
#include "PrincipalScene.h"

using namespace cocos2d;
//using namespace experimental;
class Pistola
{
public:
	Pistola();
	~Pistola();
	static void disparar(Node* rootNode, Node* pistola, float velocidadBala = 1);
	static void desaparecerBala(Sprite* bala);
};

