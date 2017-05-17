#ifndef __Principal_SCENE_H__
#define __Principal_SCENE_H__

#include "cocos2d.h"
#include "Nave.h"
#include "ui/CocosGUI.h"
#include "Pistola.h"
#include "cocostudio/CocoStudio.h"
#include "Meteoro.h"
#include "AudioEngine.h"
#include "Puntuador.h"

using namespace cocos2d;
//using namespace experimental;


class Principal : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static Scene* createScene();

	
	Node* rootNoud;
	
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
	bool onContactBegin(PhysicsContact &contact);
	void update(float dt);
	void instanciarMeteoros(float dt);
	void accionDeRayo(float dt);
	void funcionAleatoriaRayo();
	void instanciarBalas(float dt);
	void iniciarJuego();
	void detenerBalas(float dt);
	void instanciarMoneda(float dt);
	void terminarJuego();
	void cambiarGasolina(int aumento);
	void verificarColisionBounding(float dt);
	void tomarMoneda();
	void instanciarSuperMonedasALoLoco();
	void detenerSuperInstanciadorDeMonedas(float dt);
	void terminate(float dt);
	void activarEspecial(float dt);
	bool iniciado = false;
	Puntuador* puntuador;
	Nave* nave;
	ui::LoadingBar* gasolina;
	ui::Text* puntuacionTxt;
    CREATE_FUNC(Principal);
	float meteoroSobreSegundo = 2;
	int contadorDeMeteoros = 0;
	int damageBalas = -20;
	int curacion = 35;
	float tiempoConBalas = 6.f;
	float balasDelay = 0.14f;
	int categoria = 1;
	int categoriaDefault = 1;
	int accionRandom = 1;
	bool puedeEspecial = true;
	static const int tokenCurar = 8;
	static const int tokenDarMonedas = 9;
	static const int tokenNave = 10;
	static const int tokenEnergia = 12;
	static const int tokenBala = 13;
	static const int tokenEnergiaBalas = 14;
	static const int tokenAnimacionNave = 15;
	static const int tokenMoneda = 16;
	static const int tokenBounding = 17;
	static const int tokenRandom = 18;
	static const int tokenMeteoro = 50;
	static const int tiempoRayo = 7;
	int musicaFondo;
	void hacerChocable(float dt);
	PhysicsWorld* physicsWorld;
	int countColls = 0;
};

#endif // __Principal_SCENE_H__
