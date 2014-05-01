#include "Welecome.h"
#include "HelloWorldScene.h"

Welecome::Welecome(void)
{
}


Welecome::~Welecome(void)
{
}


CCScene* Welecome::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	Welecome *layer = Welecome::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool Welecome::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}
	CCSize  screenSize = CCDirector::sharedDirector()->getVisibleSize();

	CCSprite *welcome = CCSprite::create("welcome.png");
	welcome->setPosition(ccp(screenSize.width/2,screenSize.height/2));
	addChild(welcome);


	//scheduleUpdate();
	scheduleOnce(schedule_selector(Welecome::Qiehuan),0.5f);

	return true;
}

//void Welecome::onEnter()
//{
	//scheduleUpdate();
	//scheduleOnce(schedule_selector(Welecome::Qiehuan),1.0f);
//}

void Welecome::Qiehuan(float dt){

	CCScene *pScene = HelloWorld::scene();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(2.0,pScene));
}

void Welecome::update(float dt)
{
	CCLog("%f",dt);
}
