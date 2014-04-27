#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#define RATIO 128.0f


#include "cocos2d.h"

USING_NS_CC;


#include "F:\yt\soft\cocos2d-x-2.2.3\external\Box2D\Box2D.h"
#include "B2Sprite.h"
#include "F:\yt\soft\cocos2d-x-2.2.3\projects\YtTouchBird\proj.win32\Bird.h"


class HelloWorld : public cocos2d::CCLayer ,public  b2ContactListener
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);

	virtual void update(float dt);
	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);


	virtual void BeginContact(b2Contact* contact);
	virtual void EndContact(b2Contact* contact) ;

	b2World *world;
	Bird *bird;
	CCSize screenSize;
	CCSprite *barContainer;
	CCSpriteFrameCache *cache;
	B2Sprite *bg;
	B2Sprite *ground;
	B2Sprite *ground2;
	B2Sprite *down_bar;

	bool isTouch;
	bool gameend;
	int score;

private :
		void addBrid();
		void addGround( float dt);
		void initWorld();
		void addBg();
		void addBar( float dt);
		void addBarContainer();



		void loading();

		void startGame( float dt);
		void endGame();
public:

	void gameEndCallback(CCObject* pSender);
};

#endif // __HELLOWORLD_SCENE_H__
