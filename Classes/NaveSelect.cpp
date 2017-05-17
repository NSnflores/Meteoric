#include "NaveSelect.h"
#include "PresetNave.h"
#include "Puntuador.h"
#include "MainMenu.h"
#include "AudioEngine.h"
#include "Meteoro.h"
#include <string>

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include "pluginadmob\PluginAdMob.h"
#endif


USING_NS_CC;

using namespace cocostudio::timeline;

Scene* NaveSelect::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = NaveSelect::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool NaveSelect::init()
{
    
    if ( !Layer::init() )
    {
        return false;
    }
    
    rootNode = CSLoader::createNode("NaveSelect.csb");
	addChild(rootNode);

	Meteoro::InstanciarEstrellas(rootNode);

	vistaNaves = rootNode->getChildByName<ui::PageView*>("vista");
	vistaNaves->scrollToItem(0);
	monedas = rootNode->getChildByName("monedas")->getChildByName<ui::TextField*>("coins");

	auto naveSeleccionada = UserDefault::getInstance()->getStringForKey("naveSeleccionada","res/Sprites/nave0.png");
	rootNode->getChildByName<Sprite*>("naveActual")->setTexture(naveSeleccionada);
	////////////SCROLLING BUTTONS
	{
		ui::Button* btnDerecha = rootNode->getChildByName<ui::Button*>("btnDerecha");
		btnDerecha->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
		{
			if (type == ui::Widget::TouchEventType::ENDED)
			{
				vistaNaves->scrollToItem(vistaNaves->getCurrentPageIndex()+1);
			}
		});
		ui::Button* btnIzquierda = rootNode->getChildByName<ui::Button*>("btnIzquierda");
		btnIzquierda->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
		{
			if (type == ui::Widget::TouchEventType::ENDED)
			{
				vistaNaves->scrollToItem(vistaNaves->getCurrentPageIndex() - 1);
			}
		});
	}

	//confirmar compra Buttons
	{
		ui::Button* btnSi = rootNode->getChildByName("confirmar")->getChildByName<ui::Button*>("btnSi");
		btnSi->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
		{
			if (type == ui::Widget::TouchEventType::ENDED)
			{
				experimental::AudioEngine::play2d("audio/vida.ogg", false, 0.4f);
				Naves::naves[tagPorComprar].buy();
				rootNode->getChildByName("confirmar")->runAction(MoveTo::create(0.15f, Vec2(640, -210)));
				
				
				char imagen[100] = { 0 };
				sprintf(imagen, "res/Sprites/nave%i.png", tagPorComprar);
				Sprite* naveActual = vistaNaves->getParent()->getChildByName<Sprite*>("naveActual");
				naveActual->setTexture(imagen);
				UserDefault::getInstance()->setStringForKey("naveSeleccionada", imagen);


				actualizarContenedores();
			}
		});
		ui::Button* btnNo = rootNode->getChildByName("confirmar")->getChildByName<ui::Button*>("btnNo");
		btnNo->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
		{
			if (type == ui::Widget::TouchEventType::ENDED)
			{
				experimental::AudioEngine::play2d("audio/click.ogg", false, 0.4f);
				rootNode->getChildByName("confirmar")->runAction(MoveTo::create(0.15f, Vec2(640, -210)));
			}
		});
	}
	

	////Boton home
	auto btnHome = rootNode->getChildByName<ui::Button*>("btnHome");
	btnHome->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			auto escenaa = MainMenu::createScene();
			Director::getInstance()->replaceScene(TransitionFade::create(0.5f, escenaa));
			break;
		}
	});
	actualizarContenedores();

	return true;
}


void NaveSelect::actualizarContenedores()
{
	auto coleccion = vistaNaves->getChildren();
	int countN = 0;
	for (Node* node : coleccion)
	{
		ui::Button* btnSelect = node->getChildByName<ui::Button*>("btnSelect");
		Node* costNode = node->getChildByName("costNode");
		Node* nave = node->getChildByName("nave");
		bool disponible = Naves::naves[countN].isAvailable();
		int monedasTotales = Puntuador::getTotalCoins();
		if (disponible)
		{
			nave->setColor(Color3B::WHITE);
			costNode->setOpacity(0);
			btnSelect->setColor(Color3B(0x65, 0xFF, 0x78));
			btnSelect->setTitleText("select");
		}
		else
		{
			nave->setColor(Color3B(0, 0, 0));
			btnSelect->setColor(Color3B(0xFF, 0xA6, 0xEF));
			btnSelect->setTitleText("");
			auto texto = costNode->getChildByName<ui::TextField*>("coins");
			char numero[100] = { 0 };
			sprintf(numero, "%i", Naves::naves[countN].valorCoins);
			texto->setString(numero);
			if (monedasTotales < Naves::naves[countN].valorCoins)
				costNode->getChildByName("coins")->setColor(Color3B(255, 0, 0));
			else
			{
				costNode->getChildByName("coins")->setColor(Color3B::WHITE);
			}
			
		}

		char money[100] = { 0 };
		sprintf(money, "%i", monedasTotales);
		monedas->setString(money);

		btnSelect->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
		{
			if (type == ui::Widget::TouchEventType::ENDED)
			{
				int nBoton = vistaNaves->getChildren().getIndex(((Node*)sender)->getParent());
				bool disponibleBtn = Naves::naves[nBoton].isAvailable();
				if (disponibleBtn)
				{
					experimental::AudioEngine::play2d("audio/click.ogg", false, 0.4f);
					char imagen[100] = { 0 };
					sprintf(imagen, "res/Sprites/nave%i.png", nBoton);
					Sprite* naveActual = vistaNaves->getParent()->getChildByName<Sprite*>("naveActual");
					naveActual->setTexture(imagen);
					UserDefault::getInstance()->setStringForKey("naveSeleccionada",imagen);
				}
				else
				{
					if (Puntuador::getTotalCoins() >= Naves::naves[nBoton].valorCoins)
					{
						experimental::AudioEngine::play2d("audio/click.ogg", false, 0.4f);
						Node* confirmarIE = rootNode->getChildByName("confirmar");
						tagPorComprar = nBoton;
						confirmarIE->runAction(MoveTo::create(0.15f, Vec2(640, 390)));
						char pre[100] = { 0 };
						sprintf(pre, "%i", Naves::naves[tagPorComprar].valorCoins);
						confirmarIE->getChildByName("precio")->getChildByName<ui::TextField*>("coins")->setString(pre);
					}
				}
			}
		});
		
		countN++;
	}
}

