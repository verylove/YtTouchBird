#pragma once
#include "f:\yt\soft\cocos2d-x-2.2.3\projects\yttouchbird\classes\b2sprite.h"
class ActionSprite :
	public B2Sprite
{
public:

	//飞的方法
	void fly();

	//动作
	CCAction* _flyAction;


	ActionSprite(void);
	~ActionSprite(void);
};

