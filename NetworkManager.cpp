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
  DynamicJsonDocument doc(512);
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
  doc["totalSeconds"] = totalSeconds;
  
  // IDs de Partida, Campeonato e Rodada
  doc["partidaId"]        = automationConfig.partida;
  doc["campeonatoId"]     = automationConfig.campeonato;
  doc["rodadaId"]         = automationConfig.rodada;
  doc["partida"]          = automationConfig.partida;
  doc["campeonato"]       = automationConfig.campeonato;
  doc["rodada"]           = automationConfig.rodada;
  doc["match_id"]         = automationConfig.partida;
  doc["championship_id"]  = automationConfig.campeonato;
  doc["round_id"]         = automationConfig.rodada;
  doc["modalidade"]       = automationConfig.modalidade;
  doc["automationActive"]  = automationConfig.active;
  doc["automationMode"]    = automationConfig.mode;
  
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

void handleCaptivePortalRedirect() {
  String target = "http://painel.local/";

  server->sendHeader("Location", target, true);
  server->sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
  server->sendHeader("Pragma", "no-cache");
  server->sendHeader("Expires", "-1");
  server->send(302, "text/html", "<!DOCTYPE html><html><head><meta http-equiv='refresh' content='0;url=" + target + "'></head><body>Redirecionando para <a href='" + target + "'>" + target + "</a></body></html>");
}

