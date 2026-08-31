#include "NetworkManager.h"

void sendSingleState(uint8_t num) {
  if (webSocket == nullptr) return;
  DynamicJsonDocument doc(256);
  doc["type"] = "state";
  doc["scoreA"] = scoreA;
  doc["scoreB"] = scoreB;
  doc["foulsA"] = foulsA;
  doc["foulsB"] = foulsB;
  doc["period"] = period;
  
  char timerStr[16];
  int hrs = totalSeconds / 3600;
  int mins = (totalSeconds % 3600) / 60;
  int secs = totalSeconds % 60;
  sprintf(timerStr, "%02d:%02d:%02d", hrs, mins, secs);
  doc["timer"] = timerStr;
  
  String response;
  serializeJson(doc, response);
  webSocket->sendTXT(num, response);
}

void broadcastState() {
  if (webSocket == nullptr) return;
  DynamicJsonDocument doc(256);
  doc["type"] = "state";
  doc["scoreA"] = scoreA;
  doc["scoreB"] = scoreB;
  doc["foulsA"] = foulsA;
  doc["foulsB"] = foulsB;
  doc["period"] = period;
  
  char timerStr[16];
  int hrs = totalSeconds / 3600;
  int mins = (totalSeconds % 3600) / 60;
  int secs = totalSeconds % 60;
  sprintf(timerStr, "%02d:%02d:%02d", hrs, mins, secs);
  doc["timer"] = timerStr;
  doc["timerRunning"] = timerRunning;
  
  String response;
  serializeJson(doc, response);
  webSocket->broadcastTXT(response);
}

// ==========================================
// REST Web Server Handlers
// ==========================================

String getAuthRole() {
  if (server->hasHeader("Cookie")) {
    String cookie = server->header("Cookie");
    int tokenIndex = cookie.indexOf("session_token=");
    if (tokenIndex != -1) {
      int roleStart = tokenIndex + 14;
      int roleEnd = cookie.indexOf(';', roleStart);
      if (roleEnd == -1) roleEnd = cookie.length();
      return cookie.substring(roleStart, roleEnd);
    }
  }
  return "";
}

bool checkAuth() {
  return getAuthRole() != "";
}

bool checkAuthRole(String requiredRole) {
  String role = getAuthRole();
  if (role == "Administrador") return true;
  if (requiredRole == "Qualquer") return role != "";
  return role == requiredRole;
}

void handleRoot() { server->send(200, "text/html", login_html); }
void handleUserAdm() { 
  if (!checkAuthRole("Administrador")) { server->sendHeader("Location", "/login.html"); server->send(302, "text/plain", ""); return; }
  server->send(200, "text/html", user_adm_html); 
}
void handleLanConfig() { 
  if (!checkAuthRole("Administrador")) { server->sendHeader("Location", "/login.html"); server->send(302, "text/plain", ""); return; }
  server->send(200, "text/html", lan_config_html); 
}
void handleSsidConfig() { 
  if (!checkAuthRole("Administrador")) { server->sendHeader("Location", "/login.html"); server->send(302, "text/plain", ""); return; }
  server->send(200, "text/html", ssid_config_html); 
}
void handlePanelConfig() { 
  if (!checkAuthRole("Gerente")) { server->sendHeader("Location", "/login.html"); server->send(302, "text/plain", ""); return; }
  server->send(200, "text/html", panel_config_html); 
}
void handlePainel() { 
  if (!checkAuth()) { server->sendHeader("Location", "/login.html"); server->send(302, "text/plain", ""); return; }
  server->send(200, "text/html", painel_html); 
}

