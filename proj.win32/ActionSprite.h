#pragma once
#include "f:\yt\soft\cocos2d-x-2.2.3\projects\yttouchbird\classes\b2sprite.h"
class ActionSprite :
	public B2Sprite
{
public:

	//�ɵķ���
	void fly();

	//�����ķ���
	void dead();

	//����
	CCAction* _flyAction;
	CCAction* _deadAction;
	CCAction* _headAction;


	ActionSprite(void);
	~ActionSprite(void);
};

