#include "Bird.h"
#include "HelloWorldScene.h"


Bird::Bird(void)
{
	groundSize = CCSize(0,0);
}


Bird::~Bird(void)
{
}

void Bird::setGroundSize(CCSize groundsiez)
{
	groundSize = groundsiez;
}

bool Bird::init()
{
	CCSpriteFrame* frame_brid1 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("bird1.png");

	if(!ActionSprite::initWithSpriteFrame(frame_brid1)){
		return false;
	}
	CCSize screenSize = CCDirector::sharedDirector()->getVisibleSize();

	//空闲动作
	CCArray *flyFrames = CCArray::create();
	//this->_flyAction->retain();
	for(int i=1;i<4;i++){
		CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("bird%d.png",i)->getCString());
		flyFrames->addObject(frame);
	}
	CCAnimation* flyAnimation=CCAnimation::createWithSpriteFrames(flyFrames,0.05f);
	this->_flyAction = CCRepeatForever::create(CCAnimate::create(flyAnimation));
	this->_flyAction->retain();

	this->_headAction = CCRepeatForever::create( CCRotateTo::create(1.0f, 90) );
	//this->_headAction =  CCRepeatForever::create( CCBlink::create(10,100));
	this->_headAction->retain();
	
	int height = 0;
	if(this->groundSize.width!=0){
		CCPoint bridPosition = this->getPosition();
		CCSize  groundSize  = this->groundSize;
		height = bridPosition.y;
	}


	//死亡的动作
	this->_deadAction = CCSequence::create(CCMoveBy::create(0.2,ccp(0,height)),NULL);
	this->_deadAction->retain();

	return true;
}