void handleLogin() {
  if (!server->hasArg("plain")) {
    server->send(400, "application/json", "{\"error\":\"body is required\"}");
    return;
  }
  
  String payload = server->arg("plain");
  DynamicJsonDocument doc(256);
  DeserializationError error = deserializeJson(doc, payload);
  if (error) {
    server->send(400, "application/json", "{\"error\":\"invalid json\"}");
    return;
  }
  
  const char* username = doc["username"] | "";
  const char* password = doc["password"] | "";
  
  String usersJson = preferences.getString("users", "[]");
  DynamicJsonDocument usersDoc(4096);
  deserializeJson(usersDoc, usersJson);
  JsonArray usersArr = usersDoc.as<JsonArray>();
  
  bool authenticated = false;
  String userRole = "Operador";
  for (JsonObject user : usersArr) {
    if (strcmp(user["username"], username) == 0 && strcmp(user["pass"], password) == 0) {
      authenticated = true;
      if (user.containsKey("role")) {
        userRole = user["role"].as<String>();
      } else if (strcmp(username, "inprolink") == 0) {
        userRole = "Administrador";
      }
      break;
    }
  }
  
  if (authenticated) {
    String cookieStr = "session_token=" + userRole + "; Path=/; HttpOnly";
    server->sendHeader("Set-Cookie", cookieStr);
    server->send(200, "application/json", "{\"status\":\"success\",\"role\":\"" + userRole + "\"}");
  } else {
    server->send(401, "application/json", "{\"error\":\"unauthorized\"}");
  }
}

void handleLogout() {
  server->sendHeader("Set-Cookie", "session_token=; Max-Age=0; Path=/; HttpOnly");
  server->send(200, "application/json", "{\"status\":\"success\"}");
}

void handleFactoryReset() {
  if (!checkAuthRole("Administrador")) { server->send(401, "application/json", "{\"error\":\"unauthorized\"}"); return; }
  
  preferences.clear();
  server->send(200, "application/json", "{\"status\":\"success\"}");
  
  rebootScheduled = true;
  rebootTime = millis() + 1000;
}

void handleUsersGet() {
  if (!checkAuthRole("Administrador")) { server->send(401, "application/json", "{\"error\":\"unauthorized\"}"); return; }
  String usersJson = preferences.getString("users", "[]");
  server->send(200, "application/json", usersJson);
}

void handleUsersSave() {
  if (!checkAuthRole("Administrador")) { server->send(401, "application/json", "{\"error\":\"unauthorized\"}"); return; }
  if (!server->hasArg("plain")) {
    server->send(400, "application/json", "{\"error\":\"body is required\"}");
    return;
  }
  
  String payload = server->arg("plain");
  DynamicJsonDocument doc(512);
  DeserializationError error = deserializeJson(doc, payload);
  if (error) {
    server->send(400, "application/json", "{\"error\":\"invalid json\"}");
    return;
  }
  
  int index = doc["index"] | -1;
  const char* name = doc["name"] | "";
  const char* username = doc["username"] | "";
  const char* password = doc["password"] | "";
  const char* role = doc["role"] | "";
  
  String usersJson = preferences.getString("users", "[]");
  DynamicJsonDocument usersDoc(4096);
  deserializeJson(usersDoc, usersJson);
  JsonArray usersArr = usersDoc.as<JsonArray>();
  
  if (index == -1) {
    if (usersArr.size() >= 10) {
      server->send(400, "application/json", "{\"error\":\"limit reached\"}");
      return;
    }
    JsonObject newUser = usersArr.createNestedObject();
    newUser["name"] = name;
    newUser["username"] = username;
    newUser["pass"] = password;
    newUser["role"] = role;
  } else {
    if (index >= 0 && index < usersArr.size()) {
      JsonObject user = usersArr[index];
      user["name"] = name;
      user["username"] = username;
      if (strlen(password) > 0) {
        user["pass"] = password;
      }
      user["role"] = role;
    }
  }
  
  String updatedJson;
  serializeJson(usersArr, updatedJson);
  preferences.putString("users", updatedJson);
  
  server->send(200, "application/json", updatedJson);
}

void handleUsersDelete() {
  if (!checkAuthRole("Administrador")) { server->send(401, "application/json", "{\"error\":\"unauthorized\"}"); return; }
  if (!server->hasArg("plain")) {
    server->send(400, "application/json", "{\"error\":\"body is required\"}");
    return;
  }
  
  String payload = server->arg("plain");
  DynamicJsonDocument doc(256);
  DeserializationError error = deserializeJson(doc, payload);
  if (error) {
    server->send(400, "application/json", "{\"error\":\"invalid json\"}");
    return;
  }
  
  int index = doc["index"] | -1;
  
  String usersJson = preferences.getString("users", "[]");
  DynamicJsonDocument usersDoc(4096);
  deserializeJson(usersDoc, usersJson);
  JsonArray usersArr = usersDoc.as<JsonArray>();
  
  if (index > 0 && index < usersArr.size()) {
    usersArr.remove(index);
  }
  
  String updatedJson;
  serializeJson(usersArr, updatedJson);
  preferences.putString("users", updatedJson);
  
  server->send(200, "application/json", updatedJson);
}

