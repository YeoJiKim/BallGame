#include "Ball.h"
#include "Treasure.h"
#include "rs.h"

Ball::Ball(ofVec2f _ctr,
	float _radius ,/*= 5.0f*/
	ofColor _color,
	ofVec2f _vel /*= ofVec2f(ofRandomf()*5.0f, ofRandom(5.0f, 15.0f))*/,
	float _decrease /*= 0.0f*/,
	int _level) :
	_Center(_ctr),
	_Radius(_radius),
	_DecreaseSpd(_decrease),
	_Velocity(_vel),
	_Color(_color),
	_Level(_level)
	
	
{
	_Center = ofVec2f(ofGetWidth()/2.0f,ofGetHeight()/2.0f);
	_Velocity = ofVec2f();
	 _dragSpd = 5.0f;
	 _dragged = false;//构造函数里初始化数值
	 _pressed=false;
	 _freezed=false;

	
}

void Ball::update(float deltaTime)
{	
   
	
	_Center += _Velocity * deltaTime;
	
	_Radius -= deltaTime * _DecreaseSpd;
  
}
void Ball::update_2(float deltaTime)
{	
   
	//	if(_pressed)
	 //   _Velocity+=_Acc;


	if(!_freezed)
	{
	_Velocity+=_Acc;
	 _Color=ofColor::black;
	  _DecreaseSpd=1.0f;
	
	}
	else
	{
		 _Color=ofColor::blue;
	     _Velocity=ofVec2f(0,0);
		 _DecreaseSpd=0;
		
	}


	_Center += _Velocity * deltaTime;
	
	_Radius -= deltaTime * _DecreaseSpd;
  
}
void Ball::init()
{
	

	ofRectangle Rect(0.0f, 0.0f, ofGetWidth(), ofGetHeight());
	Rect.scaleFromCenter(1.2f);
	if (!Rect.inside(_Center))
	{
		resetPosVel();
	}
}

void Ball::resetPosVel()
{
	_Center.x = ofRandomWidth();
	_Center.y = -10.0f;
	_Velocity = ofVec2f(
		ofRandomf()*100.0f,
		ofRandom(100.0f, 250.0f));
}

void Ball::draw(
	bool bFill /*= true*/)
{
	ofPushStyle();
	if (bFill)
	{
		ofFill();
	}
	else
	{
		ofNoFill();
		ofSetLineWidth(4.0f);
	}
	ofSetColor(_Color);
	ofCircle(_Center, _Radius);

	if (_dragged)
	{
		ofSetColor(ofColor::green);
		ofNoFill();
		ofSetLineWidth(1.5f);
		ofCircle(_Center, _Radius + 5.0f);
	}

	if (_pressed)
	{
		ofSetColor(ofColor::red);
		ofNoFill();
		ofSetLineWidth(1.5f);
		ofCircle(_Center, _Radius + 5.0f);
	}

	ofPopStyle();


}

bool Ball::inside(ofVec2f pos)
{
	ofVec2f Offset = pos - _Center;
	bool bIn = Offset.length() <= _Radius;
	return bIn;
}

bool Ball::contact(Ball another)
{
	ofVec2f Offset = another._Center - _Center;
	bool bContact = Offset.length() <= (_Radius + another._Radius);
	return bContact;
}

bool Ball::outofrange()
{
	ofRectangle R;
	ofRectangle RLevel(0,0,ofGetWidth(),ofGetHeight());
	R=ofRectangle(_Center-ofVec2f(_Radius,_Radius),2*_Radius,2*_Radius);
	if(R.intersects(RLevel))
	{
		return false;
	}
	//SoundDie.play();

	

}
void Ball::dragTo(ofVec2f pos)
{
	ofVec2f Offset = pos - _Center;
	_Velocity = Offset * exp(-_Radius / 20.0f) *_dragSpd;

	_dragged = true;
}


void Ball::dragOff()
{

	_dragged = false;
}



