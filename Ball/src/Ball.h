#pragma once

#include "ofMain.h"

class Treasure;
class Moving;

class Ball
{
public:
	Ball(ofVec2f _ctr = ofVec2f(),
		float _radius = 5.0f,
		ofColor _color = ofColor::black,
		ofVec2f _vel = ofVec2f(ofRandomf()*5.0f, ofRandom(5.0f, 15.0f)),
		float _decrease = 0.0f,
		int _level=1);

	virtual void update(float deltaTime);
	void update_2(float deltaTime);
	void init();
	void resetPosVel();
	void draw(bool bFill = true);
	bool inside(ofVec2f pos);
	bool contact(Ball another);
	void dragTo(ofVec2f pos);
	void dragOff();
	void absorb(Ball &another);
	bool absorb(Treasure &another,ofVec2f p);
	bool absorb(Treasure &another);
	//bool absorb(Moving &another);
	void freeze(float time);
	void changeRadius(string change);
	void changeLife(string change);
	float getRadius();
	void accelerate(int key);
	void noaccelerate();
	ofVec2f getPos();
	int getMoney();
	bool outofrange();
	bool updateLive(float time,int money,int target);
	bool updateLive(float time);
	int getLevel();



	//ofSoundPlayer SoundDie;
protected:
	
	
	float _DecreaseSpd;
	ofVec2f _Velocity;
	ofColor _Color;
	float _dragSpd;
	


	bool _dragged;
	bool _pressed;
	bool _freezed;

	ofVec2f _Acc;//玩家加速度
public:
	ofVec2f _Center;
	float _Radius;
	int _Level;
};


class Ball2 : public Ball
{
public:
	Ball2(ofVec2f _ctr = ofVec2f(),
		float _radius = 5.0f,
		ofColor _color = ofColor::black,
		ofVec2f _vel = ofVec2f(ofRandomf()*5.0f, ofRandom(5.0f, 15.0f)),
		float _decrease = 0.0f);
	virtual void update(float deltaTime) override;
};






