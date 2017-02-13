#pragma once

#include "ofMain.h"


class Ball;
class Treasure;
class Moving;

class ofDragBall2App : public ofBaseApp{
private:
	ofPtr<Ball> ptrPlayerBall;
	vector<ofPtr<Ball>> Balls;

	vector<ofPtr<Treasure>> Diamonds;
	vector<ofPtr<Moving>>  Hearts;
	vector<ofPtr<Moving>>  Snows;
	// interaction
	bool _MouseLeftDragging;
	bool _KeyPressed;
	ofVec2f _PrevMousePos;
	ofVec2f _ReleaseMousePos;
	int _Key;
	// text
	ofTrueTypeFont _Font;
	ofTrueTypeFont _OverFont;

	// player performance
	float _PlayTime;
	float _LeftTime;
	float _FrozenTime;

	int _PlayMoney;////////////diamond
	int _PlayLevel;//////////level
	int _PlayTarget;///////target

	bool _Win;

	bool _RunningSC;////S����ģʽ
	bool _RunningCG;////����ģʽ

	bool _Choose;

	bool _TextSC;
	bool _TextCG;

	int flag;
	/////background

	ofImage ImgBg;
	
	ofImage ImgDeadBg;
	ofImage ImgWinBg;
	ofImage ImgNextBg;
	ofImage ImgStartBg;
	

	ofImage ImgButtonSC;
	ofImage ImgButtonCG;

	ofImage ImgDia;
	ofImage ImgGem;
	ofImage ImgHea;
	ofImage ImgSno;
	
	ofRectangle RectStartSC;
	ofRectangle RectStartCG;
	///////sound
	ofSoundPlayer SoundBG;

	ofSoundPlayer SoundDie;
	ofSoundPlayer SoundNex;
	ofSoundPlayer SoundWin;

	ofSoundPlayer SoundSeconds;
	ofSoundPlayer SoundEatDia;
	ofSoundPlayer SoundEatSno;
	ofSoundPlayer SoundEatHea;
	
	///////windowsize
	float _WindowH;
	float _WindowW;

	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		void resetGame();/////�������¿�ʼ��Ϸ
		void drawStartBg();/////��ʼѡ��
		void drawElapseTime(); /////��Ϸ�����е�����
		void drawGameOver();//////��Ϸ����
		void drawWinBg();//////������Ϸʤ��
	    void upgrade();///////��Ϸ����
		void createheart();
		void createsnow();
};
