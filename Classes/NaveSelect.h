#ifndef __NaveSelect_SCENE_H__
#define __NaveSelect_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"


class NaveSelect : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
	int tagBtnNave = 201;
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    // implement the "static create()" method manually
    CREATE_FUNC(NaveSelect);
	cocos2d::ui::PageView* vistaNaves;
	cocos2d::ui::TextField* monedas;
	int tagPorComprar = 0;
	Node* rootNode;
	void actualizarContenedores();
};

#endif // __HELLOWORLD_SCENE_H__
