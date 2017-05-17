#include "PrincipalScene.h"
#include "GameOverScene.h"
#include "Servicios.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS
#include "PluginAdMob/PluginAdMob.h"
#endif

USING_NS_CC;

using namespace cocostudio::timeline;

//Crear la escena
Scene* Principal::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    // 'layer' is an autorelease object
    auto layer = Principal::create();
	layer->physicsWorld = scene->getPhysicsWorld();
	layer->physicsWorld->setGravity(Vec2(0.f, 0.f));
    // add layer as a child to scene
    scene->addChild(layer);
	
    // return the scene
    return scene;
}
//Iniciar escena
bool Principal::init()
{
    
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    auto rootNode = CSLoader::createNode("MainScene.csb");
	rootNoud = rootNode;
    addChild(rootNode);

	//Meteoro::InstanciarEstrellas(rootNode);


	nave = new Nave(rootNode);
	schedule(schedule_selector(Principal::update));
	Servicios::ocultarBarra();
	gasolina = rootNode->getChildByName<ui::LoadingBar*>("gasolina");
	puntuacionTxt = rootNode->getChildByName<ui::Text*>("puntuacionTxt");



	cocostudio::timeline::ActionTimeline *timeline = CSLoader::createTimeline("MainScene.csb");

	rootNode->runAction(timeline);
	timeline->gotoFrameAndPlay(0, true);


	//play musica
	musicaFondo = experimental::AudioEngine::play2d("audio/musica1.mp3", true);

	//Verificarborde
	//schedule(schedule_selector(Principal::verificarColisionBounding), 0.2f);
	//Movimiento Fondo
	{
		Node* rocas = rootNode->getChildByName("rocas");
		Sprite* muestraRocas = rocas->getChildByName("muestraCompleta")->getChildByName<Sprite*>("muestra");
		auto movimientoRocas = RepeatForever::create(Sequence::create(
			MoveBy::create(1, Vec2(-muestraRocas->getContentSize().width, 0)),
			MoveBy::create(0.f, Vec2(muestraRocas->getContentSize().width, 0)),
			NULL
		)
		);
		rocas->runAction(movimientoRocas);
	}
	//EdgeBox......Bounding
	{
		Node* nodoCentro = Node::create();
		nodoCentro->setTag(tokenBounding);
		Size sizeScreen = Director::getInstance()->getVisibleSize();
		nodoCentro->setPosition(sizeScreen.width / 2, sizeScreen.height / 2);
		auto caja = PhysicsBody::createEdgeBox(Size(sizeScreen.width,sizeScreen.height-100), PhysicsMaterial(0.f,0.f, 0.f),3);
		nodoCentro->setPhysicsBody(caja);
		caja->setDynamic(false);
		//caja->setVelocityLimit(0);
		//caja->setContactTestBitmask(true);
		rootNode->addChild(nodoCentro);
	}
	gasolina->setPercent(100.f);
	ui::Button* btn = rootNode->getChildByName<ui::Button*>("btn1");
	btn->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			if (!iniciado)
			{
				iniciado = true;
				iniciarJuego();
			}
			nave->subir();
			break;
		case ui::Widget::TouchEventType::ENDED:
			nave->bajar();
			break;
		case ui::Widget::TouchEventType::CANCELED:
			nave->bajar();
			break;
		default:
			break;
		}
	});
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(Principal::onContactBegin, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
	
	puntuador = new Puntuador(categoria);

	//Cambio de NAVE
	//auto naveSeleccionada = UserDefault::getInstance()->getStringForKey("naveSeleccionada", "res/Sprites/nave0.png");
	//nave->naveSprite->setTexture(naveSeleccionada);
	

	return true;
}
//Iniciar juego
void Principal::iniciarJuego()
{
	schedule(schedule_selector(Principal::instanciarMoneda), 1.5f);
	schedule(schedule_selector(Principal::instanciarMeteoros), 1.f/meteoroSobreSegundo);
	schedule(schedule_selector(Principal::accionDeRayo), tiempoRayo);
	
}
//SUPER   InstanciadorDeMonedas
void Principal::instanciarSuperMonedasALoLoco()
{
	experimental::AudioEngine::play2d("audio/special.ogg");
	unschedule(schedule_selector(Principal::instanciarMeteoros));
	schedule(schedule_selector(Principal::instanciarMoneda), 0.2f);
	schedule(schedule_selector(Principal::detenerSuperInstanciadorDeMonedas), 3.f);
}
void Principal::detenerSuperInstanciadorDeMonedas(float dt)
{
	schedule(schedule_selector(Principal::instanciarMeteoros), 1.f / meteoroSobreSegundo);
	schedule(schedule_selector(Principal::instanciarMoneda), 1.5f);
}

