#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <WebSocketsServer.h>
#include <ESPmDNS.h>
#include <Preferences.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include <Adafruit_NeoPixel.h>

struct WifiConfig {
  String wifiSsid;
  String wifiPass;
  bool dhcp;
  String staticIp;
  String staticSubnet;
  String staticGateway;
  String staticDns;
  String apSsid;
  String apPass;
  int apChannel;
  int httpPort;
  int wsPort;
  bool autoReconnect;
};

struct AutomationConfig {
  bool active;
  String mode;
  String dominio;
  String modalidade;
  String campeonato;
  String partida;
  String etapa;
  String rodada;
};

extern WifiConfig wifiConfig;
extern AutomationConfig automationConfig;
extern Preferences preferences;

extern WebServer* server;
extern WebSocketsServer* webSocket;

extern int scoreA;
extern int scoreB;
extern int foulsA;
extern int foulsB;
extern int period;

extern bool timerRunning;
extern unsigned long timerLastMillis;
extern unsigned long totalSeconds;

extern unsigned long lastReconnectMillis;
extern bool rebootScheduled;
extern unsigned long rebootTime;

extern unsigned long resetBtnPressedMillis;
extern bool resetBtnPressed;

extern unsigned long lastPollMillis;

#endif // GLOBALS_H