void Ball::accelerate(int key)
{
	_pressed=true;
	switch(key)
	{
		case OF_KEY_LEFT:
			_Acc=ofVec2f(-exp(-_Radius / 20.0f),0);
			//_Velocity =ofVec2f(30*- exp(-_Radius / 20.0f) *_dragSpd,0);
			break;
		case OF_KEY_RIGHT:
			_Acc=ofVec2f(exp(-_Radius / 20.0f),0);
			//_Velocity =ofVec2f(20*exp(-_Radius / 20.0f) *_dragSpd,0);
			break;
		case OF_KEY_UP:
			_Acc=ofVec2f(0,-exp(-_Radius / 20.0f));
			//_Velocity =ofVec2f(0,20*- exp(-_Radius / 20.0f) *_dragSpd);
			break;
		case OF_KEY_DOWN:
			_Acc=ofVec2f(0,exp(-_Radius / 20.0f));
			//_Velocity =ofVec2f(0,20*exp(-_Radius / 20.0f) *_dragSpd);
			break;
	}

}

void Ball::noaccelerate()
{
	_Acc=ofVec2f(0,0);
	_Velocity*=0.99;
	_pressed=false;
}
void Ball::absorb(Ball &another)
{
	bool bContact = contact(another);
	if (bContact)
	{
		another.resetPosVel();	
		if(another._Color == _Color)
			changeRadius("increase");
		else if(another._Color == ofColor::white)
			changeRadius("decrease");
		else 
			changeRadius("disappear");
		
	}
}
bool Ball::absorb(Treasure &another,ofVec2f p)
{

	ofRectangle Trange=another.getRect();
	ofVec2f Tpos=another.getPosition();
	if(Trange.inside(p))
	{
		
	
		return TRUE;
	}
	else
		return FALSE;
}

bool Ball::absorb(Treasure &another)
{
	ofRectangle R;
	R=ofRectangle(_Center-ofVec2f(_Radius,_Radius),2*_Radius,2*_Radius);
	ofRectangle Trange=another.getRect();

	return (R.intersects( Trange));
}

/*bool Ball::absorb(Moving &another)
{
	ofRectangle R;
	R=ofRectangle(_Center-ofVec2f(_Radius,_Radius),2*_Radius,2*_Radius);

	ofRectangle Trange=another.getRect();

	return (R.intersects( Trange));
}*/

void Ball::freeze(float time)
{
	if(time>0)
   
	{
		_freezed=true;
   
	}

	else	
	{
		_freezed=false;
	 }
}

void Ball::changeRadius(
	string change)
{
	float amount = 20.0f / _Radius;
	if (change=="increase")
	{
		_Radius += amount;
	}	
	else if(change=="decrease")
	{
		_Radius -= 5.0f*amount;
	}
	else 
	{	
	 _Radius=PLAYER_RADIUS;
	}
	

	
}
	
float Ball::getRadius()
{
	return _Radius;
}

int Ball::getLevel()
{
	return _Level;
}
ofVec2f Ball::getPos()
{
	return _Center;
}

bool  Ball::updateLive(float time,int money,int target)
{
	bool timeenough=time>0?true:false;
	bool radiusenough=_Radius>0?true:false;
	return((money>target||timeenough)&&radiusenough&&!outofrange());
}
bool  Ball::updateLive(float time)
{
	bool timeenough=time>0?true:false;
	bool radiusenough=_Radius>0?true:false;
	return(timeenough&&radiusenough&&!outofrange());
}
Ball2::Ball2(ofVec2f _ctr /*= ofVec2f()*/, float _radius /*= 5.0f*/, ofColor _color /*= ofColor::black*/, ofVec2f _vel /*= ofVec2f(ofRandomf()*5.0f, ofRandom(5.0f, 15.0f))*/, float _decrease /*= 0.0f*/):
	Ball(_ctr,_radius,_color,_vel,_decrease)
{}

void Ball2::update(float deltaTime)
{
	_Velocity.rotate(ofRandomf()*1000.0f*deltaTime);
	Ball::update(deltaTime);
}
