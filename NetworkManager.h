#ifndef NETWORK_MANAGER_H
#define NETWORK_MANAGER_H

#include "Globals.h"
#include "WebPages.h"
#include "DisplayManager.h"

void sendSingleState(uint8_t num);
void broadcastState();
void pollScoreboardAPI();

void handleRoot();
void handleUserAdm();
void handleLanConfig();
void handleSsidConfig();
void handlePanelConfig();
void handlePainel();
void handleLogin();
void handleLogout();
void handleFactoryReset();
void handleUsersGet();
void handleUsersSave();
void handleUsersDelete();
void handleWifiStatus();
void handleWifiScan();
void handleWifiTest();
void handleWifiConfig();
void handleAutomationConfig();
void handleAutomationMode();
void handleAutomationStatus();
String urlEncode(String str);
void handleProxy();
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length);

#endif // NETWORK_MANAGER_H
