#include "ofDragBall2App.h"
#include "Ball.h"
#include "Treasure.h"
#include "rs.h"
#include "math.h"
//--------------------------------------------------------------
void ofDragBall2App::setup(){

	_WindowH=ofGetWindowHeight();
	_WindowW=ofGetWindowWidth();
	///////////////////bg
	ImgBg.loadImage("bg.jpg");
	ImgDeadBg.loadImage("deadbg.jpg");
	ImgWinBg.loadImage("winbg.jpg");
	ImgStartBg.loadImage("startbg.jpg");

	ImgButtonSC.loadImage("buttonsc.png");
	ImgButtonCG.loadImage("buttoncg.png");

	ImgDia.loadImage("diamond.png");
	ImgGem.loadImage("gem.png");
	ImgHea.loadImage("heart.png");
	ImgSno.loadImage("snow.png");
	///////////////////sound
	SoundBG.loadSound("bg.mp3");
	SoundBG.setLoop(true);
	SoundBG.setVolume(0.5f);
	SoundBG.play();

	SoundDie.loadSound("die.mp3");
	SoundDie.setVolume(0.7f);
	SoundDie.setLoop(false);
	SoundDie.setMultiPlay(true);

	SoundNex.loadSound("next.mp3");
	SoundNex.setVolume(0.5f);
	SoundNex.setLoop(false);
	SoundNex.setMultiPlay(true);

	SoundWin.loadSound("win.mp3");
	SoundWin.setVolume(0.5f);
	SoundWin.setLoop(false);
	SoundWin.setMultiPlay(true);

	SoundEatDia.loadSound("eatdia.mp3");
	SoundEatDia.setVolume(0.5f);
	SoundEatDia.setLoop(false);
	SoundEatDia.setMultiPlay(true);

	SoundEatHea.loadSound("eathea.mp3");
	SoundEatHea.setVolume(0.5f);
	SoundEatHea.setLoop(false);
	SoundEatHea.setMultiPlay(true);

	SoundEatSno.loadSound("eatsno.mp3");
	SoundEatSno.setVolume(0.5f);
	SoundEatSno.setLoop(false);
	SoundEatSno.setMultiPlay(true);

	SoundSeconds.loadSound("sec.mp3");
	SoundSeconds.setVolume(0.5f);
	SoundSeconds.setLoop(false);
	SoundSeconds.setMultiPlay(true);
	///////////////font
	_Font.loadFont("vag.ttf", 24);
	_OverFont.loadFont("vag.ttf", 50);
	///////////////game
	_PlayMoney=0;
	_PlayLevel=1;

	_Choose=false;
	_RunningSC=false;
	_RunningCG=false;

	_TextSC=false;
	_TextCG=false;
	resetGame();
	

}

//--------------------------------------------------------------
void ofDragBall2App::update(){
	float deltaTime = ofGetLastFrameTime();

	float playerBallRadius = ptrPlayerBall->getRadius();
	float timeout=_LeftTime;

	

	if(_Choose)
	{
		if (_RunningCG||_RunningSC)

	{
		

		if(!ptrPlayerBall->updateLive(timeout))
		{
			_RunningSC=false;
			SoundDie.play();
		}


		createheart();
		createsnow();

		ptrPlayerBall->update_2(deltaTime);
		

		for(ofPtr<Ball> ball: Balls)
		{
			ball->update(deltaTime);
			ptrPlayerBall->absorb(*ball);

			ball->init();
			
		}

	      

	     for(int i=0;i<Hearts.size();i++)
	    {
			Hearts[i]->update(deltaTime);
			  if(ptrPlayerBall->absorb(*Hearts[i]))
			{
				
				ptrPlayerBall->changeRadius("+");

				 SoundEatHea.play();

				 Hearts.erase(Hearts.begin()+i);
					
			}
		}

	     for(int i=0;i<Snows.size();i++)
	    {
			Snows[i]->update(deltaTime);
			  if(ptrPlayerBall->absorb(*Snows[i]))
			{
				_FrozenTime=3;
				SoundEatSno.play();
				Snows.erase(Snows.begin()+i);
					
			}
		}		 
		
		if (_MouseLeftDragging)
		{
			ptrPlayerBall->dragTo(_PrevMousePos);
		}
		

		if(_KeyPressed)
		{
			ptrPlayerBall->accelerate(_Key);
		}
		else
			ptrPlayerBall->noaccelerate();

		_PlayTime += deltaTime;

		if(_FrozenTime>0)
		  {
			  _FrozenTime-= deltaTime;
		       ptrPlayerBall->freeze(_FrozenTime);
		    }

		if(_RunningCG)
		{
			if(!ptrPlayerBall->updateLive(timeout,_PlayMoney,_PlayTarget))
		{
			_RunningCG=false;
			SoundDie.play();
		}
			_LeftTime=60.0f-_PlayTime;
	     
		
		for(int i=0;i<Diamonds.size();i++)
	      {
			  if(ptrPlayerBall->absorb(*Diamonds[i]))
			{
			
				_PlayMoney+=Diamonds[i]->getMoney();

				SoundEatDia.play();

				Diamonds.erase(Diamonds.begin()+i);
			}
		}
		upgrade(); 
		}
	}

}	

}

