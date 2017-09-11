/************************************************************
test modeにて以下の場合は、"SJ"をsearchして変更
	t_intervalを変更
	check color change
	check するline(or lineの途中からでも対応可)を変更
		どこか1箇所をtestするなら、
			update()内の"LedTest.LedId++"
		をコメントアウト.

************************************************************/
#include "ofApp.h"

/************************************************************
************************************************************/
enum{
	SIZE_DMX_UNIVERSE = 512,
};

enum LED_DEVICE_TYPE{
	LED_DEVICE_TYPE_FIXED,
	LED_DEVICE_TYPE_MOVING,
	
	LED_DEVICE_TYPE_N_WALLWASHER,
	LED_DEVICE_TYPE_N_BALL,
};

/************************************************************
private class
************************************************************/
class ODE{
private:
	char ch_IP[BUF_SIZE];
	
public:
	unsigned char universe[SIZE_DMX_UNIVERSE];
	
	ODE(const char* _ch_IP)
	{
		strcpy(ch_IP, _ch_IP);
	}
	const char* get_IP()
	{
		return ch_IP;
	}
};

struct LED_PARAM{
	int R;
	int G;
	int B;
	int W;
	
	int Pan;
	int Tilt;
	
	
	LED_PARAM()
	: R(0), G(0), B(0), W(0), Pan(0), Tilt(0)
	{
	}
	
	void clear()
	{
		R = 0; G = 0; B = 0; W = 0;
		Pan = 0; Tilt = 0;
	}
};

struct LED_LIGHT{
	const int ODE_id;
	const int AddressFrom;
	const enum LED_DEVICE_TYPE LedDeviceType;
	
	LED_PARAM LedParam;
	
	LED_LIGHT(int _ODE_id, int _AddressFrom, enum LED_DEVICE_TYPE _LedDeviceType)
	: ODE_id(_ODE_id), AddressFrom(_AddressFrom), LedDeviceType(_LedDeviceType)
	{
	}
};

struct LED_TEST{
	LED_PARAM LedParam;
	
	int LedId;
	
	LED_TEST()
	{
		clear();
		
		LedParam.R = 255; // SJ : change color for check.
	}
	
	void clear()
	{
		LedId = 0;
		LedParam.clear();
	}
};

/************************************************************
param
************************************************************/
/********************
********************/
// static OSC_TARGET Osc_DJ("10.0.0.2", 12345, 12346);
static OSC_TARGET Osc_DJ("127.0.0.1", 12345, 12346);

/********************
********************/
static ODE ode[] = {
	ODE("10.7.189.7"),
	ODE("10.7.192.86"),
	ODE("10.7.191.15"),
};
static const int NUM_ODES = sizeof(ode) / sizeof(ode[0]);

