#include "ActionSprite.h"


ActionSprite::ActionSprite(void)
{
	this->_flyAction = NULL;
	this->_deadAction = NULL;
}


ActionSprite::~ActionSprite(void)
{
}

void ActionSprite::fly()
{
	if(this->_flyAction!=NULL){
		this->runAction(this->_flyAction);
		//this->runAction(this->_headAction);
	}


}

void ActionSprite::dead()
{
	if(this->_deadAction!=NULL){
		this->stopAction(_flyAction);
		//this->stopAction(_headAction);
		this->runAction(this->_deadAction);
	}
}