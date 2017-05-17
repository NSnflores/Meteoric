#pragma once

#include "cocos2d.h"
#include "PrincipalScene.h"
using namespace cocos2d;
class Meteoro
{
public:
	static const int tipoGrande = 3;
	static const int tipoMediano = 2;
	static const int tipoChico = 1;
	static void instanciarMeteoro(Node* rootNode,float velocidadMeteoro = 3,int tipo = 1);
	static void instanciarEnergia(Node* rootNode, float velocidadMeteoro = 3);
	static void instanciarRandom(Node* rootNode, float velocidadMeteoro = 3);
	static void instanciarMoneda(Node* rootNode, float velocidadMeteoro = 3);
	static void explotar(Sprite* meteo);
	static void golpear(Sprite* meteo);
	static void instanciarEnergiaBalas(Node* rootNode, float velocidadMeteoro = 3);
	static void InstanciarEstrellas(Node* rootN)
	{
		int numEstrellas = 20;
		for (int i = 0;i < 20;i++)
		{
			Sprite* estrella = Sprite::create("star.png");
			float escala = RandomHelper::random_real(0.5f, 1.f);
			float tiempoDel = RandomHelper::random_real(0.7f, 1.2f);
			float posX = RandomHelper::random_real(0.f, Director::getInstance()->getVisibleSize().width);
			float posY = RandomHelper::random_real(0.f, Director::getInstance()->getVisibleSize().height);
			rootN->addChild(estrella);
			estrella->setGlobalZOrder(-10);
			estrella->setPosition(Vec2(posX, posY));

			ScaleBy* achicar = ScaleBy::create(tiempoDel, 0.5f);
			EaseSineInOut* sineAchi = EaseSineInOut::create(achicar);
			ScaleTo* agrandar = ScaleTo::create(tiempoDel, escala);
			EaseSineInOut* sineAgra = EaseSineInOut::create(agrandar);
			Sequence* secEscala = Sequence::create(sineAchi, sineAgra,NULL);

			RepeatForever* secuenciaFinal = RepeatForever::create(secEscala);

			estrella->setOpacity(0);
			estrella->runAction(Sequence::create(DelayTime::create(1.f),FadeIn::create(2.f),TintTo::create(1.f,100,100,100),NULL));

			estrella->runAction(secuenciaFinal);
		}
	}
	Meteoro();
	~Meteoro();
private:

	
};