/********************
********************/
static LED_LIGHT LedLight[] = {
//				ODE id		AddressFrom					Hardware(Start Address) setting 		
/*	0	*/	LED_LIGHT(	0	,	0	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	1		
/*	1	*/	LED_LIGHT(	0	,	3	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	4		
/*	2	*/	LED_LIGHT(	0	,	6	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	7		
/*	3	*/	LED_LIGHT(	0	,	9	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	10		
/*	4	*/	LED_LIGHT(	0	,	12	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	13		
/*	5	*/	LED_LIGHT(	0	,	15	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	16		
/*	6	*/	LED_LIGHT(	0	,	18	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	19		
/*	7	*/	LED_LIGHT(	0	,	21	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	22		
/*	8	*/	LED_LIGHT(	0	,	24	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	25		
/*	9	*/	LED_LIGHT(	0	,	27	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	28		
/*	10	*/	LED_LIGHT(	0	,	30	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	31		
/*	11	*/	LED_LIGHT(	0	,	33	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	34		
/*	12	*/	LED_LIGHT(	0	,	36	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	37		
/*	13	*/	LED_LIGHT(	0	,	39	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	40		
/*	14	*/	LED_LIGHT(	0	,	42	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	43		
/*	15	*/	LED_LIGHT(	0	,	45	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	46		
/*	16	*/	LED_LIGHT(	0	,	48	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	49		
/*	17	*/	LED_LIGHT(	0	,	51	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	52		
/*	18	*/	LED_LIGHT(	0	,	54	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	55		
/*	19	*/	LED_LIGHT(	0	,	57	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	58		
/*	20	*/	LED_LIGHT(	0	,	60	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	61		
/*	21	*/	LED_LIGHT(	0	,	63	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	64		
/*	22	*/	LED_LIGHT(	0	,	66	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	67		
/*	23	*/	LED_LIGHT(	0	,	69	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	70		
/*	24	*/	LED_LIGHT(	0	,	72	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	73		
/*	25	*/	LED_LIGHT(	0	,	75	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	76		
/*	26	*/	LED_LIGHT(	0	,	78	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	79		
/*	27	*/	LED_LIGHT(	0	,	81	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	82		
/*	28	*/	LED_LIGHT(	0	,	84	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	85		
/*	29	*/	LED_LIGHT(	0	,	87	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	88		
/*	30	*/	LED_LIGHT(	0	,	90	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	91		
/*	31	*/	LED_LIGHT(	0	,	93	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	94		
/*	32	*/	LED_LIGHT(	0	,	96	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	97		
/*	33	*/	LED_LIGHT(	0	,	99	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	100		
/*	34	*/	LED_LIGHT(	0	,	102	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	103		
/*	35	*/	LED_LIGHT(	0	,	105	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	106		
/*	36	*/	LED_LIGHT(	0	,	108	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	109		
/*	37	*/	LED_LIGHT(	0	,	111	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	112		
/*	38	*/	LED_LIGHT(	0	,	114	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	115		
/*	39	*/	LED_LIGHT(	0	,	117	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	118		
/*	40	*/	LED_LIGHT(	0	,	120	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	121		
/*	41	*/	LED_LIGHT(	0	,	123	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	124		
/*	42	*/	LED_LIGHT(	0	,	126	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	127		
/*	43	*/	LED_LIGHT(	0	,	129	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	130		
/*	44	*/	LED_LIGHT(	1	,	0	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	1		
/*	45	*/	LED_LIGHT(	1	,	3	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	4		
/*	46	*/	LED_LIGHT(	1	,	6	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	7		
/*	47	*/	LED_LIGHT(	1	,	9	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	10		
/*	48	*/	LED_LIGHT(	1	,	12	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	13		
/*	49	*/	LED_LIGHT(	1	,	15	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	16		
/*	50	*/	LED_LIGHT(	1	,	18	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	19		
/*	51	*/	LED_LIGHT(	1	,	21	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	22		
/*	52	*/	LED_LIGHT(	1	,	24	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	25		
/*	53	*/	LED_LIGHT(	1	,	27	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	28		
/*	54	*/	LED_LIGHT(	1	,	30	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	31		
/*	55	*/	LED_LIGHT(	1	,	33	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	34		
/*	56	*/	LED_LIGHT(	1	,	36	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	37		
/*	57	*/	LED_LIGHT(	1	,	39	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	40		
/*	58	*/	LED_LIGHT(	1	,	42	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	43		
/*	59	*/	LED_LIGHT(	1	,	45	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	46		
/*	60	*/	LED_LIGHT(	1	,	48	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	49		
/*	61	*/	LED_LIGHT(	1	,	51	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	52		
/*	62	*/	LED_LIGHT(	1	,	54	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	55		
/*	63	*/	LED_LIGHT(	1	,	57	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	58		
/*	64	*/	LED_LIGHT(	1	,	60	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	61		
/*	65	*/	LED_LIGHT(	1	,	63	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	64		
/*	66	*/	LED_LIGHT(	1	,	66	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	67		
/*	67	*/	LED_LIGHT(	1	,	69	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	70		
/*	68	*/	LED_LIGHT(	1	,	72	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	73		
/*	69	*/	LED_LIGHT(	1	,	75	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	76		
/*	70	*/	LED_LIGHT(	1	,	78	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	79		
/*	71	*/	LED_LIGHT(	1	,	81	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	82		
/*	72	*/	LED_LIGHT(	1	,	84	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	85		
/*	73	*/	LED_LIGHT(	1	,	87	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	88		
/*	74	*/	LED_LIGHT(	1	,	90	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	91		
/*	75	*/	LED_LIGHT(	1	,	93	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	94		
/*	76	*/	LED_LIGHT(	1	,	96	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	97		
/*	77	*/	LED_LIGHT(	1	,	99	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	100		
/*	78	*/	LED_LIGHT(	1	,	102	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	103		
/*	79	*/	LED_LIGHT(	1	,	105	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	106		
/*	80	*/	LED_LIGHT(	1	,	108	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	109		
/*	81	*/	LED_LIGHT(	1	,	111	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	112		
/*	82	*/	LED_LIGHT(	1	,	114	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	115		
/*	83	*/	LED_LIGHT(	1	,	117	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	118		
/*	84	*/	LED_LIGHT(	1	,	120	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	121		
/*	85	*/	LED_LIGHT(	1	,	123	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	124		
/*	86	*/	LED_LIGHT(	1	,	126	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	127		
/*	87	*/	LED_LIGHT(	1	,	129	,	LED_DEVICE_TYPE_N_WALLWASHER	),	//	130		Broadway
/*	88	*/	LED_LIGHT(	2	,	0	,	LED_DEVICE_TYPE_N_BALL	),	//	1		
/*	89	*/	LED_LIGHT(	2	,	12	,	LED_DEVICE_TYPE_N_BALL	),	//	13		
/*	90	*/	LED_LIGHT(	2	,	24	,	LED_DEVICE_TYPE_N_BALL	),	//	25		青木
/*	91	*/	LED_LIGHT(	2	,	36	,	LED_DEVICE_TYPE_N_BALL	),	//	37		ABC
/*	92	*/	LED_LIGHT(	2	,	48	,	LED_DEVICE_TYPE_N_BALL	),	//	49		TWC
/*	93	*/	LED_LIGHT(	2	,	60	,	LED_DEVICE_TYPE_N_BALL	),	//	61		町田歯科
/*	94	*/	LED_LIGHT(	2	,	72	,	LED_DEVICE_TYPE_N_BALL	),	//	73		くつ：DAIWA
/*	95	*/	LED_LIGHT(	2	,	84	,	LED_DEVICE_TYPE_N_BALL	),	//	85		とんこつラーメン
/*	96	*/	LED_LIGHT(	2	,	96	,	LED_DEVICE_TYPE_N_BALL	),	//	97		STOCK
/*	97	*/	LED_LIGHT(	2	,	108	,	LED_DEVICE_TYPE_N_BALL	),	//	109		ホームメイト
/*	98	*/	LED_LIGHT(	2	,	120	,	LED_DEVICE_TYPE_N_BALL	),	//	121		niraku
/*	99	*/	LED_LIGHT(	2	,	132	,	LED_DEVICE_TYPE_N_BALL	),	//	133		TIGER plaza - ピカデリーサーカス
/*	100	*/	LED_LIGHT(	2	,	144	,	LED_DEVICE_TYPE_N_BALL	),	//	145		cyber slot
/*	101	*/	LED_LIGHT(	2	,	156	,	LED_DEVICE_TYPE_N_BALL	),	//	157		カレーパン
/*	102	*/	LED_LIGHT(	2	,	168	,	LED_DEVICE_TYPE_N_BALL	),	//	169		マツキヨ
/*	103	*/	LED_LIGHT(	2	,	180	,	LED_DEVICE_TYPE_N_BALL	),	//	181		銀だこ
																	//			JR
};

static const int NUM_LEDS = sizeof(LedLight) / sizeof(LedLight[0]);

/********************
********************/
static LED_TEST LedTest;



/************************************************************
************************************************************/

/******************************
******************************/
ofApp::ofApp(int _BootMode)
: BootMode(BOOT_MODE(_BootMode))
, StateTestMode(STATE_TESTMODE__WAIT_START)
, T_MOVE_TO_LIGHT_POS(2 * 60) // SJ
, T_TEST_INTERVAL(15)

// , LedId_TestFrom(0) // SJ : change Led line to check.
// , LedId_TestFrom(44)
, LedId_TestFrom(88)
{
}

/******************************
******************************/
ofApp::~ofApp()
{
	/********************
	何故か、exit()で以下を記述すると、dmx commandが上手く送られず、照明が光ったまま停止してしまった。
	こちらに持ってくると所望の動作となったので、デストラクタで処理する。
	********************/
	Send_AllZero_to_AllOde();
	printMessage("GoodBye");
}

//--------------------------------------------------------------
void ofApp::setup(){
	/********************
	********************/
	font.loadFont("RictyDiminished-Regular.ttf", 15);
	
	/********************
	********************/
	ofSetWindowTitle( "DMX Light" );
	ofSetWindowShape( WIDTH, HEIGHT );
	
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	ofSetEscapeQuitsApp(false);

	/********************
	********************/
	udpConnection.Create();
	udpConnection.Bind(UDP_RECEIVE_PORT);
	udpConnection.SetNonBlocking(true);
	
	/********************
	********************/
	//at first you must specify the Ip address of this machine
	//make sure the firewall is deactivated at this point
	artnet.setup("10.0.0.2");
	
	/********************
	********************/
	b_1stMessage = true;
	
	/********************
	********************/
	b_DispGui = true;
	
	gui.setup();
	gui.add(dimmer_Fixed.setup("dimmer_Fixed", 100, 0, 255));
	gui.add(dimmer_Moving.setup("dimmer_Moving", 255, 0, 255));
	gui.add(dimmer_Nakano.setup("dimmer_Nakano", 255, 0, 255));
}

/******************************
******************************/
void ofApp::exit()
{
}

/******************************
******************************/
void ofApp::Send_AllZero_to_AllOde()
{
	for(int i = 0; i < NUM_ODES; i++){
		for(int j = 0; j < SIZE_DMX_UNIVERSE; j++){
			ode[i].universe[j] = 0;
		}
		
		artnet.sendDmx(ode[i].get_IP(), ode[i].universe, SIZE_DMX_UNIVERSE);
	}
}

//--------------------------------------------------------------
void ofApp::update(){
	/********************
	********************/
	float now = ofGetElapsedTimef();
	if(BootMode == MODE_TEST){
		if(StateTestMode == STATE_TESTMODE__WAIT_START){
			if(T_MOVE_TO_LIGHT_POS < now){
				StateTestMode = STATE_TESTMODE__DO_TEST;
				t_TestIntervalFrom = now;
				LedTest.LedId = LedId_TestFrom;
			}
			
		}else{
			if(T_TEST_INTERVAL < now - t_TestIntervalFrom){
				t_TestIntervalFrom = now;
				
				LedTest.LedId++; // SJ
				if(NUM_LEDS <= LedTest.LedId) LedTest.LedId = 0;
			}
		}
		
		return;
	}
	
	
	/********************
	********************/
	while(Osc_DJ.OscReceive.hasWaitingMessages()){
		ofxOscMessage m_receive;
		Osc_DJ.OscReceive.getNextMessage(&m_receive);
		
		if(m_receive.getAddress() == "/AreYouReady"){
			m_receive.getArgAsInt32(0); // 読み捨て
			
			ofxOscMessage m_send;
			m_send.setAddress("/Ready");
			m_send.addIntArg(1); // yes.
			Osc_DJ.OscSend.sendMessage(m_send);
			
		}else if(m_receive.getAddress() == "/Quit"){
			ofExit();
			return;
		}
	}

	/********************
	********************/
	char udpMessage[SIZE_UPD];
	udpConnection.Receive(udpMessage,SIZE_UPD);
	string message=udpMessage;
	if(message!=""){
		vector<string> params = ofSplitString(message, "|");
		
		if(b_1stMessage){
			b_1stMessage = false;
			printf("NumLeds = %lu\n", params.size() - 1);
			if(params.size() - 1 != NUM_LEDS) { ERROR_MSG(); std::exit(1); }
		}
		
		if(params.size() == NUM_LEDS + 1){
			for(int i = 0; i < params.size() - 1; i++){ // "0" is added at last value.
				vector<string> element = ofSplitString(params[i], ",");
				if(element.size() == 6){
				/*
					LedLight[i].LedParam.R		= atof(element[0].c_str());
					LedLight[i].LedParam.G		= atof(element[1].c_str());
					LedLight[i].LedParam.B		= atof(element[2].c_str());
					LedLight[i].LedParam.W		= atof(element[3].c_str());
					LedLight[i].LedParam.Pan	= atof(element[4].c_str());
					LedLight[i].LedParam.Tilt	= atof(element[5].c_str());
				*/
					LedLight[i].LedParam.R		= atoi(element[0].c_str());
					LedLight[i].LedParam.G		= atoi(element[1].c_str());
					LedLight[i].LedParam.B		= atoi(element[2].c_str());
					LedLight[i].LedParam.W		= atoi(element[3].c_str());
					LedLight[i].LedParam.Pan	= atoi(element[4].c_str());
					LedLight[i].LedParam.Tilt	= atoi(element[5].c_str());
				}
			}
		}
		
		while(message != ""){
			udpConnection.Receive(udpMessage,SIZE_UPD);
			message = udpMessage;
		}
	}
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(30);
	
	if(BootMode == MODE_TEST)	draw_test();
	else						draw_demo();
	
	draw_time(ofGetFrameRate());
}

/******************************
******************************/
void ofApp::draw_time(double FrameRate)
{
	/********************
	********************/
	char buf[BUF_SIZE];
	sprintf(buf, "%7.2f", FrameRate);
	
	/********************
	********************/
	ofSetColor(255, 255, 255);
	
	font.drawString(buf, 10, 50);
	
	/********************
	********************/
	if(b_DispGui) gui.draw();
}

/******************************
******************************/
void ofApp::draw_test()
{
	for(int i = 0; i < NUM_LEDS; i++){
		switch(LedLight[i].LedDeviceType){
			case LED_DEVICE_TYPE_FIXED:
				if(i == LedTest.LedId){
					ode[ LedLight[i].ODE_id ].universe[ LedLight[i].AddressFrom + 0 ] = dimmer_Fixed;
					ode[ LedLight[i].ODE_id ].universe[ LedLight[i].AddressFrom + 1 ] = LedTest.LedParam.R;
					ode[ LedLight[i].ODE_id ].universe[ LedLight[i].AddressFrom + 2 ] = LedTest.LedParam.G;
					ode[ LedLight[i].ODE_id ].universe[ LedLight[i].AddressFrom + 3 ] = LedTest.LedParam.B;
					ode[ LedLight[i].ODE_id ].universe[ LedLight[i].AddressFrom + 4 ] = LedTest.LedParam.W;
					ode[ LedLight[i].ODE_id ].universe[ LedLight[i].AddressFrom + 5 ] = 1; // Strobe = open.
				}else{
					ode[ LedLight[i].ODE_id ].universe[ LedLight[i].AddressFrom + 0 ] = 0; // dimmer
					ode[ LedLight[i].ODE_id ].universe[ LedLight[i].AddressFrom + 1 ] = 0;
					ode[ LedLight[i].ODE_id ].universe[ LedLight[i].AddressFrom + 2 ] = 0;
					ode[ LedLight[i].ODE_id ].universe[ LedLight[i].AddressFrom + 3 ] = 0;
					ode[ LedLight[i].ODE_id ].universe[ LedLight[i].AddressFrom + 4 ] = 0;
					ode[ LedLight[i].ODE_id ].universe[ LedLight[i].AddressFrom + 5 ] = 0; // strobe
				}
				break;
				
			case LED_DEVICE_TYPE_MOVING:
				if(i == LedTest.LedId){
					ode[ LedLight[i].ODE_id ].universe[ LedLight[i].AddressFrom +  0 ] = (unsigned char)((LedTest.LedParam.Pan >> 8) & 0xFF);	// H
					ode[ LedLight[i].ODE_id ].universe[ LedLight[i].AddressFrom +  1 ] = (unsigned char)((LedTest.LedParam.Pan >> 0) & 0xFF);	// L
					ode[ LedLight[i].ODE_id ].universe[ LedLight[i].AddressFrom +  2 ] = (unsigned char)((LedTest.LedParam.Tilt >> 8) & 0xFF);	// H
					ode[ LedLight[i].ODE_id ].universe[ LedLight[i].AddressFrom +  3 ] = (unsigned char)((LedTest.LedParam.Tilt >> 0) & 0xFF);	// L
					ode[ LedLight[i].ODE_id ].universe[ LedLight[i].AddressFrom +  4 ] = LedTest.LedParam.R;
					ode[ LedLight[i].ODE_id ].universe[ LedLight[i].AddressFrom +  5 ] = LedTest.LedParam.G;
					ode[ LedLight[i].ODE_id ].universe[ LedLight[i].AddressFrom +  6 ] = LedTest.LedParam.B;
					ode[ LedLight[i].ODE_id ].universe[ LedLight[i].AddressFrom +  7 ] = LedTest.LedParam.W;
					ode[ LedLight[i].ODE_id ].universe[ LedLight[i].AddressFrom +  8 ] = 8;	// shutter open
					ode[ LedLight[i].ODE_id ].universe[ LedLight[i].AddressFrom +  9 ] = dimmer_Moving;
					ode[ LedLight[i].ODE_id ].universe[ LedLight[i].AddressFrom + 10 ] = 0; // Pan/Tilt speed : [0 : fast] <---> [slow : 255]
					ode[ LedLight[i].ODE_id ].universe[ LedLight[i].AddressFrom + 11 ] = 0; // Blackout reset
					ode[ LedLight[i].ODE_id ].universe[ LedLight[i].AddressFrom + 12 ] = 0; // dimmer curve = standard
					
				}else{
					ode[ LedLight[i].ODE_id ].universe[ LedLight[i].AddressFrom +  0 ] = 0;	// H
					ode[ LedLight[i].ODE_id ].universe[ LedLight[i].AddressFrom +  1 ] = 0;	// L
					ode[ LedLight[i].ODE_id ].universe[ LedLight[i].AddressFrom +  2 ] = 0;	// H
					ode[ LedLight[i].ODE_id ].universe[ LedLight[i].AddressFrom +  3 ] = 0;	// L
					ode[ LedLight[i].ODE_id ].universe[ LedLight[i].AddressFrom +  4 ] = 0;
					ode[ LedLight[i].ODE_id ].universe[ LedLight[i].AddressFrom +  5 ] = 0;
					ode[ LedLight[i].ODE_id ].universe[ LedLight[i].AddressFrom +  6 ] = 0;
					ode[ LedLight[i].ODE_id ].universe[ LedLight[i].AddressFrom +  7 ] = 0;
					ode[ LedLight[i].ODE_id ].universe[ LedLight[i].AddressFrom +  8 ] = 0;
					ode[ LedLight[i].ODE_id ].universe[ LedLight[i].AddressFrom +  9 ] = 0;
					ode[ LedLight[i].ODE_id ].universe[ LedLight[i].AddressFrom + 10 ] = 0; // Pan/Tilt speed : [0 : fast] <---> [slow : 255]
					ode[ LedLight[i].ODE_id ].universe[ LedLight[i].AddressFrom + 11 ] = 0; // Blackout reset
					ode[ LedLight[i].ODE_id ].universe[ LedLight[i].AddressFrom + 12 ] = 0; // dimmer curve = standard
				}
				break;
				
			case LED_DEVICE_TYPE_N_WALLWASHER:
			{
				if(i == LedTest.LedId){
					ode[ LedLight[i].ODE_id ].universe[ LedLight[i].AddressFrom + 0 ] = LedTest.LedParam.R;
					ode[ LedLight[i].ODE_id ].universe[ LedLight[i].AddressFrom + 1 ] = LedTest.LedParam.G;
					ode[ LedLight[i].ODE_id ].universe[ LedLight[i].AddressFrom + 2 ] = LedTest.LedParam.B;
				}else{
					ode[ LedLight[i].ODE_id ].universe[ LedLight[i].AddressFrom + 0 ] = 0;
					ode[ LedLight[i].ODE_id ].universe[ LedLight[i].AddressFrom + 1 ] = 0;
					ode[ LedLight[i].ODE_id ].universe[ LedLight[i].AddressFrom + 2 ] = 0;
				}
			}
				break;
				
			case LED_DEVICE_TYPE_N_BALL:
			{
				if(i == LedTest.LedId){
					for(int j = 0; j < 4; j++){ // each ball has 4 Led modules
						ode[ LedLight[i].ODE_id ].universe[ LedLight[i].AddressFrom + 3 * j + 0 ] = LedTest.LedParam.R; // 3 means RGB
						ode[ LedLight[i].ODE_id ].universe[ LedLight[i].AddressFrom + 3 * j + 1 ] = LedTest.LedParam.G;
						ode[ LedLight[i].ODE_id ].universe[ LedLight[i].AddressFrom + 3 * j + 2 ] = LedTest.LedParam.B;
					}
				}else{
					for(int j = 0; j < 4; j++){ // each ball has 4 Led modules
						ode[ LedLight[i].ODE_id ].universe[ LedLight[i].AddressFrom + 3 * j + 0 ] = 0;
						ode[ LedLight[i].ODE_id ].universe[ LedLight[i].AddressFrom + 3 * j + 1 ] = 0;
						ode[ LedLight[i].ODE_id ].universe[ LedLight[i].AddressFrom + 3 * j + 2 ] = 0;
					}
				}
			}
				break;
		}
	}
	
	for(int i = 0; i < NUM_ODES; i++){
		artnet.sendDmx(ode[i].get_IP(), ode[i].universe, SIZE_DMX_UNIVERSE);
	}
}

/******************************
******************************/
void ofApp::draw_demo()
{
	/********************
	********************/
	for(int i = 0; i < NUM_LEDS; i++){
		switch(LedLight[i].LedDeviceType){
			case LED_DEVICE_TYPE_FIXED:
				ode[ LedLight[i].ODE_id ].universe[ LedLight[i].AddressFrom + 0 ] = dimmer_Fixed;
				ode[ LedLight[i].ODE_id ].universe[ LedLight[i].AddressFrom + 1 ] = LedLight[i].LedParam.R;
				ode[ LedLight[i].ODE_id ].universe[ LedLight[i].AddressFrom + 2 ] = LedLight[i].LedParam.G;
				ode[ LedLight[i].ODE_id ].universe[ LedLight[i].AddressFrom + 3 ] = LedLight[i].LedParam.B;
				ode[ LedLight[i].ODE_id ].universe[ LedLight[i].AddressFrom + 4 ] = LedLight[i].LedParam.W;
				ode[ LedLight[i].ODE_id ].universe[ LedLight[i].AddressFrom + 5 ] = 1; // Strobe = open.
				
				break;
				
			case LED_DEVICE_TYPE_MOVING:
				ode[ LedLight[i].ODE_id ].universe[ LedLight[i].AddressFrom +  0 ] = (unsigned char)((LedLight[i].LedParam.Pan >> 8) & 0xFF);	// H
				ode[ LedLight[i].ODE_id ].universe[ LedLight[i].AddressFrom +  1 ] = (unsigned char)((LedLight[i].LedParam.Pan >> 0) & 0xFF);	// L
				ode[ LedLight[i].ODE_id ].universe[ LedLight[i].AddressFrom +  2 ] = (unsigned char)((LedLight[i].LedParam.Tilt >> 8) & 0xFF);	// H
				ode[ LedLight[i].ODE_id ].universe[ LedLight[i].AddressFrom +  3 ] = (unsigned char)((LedLight[i].LedParam.Tilt >> 0) & 0xFF);	// L
				ode[ LedLight[i].ODE_id ].universe[ LedLight[i].AddressFrom +  4 ] = LedLight[i].LedParam.R;
				ode[ LedLight[i].ODE_id ].universe[ LedLight[i].AddressFrom +  5 ] = LedLight[i].LedParam.G;
				ode[ LedLight[i].ODE_id ].universe[ LedLight[i].AddressFrom +  6 ] = LedLight[i].LedParam.B;
				ode[ LedLight[i].ODE_id ].universe[ LedLight[i].AddressFrom +  7 ] = LedLight[i].LedParam.W;
				ode[ LedLight[i].ODE_id ].universe[ LedLight[i].AddressFrom +  8 ] = 8;	// shutter open
				
				// ode[ LedLight[i].ODE_id ].universe[ LedLight[i].AddressFrom +  9 ] = LedDimmerCopy;
				ode[ LedLight[i].ODE_id ].universe[ LedLight[i].AddressFrom +  9 ] = dimmer_Moving; // moving Lightは暗いので、常にmax.
				
				ode[ LedLight[i].ODE_id ].universe[ LedLight[i].AddressFrom + 10 ] = 0; // Pan/Tilt speed : [0 : fast] <---> [slow : 255]
				ode[ LedLight[i].ODE_id ].universe[ LedLight[i].AddressFrom + 11 ] = 0; // Blackout reset
				ode[ LedLight[i].ODE_id ].universe[ LedLight[i].AddressFrom + 12 ] = 0; // dimmer curve = standard
				
				break;
				
			case LED_DEVICE_TYPE_N_WALLWASHER:
			{
				/********************
				********************/
				int R = LedLight[i].LedParam.R + LedLight[i].LedParam.W;
				R = int(R * ((double)dimmer_Nakano / 255));
				if(255 < R) R = 255;
				if(R < 0) R = 0;
				
				int G = LedLight[i].LedParam.G + LedLight[i].LedParam.W;
				G = int(G * ((double)dimmer_Nakano / 255));
				if(255 < G) G = 255;
				if(G < 0) G = 0;
				
				int B = LedLight[i].LedParam.B + LedLight[i].LedParam.W;
				B = int(B * ((double)dimmer_Nakano / 255));
				if(255 < B) B = 255;
				if(B < 0) B = 0;
				
				/********************
				********************/
				ode[ LedLight[i].ODE_id ].universe[ LedLight[i].AddressFrom + 0 ] = (unsigned char)R;
				ode[ LedLight[i].ODE_id ].universe[ LedLight[i].AddressFrom + 1 ] = (unsigned char)G;
				ode[ LedLight[i].ODE_id ].universe[ LedLight[i].AddressFrom + 2 ] = (unsigned char)B;
			}
				break;
				
			case LED_DEVICE_TYPE_N_BALL:
			{
				/********************
				********************/
				int R = LedLight[i].LedParam.R + LedLight[i].LedParam.W;
				R = int(R * ((double)dimmer_Nakano / 255));
				if(255 < R) R = 255;
				if(R < 0) R = 0;
				
				int G = LedLight[i].LedParam.G + LedLight[i].LedParam.W;
				G = int(G * ((double)dimmer_Nakano / 255));
				if(255 < G) G = 255;
				if(G < 0) G = 0;
				
				int B = LedLight[i].LedParam.B + LedLight[i].LedParam.W;
				B = int(B * ((double)dimmer_Nakano / 255));
				if(255 < B) B = 255;
				if(B < 0) B = 0;
				
				/********************
				********************/
				for(int j = 0; j < 4; j++){ // each ball has 4 Led modules
					ode[ LedLight[i].ODE_id ].universe[ LedLight[i].AddressFrom + 3 * j + 0 ] = (unsigned char)R; // 3 means RGB.
					ode[ LedLight[i].ODE_id ].universe[ LedLight[i].AddressFrom + 3 * j + 1 ] = (unsigned char)G;
					ode[ LedLight[i].ODE_id ].universe[ LedLight[i].AddressFrom + 3 * j + 2 ] = (unsigned char)B;
				}
			}
				break;

		}
	}
	
	/********************
	********************/
	for(int i = 0; i < NUM_ODES; i++){
		artnet.sendDmx(ode[i].get_IP(), ode[i].universe, SIZE_DMX_UNIVERSE);
	}
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	
	const int DIMMER_STEP = 5;
	
	enum STATE_INPUT{
		STATE_INPUT_NONE,
		
		STATE_INPUT_LED_NUMBER,
		
		STATE_INPUT_R,
		STATE_INPUT_G,
		STATE_INPUT_B,
		STATE_INPUT_W,

		STATE_INPUT_PAN,
		STATE_INPUT_TILT,
	};
	
	static enum STATE_INPUT StateInput = STATE_INPUT_NONE;
	static int input[BUF_SIZE];
	static int index = 0;
	
	switch(key){
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			if(StateInput != STATE_INPUT_NONE){
				if(index < BUF_SIZE){
					input[index] = key - '0';
					index++;
				}
				printf("%d", key - '0');
				fflush(stdout);
			}
			break;
		
		case 'b':
			StateInput = STATE_INPUT_B;
			index = 0;
			printMessage("B");
			break;
			
		case 'c':
			StateInput = STATE_INPUT_NONE;
			
			LedTest.clear();
			printMessage("clear");
			
			break;
			
		case 'd':
			b_DispGui = !b_DispGui;
			break;
			
		case 'g':
			StateInput = STATE_INPUT_G;
			index = 0;
			printMessage("G");
			break;
			
		case 'l':
			StateInput = STATE_INPUT_LED_NUMBER;
			index = 0;
			printMessage("LedNumber");
			break;

		case 'p':
			StateInput = STATE_INPUT_PAN;
			index = 0;
			printMessage("Pan");
			break;
			
		case 'r':
			StateInput = STATE_INPUT_R;
			index = 0;
			printMessage("R");
			break;
			
		case 't':
			StateInput = STATE_INPUT_TILT;
			index = 0;
			printMessage("Tilt");
			break;
			
		case 'w':
			StateInput = STATE_INPUT_W;
			index = 0;
			printMessage("W");
			break;

			
		case OF_KEY_RETURN:
		{
			index--;
			
			if(index < 0){
				// nothing.
			}else{
				int input_val = 0;
				int i = 0;
				
				while(0 <= index){
					input_val += input[i] * pow(10, index);
					
					i++;
					index--;
				}
				
				switch(StateInput){
					case STATE_INPUT_LED_NUMBER:
						LedTest.LedId = (unsigned char)input_val;
						break;
						
					case STATE_INPUT_R:
						LedTest.LedParam.R = (unsigned char)input_val;
						break;
						
					case STATE_INPUT_G:
						LedTest.LedParam.G = (unsigned char)input_val;
						break;
						
					case STATE_INPUT_B:
						LedTest.LedParam.B = (unsigned char)input_val;
						break;
						
					case STATE_INPUT_W:
						LedTest.LedParam.W = (unsigned char)input_val;
						break;
						
					case STATE_INPUT_PAN:
						LedTest.LedParam.Pan = input_val;
						break;
						
					case STATE_INPUT_TILT:
						LedTest.LedParam.Tilt = input_val;
						break;
					
					default:
						break;
				}
				
				printf(	"\n[%d] (%d, %d, %d, %d, %d(%X), %d(%X))\n",
						LedTest.LedId, LedTest.LedParam.R, LedTest.LedParam.G, LedTest.LedParam.B, LedTest.LedParam.W,
						LedTest.LedParam.Pan, LedTest.LedParam.Pan, LedTest.LedParam.Tilt, LedTest.LedParam.Tilt);
			}
			index = 0;
		}
		
			break;
			
		case OF_KEY_UP:
		{
		}
			break;
			
		case OF_KEY_DOWN:
		{
		}
			break;
			
		default:
			break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