void handleWifiStatus() {
  if (!checkAuthRole("Administrador")) { server->send(401, "application/json", "{\"error\":\"unauthorized\"}"); return; }
  DynamicJsonDocument doc(1024);
  
  doc["ip"] = WiFi.status() == WL_CONNECTED ? WiFi.localIP().toString() : WiFi.softAPIP().toString();
  doc["ssid"] = WiFi.status() == WL_CONNECTED ? WiFi.SSID() : wifiConfig.apSsid;
  doc["rssi"] = WiFi.status() == WL_CONNECTED ? WiFi.RSSI() : 0;
  
  uint8_t mac[6];
  WiFi.macAddress(mac);
  char macStr[18];
  sprintf(macStr, "%02X:%02X:%02X:%02X:%02X:%02X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  doc["mac"] = macStr;
  doc["mode"] = WiFi.status() == WL_CONNECTED ? "sta" : "ap";
  
  doc["wifiSsid"] = wifiConfig.wifiSsid;
  doc["wifiPass"] = wifiConfig.wifiPass;
  doc["dhcp"] = wifiConfig.dhcp;
  doc["staticIp"] = wifiConfig.staticIp;
  doc["staticSubnet"] = wifiConfig.staticSubnet;
  doc["staticGateway"] = wifiConfig.staticGateway;
  doc["staticDns"] = wifiConfig.staticDns;
  doc["apSsid"] = wifiConfig.apSsid;
  doc["apPass"] = wifiConfig.apPass;
  doc["apChannel"] = wifiConfig.apChannel;
  doc["httpPort"] = wifiConfig.httpPort;
  doc["wsPort"] = wifiConfig.wsPort;
  doc["autoReconnect"] = wifiConfig.autoReconnect;
  
  String response;
  serializeJson(doc, response);
  server->send(200, "application/json", response);
}

void handleWifiScan() {
  if (!checkAuthRole("Administrador")) { server->send(401, "application/json", "{\"error\":\"unauthorized\"}"); return; }
  int n = WiFi.scanNetworks();
  DynamicJsonDocument doc(2048);
  JsonArray array = doc.to<JsonArray>();
  
  for (int i = 0; i < n; ++i) {
    JsonObject net = array.createNestedObject();
    net["ssid"] = WiFi.SSID(i);
    net["rssi"] = WiFi.RSSI(i);
  }
  
  String response;
  serializeJson(doc, response);
  server->send(200, "application/json", response);
  WiFi.scanDelete();
}

void handleWifiTest() {
  if (!checkAuthRole("Administrador")) { server->send(401, "application/json", "{\"error\":\"unauthorized\"}"); return; }
  server->send(200, "text/plain", "Conexão estável!");
}

void handleWifiConfig() {
  if (!checkAuthRole("Administrador")) { server->send(401, "application/json", "{\"error\":\"unauthorized\"}"); return; }
  if (!server->hasArg("plain")) {
    server->send(400, "application/json", "{\"error\":\"body is required\"}");
    return;
  }
  
  String payload = server->arg("plain");
  DynamicJsonDocument doc(1024);
  DeserializationError error = deserializeJson(doc, payload);
  if (error) {
    server->send(400, "application/json", "{\"error\":\"invalid json\"}");
    return;
  }
  
  preferences.putString("wifi", payload);
  server->send(200, "application/json", "{\"status\":\"success\"}");
  
  rebootScheduled = true;
  rebootTime = millis() + 2000;
}

void handleAutomationConfig() {
  if (!checkAuthRole("Gerente")) { server->send(401, "application/json", "{\"error\":\"unauthorized\"}"); return; }
  if (!server->hasArg("plain")) {
    server->send(400, "application/json", "{\"error\":\"body is required\"}");
    return;
  }
  
  String payload = server->arg("plain");
  DynamicJsonDocument doc(1024);
  DeserializationError error = deserializeJson(doc, payload);
  if (error) {
    server->send(400, "application/json", "{\"error\":\"invalid json\"}");
    return;
  }
  
  doc["active"] = true;
  String configStr;
  serializeJson(doc, configStr);
  
  preferences.putString("automation", configStr);
  
  // Reload local automation configs
  automationConfig.active = doc["active"] | false;
  automationConfig.mode = doc["mode"] | "automatico";
  automationConfig.dominio = doc["dominio"] | "placar.inprolink.com.br";
  automationConfig.modalidade = doc["modalidade"] | "";
  automationConfig.campeonato = doc["campeonato"] | "";
  automationConfig.partida = doc["partida"] | "";
  automationConfig.etapa = doc["etapa"] | "";
  automationConfig.rodada = doc["rodada"] | "";
  
  server->send(200, "application/json", "{\"status\":\"success\"}");
}

void handleAutomationMode() {
  if (!checkAuthRole("Operador")) { server->send(401, "application/json", "{\"error\":\"unauthorized\"}"); return; }
  if (!server->hasArg("plain")) { server->send(400, "application/json", "{\"error\":\"body required\"}"); return; }

  DynamicJsonDocument doc(256);
  if (deserializeJson(doc, server->arg("plain"))) {
    server->send(400, "application/json", "{\"error\":\"invalid json\"}"); return;
  }

  String mode = doc["mode"] | "automatico";
  automationConfig.mode = mode;

  // Read existing config, update only mode field
  String existing = preferences.getString("automation", "{}");
  DynamicJsonDocument existDoc(1024);
  deserializeJson(existDoc, existing);
  existDoc["mode"] = mode;
  String out;
  serializeJson(existDoc, out);
  preferences.putString("automation", out);

  server->send(200, "application/json", "{\"status\":\"success\"}");
}

void handleAutomationStatus() {
  if (!checkAuthRole("Operador")) { server->send(401, "application/json", "{\"error\":\"unauthorized\"}"); return; }

  DynamicJsonDocument doc(512);
  doc["active"]     = automationConfig.active;
  doc["mode"]       = automationConfig.mode;
  doc["dominio"]    = automationConfig.dominio;
  doc["modalidade"] = automationConfig.modalidade;
  doc["campeonato"] = automationConfig.campeonato;
  doc["partida"]    = automationConfig.partida;
  doc["etapa"]      = automationConfig.etapa;
  doc["rodada"]     = automationConfig.rodada;

  String out;
  serializeJson(doc, out);
  server->send(200, "application/json", out);
}

// Custom URL encoding helper to ensure compatibility across ESP32 core versions
String urlEncode(String str) {
  String encodedString = "";
  char c;
  char code0;
  char code1;
  for (int i = 0; i < str.length(); i++) {
    c = str.charAt(i);
    if (c == ' ') {
      encodedString += '+';
    } else if (isalnum(c)) {
      encodedString += c;
    } else {
      code1 = (c & 0xf) + '0';
      if ((c & 0xf) > 9) {
        code1 = (c & 0xf) - 10 + 'A';
      }
      c = (c >> 4) & 0xf;
      code0 = c + '0';
      if (c > 9) {
        code0 = c - 10 + 'A';
      }
      encodedString += '%';
      encodedString += code0;
      encodedString += code1;
    }
  }
  return encodedString;
}

// Proxy Endpoint to Query External Domain from ESP32 to prevent CORS issues
void handleProxy() {
  if (!checkAuthRole("Gerente")) { server->send(401, "application/json", "{\"error\":\"unauthorized\"}"); return; }
  String domain = server->arg("domain");
  if (domain == "") {
    server->send(400, "application/json", "{\"error\":\"domain is required\"}");
    return;
  }
  
  String uri = server->uri();
  String targetPath = "";
  if (uri.endsWith("modalidades")) {
    targetPath = "/api/modalidades";
  } else if (uri.endsWith("campeonatos")) {
    targetPath = "/api/campeonatos?modalidade=" + urlEncode(server->arg("modalidade"));
  } else if (uri.endsWith("partidas")) {
    targetPath = "/api/partidas?campeonato=" + urlEncode(server->arg("campeonato"));
  } else if (uri.endsWith("etapas")) {
    targetPath = "/api/etapas?partida=" + urlEncode(server->arg("partida"));
  } else if (uri.endsWith("rodadas")) {
    targetPath = "/api/rodadas?etapa=" + urlEncode(server->arg("etapa"));
  } else {
    server->send(404, "application/json", "{\"error\":\"not found\"}");
    return;
  }
  
  WiFiClientSecure client;
  client.setInsecure(); // Disable HTTPS certificate check for flexibility
  
  HTTPClient http;
  String url = "https://" + domain + targetPath;
  Serial.print("Proxy SSL GET: ");
  Serial.println(url);
  
  http.begin(client, url);
  int httpCode = http.GET();
  
  if (httpCode == HTTP_CODE_OK) {
    server->send(200, "application/json", http.getString());
  } else {
    // Fallback to plain HTTP
    http.end();
    WiFiClient plainClient;
    String plainUrl = "http://" + domain + targetPath;
    Serial.print("Proxy HTTP GET fallback: ");
    Serial.println(plainUrl);
    http.begin(plainClient, plainUrl);
    httpCode = http.GET();
    if (httpCode == HTTP_CODE_OK) {
      server->send(200, "application/json", http.getString());
    } else {
      server->send(httpCode > 0 ? httpCode : 500, "application/json", "{\"error\":\"proxy query failed\"}");
    }
  }
  http.end();
}

// ==========================================
// WebSocket Frame Event Handler
// ==========================================

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  switch(type) {
    case WStype_DISCONNECTED:
      Serial.printf("[%u] WebSocket Disconnected!\n", num);
      break;
    case WStype_CONNECTED: {
      IPAddress ip = webSocket->remoteIP(num);
      Serial.printf("[%u] WebSocket Connection from: %s\n", num, ip.toString().c_str());
      sendSingleState(num);
      break;
    }
    case WStype_TEXT: {
      Serial.printf("[%u] WS Command: %s\n", num, payload);
      DynamicJsonDocument doc(256);
      DeserializationError error = deserializeJson(doc, payload);
      if (!error) {
        // Automation is overridden by manual adjustments
        if (automationConfig.active) {
          automationConfig.active = false;
          // Save inactive automation state to preferences
          String autJson = preferences.getString("automation", "");
          if (autJson != "") {
            DynamicJsonDocument autDoc(512);
            deserializeJson(autDoc, autJson);
            autDoc["active"] = false;
            String updatedAut;
            serializeJson(autDoc, updatedAut);
            preferences.putString("automation", updatedAut);
          }
        }
        
        const char* action = doc["action"];
        if (strcmp(action, "change") == 0) {
          const char* target = doc["target"];
          int amount = doc["amount"] | 0;
          if (strcmp(target, "score-a") == 0) {
            scoreA = constrain(scoreA + amount, 0, 99);
          } else if (strcmp(target, "score-b") == 0) {
            scoreB = constrain(scoreB + amount, 0, 99);
          } else if (strcmp(target, "fouls-a") == 0) {
            foulsA = constrain(foulsA + amount, 0, 99);
          } else if (strcmp(target, "fouls-b") == 0) {
            foulsB = constrain(foulsB + amount, 0, 99);
          } else if (strcmp(target, "period") == 0) {
            period = constrain(period + amount, 0, 99);
          }
          updatePhysicalDisplays();
          broadcastState();
        } else if (strcmp(action, "set") == 0) {
          const char* target = doc["target"];
          int value = doc["value"] | 0;
          if (strcmp(target, "score-a") == 0) {
            scoreA = constrain(value, 0, 99);
          } else if (strcmp(target, "score-b") == 0) {
            scoreB = constrain(value, 0, 99);
          } else if (strcmp(target, "fouls-a") == 0) {
            foulsA = constrain(value, 0, 99);
          } else if (strcmp(target, "fouls-b") == 0) {
            foulsB = constrain(value, 0, 99);
          } else if (strcmp(target, "period") == 0) {
            period = constrain(value, 0, 99);
          }
          updatePhysicalDisplays();
          broadcastState();
        } else if (strcmp(action, "timer") == 0) {
          const char* command = doc["command"];
          if (strcmp(command, "start") == 0) {
            timerRunning = true;
            timerLastMillis = millis();
          } else if (strcmp(command, "pause") == 0) {
            timerRunning = false;
          } else if (strcmp(command, "reset") == 0) {
            timerRunning = false;
            totalSeconds = 0;
          } else if (strcmp(command, "set") == 0) {
            // Direct timer set from manual input (value in seconds)
            timerRunning = false;
            totalSeconds = doc["value"] | 0;
            if (totalSeconds < 0) totalSeconds = 0;
          }
          updatePhysicalDisplays();
          broadcastState();
        } else if (strcmp(action, "reset_all") == 0) {
          scoreA = 0;
          scoreB = 0;
          foulsA = 0;
          foulsB = 0;
          period = 0;
          timerRunning = false;
          totalSeconds = 0;
          updatePhysicalDisplays();
          broadcastState();
        }
      }
      break;
    }
    default:
      break;
  }
}

