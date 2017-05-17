#include "Pistola.h"

void Pistola::disparar(Node* rootNode, Node* nave, float velocidadBala)
{
	Size sizeScreen = Director::getInstance()->getVisibleSize();
	Sprite* bala = Sprite::create("lasers/laser1.png");
	auto rota = -nave->getRotation();
	auto seno = sin(rota*3.1416 / 180);
	auto coseno = cos(rota*3.1416 / 180);

	rootNode->addChild(bala);
	bala->setTag(Principal::tokenBala);
	auto balaFisica = PhysicsBody::createCircle(bala->getContentSize().height/2, PHYSICSBODY_MATERIAL_DEFAULT);
	balaFisica->setDynamic(false);
	balaFisica->setContactTestBitmask(true);
	bala->setGlobalZOrder(-10.f);
	balaFisica->setPositionOffset(Vec2(bala->getContentSize().width / 2 - bala->getContentSize().height / 2, 0));
	bala->setPosition(Vec2(nave->getPositionX() + (coseno * nave->getContentSize().width / 4) /*+ (coseno * bala->getContentSize().width / 2)*/,
						   nave->getPositionY() + (seno * nave->getContentSize().width / 2) + (seno * bala->getContentSize().width / 2)));
	bala->setRotation(-rota);
	bala->setPhysicsBody(balaFisica);
	auto movimiento = MoveBy::create(velocidadBala, Vec2(sizeScreen.width * coseno, sizeScreen.width * seno));
	//auto movimiento = MoveBy::create(velocidadBala, Vec2(sizeScreen.width,0));
	bala->runAction(Sequence::create(movimiento,RemoveSelf::create(true),NULL));

	
	experimental::AudioEngine::play2d("audio/laser.ogg", false, 0.5);
}
void Pistola::desaparecerBala(Sprite* bala)
{
	auto remover = RemoveSelf::create(true);
	bala->runAction(remover);
}
Pistola::Pistola()
{
}
Pistola::~Pistola()
{
}
