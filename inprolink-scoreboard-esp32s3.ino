#include "Globals.h"
#include "WebPages.h"

#include "DisplayManager.h"
#include "NetworkManager.h"

// ==========================================

void setup() {
  Serial.begin(115200);
  delay(100);
  Serial.println("Iniciando Inprolink Scoreboard Controller...");
  
  // Factory reset button pin setup
  pinMode(0, INPUT_PULLUP);
  
  // Load preferences from NVS
  preferences.begin("scoreboard", false);
  
  // Initialize users NVS list if empty
  String usersJson = preferences.getString("users", "");
  if (usersJson == "") {
    usersJson = "[{\"name\":\"Administrador Inprolink\",\"username\":\"inprolink\",\"pass\":\"link@link\",\"role\":\"Administrador\"}]";
    preferences.putString("users", usersJson);
  }
  
  // Load Wifi settings and automate configurations
  String wifiJson = preferences.getString("wifi", "");
  if (wifiJson == "") {
    wifiConfig.wifiSsid = "";
    wifiConfig.wifiPass = "";
    wifiConfig.dhcp = true;
    wifiConfig.staticIp = "192.168.1.200";
    wifiConfig.staticSubnet = "255.255.255.0";
    wifiConfig.staticGateway = "192.168.1.1";
    wifiConfig.staticDns = "8.8.8.8";
    wifiConfig.apSsid = "inprolink_system";
    wifiConfig.apPass = "too@ajw8i67";
    wifiConfig.apChannel = 6;
    wifiConfig.httpPort = 80;
    wifiConfig.wsPort = 81;
    wifiConfig.autoReconnect = true;
  } else {
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, wifiJson);
    wifiConfig.wifiSsid = doc["wifiSsid"] | "";
    wifiConfig.wifiPass = doc["wifiPass"] | "";
    wifiConfig.dhcp = doc["dhcp"] | true;
    wifiConfig.staticIp = doc["staticIp"] | "192.168.1.200";
    wifiConfig.staticSubnet = doc["staticSubnet"] | "255.255.255.0";
    wifiConfig.staticGateway = doc["staticGateway"] | "192.168.1.1";
    wifiConfig.staticDns = doc["staticDns"] | "8.8.8.8";
    wifiConfig.apSsid = doc["apSsid"] | "inprolink_system";
    wifiConfig.apPass = doc["apPass"] | "too@ajw8i67";
    wifiConfig.apChannel = doc["apChannel"] | 6;
    wifiConfig.httpPort = doc["httpPort"] | 80;
    wifiConfig.wsPort = doc["wsPort"] | 81;
    wifiConfig.autoReconnect = doc["autoReconnect"] | true;
  }
  
  String autJson = preferences.getString("automation", "");
  if (autJson == "") {
    automationConfig.active = false;
    automationConfig.mode = "automatico";
    automationConfig.dominio = "placar.inprolink.com.br";
    automationConfig.modalidade = "";
    automationConfig.campeonato = "";
    automationConfig.partida = "";
    automationConfig.etapa = "";
    automationConfig.rodada = "";
  } else {
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, autJson);
    automationConfig.active = doc["active"] | false;
    automationConfig.mode = doc["mode"] | "automatico";
    automationConfig.dominio = doc["dominio"] | "placar.inprolink.com.br";
    automationConfig.modalidade = doc["modalidade"] | "";
    automationConfig.campeonato = doc["campeonato"] | "";
    automationConfig.partida = doc["partida"] | "";
    automationConfig.etapa = doc["etapa"] | "";
    automationConfig.rodada = doc["rodada"] | "";
  }
  
  // Initialize WS2812B NeoPixel strips for the 16 digits
  for (int i = 0; i < 16; i++) {
    digits[i] = new Adafruit_NeoPixel(35, digitPins[i], NEO_GRB + NEO_KHZ800);
    digits[i]->begin();
    digits[i]->setBrightness(50);
    digits[i]->show();
  }
  updatePhysicalDisplays();
  
  // Establish WiFi access point and station mode connections
  WiFi.disconnect(true);
  delay(100);
  WiFi.softAPConfig(IPAddress(192, 168, 4, 1), IPAddress(192, 168, 4, 1), IPAddress(255, 255, 255, 0));
  WiFi.softAP(wifiConfig.apSsid.c_str(), wifiConfig.apPass.c_str(), wifiConfig.apChannel);
  
  if (wifiConfig.wifiSsid.length() > 0) {
    WiFi.mode(WIFI_AP_STA);
    if (!wifiConfig.dhcp) {
      IPAddress ip, subnet, gateway, dns;
      ip.fromString(wifiConfig.staticIp);
      subnet.fromString(wifiConfig.staticSubnet);
      gateway.fromString(wifiConfig.staticGateway);
      dns.fromString(wifiConfig.staticDns);
      WiFi.config(ip, gateway, subnet, dns);
    }
    WiFi.begin(wifiConfig.wifiSsid.c_str(), wifiConfig.wifiPass.c_str());
    Serial.println("Wi-Fi STA iniciando conexão...");
  } else {
    WiFi.mode(WIFI_AP);
    Serial.println("Wi-Fi operando somente em modo AP.");
  }
  
  // Initialize local mDNS Responder
  if (MDNS.begin("inprolink_system")) {
    Serial.println("mDNS ativo: http://inprolink_system.local");
  }
  
  // Start Web Server on custom HTTP port
  server = new WebServer(wifiConfig.httpPort);
  
  const char * headerKeys[] = {"Cookie"};
  server->collectHeaders(headerKeys, 1);
  
  server->on("/", handleRoot);
  server->on("/login.html", handleRoot);
  server->on("/user_adm.html", handleUserAdm);
  server->on("/lan_config.html", handleLanConfig);
  server->on("/ssid_config.html", handleSsidConfig);
  server->on("/panel_config.html.html", handlePanelConfig);
  server->on("/panel_config.html", handlePanelConfig);
  server->on("/painel.html", handlePainel);
  
  server->on("/api/login", HTTP_POST, handleLogin);
  server->on("/api/logout", HTTP_POST, handleLogout);
  server->on("/api/factory_reset", HTTP_POST, handleFactoryReset);
  server->on("/api/users", HTTP_GET, handleUsersGet);
  server->on("/api/users", HTTP_POST, handleUsersSave);
  server->on("/api/users/delete", HTTP_POST, handleUsersDelete);
  
  server->on("/api/wifi/status", HTTP_GET, handleWifiStatus);
  server->on("/api/wifi/scan", HTTP_GET, handleWifiScan);
  server->on("/api/wifi/test", HTTP_GET, handleWifiTest);
  server->on("/api/wifi/config", HTTP_POST, handleWifiConfig);
  
  server->on("/api/automation/config", HTTP_POST, handleAutomationConfig);
  server->on("/api/automation/mode",   HTTP_POST, handleAutomationMode);
  server->on("/api/automation/status", HTTP_GET,  handleAutomationStatus);
  
  server->on("/api/proxy/modalidades", HTTP_GET, handleProxy);
  server->on("/api/proxy/campeonatos", HTTP_GET, handleProxy);
  server->on("/api/proxy/partidas", HTTP_GET, handleProxy);
  server->on("/api/proxy/etapas", HTTP_GET, handleProxy);
  server->on("/api/proxy/rodadas", HTTP_GET, handleProxy);
  
  server->begin();
  Serial.printf("Servidor HTTP iniciado na porta %d\n", wifiConfig.httpPort);
  
  // Start WebSocket server on custom port
  webSocket = new WebSocketsServer(wifiConfig.wsPort);
  webSocket->begin();
  webSocket->onEvent(webSocketEvent);
  Serial.printf("WebSocket iniciado na porta %d\n", wifiConfig.wsPort);
}