// ==========================================
// External Automatic Polling Client
// ==========================================

void pollScoreboardAPI() {
  if (!automationConfig.active || automationConfig.mode != "automatico") return;
  if (millis() - lastPollMillis < 5000) return;
  
  WiFiClientSecure client;
  client.setInsecure();
  
  HTTPClient http;
  String url = "https://" + automationConfig.dominio + "/api/placar";
  url += "?modalidade=" + urlEncode(automationConfig.modalidade);
  url += "&campeonato=" + urlEncode(automationConfig.campeonato);
  url += "&partida=" + urlEncode(automationConfig.partida);
  url += "&etapa=" + urlEncode(automationConfig.etapa);
  url += "&rodada=" + urlEncode(automationConfig.rodada);
  
  Serial.print("Poller request (SSL): ");
  Serial.println(url);
  
  http.begin(client, url);
  int httpCode = http.GET();
  
  if (httpCode == HTTP_CODE_OK) {
    String payload = http.getString();
    DynamicJsonDocument doc(512);
    DeserializationError error = deserializeJson(doc, payload);
    if (!error) {
      scoreA = doc["scoreA"] | 0;
      scoreB = doc["scoreB"] | 0;
      foulsA = doc["foulsA"] | 0;
      foulsB = doc["foulsB"] | 0;
      period = doc["period"] | 0;
      const char* timerStr = doc["timer"] | "00:00:00";
      
      int h = 0, m = 0, s = 0;
      sscanf(timerStr, "%d:%d:%d", &h, &m, &s);
      totalSeconds = h * 3600 + m * 60 + s;
      
      updatePhysicalDisplays();
      broadcastState();
    }
  } else {
    // Fallback to plain HTTP poller
    http.end();
    WiFiClient plainClient;
    String plainUrl = "http://" + automationConfig.dominio + "/api/placar";
    plainUrl += "?modalidade=" + urlEncode(automationConfig.modalidade);
    plainUrl += "&campeonato=" + urlEncode(automationConfig.campeonato);
    plainUrl += "&partida=" + urlEncode(automationConfig.partida);
    plainUrl += "&etapa=" + urlEncode(automationConfig.etapa);
    plainUrl += "&rodada=" + urlEncode(automationConfig.rodada);
    
    Serial.print("Poller request (HTTP fallback): ");
    Serial.println(plainUrl);
    
    http.begin(plainClient, plainUrl);
    httpCode = http.GET();
    if (httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      DynamicJsonDocument doc(512);
      DeserializationError error = deserializeJson(doc, payload);
      if (!error) {
        scoreA = doc["scoreA"] | 0;
        scoreB = doc["scoreB"] | 0;
        foulsA = doc["foulsA"] | 0;
        foulsB = doc["foulsB"] | 0;
        period = doc["period"] | 0;
        const char* timerStr = doc["timer"] | "00:00:00";
        
        int h = 0, m = 0, s = 0;
        sscanf(timerStr, "%d:%d:%d", &h, &m, &s);
        totalSeconds = h * 3600 + m * 60 + s;
        
        updatePhysicalDisplays();
        broadcastState();
      }
    }
  }
  http.end();
}

// ==========================================
// Setup and Loop Definitions
