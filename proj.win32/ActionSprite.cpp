#include "ActionSprite.h"


ActionSprite::ActionSprite(void)
{
	this->_flyAction = NULL;
}


ActionSprite::~ActionSprite(void)
{
}

void ActionSprite::fly()
{
	if(this->_flyAction!=NULL){
		this->runAction(this->_flyAction);
	}


}