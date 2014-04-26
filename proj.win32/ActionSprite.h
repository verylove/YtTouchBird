#pragma once
#include "f:\yt\soft\cocos2d-x-2.2.3\projects\yttouchbird\classes\b2sprite.h"
class ActionSprite :
	public B2Sprite
{
public:

	//飞的方法
	void fly();

	//死亡的方法
	void dead();

	//动作
	CCAction* _flyAction;
	CCAction* _deadAction;
	CCAction* _headAction;


	ActionSprite(void);
	~ActionSprite(void);
};

