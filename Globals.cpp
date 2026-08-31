#include "Globals.h"

WifiConfig wifiConfig;
AutomationConfig automationConfig;
Preferences preferences;

WebServer* server = nullptr;
WebSocketsServer* webSocket = nullptr;

int scoreA = 0;
int scoreB = 0;
int foulsA = 0;
int foulsB = 0;
int period = 0;

bool timerRunning = false;
unsigned long timerLastMillis = 0;
unsigned long totalSeconds = 0;

unsigned long lastReconnectMillis = 0;
bool rebootScheduled = false;
unsigned long rebootTime = 0;

unsigned long resetBtnPressedMillis = 0;
bool resetBtnPressed = false;

unsigned long lastPollMillis = 0;