//--------------------------------------------------------------
void ofDragBall2App::draw(){
	/////显示背景

	
	if(_Choose)
    {
	
	 if(_RunningCG||_RunningSC )
	{
		ImgBg.draw(0,0,ofGetWidth(),ofGetHeight());
		ptrPlayerBall->draw();
		for(ofPtr<Ball> ball: Balls)
		{
			ball->draw(false);			
		}

		for(ofPtr<Moving> heart:Hearts)
		{
			heart->draw();
		}

		for(ofPtr<Moving> snow:Snows)
		{
			snow->draw();
		}

		if(_RunningCG)
		{

		 

			for(ofPtr<Treasure> treasure:Diamonds)
			{
			treasure->draw();
			}
		}

	}
	
	else if(_Win)
	{
		  drawWinBg(); 
	}

	else
	{
		drawGameOver();
	}
	
	
	if(!_Win)
	{
	   drawElapseTime();
	}


	}

	else
	{
		drawStartBg();
	}
	
}
void ofDragBall2App::drawWinBg(){

	
	ImgWinBg.draw(0,0,ofGetWidth(),ofGetHeight());

	ofPushStyle();
	ofSetColor(ofColor::black);
	string GameWinString = "You Win";
	float txtWidth = _OverFont.stringWidth( GameWinString);
	ofSetHexColor(0xffffff);
	_OverFont.drawString( GameWinString, ofGetWidth() / 2.0f - txtWidth / 2.0f, ofGetHeight() / 2.0f);
	ofSetColor(255,122,220);
	_OverFont.drawString( GameWinString, ofGetWidth() / 2.0f - txtWidth / 2.0f +2, ofGetHeight() / 2.0f+2);
	ofPopStyle();

	ofPushStyle();
	ofSetColor(ofColor::red);
	string GameResetString="F1:Restart";
	_Font.drawString(GameResetString,20,ofGetHeight()-35);
	ofPopStyle();


}

void ofDragBall2App::drawStartBg()
{
	RectStartCG=ofRectangle(ofPoint(ofGetWidth() / 2.0f ,0.5*ofGetHeight()),100,50);
	RectStartSC=ofRectangle(ofPoint(ofGetWidth() / 2.0f ,0.5*ofGetHeight()+60),100,50);


	ImgStartBg.draw(0,0,ofGetWidth(),ofGetHeight());

	 string txtStringCG="Stage：";
	 float txtWidthCG = _Font.stringWidth(txtStringCG);

	 string txtStringSC="Survive：";
	 float txtWidthSC = _Font.stringWidth(txtStringSC);

	 ofPushStyle();
	 ofSetHexColor(0xffffff);
	 _Font.drawString(txtStringCG, ofGetWidth() / 2.0f-100, 0.5*ofGetHeight()+30);
	 ofSetColor(255,122,220);
	 _Font.drawString(txtStringCG, ofGetWidth() / 2.0f-100 +2, 0.5*ofGetHeight()+30);

	 ofSetHexColor(0xffffff);
	 _Font.drawString(txtStringSC, ofGetWidth() / 2.0f-100  , 0.5*ofGetHeight()+60+30);
	 ofSetColor(255,122,220);
	 _Font.drawString(txtStringSC, ofGetWidth() / 2.0f-100 +2, 0.5*ofGetHeight()+60+30);
	 ofPopStyle();
	
	
	ImgButtonCG.draw(RectStartCG);
	ImgButtonSC.draw(RectStartSC);
}



