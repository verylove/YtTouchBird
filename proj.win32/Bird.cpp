#include "Bird.h"



Bird::Bird(void)
{
}


Bird::~Bird(void)
{
}

bool Bird::init()
{
	CCSpriteFrame* frame_brid1 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("bird1.png");

	if(!ActionSprite::initWithSpriteFrame(frame_brid1)){
		return false;
	}

	//¿ÕÏĞ¶¯×÷
	CCArray *flyFrames = CCArray::create();
	//this->_flyAction->retain();
	for(int i=1;i<4;i++){
		CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("bird%d.png",i)->getCString());
		flyFrames->addObject(frame);
	}
	CCAnimation* flyAnimation=CCAnimation::createWithSpriteFrames(flyFrames,0.05f);
	this->_flyAction = CCRepeatForever::create(CCAnimate::create(flyAnimation));
	this->_flyAction->retain();
	
	return true;
}
