/************************************************************
************************************************************/
#pragma once

/************************************************************
************************************************************/
#include "ofMain.h"
#include "ofxArtnet.h"
#include "ofxGui.h"
#include "ofxNetwork.h"
#include "ofxOsc.h"

#include "sjCommon.h"



/************************************************************
************************************************************/

/**************************************************
**************************************************/
class OSC_SEND{
private:
	char IP[BUF_SIZE];
	int Port;

	ofxOscSender sender;
	
public:
	OSC_SEND(const char* _IP, int _Port)
	{
		if(_Port != -1){
			sprintf(IP, "%s", _IP);
			Port = _Port;
			
			sender.setup(IP, Port);
		}
	}
	
	void sendMessage(ofxOscMessage &message)
	{
		if(Port != -1){
			sender.sendMessage(message);
		}
	}
};

class OSC_RECEIVE{
private:
	int Port;
	ofxOscReceiver	receiver;
	
public:
	OSC_RECEIVE(int _Port)
	{
		if(_Port != -1){
			Port = _Port;
			receiver.setup(Port);
		}
	}
	
	bool hasWaitingMessages()
	{
		if(Port == -1){
			return false;
		}else{
			return receiver.hasWaitingMessages();
		}
	}
	
	bool getNextMessage(ofxOscMessage *msg)
	{
		if(Port == -1){
			return false;
		}else{
			return receiver.getNextMessage(msg);
		}
	}
};

class OSC_TARGET{
private:
public:
	OSC_SEND	OscSend;
	OSC_RECEIVE	OscReceive;
	
	OSC_TARGET(const char* _SendTo_IP, int _SendTo_Port, int _Receive_Port)
	: OscSend(_SendTo_IP, _SendTo_Port), OscReceive(_Receive_Port)
	{
	}
};

/**************************************************
**************************************************/
class ofApp : public ofBaseApp{
private:
	/****************************************
	****************************************/
	enum BOOT_MODE{
		MODE_TEST,
		MODE_DEMO,
		
		NUM_MODES,
	};
	enum STATE_TESTMODE{
		STATE_TESTMODE__WAIT_START,
		STATE_TESTMODE__DO_TEST,
	};
	
	enum{
		WIDTH = 300,
		HEIGHT = 400,
	};
	enum{
		UDP_RECEIVE_PORT = 12347,
		SIZE_UPD = 100000,
	};
	
	/****************************************
	****************************************/
	/********************
	********************/
	BOOT_MODE BootMode;
	
	ofxUDPManager udpConnection;
	ofxArtnet artnet;
	
	bool b_1stMessage;
	
	ofTrueTypeFont font;
	
	/********************
	********************/
	ofxPanel gui;
	ofxIntSlider dimmer_Fixed;
	ofxIntSlider dimmer_Moving;
	ofxIntSlider dimmer_Nakano;
	
	bool b_DispGui;
	
	/********************
	********************/
	STATE_TESTMODE StateTestMode;
	
	float t_TestIntervalFrom;
	
	const int LedId_TestFrom;
	const float T_MOVE_TO_LIGHT_POS;
	const float T_TEST_INTERVAL;
	
	
	/****************************************
	****************************************/
	void Send_AllZero_to_AllOde();
	void draw_test();
	void draw_demo();
	void draw_time(double FrameRate);
	
public:
	/****************************************
	****************************************/
	ofApp(int _BootMode);
	~ofApp();
	
	void setup();
	void update();
	void draw();
	void exit();

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
		
};
