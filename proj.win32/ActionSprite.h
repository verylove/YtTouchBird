#pragma once
#include "f:\yt\soft\cocos2d-x-2.2.3\projects\yttouchbird\classes\b2sprite.h"
class ActionSprite :
	public B2Sprite
{
public:

	//�ɵķ���
	void fly();

	//����
	CCAction* _flyAction;


	ActionSprite(void);
	~ActionSprite(void);
};