void ofDragBall2App::drawElapseTime()
{
	
	string _TimeCG=ofToString(int(_LeftTime*100)/100.0f);
	string _TimeSC=ofToString(int(_PlayTime*100)/100.0f);
	string _FTime=ofToString(int(_FrozenTime*100)/100.0f);

	ofPushStyle();
	if(_TextCG)
	{ofSetHexColor(0xffffff);
	_Font.drawString("Time:"+ofToString(_TimeCG), 10.0f, 30.0f);
	ofSetColor(255,122,220);
	_Font.drawString("Time:"+ofToString(_TimeCG), 12.0f, 32.0f);
	ofSetHexColor(0xffffff);
	_Font.drawString("Mode:Stage",ofGetWindowWidth()-200.0f, 30.0f);
	ofSetColor(255,122,220);
	_Font.drawString("Mode:Stage",ofGetWindowWidth()-198.0f, 32.0f);
	ofSetHexColor(0xffffff);
	_Font.drawString("Target:"+ofToString(_PlayTarget), ofGetWindowWidth()-200.0f-50, 60.0f+10);
	ofSetColor(255,122,220);
	_Font.drawString("Target:"+ofToString(_PlayTarget), ofGetWindowWidth()-198.0f-50, 62.0f+10);
	ofSetHexColor(0xffffff);
	_Font.drawString("Level:"+ofToString(_PlayLevel),ofGetWindowWidth()-200.0f-100, 90.0f+20);
	ofSetColor(255,122,220);
	_Font.drawString("Level:"+ofToString(_PlayLevel), ofGetWindowWidth()-198.0f-100, 92.0f+20);
	ofSetHexColor(0xffffff);
	_Font.drawString("Score:"+ofToString(_PlayMoney),60.0f,60.0f+10);
	ofSetColor(255,122,220);
	_Font.drawString("Score:"+ofToString(_PlayMoney),62.0f,62.0f+10);

	ofSetHexColor(0xffffff);
	_Font.drawString("FrozenTime:"+ofToString(_FTime),110.0f,90.0f+20);
	ofSetColor(255,122,220);
	_Font.drawString("FrozenTime:"+ofToString(_FTime),112.0f,92.0f+20);
	}

	string _RadiusSC=ofToString(int(ptrPlayerBall->_Radius*100)/100.0f);
	if(_TextSC)
	{
	ofSetHexColor(0xffffff);
	_Font.drawString("Time:"+ofToString(_TimeSC), 10.0f, 30.0f);
	ofSetColor(255,122,220);
	_Font.drawString("Time:"+ofToString(_TimeSC), 12.0f, 32.0f);
	ofSetHexColor(0xffffff);
	_Font.drawString("Mode:Survive",ofGetWindowWidth()-200.0f, 30.0f);
	ofSetColor(255,122,220);
	_Font.drawString("Mode:Survive",ofGetWindowWidth()-198.0f, 32.0f);
	ofSetHexColor(0xffffff);
	_Font.drawString("Radius:"+ofToString(_RadiusSC), ofGetWindowWidth()-200.0f-50, 60.0f+10);
	ofSetColor(255,122,220);
	_Font.drawString("Radius:"+ofToString(_RadiusSC), ofGetWindowWidth()-198.0f-50, 62.0f+10);
	ofSetHexColor(0xffffff);
	_Font.drawString("FrozenTime:"+ofToString(_FTime),60.0f,60.0f+10);
	ofSetColor(255,122,220);
	_Font.drawString("FrozenTime:"+ofToString(_FTime),62.0f,62.0f+10);
	}
	
	
	
	
	ofPopStyle();
}

