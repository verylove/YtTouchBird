#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#define RATIO 48.0f


#include "cocos2d.h"

USING_NS_CC;


#include "F:\yt\soft\cocos2d-x-2.2.3\external\Box2D\Box2D.h"
#include "B2Sprite.h"

class HelloWorld : public cocos2d::CCLayer
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

	b2World *world;
	B2Sprite *bird;
	CCSize screenSize;
	CCSprite *barContainer;
private :
		void addBrid();
		void addGround();
		void initWorld();
		void addBar( float dt);
		void addBarContainer();
};

#endif // __HELLOWORLD_SCENE_H__