//Accion de rayo
void Principal::accionDeRayo(float dt)
{
	

	auto Rayo = rootNoud->getChildByName<Sprite*>("rayo");
	Rayo->setOpacity(255);
	MoveTo* moverIzquierda = MoveTo::create(1.5f, Vec2(0, 360));
	
	DelayTime* tiempoEspera = DelayTime::create(1.f);
	
	FadeOut* difuminar = FadeOut::create(0.3f);
	CallFunc* llamada = CallFunc::create(CC_CALLBACK_0(Principal::funcionAleatoriaRayo, this));

	MoveTo* regresar = MoveTo::create(0.f, Vec2(1400, 360));
	Sequence* secuencia = Sequence::create(tiempoEspera, llamada, difuminar,regresar, NULL);

	Spawn* accionesFinales = Spawn::create(moverIzquierda, secuencia, NULL);

	//Pintar Rayo
	accionRandom = RandomHelper::random_int(1,3);
	switch (accionRandom)
	{
	case 1:
		Rayo->setColor(Color3B(0xFF,0xFD,0xA7));
		break;
	case 2:
		Rayo->setColor(Color3B(0xFF,0x8A,0x98));
		break;
	case 3:
		Rayo->setColor(Color3B::WHITE);
		break;
	}

	Rayo->runAction(accionesFinales);

}
//Funcion Aleatoria del rayo
void Principal::funcionAleatoriaRayo()
{
	switch (accionRandom)
	{
	case 1:
		nave->hacerChiquita();
		break;
	case 2:
		nave->hacerGrandota();
		break;
	case 3:
		nave->invertirPantalla();
		experimental::AudioEngine::play2d("audio/invertir.ogg");
		break;
	}
	scheduleOnce(schedule_selector(Principal::hacerChocable), 0.25f);
}
//Instanciar balas
void Principal::instanciarBalas(float dt)
{
	Pistola::disparar(rootNoud, nave->naveSprite);
}
//Detener balas
void Principal::detenerBalas(float dt)
{
	unschedule(schedule_selector(Principal::instanciarBalas));
}
void Principal::hacerChocable(float dt)
{
	nave->chocable = true;
}
//Instanciacion de meteoros
void Principal::instanciarMeteoros(float dt)
{
	//Meteoro::instanciarRandom(rootNoud);
	schedule(schedule_selector(Principal::instanciarMeteoros), 1.f / meteoroSobreSegundo);

	int numRan = random(0, 50);
	if (numRan >= 6)
	{
		Meteoro::instanciarMeteoro(rootNoud, 3, RandomHelper::random_int(1, 3));
	}
	else if (numRan >= 4)
	{
		Meteoro::instanciarEnergia(rootNoud);
	}
	else if (numRan >= 2)
	{
		Meteoro::instanciarEnergiaBalas(rootNoud);
	}
	else if(puedeEspecial && numRan == 1)
	{
		Meteoro::instanciarRandom(rootNoud);
	}

}
//Instanciacion de monedas
void Principal::instanciarMoneda(float dt)
{
	Meteoro::instanciarMoneda(rootNoud);
}
void Principal::activarEspecial(float dt)
{
	puedeEspecial = true;
}
//Colisiones
bool Principal::onContactBegin(PhysicsContact &contact)
{
	auto a =(Sprite*)contact.getShapeA()->getBody()->getOwner();
	auto b = (Sprite*)contact.getShapeB()->getBody()->getOwner();
	auto tagA = a->getTag();
	auto tagB = b->getTag();
	if (!nave->chocable)
		return false;
	////////Choque con BOUNDING
	/*if (tagA == tokenBounding && tagB == tokenNave)
	{
		char choques[100] = { 0 };
		sprintf(choques, "%i", ++countColls);
		rootNoud->getChildByName<ui::Text*>("counter")->setString(choques);
		nave->naveSprite->runAction(RotateTo::create(0.1f, 0));
	}
	else if (tagB == tokenBounding && tagA == tokenNave)
	{
		char choques[100] = { 0 };
		sprintf(choques, "%i", ++countColls);
		rootNoud->getChildByName<ui::Text*>("counter")->setString(choques);
		nave->naveSprite->runAction(RotateTo::create(0.1f, 0));
	}*/

	//////////Choque con Special
	if (tagA == tokenRandom && tagB == tokenNave)
	{
		//nave->hacerGrandota();
		//nave->hacerChiquita();
		scheduleOnce(schedule_selector(Principal::hacerChocable), 0.25f);
		nave->darMonedas();
		instanciarSuperMonedasALoLoco();
		puedeEspecial = false;
		a->runAction(Sequence::create(FadeOut::create(0.2f), RemoveSelf::create(true), NULL));
		schedule(schedule_selector(Principal::activarEspecial), 15.f);
		//nave->invertirPantalla();
		

	}
	else if (tagB == tokenRandom && tagA == tokenNave)
	{
		//nave->hacerGrandota();
		//nave->hacerChiquita();
		scheduleOnce(schedule_selector(Principal::hacerChocable), 0.25f);
		nave->darMonedas();
		instanciarSuperMonedasALoLoco();
		puedeEspecial = false;
		b->runAction(Sequence::create(FadeOut::create(0.2f), RemoveSelf::create(true), NULL));
		schedule(schedule_selector(Principal::activarEspecial), 15.f);
		//nave->invertirPantalla();
	}
	//////////Choque con Meteoro
	if (tagA >= tokenMeteoro && tagA<55 && tagB == tokenNave)
	{
		Meteoro::explotar(a);
		cambiarGasolina(damageBalas);

	}
	else if (tagB >= tokenMeteoro && tagB<55 && tagA == tokenNave)
	{
		Meteoro::explotar(b);
		cambiarGasolina(damageBalas);
	}
	/////////////Tomar Energia
	else if (tagA == tokenEnergia && tagB == tokenNave)
	{
		a->runAction(Sequence::create(FadeOut::create(0.2f), RemoveSelf::create(true), NULL));
		cambiarGasolina(curacion);

		experimental::AudioEngine::play2d("audio/vida.ogg", false, 0.5);
	}
	else if (tagB == tokenEnergia && tagA == tokenNave)
	{
		b->runAction(Sequence::create(FadeOut::create(0.2f), RemoveSelf::create(true), NULL));
		cambiarGasolina(curacion);

		experimental::AudioEngine::play2d("audio/vida.ogg", false, 0.5);
	}
	/////////////Tomar Energia Balas
	else if (tagA == tokenEnergiaBalas && tagB == tokenNave)
	{
		unschedule(schedule_selector(Principal::detenerBalas));
		a->runAction(Sequence::create(FadeOut::create(0.2f),RemoveSelf::create(true),NULL));
		schedule(schedule_selector(Principal::instanciarBalas), balasDelay);
		scheduleOnce(schedule_selector(Principal::detenerBalas), tiempoConBalas);

		experimental::AudioEngine::play2d("audio/tomoLaser.ogg", false, 0.5);
	}
	else if (tagB == tokenEnergiaBalas && tagA == tokenNave)
	{
		unschedule(schedule_selector(Principal::detenerBalas));
		b->runAction(Sequence::create(FadeOut::create(0.2f), RemoveSelf::create(true), NULL));
		schedule(schedule_selector(Principal::instanciarBalas), balasDelay);
		scheduleOnce(schedule_selector(Principal::detenerBalas), tiempoConBalas);

		experimental::AudioEngine::play2d("audio/tomoLaser.ogg", false, 0.5);
	}
	/////////Impacto Bala
	else if (tagA >= tokenMeteoro && tagA<55 && tagB == tokenBala)
	{
		Meteoro::golpear(a);
		Pistola::desaparecerBala(b);
	}
	else if (tagB >= tokenMeteoro && tagB<55 && tagA == tokenBala)
	{
		Meteoro::golpear(b);
		Pistola::desaparecerBala(a);
	}
	//Impacto Moneda  -  Meteoro
	else if (tagA >= tokenMeteoro && tagA<55 && tagB == tokenMoneda)
	{
		
		a->runAction(RemoveSelf::create(true));
	}
	else if (tagB >= tokenMeteoro && tagB<55 && tagA == tokenMoneda)
	{
		
		b->runAction(RemoveSelf::create(true));
	}
	//Tomar Moneda
	else if (tagB == tokenNave && tagA == tokenMoneda)
	{
		tomarMoneda();
		a->runAction(Sequence::create(FadeOut::create(0.2f), RemoveSelf::create(true), NULL));
	}
	else if (tagA == tokenNave && tagB == tokenMoneda)
	{
		tomarMoneda();
		b->runAction(Sequence::create(FadeOut::create(0.2f), RemoveSelf::create(true), NULL));
	}
	//Cero Colisiones
	return false;
}
//Tomar Moneda
void Principal::tomarMoneda()
{
	meteoroSobreSegundo += 0.1f;

	experimental::AudioEngine::play2d("audio/moneda.ogg", false,0.1f);
	puntuador->addPuntuacion();
	int puntuacion = puntuador->getPuntuacion();
	char str[100] = { 0 };
	sprintf(str, "%d", puntuacion);
	puntuacionTxt->setString(str);
}
//Actualizar rotacion
void Principal::update(float dt)
{
	nave->naveSprite->setPositionX(400);
	float rotaAnterior = nave->naveSprite->getRotation();
	float rotacion = -nave->naveFisica->getVelocity().y / nave->velocidadMaxima * nave->angulo;
	float diferencia = rotacion - rotaAnterior;
	if(diferencia < 6 && diferencia > -6)
		nave->naveSprite->setRotation(rotacion);
	else if(diferencia > 6)
	{
		nave->naveSprite->setRotation(rotaAnterior + 6);
	}
	else
	{
		nave->naveSprite->setRotation(rotaAnterior - 6);
	}
	Size sizeScreen = Director::getInstance()->getVisibleSize();
	if (nave->naveSprite->getPositionY() > (690 - nave->naveSprite->getContentSize().height / 2))
	{
		nave->naveSprite->setPositionY(670 - nave->naveSprite->getContentSize().height / 2);
		nave->naveSprite->runAction(RotateTo::create(0.1f, 0));
	}
	else if (nave->naveSprite->getPositionY() < (nave->naveSprite->getContentSize().height / 2))
	{
		nave->naveSprite->setPositionY(nave->naveSprite->getContentSize().height / 2 + 52);
		nave->naveSprite->runAction(RotateTo::create(0.1f, 0));
	}
}
//Cambiar nivel de gasolina
void Principal::cambiarGasolina(int aumento)
{
	int gasolinaActual = gasolina->getPercent() + aumento;
	gasolina->setPercent(gasolinaActual);
	//float tinteo = gasolinaActual / 100 * 255;
	if (gasolinaActual <= 0)
	{
		terminarJuego();
	}
	//nave->naveSprite->setColor(Color3B(255, tinteo, tinteo));
	else if (gasolinaActual <= -damageBalas)
	{
		auto animacionPeligro = RepeatForever::create(Sequence::create(TintTo::create(0.25, 255, 0, 0), TintTo::create(0.25, 255, 255, 255), NULL));
		animacionPeligro->setTag(tokenAnimacionNave);
		nave->naveSprite->runAction(animacionPeligro);

	}
	else
	{
		nave->naveSprite->stopActionByTag(tokenAnimacionNave);
		nave->naveSprite->setColor(Color3B(255, 255, 255));
	}	
}
void Principal::terminarJuego()
{
	experimental::AudioEngine::stopAll();
	//nave->naveSprite->setColor(Color3B(255, 255, 255));
	nave->Explotar();
	unschedule(schedule_selector(Principal::instanciarBalas));
	rootNoud->runAction(FadeOut::create(0.4f));
	puntuador->setLastPuntuacion();

	scheduleOnce(schedule_selector(Principal::terminate), 0.4f);
}
void Principal::terminate(float dt)
{
	auto escena = GameOverScene::createScene();
	Director::getInstance()->replaceScene(TransitionMoveInL::create(0.5, escena));
}
int cocococo = 0;
void Principal::verificarColisionBounding(float dt)
{
	/*Vec2 posicion = nave->naveSprite->getPosition();
	Size tamaño = nave->naveSprite->getContentSize();
	if (posicion.y <= tamaño.height + 10)
	{
		auto texto = rootNoud->getChildByName<ui::Text*>("texto");
		char ch[100] = { 0 };
		sprintf(ch, "%i",cocococo);
		texto->setString(ch);
		cocococo++;
	}*/
}