//--------------------------------------------------------------
void ofDragBall2App::keyPressed(int key){
	_KeyPressed=true;
	_Key=key;
	switch(key)
	{
	
	case OF_KEY_F1:
		_Choose=true;
		if(flag==1)
		{
			_RunningCG=true;
			_RunningSC=false;
		}
		if(flag==0)
		{
			_RunningCG=false;
			_RunningSC=true;

		}

		_PlayMoney=0;
	    _PlayLevel=1;
		resetGame();
		break;
	case OF_KEY_F2:
		
		_Choose=false;
		_RunningCG=false;
		_RunningSC=false;
		_TextCG=false;
		_TextSC=false;

		
		_PlayMoney=0;
	    _PlayLevel=1;
		resetGame();

		
		break;
	default:
		break;
	}

}

//--------------------------------------------------------------
void ofDragBall2App::keyReleased(int key){
	_KeyPressed=false;
	
}

//--------------------------------------------------------------
void ofDragBall2App::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofDragBall2App::mouseDragged(int x, int y, int button){
	_PrevMousePos = ofVec2f(x, y);	

}

//--------------------------------------------------------------
void ofDragBall2App::mousePressed(int x, int y, int button){
	if(_RunningCG)
	{
	 _MouseLeftDragging =((button == 0)&&_PlayLevel>1);
	 _PrevMousePos = ofVec2f(x, y);
	}
	if(_RunningSC)
	{
	_MouseLeftDragging =((button == 0));
	 _PrevMousePos = ofVec2f(x, y);
	}

}

//--------------------------------------------------------------
void ofDragBall2App::mouseReleased(int x, int y, int button){

	
	if (button == 0)
	{   
		_MouseLeftDragging = false;	
		ptrPlayerBall->dragOff();

		if(!_Choose)
		{
		if(RectStartCG.inside(x,y))
		{
			_Choose=true;
			_RunningCG=true;
			_RunningSC=false;
			_TextSC=false;
	         _TextCG=true;
			 flag=1;
		}

		if(RectStartSC.inside(x,y))
		{
			_Choose=true;
			_RunningSC=true;
			_RunningCG=false;
			_TextSC=true;
	        _TextCG=false;
			flag=0;
		}
		}
	}
	
	
}

//--------------------------------------------------------------
void ofDragBall2App::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofDragBall2App::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofDragBall2App::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofDragBall2App::gotMessage(ofMessage msg){

}


void ofDragBall2App::drawGameOver()
{
	if(_TextCG)
	{
	ImgDeadBg.draw(0,0,ofGetWidth(),ofGetHeight());
	ofPushStyle();
	ofSetColor(ofColor::black);
	string GameOverString = "You Lose";
	float txtWidth = _OverFont.stringWidth(GameOverString);
	_OverFont.drawString(GameOverString, ofGetWidth() / 2.0f - txtWidth / 2.0f, ofGetHeight() / 2.0f);
	ofPopStyle();
	}

	if(_TextSC)
	{
	ImgWinBg.draw(0,0,ofGetWidth(),ofGetHeight());
	ofPushStyle();
	ofSetColor(ofColor::black);
	string _TimeSC=ofToString(int(_PlayTime*100)/100.0f);
	string RecordString = "Your Record  "+_TimeSC;
	float txtWidthR= _OverFont.stringWidth(RecordString);
	_OverFont.drawString(RecordString, ofGetWidth() / 2.0f - txtWidthR / 2.0f, ofGetHeight() / 2.0f);


	ofPopStyle();
	}

	ofPushStyle();
	ofSetColor(ofColor::red);
	string GameResetString="F1:Restart";
	_Font.drawString(GameResetString,20,ofGetHeight()-35);
	ofPopStyle();

	ofPushStyle();
	//ofSetColor(ofColor::red);
	//string GameMenuString="F2:Menu";
	//_Font.drawString(GameMenuString,ofGetWidth()-150,ofGetHeight()-35);
	ofPopStyle();
}

//--------------------------------------------------------------
void ofDragBall2App::dragEvent(ofDragInfo dragInfo){ 

}

