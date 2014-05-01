#pragma once
#include "cocos2d.h"

USING_NS_CC;

class Welecome :	public cocos2d::CCLayer
{
public:

	CREATE_FUNC(Welecome);
	virtual bool init();
	virtual void update(float dt);
	//virtual void onEnter();
	static cocos2d::CCScene* scene();
	void Qiehuan(float dt);

public:
	Welecome(void);
	~Welecome(void);
};

