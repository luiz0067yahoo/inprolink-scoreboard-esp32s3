#include "Globals.h"
#include "WebPages.h"

#include "DisplayManager.h"
#include "NetworkManager.h"

// ==========================================

void setup() {
  setCpuFrequencyMhz(240);
  Serial.begin(115200);
  delay(50);
  Serial.printf("Iniciando Esporte7 Scoreboard Controller (%d MHz)...\n", getCpuFrequencyMhz());
  
  // Factory reset button pin setup
  pinMode(0, INPUT_PULLUP);
  
  // Load preferences from NVS
  preferences.begin("scoreboard", false);
  
  // Initialize users NVS list if empty
  String usersJson = preferences.getString("users", "");
  if (usersJson == "") {
    usersJson = "[{\"name\":\"Administrador Esporte7\",\"username\":\"esporte7\",\"pass\":\"link@link\",\"role\":\"Administrador\"}]";
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
    wifiConfig.apSsid = "esporte7system";
    wifiConfig.apPass = "Esporte7@";
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
    wifiConfig.apSsid = doc["apSsid"] | "esporte7system";
    wifiConfig.apPass = doc["apPass"] | "Esporte7@";
    wifiConfig.apChannel = doc["apChannel"] | 6;
    wifiConfig.httpPort = doc["httpPort"] | 80;
    wifiConfig.wsPort = doc["wsPort"] | 81;
    wifiConfig.autoReconnect = doc["autoReconnect"] | true;
  }
  
  String autJson = preferences.getString("automation", "");
  if (autJson == "") {
    automationConfig.active = false;
    automationConfig.mode = "automatico";
    automationConfig.dominio = "esportes7.com.br";
    automationConfig.porta = 0;
    automationConfig.prefixo = "/api/";
    automationConfig.modalidade = "";
    automationConfig.campeonato = "";
    automationConfig.partida = "";
    automationConfig.etapa = "";
    automationConfig.rodada = "";
  } else {
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, autJson);
    auto getStringField = [&](const char* k1, const char* k2 = nullptr, const char* k3 = nullptr) -> String {
      const char* keys[3] = { k1, k2, k3 };
      for (int i = 0; i < 3; i++) {
        if (keys[i] && doc.containsKey(keys[i])) {
          if (doc[keys[i]].is<int>()) return String(doc[keys[i]].as<int>());
          if (doc[keys[i]].is<long>()) return String(doc[keys[i]].as<long>());
          const char* s = doc[keys[i]] | "";
          if (s && strlen(s) > 0) return String(s);
          return doc[keys[i]].as<String>();
        }
      }
      return "";
    };

    automationConfig.active = doc["active"] | false;
    automationConfig.mode = doc["mode"] | "automatico";
    automationConfig.dominio = cleanDomain(doc["dominio"] | "esportes7.com.br");
    automationConfig.porta = doc["porta"] | (doc["port"] | 0);
    automationConfig.prefixo = doc["prefixo"] | (doc["prefix"] | "/api/");
    automationConfig.modalidade = getStringField("modalidade");
    automationConfig.campeonato = getStringField("campeonato", "campeonatoId", "championship_id");
    automationConfig.partida = getStringField("partida", "partidaId", "match_id");
    automationConfig.etapa = getStringField("etapa");
    automationConfig.rodada = getStringField("rodada", "rodadaId", "round_id");
  }
  
  // Initialize WS2812B NeoPixel strips for the 18 digits and display 0 on all of them
  invalidateDisplayCache();
  for (int i = 0; i < 18; i++) {
    digits[i] = new Adafruit_NeoPixel(35, digitPins[i], NEO_GRB + NEO_KHZ800);
    digits[i]->begin();
    digits[i]->setBrightness(50);
    drawDigit(i, 0, getDigitColor(i));
  }

  // Inicializar 5 LEDs sempre acesos na GPIO 15
  separatorPixels = new Adafruit_NeoPixel(5, 15, NEO_GRB + NEO_KHZ800);
  separatorPixels->begin();
  separatorPixels->setBrightness(50);
  for (int led = 0; led < 5; led++) {
    separatorPixels->setPixelColor(led, 0xFFFFFF);
  }
  separatorPixels->show();
  
  // Establish WiFi access point and station mode connections
  WiFi.disconnect(true);
  delay(100);
  WiFi.softAPConfig(IPAddress(192, 168, 4, 1), IPAddress(192, 168, 4, 1), IPAddress(255, 255, 255, 0));
  WiFi.softAP(wifiConfig.apSsid.c_str(), wifiConfig.apPass.c_str(), wifiConfig.apChannel);
  
  // Iniciar DNS Server (Captive Portal) no modo AP - redireciona qualquer domínio para 192.168.4.1
  dnsServer.setErrorReplyCode(DNSReplyCode::NoError);
  dnsServer.start(53, "*", IPAddress(192, 168, 4, 1));
  Serial.println("DNS Server (Captive Portal) ativo no IP 192.168.4.1 (porta 53)");

  // Always use AP_STA so scanning is available even when not yet connected to a router
  WiFi.mode(WIFI_AP_STA);
  
  if (wifiConfig.wifiSsid.length() > 0) {
    if (!wifiConfig.dhcp) {
      IPAddress ip, subnet, gateway, dns;
      ip.fromString(wifiConfig.staticIp);
      subnet.fromString(wifiConfig.staticSubnet);
      gateway.fromString(wifiConfig.staticGateway);
      dns.fromString(wifiConfig.staticDns);
      WiFi.config(ip, gateway, subnet, dns);
    }
    WiFi.setAutoReconnect(true);
    WiFi.begin(wifiConfig.wifiSsid.c_str(), wifiConfig.wifiPass.c_str());
    Serial.println("Wi-Fi STA iniciando conexão...");
  } else {
    Serial.println("Wi-Fi operando em modo AP (com STA habilitado para escaneamento).");
  }
  
  // Event listener to log router IP assignment
  WiFi.onEvent([](WiFiEvent_t event, WiFiEventInfo_t info) {
    if (event == ARDUINO_EVENT_WIFI_STA_GOT_IP) {
      Serial.printf("[mDNS/STA] IP atribuído pelo roteador: %s\n", WiFi.localIP().toString().c_str());
    }
  });

  // Initialize initial mDNS Responder
  if (MDNS.begin("painel")) {
    MDNS.addService("http", "tcp", 80);
    MDNS.addService("ws", "tcp", wifiConfig.wsPort);
    Serial.println("mDNS inicial ativo: http://painel.local");
  }
  
  // Iniciar servidor HTTP na porta 80 (servidor web principal - rápido, direto e sem avisos de certificado)
  server = new ESPWebServer(wifiConfig.httpPort);

  // Iniciar servidor HTTPS na porta 443 apenas para redirecionar para HTTP e limpar cache HSTS de navegadores
  httpsServer = new ESPWebServerSecure(443);
  httpsServer->setServerKeyAndCert(server_key_der, server_key_der_len, server_cert_der, server_cert_der_len);
  httpsServer->onNotFound([]() {
    String host = httpsServer->hostHeader();
    int colon = host.indexOf(':');
    if (colon >= 0) host = host.substring(0, colon);
    if (host.length() == 0) host = "painel.local";
    String target = "http://" + host + httpsServer->uri();
    httpsServer->sendHeader("Location", target, true);
    httpsServer->sendHeader("Strict-Transport-Security", "max-age=0", true);
    httpsServer->send(302, "text/plain", "");
  });
  httpsServer->begin();
  
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
  server->on("/api/wifi/forget", HTTP_POST, handleWifiForget);
  
  server->on("/api/automation/config", HTTP_POST, handleAutomationConfig);
  server->on("/api/automation/mode",   HTTP_POST, handleAutomationMode);
  server->on("/api/automation/status", HTTP_GET,  handleAutomationStatus);
  
  // server->on("/api/modalidades", HTTP_GET, handleProxy); (Removido a pedido: usar direto https://esporte7.com.br:8080/api/modalidades)
  server->on("/api/campeonatos", HTTP_GET, handleProxy);
  server->on("/api/partidas", HTTP_GET, handleProxy);
  server->on("/api/sports", HTTP_GET, handleProxy);
  server->on("/api/clubs/toledao/championships", HTTP_GET, handleProxy);
  server->on("/api/proxy/sports", HTTP_GET, handleProxy);
  server->on("/api/proxy/campeonatos", HTTP_GET, handleProxy);
  server->on("/api/proxy/partidas", HTTP_GET, handleProxy);
  server->on("/api/proxy/etapas", HTTP_GET, handleProxy);
  server->on("/api/proxy/rodadas", HTTP_GET, handleProxy);
  server->on("/api/proxy", HTTP_GET, handleProxy);
  
  // POST routes for pushing data (gols, updates)
  server->on("/api/proxy_post/gols", HTTP_POST, handleProxyPost);
  
  // Placar: atualização automática via AJAX (HTTP GET) e comandos (HTTP POST)
  server->on("/api/scoreboard/state", HTTP_GET, handleScoreboardState);
  server->on("/api/scoreboard", HTTP_GET, handleScoreboardState);
  server->on("/api/state", HTTP_GET, handleScoreboardState);
  server->on("/api/scoreboard/action", HTTP_POST, handleScoreboardAction);
  
  // Rotas de detecção de Captive Portal (Android, Apple iOS/macOS, Windows, Firefox/Chrome)
  server->on("/generate_204", handleCaptivePortalRedirect);
  server->on("/gen_204", handleCaptivePortalRedirect);
  server->on("/hotspot-detect.html", handleCaptivePortalRedirect);
  server->on("/library/test/success.html", handleCaptivePortalRedirect);
  server->on("/connecttest.txt", handleCaptivePortalRedirect);
  server->on("/ncsi.txt", handleCaptivePortalRedirect);
  server->on("/success.txt", handleCaptivePortalRedirect);
  server->on("/canonical.html", handleCaptivePortalRedirect);
  server->on("/redirect", handleCaptivePortalRedirect);

  // Captive Portal / 404 fallback redirect
  server->onNotFound([]() {
    String uri = server->uri();
    
    // Suporte dinâmico para rotas de partidas da API (/api/championships/{id}/matches)
    if (uri.startsWith("/api/championships/") && uri.endsWith("/matches")) {
      handleProxy();
      return;
    }
    
    String host = server->hostHeader();
    
    // Se a requisição for de domínio externo (captive portal do celular/SO), redireciona para painel.local
    if (host.indexOf("painel.local") == -1 && host.indexOf("placar.local") == -1 && host.indexOf("192.168.4.1") == -1) {
      handleCaptivePortalRedirect();
      return;
    }
    
    // Se a rota não existir, redireciona para a raiz mantendo o host/protocolo atual
    server->sendHeader("Location", "/", true);
    server->send(302, "text/plain", "");
  });

  server->begin();
  Serial.printf("Servidor HTTP iniciado na porta %d (http://painel.local/)\n", wifiConfig.httpPort);
  
  // Start WebSocket server on custom port
  webSocket = new WebSocketsServer(wifiConfig.wsPort);
  webSocket->begin();
  webSocket->onEvent(webSocketEvent);
  Serial.printf("WebSocket iniciado na porta %d\n", wifiConfig.wsPort);
}