void handleRoot() { 
  if (checkAuth()) {
    server->sendHeader("Location", "/painel.html", true);
    server->send(302, "text/plain", "");
    return;
  }
  server->send_P(200, "text/html", login_html); 
}
void handleUserAdm() { 
  if (!checkAuthRole("Administrador")) { server->sendHeader("Location", "/login.html", true); server->send(302, "text/plain", ""); return; }
  server->send_P(200, "text/html", user_adm_html); 
}
void handleLanConfig() { 
  if (!checkAuthRole("Administrador")) { server->sendHeader("Location", "/login.html", true); server->send(302, "text/plain", ""); return; }
  server->send_P(200, "text/html", lan_config_html); 
}
void handleSsidConfig() { 
  if (!checkAuthRole("Administrador")) { server->sendHeader("Location", "/login.html", true); server->send(302, "text/plain", ""); return; }
  server->send_P(200, "text/html", ssid_config_html); 
}
void handlePanelConfig() { 
  if (!checkAuthRole("Gerente")) { server->sendHeader("Location", "/login.html", true); server->send(302, "text/plain", ""); return; }
  server->sendHeader("Cache-Control", "no-store, no-cache, must-revalidate, max-age=0");
  server->sendHeader("Pragma", "no-cache");
  server->sendHeader("Expires", "0");
  server->send_P(200, "text/html", panel_config_html); 
}
void handlePainel() { 
  if (!checkAuth()) { server->sendHeader("Location", "/login.html", true); server->send(302, "text/plain", ""); return; }
  server->send_P(200, "text/html", painel_html); 
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
      } else if (strcmp(username, "esporte7") == 0) {
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
  
  bool isConnected = (WiFi.status() == WL_CONNECTED);
  doc["connected"] = isConnected;
  doc["ip"] = isConnected ? WiFi.localIP().toString() : WiFi.softAPIP().toString();
  doc["currentIp"] = isConnected ? WiFi.localIP().toString() : WiFi.softAPIP().toString();
  doc["currentSubnet"] = isConnected ? WiFi.subnetMask().toString() : "255.255.255.0";
  doc["currentGateway"] = isConnected ? WiFi.gatewayIP().toString() : "0.0.0.0";
  doc["currentDns"] = isConnected ? WiFi.dnsIP().toString() : "0.0.0.0";
  doc["subnet"] = doc["currentSubnet"];
  doc["gateway"] = doc["currentGateway"];
  doc["dns"] = doc["currentDns"];
  
  doc["ssid"] = isConnected ? WiFi.SSID() : wifiConfig.apSsid;
  doc["rssi"] = isConnected ? WiFi.RSSI() : 0;
  
  uint8_t mac[6];
  WiFi.macAddress(mac);
  char macStr[18];
  sprintf(macStr, "%02X:%02X:%02X:%02X:%02X:%02X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  doc["mac"] = macStr;
  doc["mode"] = isConnected ? "sta" : "ap";
  
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
  // Garantir que a interface STA esteja ativa para permitir o escaneamento
  wifi_mode_t currentMode = WiFi.getMode();
  if ((currentMode & WIFI_MODE_STA) == 0) {
    WiFi.mode(WIFI_MODE_APSTA);
    delay(100);
  }

  // Se o ESP32 estiver tentando conectar a um roteador (connecting),
  // o driver do Wi-Fi aborta o scan com erro ESP_ERR_WIFI_STATE (-2).
  // Chamar WiFi.disconnect(false) coloca a STA em repouso e libera o rádio.
  bool wasConnected = (WiFi.status() == WL_CONNECTED);
  if (!wasConnected) {
    WiFi.disconnect(false);
    delay(100);
  }

  Serial.println("[Wi-Fi] Iniciando escaneamento de redes...");
  WiFi.scanDelete();

  int16_t n = WiFi.scanNetworks(false, true, false, 250);
  if (n < 0) {
    Serial.printf("[Wi-Fi] Falha temporária no scan (%d), tentando novamente...\n", n);
    WiFi.disconnect(false);
    delay(200);
    n = WiFi.scanNetworks(false, true, false, 300);
  }
  Serial.printf("[Wi-Fi] Scan concluído. Redes detectadas: %d\n", n);

  DynamicJsonDocument doc(4096);
  JsonArray array = doc.to<JsonArray>();
  
  if (n > 0) {
    std::vector<String> seenSSIDs;
    for (int i = 0; i < n; ++i) {
      String ssid = WiFi.SSID(i);
      if (ssid.length() == 0) continue; // Ignorar redes ocultas sem SSID
      
      bool alreadySeen = false;
      for (const String& s : seenSSIDs) {
        if (s == ssid) {
          alreadySeen = true;
          break;
        }
      }
      if (!alreadySeen) {
        seenSSIDs.push_back(ssid);
        JsonObject net = array.createNestedObject();
        net["ssid"] = ssid;
        net["rssi"] = WiFi.RSSI(i);
        net["secure"] = (WiFi.encryptionType(i) != WIFI_AUTH_OPEN);
      }
    }
    WiFi.scanDelete();
  }
  
  // Se antes estava conectado, restabelece a conexão
  if (wasConnected && wifiConfig.wifiSsid.length() > 0) {
    WiFi.begin(wifiConfig.wifiSsid.c_str(), wifiConfig.wifiPass.c_str());
  }
  
  String response;
  serializeJson(doc, response);
  server->send(200, "application/json", response);
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

void handleWifiForget() {
  if (!checkAuthRole("Administrador")) { 
    server->send(401, "application/json", "{\"error\":\"unauthorized\"}"); 
    return; 
  }
  
  Serial.println("[Wi-Fi] Solicitado esquecer rede Wi-Fi...");
  
  // Limpar credenciais Wi-Fi da memória
  wifiConfig.wifiSsid = "";
  wifiConfig.wifiPass = "";
  
  // Atualizar NVS de preferências mantendo demais configurações salvas
  DynamicJsonDocument doc(1024);
  String wifiJson = preferences.getString("wifi", "");
  if (wifiJson.length() > 0) {
    deserializeJson(doc, wifiJson);
  }
  doc["wifiSsid"] = "";
  doc["wifiPass"] = "";
  String out;
  serializeJson(doc, out);
  preferences.putString("wifi", out);
  
  // Desconectar do roteador e apagar credenciais salvas no rádio Wi-Fi
  WiFi.disconnect(true, true);
  
  // Reativar e reconfigurar o AP para garantir contingência e acesso imediato
  WiFi.enableAP(true);
  WiFi.softAPConfig(IPAddress(192, 168, 4, 1), IPAddress(192, 168, 4, 1), IPAddress(255, 255, 255, 0));
  WiFi.softAP(wifiConfig.apSsid.c_str(), wifiConfig.apPass.c_str(), wifiConfig.apChannel);
  
  // SoftAP configurado para contingencia imediata
  
  server->send(200, "application/json", "{\"status\":\"success\",\"message\":\"Rede esquecida com sucesso!\"}");
  
  // Agendar reinício em 2 segundos para inicialização limpa no modo AP
  rebootScheduled = true;
  rebootTime = millis() + 2000;
}

void handleAutomationConfig() {
  if (!checkAuth()) { server->send(401, "application/json", "{\"error\":\"unauthorized\"}"); return; }
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

  // Reload local automation configs
  automationConfig.active = doc["active"] | true;
  automationConfig.mode = doc["mode"] | "automatico";
  automationConfig.dominio = cleanDomain(doc["dominio"] | "esportes7.com.br");
  automationConfig.porta = doc["porta"] | (doc["port"] | 0);
  automationConfig.prefixo = doc["prefixo"] | (doc["prefix"] | "/api/");
  automationConfig.modalidade = getStringField("modalidade");
  automationConfig.campeonato = getStringField("campeonato", "campeonatoId", "championship_id");
  automationConfig.partida = getStringField("partida", "partidaId", "match_id");
  automationConfig.etapa = getStringField("etapa");
  automationConfig.rodada = getStringField("rodada", "rodadaId", "round_id");
  
  Serial.print("Salvo automacao: Camp=");
  Serial.print(automationConfig.campeonato);
  Serial.print(", Rod=");
  Serial.print(automationConfig.rodada);
  Serial.print(", Part=");
  Serial.println(automationConfig.partida);

  server->send(200, "application/json", "{\"status\":\"success\"}");
}

void handleAutomationMode() {
  if (!checkAuth()) { server->send(401, "application/json", "{\"error\":\"unauthorized\"}"); return; }
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
  if (!checkAuth()) { server->send(401, "application/json", "{\"error\":\"unauthorized\"}"); return; }

  DynamicJsonDocument doc(512);
  doc["active"]         = automationConfig.active;
  doc["mode"]           = automationConfig.mode;
  doc["dominio"]        = automationConfig.dominio;
  doc["porta"]          = automationConfig.porta;
  doc["prefixo"]        = automationConfig.prefixo;
  doc["modalidade"]     = automationConfig.modalidade;
  doc["campeonato"]     = automationConfig.campeonato;
  doc["partida"]        = automationConfig.partida;
  doc["etapa"]          = automationConfig.etapa;
  doc["rodada"]         = automationConfig.rodada;
  doc["campeonatoId"]   = automationConfig.campeonato;
  doc["partidaId"]      = automationConfig.partida;
  doc["rodadaId"]       = automationConfig.rodada;
  doc["match_id"]       = automationConfig.partida;
  doc["championship_id"]= automationConfig.campeonato;
  doc["round_id"]       = automationConfig.rodada;

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

String cleanDomain(String d) {
  d.trim();
  d.replace("https://", "");
  d.replace("http://", "");
  while (d.endsWith("/")) d = d.substring(0, d.length() - 1);
  if (d == "" || d == "esporte7.com.br") d = "esportes7.com.br";
  return d;
}

String buildApiUrl(String baseInput, String targetPath) {
  baseInput.trim();
  bool isHttps = true;
  if (baseInput.startsWith("http://")) {
    isHttps = false;
    baseInput = baseInput.substring(7);
  } else if (baseInput.startsWith("https://")) {
    isHttps = true;
    baseInput = baseInput.substring(8);
  }
  
  while (baseInput.endsWith("/")) {
    baseInput = baseInput.substring(0, baseInput.length() - 1);
  }
  
  String prefix = automationConfig.prefixo.length() > 0 ? automationConfig.prefixo : "/api/";
  if (!prefix.startsWith("/")) prefix = "/" + prefix;
  if (!prefix.endsWith("/")) prefix = prefix + "/";

  // Se baseInput já termina com /api, remove para evitar duplicação (/api/api/...)
  if (baseInput.endsWith("/api")) {
    baseInput = baseInput.substring(0, baseInput.length() - 4);
    while (baseInput.endsWith("/")) {
      baseInput = baseInput.substring(0, baseInput.length() - 1);
    }
  }
  
  if (targetPath.startsWith("/")) {
    targetPath = targetPath.substring(1);
  }
  if (targetPath.startsWith("api/")) {
    targetPath = targetPath.substring(4);
  }
  
  String proto = isHttps ? "https://" : "http://";
  return proto + baseInput + prefix + targetPath;
}

// Proxy Endpoint to Query External Domain from ESP32 to prevent CORS issues
void handleProxy() {
  if (!checkAuth()) { server->send(401, "application/json", "{\"error\":\"unauthorized\"}"); return; }
  String domain = cleanDomain(server->arg("domain"));
  String port = server->arg("port");
  if (port == "" && server->hasArg("porta")) port = server->arg("porta");
  if (port == "" && automationConfig.porta > 0) port = String(automationConfig.porta);
  if (port == "8080" || port == "0" || port == "80" || port == "443") port = "";
  
  if (domain == "" || domain == "esporte7.com.br") {
    if (automationConfig.dominio != "") {
      domain = cleanDomain(automationConfig.dominio);
    } else {
      domain = "esportes7.com.br";
    }
  }
  
  // Se o domínio informado não tiver porta explícita, anexa a porta informada se houver porta customizada
  int colonIdx = domain.indexOf(':', domain.startsWith("http") ? 8 : 0);
  if (colonIdx == -1 && port.length() > 0) {
    domain += ":" + port;
  }
  
  String url = "";
  if (server->hasArg("url")) {
    url = server->arg("url");
    url.replace("esporte7.com.br:8080", "esportes7.com.br");
    url.replace("esporte7.com.br", "esportes7.com.br");
    url.replace(":8080/api", "/api");
    url.replace("/api/modalidades", "/api/sports");
    url.replace("/api/campeonatos", "/api/clubs/1/championships");
  } else {
    String uri = server->uri();
    String targetPath = "";
    if (uri.endsWith("modalidades") || uri.endsWith("sports")) {
      targetPath = "sports";
    } else if (uri.endsWith("campeonatos")) {
      String modId = server->hasArg("modalidade") ? server->arg("modalidade") : server->arg("sport_id");
      targetPath = "clubs/1/championships";
      if (modId.length() > 0) {
        targetPath += "?sport_id=" + urlEncode(modId);
      }
    } else if (uri.indexOf("championships") >= 0 && !uri.endsWith("/matches")) {
      String sportId = server->hasArg("sport_id") ? server->arg("sport_id") : server->arg("modalidade");
      targetPath = "clubs/1/championships";
      if (sportId.length() > 0) {
        targetPath += "?sport_id=" + urlEncode(sportId);
      }
    } else if (uri.endsWith("partidas")) {
      String campId = server->hasArg("campeonato") ? server->arg("campeonato") : server->arg("championship_id");
      targetPath = "championships/" + urlEncode(campId) + "/matches";
    } else if (uri.indexOf("matches") >= 0) {
      String campId = "";
      if (uri.startsWith("/api/championships/")) {
        int start = 19; // comprimento de "/api/championships/"
        int end = uri.indexOf("/matches", start);
        if (end > start) {
          campId = uri.substring(start, end);
        }
      }
      if (campId == "") {
        campId = server->hasArg("campeonato") ? server->arg("campeonato") : server->arg("championship_id");
      }
      targetPath = "championships/" + urlEncode(campId) + "/matches";
    } else {
      server->send(404, "application/json", "{\"error\":\"not found\"}");
      return;
    }
    url = buildApiUrl(domain, targetPath);
  }
  Serial.print("Proxy request: ");
  Serial.println(url);
  
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("[Proxy] AVISO: ESP32 não está conectado à rede Wi-Fi com internet (STA)!");
    server->sendHeader("Access-Control-Allow-Origin", "*");
    server->send(503, "application/json", "{\"error\":\"esp32_offline\",\"message\":\"ESP32 nao esta conectado ao Wi-Fi com internet. Conecte o placar a sua rede Wi-Fi.\"}");
    return;
  }

  HTTPClient http;
  http.setTimeout(15000);
  http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
  int httpCode = -1;
  
  if (url.startsWith("https://")) {
    WiFiClientSecure client;
    client.setInsecure(); // Disable HTTPS certificate check for flexibility
    client.setTimeout(15000);
    http.begin(client, url);
    http.addHeader("User-Agent", "Mozilla/5.0 (ESP32 Scoreboard)");
    http.addHeader("Accept", "application/json, text/plain, */*");
    http.addHeader("Accept-Encoding", "identity");
    http.addHeader("Connection", "close");
    httpCode = http.GET();
    
    Serial.printf("[Proxy] HTTPS status: %d\n", httpCode);
    if (httpCode == HTTP_CODE_OK) {
      server->sendHeader("Access-Control-Allow-Origin", "*");
      server->send(200, "application/json", http.getString());
      http.end();
      return;
    }
    if (httpCode < 0) {
      Serial.printf("[Proxy] HTTPS erro: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();
    
    // Fallback: tentar em HTTP puro se HTTPS falhar
    String plainUrl = "http://" + url.substring(8);
    Serial.print("[Proxy] HTTP fallback: ");
    Serial.println(plainUrl);
    WiFiClient plainClient;
    plainClient.setTimeout(15000);
    http.begin(plainClient, plainUrl);
    http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
    http.addHeader("User-Agent", "Mozilla/5.0 (ESP32 Scoreboard)");
    http.addHeader("Accept", "application/json, text/plain, */*");
    http.addHeader("Accept-Encoding", "identity");
    http.addHeader("Connection", "close");
    httpCode = http.GET();
    Serial.printf("[Proxy] HTTP fallback status: %d\n", httpCode);
    if (httpCode == HTTP_CODE_OK) {
      server->sendHeader("Access-Control-Allow-Origin", "*");
      server->send(200, "application/json", http.getString());
      http.end();
      return;
    }
    http.end();
  } else {
    WiFiClient plainClient;
    plainClient.setTimeout(15000);
    http.begin(plainClient, url);
    http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
    http.addHeader("User-Agent", "Mozilla/5.0 (ESP32 Scoreboard)");
    http.addHeader("Accept", "application/json, text/plain, */*");
    http.addHeader("Accept-Encoding", "identity");
    http.addHeader("Connection", "close");
    httpCode = http.GET();
    Serial.printf("[Proxy] HTTP status: %d\n", httpCode);
    if (httpCode == HTTP_CODE_OK) {
      server->sendHeader("Access-Control-Allow-Origin", "*");
      server->send(200, "application/json", http.getString());
      http.end();
      return;
    }
    http.end();
  }
  
  server->sendHeader("Access-Control-Allow-Origin", "*");
  server->send(httpCode > 0 ? httpCode : 500, "application/json", "{\"error\":\"proxy query failed\",\"code\":" + String(httpCode) + "}");
}

// Proxy Endpoint for POST Requests
void handleProxyPost() {
  if (!checkAuthRole("Gerente")) { server->send(401, "application/json", "{\"error\":\"unauthorized\"}"); return; }
  String domain = cleanDomain(server->arg("domain"));
  if (domain == "") {
    server->send(400, "application/json", "{\"error\":\"domain is required\"}");
    return;
  }
  
  String uri = server->uri();
  String targetPath = "";
  if (uri.endsWith("gols")) {
    targetPath = "/api/gols"; 
  } else {
    int postIdx = uri.indexOf("/api/proxy_post/");
    if (postIdx >= 0) {
      targetPath = uri.substring(postIdx + 15);
    } else {
      server->send(404, "application/json", "{\"error\":\"not found\"}");
      return;
    }
  }
  
  String payload = server->hasArg("plain") ? server->arg("plain") : "";
  String url = buildApiUrl(domain, targetPath);
  Serial.print("Proxy POST: ");
  Serial.println(url);
  
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("[Proxy POST] AVISO: ESP32 não está conectado à rede Wi-Fi com internet (STA)!");
    server->sendHeader("Access-Control-Allow-Origin", "*");
    server->send(503, "application/json", "{\"error\":\"esp32_offline\",\"message\":\"ESP32 nao esta conectado ao Wi-Fi com internet\"}");
    return;
  }

  HTTPClient http;
  http.setTimeout(15000);
  http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
  int httpCode = -1;
  
  if (url.startsWith("https://")) {
    WiFiClientSecure client;
    client.setInsecure();
    client.setTimeout(15000);
    http.begin(client, url);
    http.addHeader("User-Agent", "Mozilla/5.0 (ESP32 Scoreboard)");
    http.addHeader("Accept", "application/json, text/plain, */*");
    http.addHeader("Accept-Encoding", "identity");
    http.addHeader("Connection", "close");
    http.addHeader("Content-Type", "application/json");
    httpCode = http.POST(payload);
    if (httpCode >= 200 && httpCode < 300) {
      server->sendHeader("Access-Control-Allow-Origin", "*");
      server->send(httpCode, "application/json", http.getString());
      http.end();
      return;
    }
    http.end();
    
    // Fallback: tentar em HTTP puro se HTTPS falhar
    String plainUrl = "http://" + url.substring(8);
    Serial.print("Proxy HTTP POST fallback: ");
    Serial.println(plainUrl);
    WiFiClient plainClient;
    plainClient.setTimeout(15000);
    http.begin(plainClient, plainUrl);
    http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
    http.addHeader("User-Agent", "Mozilla/5.0 (ESP32 Scoreboard)");
    http.addHeader("Accept", "application/json, text/plain, */*");
    http.addHeader("Accept-Encoding", "identity");
    http.addHeader("Connection", "close");
    http.addHeader("Content-Type", "application/json");
    httpCode = http.POST(payload);
    if (httpCode >= 200 && httpCode < 300) {
      server->sendHeader("Access-Control-Allow-Origin", "*");
      server->send(httpCode, "application/json", http.getString());
      http.end();
      return;
    }
    http.end();
  } else {
    WiFiClient plainClient;
    plainClient.setTimeout(15000);
    http.begin(plainClient, url);
    http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
    http.addHeader("User-Agent", "Mozilla/5.0 (ESP32 Scoreboard)");
    http.addHeader("Accept", "application/json, text/plain, */*");
    http.addHeader("Accept-Encoding", "identity");
    http.addHeader("Connection", "close");
    http.addHeader("Content-Type", "application/json");
    httpCode = http.POST(payload);
    if (httpCode >= 200 && httpCode < 300) {
      server->sendHeader("Access-Control-Allow-Origin", "*");
      server->send(httpCode, "application/json", http.getString());
      http.end();
      return;
    }
    http.end();
  }
  
  server->sendHeader("Access-Control-Allow-Origin", "*");
  server->send(httpCode > 0 ? httpCode : 500, "application/json", "{\"error\":\"proxy POST query failed\",\"code\":" + String(httpCode) + "}");
}

// ==========================================
// Scoreboard State & Action HTTP Endpoints (AJAX)
// ==========================================

void handleScoreboardState() {
  DynamicJsonDocument doc(512);
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
  doc["totalSeconds"] = totalSeconds;
  
  // IDs de Partida, Campeonato e Rodada
  doc["partidaId"]        = automationConfig.partida;
  doc["campeonatoId"]     = automationConfig.campeonato;
  doc["rodadaId"]         = automationConfig.rodada;
  doc["partida"]          = automationConfig.partida;
  doc["campeonato"]       = automationConfig.campeonato;
  doc["rodada"]           = automationConfig.rodada;
  doc["match_id"]         = automationConfig.partida;
  doc["championship_id"]  = automationConfig.campeonato;
  doc["round_id"]         = automationConfig.rodada;
  doc["modalidade"]       = automationConfig.modalidade;
  doc["automationActive"]  = automationConfig.active;
  doc["automationMode"]    = automationConfig.mode;
  
  String json;
  serializeJson(doc, json);
  server->sendHeader("Access-Control-Allow-Origin", "*");
  server->sendHeader("Cache-Control", "no-store, no-cache, must-revalidate, max-age=0");
  server->send(200, "application/json", json);
}

void handleScoreboardAction() {
  if (!server->hasArg("plain")) {
    server->send(400, "application/json", "{\"error\":\"Missing payload\"}");
    return;
  }
  
  DynamicJsonDocument doc(512);
  DeserializationError error = deserializeJson(doc, server->arg("plain"));
  if (error) {
    server->send(400, "application/json", "{\"error\":\"Invalid JSON\"}");
    return;
  }
  
  const char* action = doc["action"];
  if (action && strcmp(action, "sync_external") == 0) {
    if (doc.containsKey("scoreA")) scoreA = doc["scoreA"].as<int>();
    if (doc.containsKey("scoreB")) scoreB = doc["scoreB"].as<int>();
    if (doc.containsKey("foulsA")) foulsA = doc["foulsA"].as<int>();
    if (doc.containsKey("foulsB")) foulsB = doc["foulsB"].as<int>();
    if (doc.containsKey("period")) period = doc["period"].as<int>();
    if (doc.containsKey("totalSeconds")) totalSeconds = doc["totalSeconds"].as<int>();
    if (doc.containsKey("timerRunning")) timerRunning = doc["timerRunning"].as<bool>();
    updatePhysicalDisplays();
    broadcastState();
    server->send(200, "application/json", "{\"status\":\"success\"}");
    return;
  }
  
  // Automation is overridden by manual adjustments
  if (automationConfig.active) {
    automationConfig.active = false;
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
  
  if (action) {
    if (strcmp(action, "change") == 0) {
      const char* target = doc["target"];
      int amount = doc["amount"] | 0;
      if (strcmp(target, "score-a") == 0) scoreA = constrain(scoreA + amount, 0, 999);
      else if (strcmp(target, "score-b") == 0) scoreB = constrain(scoreB + amount, 0, 999);
      else if (strcmp(target, "fouls-a") == 0) foulsA = constrain(foulsA + amount, 0, 99);
      else if (strcmp(target, "fouls-b") == 0) foulsB = constrain(foulsB + amount, 0, 99);
      else if (strcmp(target, "period") == 0) period = constrain(period + amount, 0, 99);
      updatePhysicalDisplays();
      broadcastState();
    } else if (strcmp(action, "set") == 0) {
      const char* target = doc["target"];
      int value = doc["value"] | 0;
      if (strcmp(target, "score-a") == 0) scoreA = constrain(value, 0, 999);
      else if (strcmp(target, "score-b") == 0) scoreB = constrain(value, 0, 999);
      else if (strcmp(target, "fouls-a") == 0) foulsA = constrain(value, 0, 99);
      else if (strcmp(target, "fouls-b") == 0) foulsB = constrain(value, 0, 99);
      else if (strcmp(target, "period") == 0) period = constrain(value, 0, 99);
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
  
  handleScoreboardState();
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
            scoreA = constrain(scoreA + amount, 0, 999);
          } else if (strcmp(target, "score-b") == 0) {
            scoreB = constrain(scoreB + amount, 0, 999);
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
            scoreA = constrain(value, 0, 999);
          } else if (strcmp(target, "score-b") == 0) {
            scoreB = constrain(value, 0, 999);
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
  if (millis() - lastPollMillis < 3000) return;
  lastPollMillis = millis();
  
  String dom = cleanDomain(automationConfig.dominio);
  if (dom == "" || dom == "esporte7.com.br") dom = "esportes7.com.br";
  int colonIdx = dom.indexOf(':', dom.startsWith("http") ? 8 : 0);
  if (colonIdx == -1 && automationConfig.porta > 0 && automationConfig.porta != 80 && automationConfig.porta != 443 && automationConfig.porta != 8080) {
    dom += ":" + String(automationConfig.porta);
  }
  
  String camp = automationConfig.campeonato;
  if (camp == "" || camp == "10") camp = "76";
  String url = "https://" + dom + "/api/championships/" + camp + "/matches";
  
  if (WiFi.status() != WL_CONNECTED) return;
  
  Serial.print("Poller request matches: ");
  Serial.println(url);
  
  int httpCode = -1;
  HTTPClient http;
  http.setTimeout(10000);
  http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);

  if (url.startsWith("https://")) {
    WiFiClientSecure client;
    client.setInsecure();
    client.setTimeout(10000);
    http.begin(client, url);
    http.addHeader("User-Agent", "Mozilla/5.0 (ESP32 Scoreboard)");
    http.addHeader("Accept", "application/json, text/plain, */*");
    http.addHeader("Accept-Encoding", "identity");
    http.addHeader("Connection", "close");
    httpCode = http.GET();
  } else {
    WiFiClient plainClient;
    plainClient.setTimeout(10000);
    http.begin(plainClient, url);
    http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
    http.addHeader("User-Agent", "Mozilla/5.0 (ESP32 Scoreboard)");
    http.addHeader("Accept", "application/json, text/plain, */*");
    http.addHeader("Accept-Encoding", "identity");
    http.addHeader("Connection", "close");
    httpCode = http.GET();
  }
  
  auto processResponse = [&](String payload) {
    DynamicJsonDocument doc(16384);
    DeserializationError error = deserializeJson(doc, payload);
    if (!error) {
      JsonObject targetMatch;
      bool found = false;

      if (doc.is<JsonArray>()) {
        JsonArray matches = doc.as<JsonArray>();
        String targetPartida = automationConfig.partida;
        String targetRodada = automationConfig.rodada;
        String targetMod = automationConfig.modalidade;

        // 1. Procura partida com ID específico
        if (targetPartida != "") {
          for (JsonObject m : matches) {
            String mId = m["id"].is<int>() ? String(m["id"].as<int>()) : m["id"].as<String>();
            if (mId == targetPartida) {
              targetMatch = m;
              found = true;
              break;
            }
          }
        }

        // 2. Se não encontrou por ID específico, filtra por rodada e modalidade buscando 'live'
        if (!found) {
          for (JsonObject m : matches) {
            // Filtro por rodada
            if (targetRodada != "" && targetRodada != "Todas as Rodadas") {
              int rNum = m["round_number"] | 0;
              const char* rName = m["round_name"] | "";
              String sNum = String(rNum);
              String sRod = "Rodada " + sNum;
              if (targetRodada != sNum && targetRodada != sRod && targetRodada != String(rName)) {
                continue;
              }
            }

            // Filtro por modalidade (se disponível no objeto da partida)
            if (targetMod != "") {
              if (m.containsKey("sport_id") && String(m["sport_id"].as<int>()) != targetMod) continue;
              if (m.containsKey("category_id") && String(m["category_id"].as<int>()) == targetMod) {
                // Correspondência com categoria
              }
            }

            const char* st = m["status"] | "";
            if (strcmp(st, "live") == 0 || strcmp(st, "in_progress") == 0) {
              targetMatch = m;
              found = true;
              break;
            }
            if (!found) {
              targetMatch = m;
            }
          }
          if (targetMatch) found = true;
        }

        // 3. Fallback: primeira 'live' ou primeira partida geral
        if (!found) {
          for (JsonObject m : matches) {
            const char* st = m["status"] | "";
            if (strcmp(st, "live") == 0 || strcmp(st, "in_progress") == 0) {
              targetMatch = m;
              found = true;
              break;
            }
          }
          if (!found && matches.size() > 0) {
            targetMatch = matches[0];
            found = true;
          }
        }
      } else if (doc.is<JsonObject>()) {
        if (doc.containsKey("match")) targetMatch = doc["match"];
        else targetMatch = doc.as<JsonObject>();
        found = true;
      }

      if (found) {
        int newScoreA = targetMatch["home_score"] | 0;
        int newScoreB = targetMatch["away_score"] | 0;
        bool stateChanged = false;

        if (scoreA != newScoreA || scoreB != newScoreB) {
          scoreA = newScoreA;
          scoreB = newScoreB;
          stateChanged = true;
        }

        if (targetMatch.containsKey("match_details")) {
          JsonObject md = targetMatch["match_details"];
          if (md.containsKey("current_timer_value")) {
            int newSecs = md["current_timer_value"].as<int>();
            bool newRunning = md["timer_running"] | false;
            if (totalSeconds != newSecs || timerRunning != newRunning) {
              totalSeconds = newSecs;
              timerRunning = newRunning;
              stateChanged = true;
            }
          }
        }

        if (targetMatch.containsKey("round_number")) {
          int newPeriod = targetMatch["round_number"].as<int>();
          if (period != newPeriod && newPeriod > 0) {
            period = newPeriod;
            stateChanged = true;
          }
        }

        if (stateChanged) {
          updatePhysicalDisplays();
          broadcastState();
        }
      }
    }
  };
  
  if (httpCode == HTTP_CODE_OK) {
    String payload = http.getString();
    processResponse(payload);
  } else if (url.startsWith("https://")) {
    // Fallback para HTTP puro se HTTPS falhar
    http.end();
    String plainUrl = "http://" + url.substring(8);
    WiFiClient plainClient;
    plainClient.setTimeout(10000);
    Serial.print("Poller request (HTTP fallback): ");
    Serial.println(plainUrl);
    
    http.begin(plainClient, plainUrl);
    http.addHeader("User-Agent", "Mozilla/5.0 (ESP32 Scoreboard)");
    http.addHeader("Accept", "application/json, text/plain, */*");
    httpCode = http.GET();
    if (httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      processResponse(payload);
    }
  }
  http.end();
}

// ==========================================
// Setup and Loop Definitions
