#include "Treasure.h"
#include "rs.h"

Treasure::Treasure(
		ofVec2f _ctr,// = ofVec2f(ofRandom(0.0f,(float)ofGetWindowWidth()), ofRandom(0.0f,(float)ofGetWindowHeight()))
		ofVec2f _size,
		ofImage* I,
		ofVec2f _vel,
		int _money):
		_tCenter(_ctr),
			_tSize(_size),
			_tImage(I),
			_tVelocity(_vel),
			_tMoney(_money)
			
			
	
{
	
}
void Treasure::draw()
{
	if(_tImage==NULL)
	{
	ofSetRectMode(OF_RECTMODE_CENTER);
	ofRect(_tCenter.x,_tCenter.y,_tSize.x,_tSize.y);
	}
	else
	{
		ofRectangle R;
		R.setFromCenter(_tCenter,_tSize.x,_tSize.y);
		_tImage->draw(R);
	}
}

void Treasure::update(float delatime)
{
	_tCenter+=_tVelocity*delatime;
}


int Treasure::getMoney()
{
	return _tMoney;
}

ofRectangle Treasure::getRect()
{
	ofVec2f P=_tCenter;
	ofRectangle R;
	R.setFromCenter(P,_tSize.x,_tSize.y);
	return R;
}

void Treasure::setSize(ofVec2f s)
{
	_tSize=s;
}

ofImage* Treasure::getImage()
{
	return _tImage;
}

ofVec2f Treasure::getPosition()
{
	return _tCenter;
}

void Treasure::setPosition(ofVec2f P)
{
	_tCenter=P;
}

//void Treasure::erase(Treasure another)
//{
//	delete another;
//}

Moving::Moving(ofVec2f _ctr ,
		ofVec2f _size,
		ofImage* I,
		ofVec2f _vel ):
         Treasure(_ctr,_size,I,_vel)
{
}

void  Moving::update(float deltaTime)
{
	_tVelocity.rotate(ofRandomf()*1000.0f*deltaTime);
	Treasure::update(deltaTime);
}

void Moving::resetPosVel()
{
	_tCenter.x = ofRandomWidth();
	_tCenter.y = -10.0f;
	_tVelocity = ofVec2f(
		ofRandomf()*100.0f,
		ofRandom(100.0f, 250.0f));
}