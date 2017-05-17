#include "Nave.h"

Nave::Nave(Node* rootNodeT)
{

	rootNode = rootNodeT;
	//naveSprite = rootNodeT->getChildByName<Sprite*>("Nave");
	naveSprite = Sprite::create(UserDefault::getInstance()->getStringForKey("naveSeleccionada", "res/Sprites/nave0.png"));
	naveSprite->setScale(0.5f);
	naveSprite->setPosition(Vec2(Director::getInstance()->getVisibleSize().width/3,Director::getInstance()->getVisibleSize().height/2));
	rootNodeT->addChild(naveSprite);
	
	naveSprite->setTag(10);
	naveFisica = PhysicsBody::createBox(naveSprite->getContentSize(),
										PhysicsMaterial(0.1f,0.f,0.f));
	naveSprite->setPhysicsBody(naveFisica);
	particulaEmision = ParticleSystemQuad::create("res/Default/defaultParticle.plist");
	naveSprite->addChild(particulaEmision);
	particulaEmision->setScale(1.5f);
	particulaEmision->setPosition(Vec2(-8, naveSprite->getContentSize().height/2));
	//particulaEmision = naveSprite->getChildByName<ParticleSystemQuad*>("particula");	
	particulaEmision->setGravity(Vec2(-2000, 0));
	particulaEmision->setEmissionRate(emisionRate);
	naveFisica->setRotationEnable(false);
	//naveFisica->setGravityEnable(false);
	naveFisica->setDynamic(true);
	naveFisica->setVelocityLimit(velocidadMaxima);
	naveFisica->setContactTestBitmask(true);
}
Nave::~Nave()
{
}
