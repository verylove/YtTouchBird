#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "f:\yt\soft\cocos2d-x-2.2.3\projects\YtTouchBird\proj.win32\Welecome.h"

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
 
	this->down_bar = NULL;
	score = 0;
	this->Xdownbar = 0;
	this->Xbird = 0;
	barTag = 0;

	//加载PLIST
	this->cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	this->cache->addSpriteFramesWithFile("flappy_packer.plist","flappy_packer.png");


	CCSprite *startgame = CCSprite::createWithSpriteFrameName("getready.png");
	startgame->setPosition(ccp(this->screenSize.width/2,this->screenSize.height/2+300));
	addChild(startgame,1);


	//CCMenuItemImage *startgameItemImage = CCMenuItemImage::create("start.png","start.png",this,menu_selector(HelloWorld::gameEndCallback));
	CCMenuItemSprite  *startgameItemImage = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("start.png"),
		CCSprite::createWithSpriteFrameName("start.png"),this,menu_selector(HelloWorld::gameEndCallback));
	CCMenu* menu = CCMenu::create(startgameItemImage,NULL);
	addChild(menu,1);

	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("mp3/fly.mp3");
	 CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("mp3/dead.wav");
	 CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("mp3/score.mp3");

	initWorld();

	addBg();
	addGround(123);
	addBrid();
	gameend = false;
	ispass = false;

	//scheduleOnce(schedule_selector(HelloWorld::startGame),1);
	return true;
}


void HelloWorld::loading()
{
	
}

void HelloWorld::initWorld(){
	this->world = new b2World(b2Vec2(0,-9.8));

	//设置子元素侦听
	this->world->SetContactListener(this);
}

void HelloWorld::startGame( float dt)
{
	delete this->world;
	this->score = 0;
	this->down_bar = NULL;
	this->Xdownbar = 0;
	this->Xbird = 0;
	barTag = 0;
	barArray[0]=false;
	barArray[1]=false;

	isTouch = false;
	gameend = false;

	removeAllChildren();

	setTouchEnabled(true);
	
	initWorld();


	CCLabelAtlas* label2 = CCLabelAtlas::create("0123456789", "1.png", 17, 22, '0');
	addChild(label2, 1, 9);
	label2->setPosition(ccp(this->screenSize.width/2-30,this->screenSize.height/2+360));
	//label2->setColor(ccWHITE);
	label2->setScale(4);
	char string[12] = {0};
	sprintf(string,"%d",this->score);
	label2->setString(string);

	scheduleUpdate();
	schedule(schedule_selector(HelloWorld::addBar),1);
	//scheduleOnce(schedule_selector(HelloWorld::addBar),1);

	addBg();
	addGround(123);
	addBrid();
	addBarContainer();


}

void HelloWorld::endGame()
{

	gameend = true;

	setTouchEnabled(false);

	if(this->bird->getPosition().y>320){
		CCLog("%f",this->bird->getPosition().y);
		this->bird->dead();
	}

	unscheduleUpdate();
	unschedule(schedule_selector(HelloWorld::addBar));

	//this->removeChild(this->bird);

	CCSprite *gameover = CCSprite::createWithSpriteFrameName("gameover.png");
	gameover->setPosition(ccp(this->screenSize.width/2,this->screenSize.height/2));
	gameover->runAction(CCMoveTo::create(0.5f,ccp(this->screenSize.width/2,this->screenSize.height/2+240)));
	addChild(gameover,1,1);

	//CCMenuItemImage *gameoverMenuItem = CCMenuItemImage::create("start.png","start.png",this,menu_selector(HelloWorld::gameEndCallback));
	CCMenuItemSprite  *gameoverMenuItem = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("start.png"),
		CCSprite::createWithSpriteFrameName("start.png"),this,menu_selector(HelloWorld::gameEndCallback));
	CCMenu *menu = CCMenu::create(gameoverMenuItem, NULL);
	//b2BodyDef gameoverMenuItemDef;
	//gameoverMenuItemDef.type = b2_staticBody;
	///gameoverMenuItemDef.position = b2Vec2(this->screenSize.width/2/RATIO,this->screenSize.height/2/RATIO);
	//b2Body *gameoverBody = this->world->CreateBody(&gameoverMenuItemDef);
	//menu->setPosition( CCPointZero );
	menu->setPosition(ccp(this->screenSize.width/2,this->screenSize.height/2-100));
	menu->setOpacity(0);

	CCActionInterval*  move = CCMoveBy::create(0.5, ccp(0,100));
	CCActionInterval*  show = CCFadeIn::create(0.5);
	CCAction*  action = CCSpawn::create( show, move, NULL);
	CCFiniteTimeAction* taction = CCSequence::create(CCDelayTime::create(0.3),action,NULL);

	menu->runAction(taction);
	

	addChild(menu,1,2);
}