void loop() {
  // Feed web servers
  if (server != nullptr) server->handleClient();
  if (webSocket != nullptr) webSocket->loop();
  
  // Keep chronometer accurate
  if (timerRunning) {
    unsigned long now = millis();
    if (now - timerLastMillis >= 1000) {
      unsigned long elapsedSecs = (now - timerLastMillis) / 1000;
      totalSeconds += elapsedSecs;
      timerLastMillis += elapsedSecs * 1000;
      
      updatePhysicalDisplays();
      broadcastState();
    }
  }
  
  // Handle Wi-Fi automatic reconnection in STA mode
  if (wifiConfig.wifiSsid.length() > 0 && WiFi.status() != WL_CONNECTED && wifiConfig.autoReconnect) {
    unsigned long now = millis();
    if (now - lastReconnectMillis >= 15000) { // Try every 15 seconds
      lastReconnectMillis = now;
      Serial.println("Reconexão Wi-Fi automática em andamento...");
      WiFi.begin(wifiConfig.wifiSsid.c_str(), wifiConfig.wifiPass.c_str());
    }
  }
  
  // Factory reset button handler (hold BOOT pin for 5 seconds)
  if (digitalRead(0) == LOW) {
    if (!resetBtnPressed) {
      resetBtnPressed = true;
      resetBtnPressedMillis = millis();
    } else {
      if (millis() - resetBtnPressedMillis >= 5000) {
        Serial.println("Factory Reset físico acionado! Limpando NVS...");
        preferences.clear();
        
        // Clear all NeoPixel strips to indicate success
        for (int i = 0; i < 16; i++) {
          if (digits[i] != nullptr) {
            digits[i]->clear();
            digits[i]->show();
          }
        }
        delay(1000);
        ESP.restart();
      }
    }
  } else {
    resetBtnPressed = false;
  }
  
  // Automatic API Polling Client (every 3 seconds if active)
  if (automationConfig.active && WiFi.status() == WL_CONNECTED) {
    unsigned long now = millis();
    if (now - lastPollMillis >= 3000) {
      lastPollMillis = now;
      pollScoreboardAPI();
    }
  }
  
  // Delayed reboot handler
  if (rebootScheduled && millis() >= rebootTime) {
    Serial.println("Reiniciando ESP32...");
    ESP.restart();
  }
}
