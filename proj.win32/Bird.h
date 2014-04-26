#pragma once

#include "ActionSprite.h"


class Bird :
	public ActionSprite
{
	

public:

	CCSize groundSize;

	void setGroundSize(CCSize); 

	Bird(void);

	~Bird(void);
	

	CREATE_FUNC(Bird);

	virtual bool init();

};

