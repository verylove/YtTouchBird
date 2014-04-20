#pragma once

#include "ActionSprite.h"


class Bird :
	public ActionSprite
{
	

public:
	Bird(void);

	~Bird(void);
	

	CREATE_FUNC(Bird);

	virtual bool init();

};

