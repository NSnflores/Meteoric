#ifndef NAVE_H
#define NAVE_H

#include "cocos2d.h"
//#include "PrincipalScene.h"
#include "AudioEngine.h"

using namespace cocos2d;
//using namespace experimental;

class Nave
{
public:
	Nave(Node* rootNodeT);
	~Nave();
	Node* rootNode;
	Sprite* naveSprite;
	PhysicsBody* naveFisica;
	ParticleSystemQuad* particulaEmision;
	bool rotada = false;

	float velocidadArriba = 500000.f;
	float velocidadAbajo = -500000.f;
	float velocidadMaxima = 800;
	float angulo = 45;
	float emisionRate = 100;
	bool chocable = true;
	//unsigned int sonidoTurbina = 0;
	void Explotar()
	{
		naveSprite->stopAllActions();
		naveSprite->setColor(Color3B::WHITE);
		//Animacion
			Vector<SpriteFrame*> animFrames(9);
			char str[100] = { 0 };
			for (int i = 0; i < 9; i++)
			{
				sprintf(str, "explosion/pixelExplosion0%d.png", i);
				auto frame = SpriteFrame::create(str, Rect(0, 0, 96, 96)); //we assume that the sprites' dimentions are 96*96 rectangles.
				animFrames.pushBack(frame);
			}
			
			auto animacionExplosion = Animation::createWithSpriteFrames(animFrames, 0.07f);
			auto anima = Animate::create(animacionExplosion);
			//naveFisica->setDynamic(false);
			
			naveSprite->runAction(anima);
			naveSprite->runAction(Sequence::create(DelayTime::create(0.07f), ScaleTo::create(0.f, 1.5f),NULL));
		particulaEmision->setEmissionRate(0.f);
		naveFisica->removeFromWorld();
		
		experimental::AudioEngine::play2d("explosionLarga.ogg", false, 1.f);

		//particulaEmision->runAction(FadeOut::create(0.1f));
	}
	
	void subir()
	{
		emitirParticula();
		naveFisica->resetForces();
		naveFisica->applyForce(Vec2(0, velocidadArriba));

		/*auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
		sonidoTurbina = audio->playEffect("audio/turbina.ogg", true, 0.6f, 0.f, 0.1f);*/
	}
	void bajar()
	{
		detenerEmision();
		naveFisica->resetForces();
		naveFisica->applyForce(Vec2(0, velocidadAbajo));

		/*auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
		audio->stopEffect(sonidoTurbina);*/
	}
	void detenerEmision()
	{
		particulaEmision->setEmissionRate(0);
	}
	void emitirParticula()
	{
		particulaEmision->setEmissionRate(emisionRate);
	}
	int randomAction()
	{

	}
	void hacerChiquita()
	{
		float tmp = 0.08f;
		float peq = 0.38f;
		float gra = 0.5f;
		auto peque = ScaleTo::create(tmp, peq);
		auto regre = ScaleTo::create(tmp, gra);
		auto peque1 = ScaleTo::create(tmp, peq);
		auto regre1 = ScaleTo::create(tmp, gra);
		auto peque2 = ScaleTo::create(tmp, peq);
		auto delayt = DelayTime::create(4.f);
		auto peque3 = ScaleTo::create(tmp, gra);
		auto regre3 = ScaleTo::create(tmp, peq);
		auto peque4 = ScaleTo::create(tmp, gra);
		auto regre4 = ScaleTo::create(tmp, peq);
		auto peque5 = ScaleTo::create(tmp, gra);
		auto secu = Sequence::create(peque, regre, peque1, regre1, peque2,delayt,peque3,regre3,peque4,regre4,peque5, NULL);
		naveSprite->runAction(secu);
		experimental::AudioEngine::play2d("audio/chica.ogg",false,1.f);
		
	}
	void hacerGrandota()
	{
		float tmp = 0.08f;
		float peq = 0.62f;
		float gra = 0.5f;
		auto peque = ScaleTo::create(tmp, peq);
		auto regre = ScaleTo::create(tmp, gra);
		auto peque1 = ScaleTo::create(tmp, peq);
		auto regre1 = ScaleTo::create(tmp, gra);
		auto peque2 = ScaleTo::create(tmp, peq);
		auto delayt = DelayTime::create(4.f);
		auto peque3 = ScaleTo::create(tmp, gra);
		auto regre3 = ScaleTo::create(tmp, peq);
		auto peque4 = ScaleTo::create(tmp, gra);
		auto regre4 = ScaleTo::create(tmp, peq);
		auto peque5 = ScaleTo::create(tmp, gra);
		auto secu = Sequence::create(peque, regre, peque1, regre1, peque2, delayt, peque3, regre3, peque4, regre4, peque5, NULL);
		naveSprite->runAction(secu);
		experimental::AudioEngine::play2d("audio/grande.ogg",false,1.f);
	}

	void invertirPantalla()
	{	
		float angulo = rotada ? 0 : 180;
		rotada = !rotada;
		rootNode->getChildByName("btn1")->runAction(RotateTo::create(0.25f, Vec3(0.f, -angulo, 0.f)));
		rootNode->getParent()->runAction(RotateTo::create(0.25f, Vec3(0.f, angulo, 0.f)));
		rootNode->getChildByName("puntuacionTxt")->runAction(RotateTo::create(0.25f, Vec3(0.f, -angulo, 0.f)));
		chocable = false;
	}
	void darMonedas()
	{
		if (rotada)
			invertirPantalla();
		for (Node* nd : rootNode->getChildren())
		{
			
			int tg = nd->getTag();
			if (tg >= 50 && tg < 56)
			{
				Sprite* sprt = (Sprite*)nd;
				PhysicsBody* cuerpo = ((Sprite*)nd)->getPhysicsBody();
				cuerpo->removeFromWorld();
				sprt->runAction(FadeOut::create(0.3f));
				
			}
		}
	}
};
#endif
