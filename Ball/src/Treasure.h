#pragma once
#include "ofMain.h"
class Treasure
{
public:
	Treasure(
		ofVec2f _ctr = ofVec2f(ofRandom(0.0f,(float)ofGetWindowWidth()), ofRandom(0.0f,(float)ofGetWindowHeight())),
		ofVec2f _size=ofVec2f(20,20),
		ofImage* I=NULL,
		ofVec2f _vel =ofVec2f(0,0),
		int _money=1
		);

public:
		
	void draw();
	virtual void update(float deltaTime);
	void  setPosition(ofVec2f P);
	void setSize(ofVec2f s);
	//void erase(Treasure another);

	ofImage* getImage();
	ofRectangle getRect();// 获得所在的矩形范围
	ofVec2f getPosition();
	int getMoney();
protected:
	ofVec2f _tCenter;
	ofVec2f _tSize;
	ofImage* _tImage;
	ofVec2f _tVelocity;
public:

	int _tMoney;
};


class Moving :public Treasure{
public:
	Moving(ofVec2f _ctr = ofVec2f(ofRandom(0.0f,(float)ofGetWindowWidth()),0),
		ofVec2f _size=ofVec2f(20,20),
		ofImage* I=NULL,
		ofVec2f _vel = ofVec2f(ofRandomf()*5.0f, ofRandom(5.0f, 15.0f)));

	void resetPosVel();
	virtual void update(float deltaTime) override;
protected:
	
	
	
};