void loop() {
  // Feed web servers and captive portal DNS
  dnsServer.processNextRequest();
  if (server != nullptr) server->handleClient();
  if (httpsServer != nullptr) httpsServer->handleClient();
  if (webSocket != nullptr) webSocket->loop();
  
  unsigned long now = millis();

  // Keep chronometer accurate
  if (timerRunning) {
    if (now - timerLastMillis >= 1000) {
      unsigned long elapsedSecs = (now - timerLastMillis) / 1000;
      totalSeconds += elapsedSecs;
      timerLastMillis += elapsedSecs * 1000;
      
      broadcastState();
    }
  }
  
  // Atualização periódica exclusiva dos sinais nas portas I/O (fitas WS2812B) a cada 250 milissegundos
  // A página web NÃO é atualizada aqui; nenhuma mensagem de rede/WebSocket é transmitida
  static unsigned long lastLedsUpdateMillis = 0;
  if (now - lastLedsUpdateMillis >= 250) {
    lastLedsUpdateMillis = now;
    updatePhysicalDisplays();
  }
  
  // Manter o ponto de acesso AP 'esporte7system' sempre ativo em conjunto com a rede local (WIFI_AP_STA),
  // Manter o ponto de acesso AP 'esporte7system' sempre ativo em conjunto com a rede local (WIFI_AP_STA)
  static bool lastConnected = false;
  bool isConnected = (WiFi.status() == WL_CONNECTED);
  if (isConnected != lastConnected) {
    lastConnected = isConnected;
    if (isConnected) {
      Serial.printf("[Wi-Fi] Conectado à rede local com sucesso! IP local: %s\n", WiFi.localIP().toString().c_str());
      Serial.printf("[MEM] Free Heap: %d bytes\n", ESP.getFreeHeap());
    } else {
      Serial.println("[Wi-Fi] Desconectado da rede local! Ponto de acesso 'esporte7system' segue ativo.");
      dnsServer.start(53, "*", IPAddress(192, 168, 4, 1));
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
        for (int i = 0; i < 18; i++) {
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