//侦听子元素链接开始
void HelloWorld::BeginContact(b2Contact* contact) {
	if(contact->GetFixtureA()->GetBody()->GetUserData()==bird||
	   contact->GetFixtureB()->GetBody()->GetUserData()==bird){
			  CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("mp3/dead.wav");
			  endGame();
		  // CCMessageBox("游戏失败","游戏失败");
	}
}

//侦听子元素链接结束
void HelloWorld::EndContact(b2Contact* contact) { 
	
}

void HelloWorld::update(float dt){
	this->world->Step(dt,8,3);

	float nowRotation = this->bird->getRotation();

	if(isTouch==true){
		isTouch = false;
		this->bird->setRotation(45);
	}else{		
		float birdRotation = nowRotation -2;
		if(birdRotation<-90) birdRotation = -90;
		this->bird->setRotation(birdRotation);
	}
	
	if(gameend==true) this->bird->setRotation(-90);
	
		
	CCSprite *s;
	//遍历棍
	b2Body *node  = this->world->GetBodyList();
	while(node){
		b2Body *b = node;
		node  = node->GetNext();
		if(b->GetUserData()!=NULL){

			//if(b->GetUserData()==this->down_bar){
			//	CCLog("down_bar is :%f \n",this->down_bar->getPositionX());
			//}else if(b->GetUserData()==this->ground){
			//	CCLog("ground is :%f \n",this->ground->getPositionX());
			//}else if(b->GetUserData()==this->ground2){
			//	CCLog("ground2 is :%f \n",this->ground2->getPositionX());
			//}

			if(b->GetUserData()==this->down_bar || b->GetUserData()==this->down_bar2){

				this->Xbird= this->bird->getPosition().x/RATIO;


				this->Xdownbar = b->GetPosition().x;	

				CCSprite* downSprite = (CCSprite*)b->GetUserData();
				int index = downSprite->getTag();

				if(barArray[index]==false && this->Xdownbar<this->Xbird){
					barArray[index]=true;
					//CCLog("== %d",index);
					this->score = this->score + 1;
					char string[12] = {0};
					CCLabelAtlas* label2 = (CCLabelAtlas*)getChildByTag(9);
					sprintf(string, "%d", (int)this->score);
					label2->setString( string ); 
					CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("mp3/score.mp3");

				}

				//CCLog("*** %f , %f\n",this->Xdownbar,this->Xbird);	


				if(b->GetPosition().x<-3){
					s = (CCSprite*)b->GetUserData();
					if(s!=NULL){
						s->removeFromParent();
						CCLog("remove");
					}
					this->world->DestroyBody(b);
				}
			}
			
			if(b->GetUserData()==this->ground){
				if(b->GetPosition().x<0){
					addGround(dt);
				}

			}
		}
	}
	
}

void HelloWorld::addBg()
{
	this->bg = B2Sprite::create("bg.png");
	CCSize size = this->bg->getContentSize();

	b2BodyDef bgBodyDef;
	bgBodyDef.type = b2_staticBody;
	bgBodyDef.position = b2Vec2(size.width/2/RATIO,size.height/2/RATIO);
	b2Body *bgBody = this->world->CreateBody(&bgBodyDef);

	this->bg->setPTMRatio(RATIO);
	this->bg->setB2Body(bgBody);
	addChild(this->bg);
}

void HelloWorld::addBrid(){
	//this->bird = B2Sprite::create("CloseNormal.png");
	//this->bird = B2Sprite::createWithSpriteFrame(this->cache->spriteFrameByName("bird1.png"));
	this->bird = (Bird *)Bird::create();
	

	CCSize size = this->bird->getContentSize();

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;//动态的
	bodyDef.position = b2Vec2(screenSize.width/4/RATIO,5);
	b2Body *birdBody = this->world->CreateBody(&bodyDef);


	b2PolygonShape birdShape;
	birdShape.SetAsBox(size.width/2/RATIO-0.1,size.height/2/RATIO-0.1);

	b2FixtureDef birdFixtureDef;
	birdFixtureDef.shape = &birdShape;
	birdBody->CreateFixture(&birdFixtureDef);

	this->bird->setPTMRatio(RATIO);
	this->bird->setB2Body(birdBody);
	this->addChild(this->bird,2);
	this->bird->fly();
	this->bird->setRotation(0);
}




