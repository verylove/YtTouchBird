#include "HelloWorldScene.h"

USING_NS_CC;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
	this->screenSize = CCDirector::sharedDirector()->getVisibleSize();
 
	initWorld();
	addBrid();
	addBarContainer();
	addGround();

	scheduleUpdate();
	schedule(schedule_selector(HelloWorld::addBar),1);

	setTouchEnabled(true);

    return true;
}

void HelloWorld::initWorld(){
	this->world = new b2World(b2Vec2(0,-9.8));
}

void HelloWorld::update(float dt){
	this->world->Step(dt,8,3);
	CCSprite *s;
	//遍历棍
	b2Body *node  = this->world->GetBodyList();
	while(node){
		b2Body *b = node;
		node  = node->GetNext();
		if(b->GetUserData()!=NULL){
			if(b->GetPosition().x<-3){
				s = (CCSprite*)b->GetUserData();
				if(s!=NULL){
					s->removeFromParent();
					CCLog("remove");
				}
				this->world->DestroyBody(b);
			}
		}
	}
}

void HelloWorld::addBrid(){
	this->bird = B2Sprite::create("CloseNormal.png");
	CCSize size = this->bird->getContentSize();

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;//动态的
	bodyDef.position = b2Vec2(screenSize.width/2/RATIO,9);
	b2Body *birdBody = this->world->CreateBody(&bodyDef);

	b2PolygonShape birdShape;
	birdShape.SetAsBox(size.width/2/RATIO,size.height/2/RATIO);

	b2FixtureDef birdFixtureDef;
	birdFixtureDef.shape = &birdShape;
	birdBody->CreateFixture(&birdFixtureDef);

	this->bird->setPTMRatio(RATIO);
	this->bird->setB2Body(birdBody);
	this->addChild(this->bird);
}

void HelloWorld::addGround()
{
	B2Sprite *ground = B2Sprite::create("ground1.png");
	CCSize size = ground->getContentSize();


	b2BodyDef bDef;
	bDef.type = b2_staticBody;
	bDef.position = b2Vec2(size.width/2/RATIO,size.height/2/RATIO);
	b2Body *groundBody = this->world->CreateBody(&bDef);

	b2PolygonShape groundShape;
	groundShape.SetAsBox(size.width/2/RATIO,size.height/2/RATIO);

	b2FixtureDef groundFixtureDef;
	groundFixtureDef.shape = &groundShape;
	groundBody->CreateFixture(&groundFixtureDef);

	ground->setB2Body(groundBody);
	ground->setPTMRatio(RATIO);

	this->addChild(ground);
}

void HelloWorld::addBar(float dt)
{
	float offset  = -rand()%5;

	//down bar 

	B2Sprite *down_bar = B2Sprite::create("bar_down.png");
	CCSize down_bar_size = down_bar->getContentSize();

	b2BodyDef down_bar_body_def;
	//类型 运动型
	down_bar_body_def.type = b2_kinematicBody; 
	//设置位置右边 高度 + 偏移
	down_bar_body_def.position = b2Vec2(screenSize.width/RATIO+2,down_bar_size.height/RATIO/2+offset);
	//线性运动向右移动
	down_bar_body_def.linearVelocity = b2Vec2(-5,0);
	//是物理世界元素
	b2Body *down_bar_body = this->world->CreateBody(&down_bar_body_def);

	
	b2PolygonShape down_bar_shape;
	//碰撞图形为盒子
	down_bar_shape.SetAsBox(down_bar_size.width/2/RATIO,
		down_bar_size.height/2/RATIO);
	b2FixtureDef down_bar_fixture_def;
	down_bar_fixture_def.shape = &down_bar_shape;
	//设置碰撞
	down_bar_body->CreateFixture(&down_bar_fixture_def);

	//和b2D绑定起来
	down_bar->setB2Body(down_bar_body);
	down_bar->setPTMRatio(RATIO);
	this->barContainer->addChild(down_bar);

	//up bar 
	B2Sprite *up_bar = B2Sprite::create("bar_up.png");
	CCSize up_bar_size = up_bar->getContentSize();

	b2BodyDef up_bar_body_def;
	//类型 运动型
	up_bar_body_def.type = b2_kinematicBody; 
	//设置位置右边 高度 + 偏移
	up_bar_body_def.position = b2Vec2(screenSize.width/RATIO+2,
		up_bar_size.height/RATIO+offset+2+up_bar_size.height/2/RATIO);
	//线性运动向右移动
	up_bar_body_def.linearVelocity = b2Vec2(-5,0);
	//是物理世界元素
	b2Body *up_bar_body = this->world->CreateBody(&up_bar_body_def);


	b2PolygonShape up_bar_shape;
	//碰撞图形为盒子
	up_bar_shape.SetAsBox(up_bar_size.width/2/RATIO,up_bar_size.height/2/RATIO);
	b2FixtureDef up_bar_fixture_def;
	up_bar_fixture_def.shape = &up_bar_shape;
	//设置碰撞
	up_bar_body->CreateFixture(&up_bar_fixture_def);

	//和b2D绑定起来
	up_bar->setB2Body(up_bar_body);
	up_bar->setPTMRatio(RATIO);
	this->barContainer->addChild(up_bar);

}

void HelloWorld::addBarContainer()
{
	this->barContainer = CCSprite::create();
	this->addChild(this->barContainer);
}

 void HelloWorld::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
 {
	this->bird->getB2Body()->SetLinearVelocity(b2Vec2(0,5));
 }

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}