void ofDragBall2App::resetGame(){

	_MouseLeftDragging = false;
	_PlayTime=0.0f;
	_LeftTime=60.f;
	_KeyPressed=false;

	
	_Win=FALSE;

	//_Running=TRUE;
	_FrozenTime=0;
	

	 _PlayTarget=10*_PlayLevel;


	if(!Balls.empty())
	{
		Balls.clear();
	}
	if(!Diamonds.empty())
	{
		Diamonds.clear();
	}

	if(!Hearts.empty())
	{
		Hearts.clear();
	}

	if(!Snows.empty())
	{
		Snows.clear();
	}

	ptrPlayerBall.reset(new Ball(ofVec2f(ofGetWidth() / 2.0f, ofGetHeight() - 2*PLAYER_RADIUS), PLAYER_RADIUS,
		ofColor::black,
		ofVec2f(0.0f,0.0f),
		1.0f));

	for (int i = 0; i < BALL_AMOUNT*_PlayLevel; i++)
	{
		ofPtr<Ball> pBall;
		
		ofColor cr;


		if(i<BALL_AMOUNT*0.7)
		cr=ofColor::white;///碰到就缩小半径
		else 
			cr=ofColor::black;///碰到增大半径
		
		if (ofRandom(1.0f)>0.75f)
		{
			pBall.reset(new Ball(ofVec2f(ofRandomWidth(), -10.0f), 5.0f, cr));
		}
		else
		{
			pBall.reset(new Ball2(ofVec2f(ofRandomWidth(), -10.0f), 5.0f, cr));
	      
		
		}
	
		pBall->resetPosVel();
		Balls.push_back(pBall);
	
	}

	for(int i=0;i<TREASURE_AMOUNT;i++)
	{
		ofPtr<Treasure> pTreasure;

		if (ofRandom(1.0f)<0.85f)
		{
		pTreasure.reset(new Treasure(
			ofVec2f(ofRandom(10.0f,(float)ofGetWindowWidth()-10), ofRandom(120.0f,(float)ofGetWindowHeight()-2.5*PLAYER_RADIUS)),
			ofVec2f(30,30),
			&ImgDia,
			ofVec2f(0,0),
			1));
		}

		else
		{
		pTreasure.reset(new Treasure(
			ofVec2f(ofRandom(10.0f,(float)ofGetWindowWidth()-10), ofRandom(120.0f,(float)ofGetWindowHeight()-2.5*PLAYER_RADIUS)),
			ofVec2f(30,30),
			&ImgGem,
			ofVec2f(0,0),
			2));
		}

		Diamonds.push_back(pTreasure);
	}

	
}


void ofDragBall2App::createheart()
{
	
		float rn = ofRandom(0,100);
	
		float Probability = 1.0f - exp(-0.001f*_PlayTime);
		Probability *= 20.0f;
		 ofPtr<Moving> pHeart;
		if (rn<Probability)
		{
		  pHeart.reset(new Moving(ofVec2f(ofRandom(0.0f,(float)ofGetWindowWidth()),0.0f),
					  ofVec2f(20,20),
					  &ImgHea,
					  ofVec2f(ofRandomf()*5.0f, ofRandom(5.0f, 15.0f))));
		  pHeart->resetPosVel();
		  Hearts.push_back(pHeart);
		}	
	
}
void ofDragBall2App::createsnow()
{
	float rn = ofRandom(0,100);
	
	float Probability = 1.0f - exp(-0.001f*pow(10,_PlayLevel-1)*_PlayTime);
		Probability *= 10.0f;
		 ofPtr<Moving> pSnow;
		if (rn<Probability)
		{
		  pSnow.reset(new Moving(ofVec2f(ofRandom(0.0f,(float)ofGetWindowWidth()),0.0f),
					  ofVec2f(30,30),
					  &ImgSno,
					  ofVec2f(ofRandomf()*5.0f, ofRandom(5.0f, 15.0f))));
		 pSnow->resetPosVel();
		  Snows.push_back(pSnow);
		}
}

void ofDragBall2App::upgrade()
{
	if(_PlayLevel< FINAL_LEVEL)
	{
		if(_PlayMoney>=_PlayTarget)
		{
			_PlayLevel+=ptrPlayerBall->getLevel();
			SoundNex.play();
			resetGame();

			
		}
	}
	if(_PlayMoney>=_PlayTarget&&_PlayLevel== FINAL_LEVEL)
	{
		
		_RunningCG=FALSE;
		
		_Win=TRUE;
		SoundWin.play();
	}
}