void HelloWorld::addGround( float dt)
{

	//B2Sprite *ground = B2Sprite::create("ground.png");
	//B2Sprite *ground = B2Sprite::createWithSpriteFrame(this->cache->spriteFrameByName("ground.png"));
	this->ground = B2Sprite::create("ground.png");
	CCSize size = ground->getContentSize();




	b2BodyDef bDef;
	bDef.type = b2_kinematicBody;
	bDef.position = b2Vec2(size.width/2/RATIO,size.height/2/RATIO);
	bDef.linearVelocity = b2Vec2(-3,0);
	b2Body *groundBody = this->world->CreateBody(&bDef);

	b2PolygonShape groundShape;
	groundShape.SetAsBox(size.width/2/RATIO,size.height/2/RATIO);

	b2FixtureDef groundFixtureDef;
	groundFixtureDef.shape = &groundShape;
	groundBody->CreateFixture(&groundFixtureDef);

	this->ground->setB2Body(groundBody);
	this->ground->setPTMRatio(RATIO);

	this->addChild(this->ground);


	this->ground2 = B2Sprite::create("ground.png");


	b2BodyDef bDef2;
	bDef2.type = b2_kinematicBody;
	bDef2.position = b2Vec2(size.width/RATIO,size.height/2/RATIO);
	bDef2.linearVelocity = b2Vec2(-3,0);
	b2Body *groundBody2 = this->world->CreateBody(&bDef2);

	b2PolygonShape groundShape2;
	groundShape2.SetAsBox(size.width/2/RATIO,size.height/2/RATIO);

	b2FixtureDef groundFixtureDef2;
	groundFixtureDef2.shape = &groundShape;
	groundBody2->CreateFixture(&groundFixtureDef2);

	this->ground2->setB2Body(groundBody2);
	this->ground2->setPTMRatio(RATIO);

	this->addChild(this->ground2);

		
}



void HelloWorld::addBar(float dt)
{
	float offset  = -rand()%5;

	if(this->down_bar!=NULL &&this->down_bar->getPosition().x>0){
		//down bar 

		//B2Sprite *down_bar = B2Sprite::create("bar_down.png");

		this->down_bar2 = B2Sprite::createWithSpriteFrame(this->cache->spriteFrameByName("holdback1.png"));


		CCSize down_bar_size = down_bar2->getContentSize();

		b2BodyDef down_bar_body_def;
		//类型 运动型
		down_bar_body_def.type = b2_kinematicBody; 
		//设置位置右边 高度 + 偏移
		down_bar_body_def.position = b2Vec2(screenSize.width/RATIO,down_bar_size.height/RATIO/2+offset);
		//线性运动向右移动
		down_bar_body_def.linearVelocity = b2Vec2(-3,0);
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
		this->down_bar2->setB2Body(down_bar_body);
		this->down_bar2->setPTMRatio(RATIO);

		barArray[1] = false;
		this->down_bar2->setTag(1);
		this->barContainer->addChild(this->down_bar2);
	}else{
		//down bar 

		//B2Sprite *down_bar = B2Sprite::create("bar_down.png");

		this->down_bar = B2Sprite::createWithSpriteFrame(this->cache->spriteFrameByName("holdback1.png"));


		CCSize down_bar_size = down_bar->getContentSize();

		b2BodyDef down_bar_body_def;
		//类型 运动型
		down_bar_body_def.type = b2_kinematicBody; 
		//设置位置右边 高度 + 偏移
		down_bar_body_def.position = b2Vec2(screenSize.width/RATIO,down_bar_size.height/RATIO/2+offset);
		//线性运动向右移动
		down_bar_body_def.linearVelocity = b2Vec2(-3,0);
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
		this->down_bar->setB2Body(down_bar_body);
		this->down_bar->setPTMRatio(RATIO);


		barArray[0] = false;
		this->down_bar->setTag(0);
		this->barContainer->addChild(this->down_bar);
	}
	


	//up bar 
	//B2Sprite *up_bar = B2Sprite::create("bar_up.png");
	B2Sprite *up_bar = B2Sprite::createWithSpriteFrame(this->cache->spriteFrameByName("holdback2.png"));

	CCSize up_bar_size = up_bar->getContentSize();

	b2BodyDef up_bar_body_def;
	//类型 运动型
	up_bar_body_def.type = b2_kinematicBody; 
	//设置位置右边 高度 + 偏移
	up_bar_body_def.position = b2Vec2(screenSize.width/RATIO,
		up_bar_size.height/RATIO+offset+2+up_bar_size.height/2/RATIO);
	//线性运动向右移动
	up_bar_body_def.linearVelocity = b2Vec2(-3,0);
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
	 isTouch = true;

	 this->bird->getB2Body()->ApplyTorque(50.0f);
	 CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("mp3/fly.mp3");
	this->bird->getB2Body()->SetLinearVelocity(b2Vec2(0,5));
 }

 

 void HelloWorld::gameEndCallback(CCObject* pSender)
 {
	 startGame(123);
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
