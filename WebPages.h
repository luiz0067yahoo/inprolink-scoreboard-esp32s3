#ifndef WEB_PAGES_H
#define WEB_PAGES_H

#include <Arduino.h>

// ==========================================
// Embedded Web Assets (HTML/CSS/JS)
// ==========================================

const char login_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="pt-BR">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Login Administrador - Inprolink System</title>

  <style>
    * {
      box-sizing: border-box;
      margin: 0;
      padding: 0;
      font-family: 'Montserrat', sans-serif;
      user-select: none;
    }

    body {
      background-color: #050505;
      color: #ffffff;
      display: flex;
      justify-content: center;
      align-items: center;
      min-height: 100vh;
      padding: 20px;
    }

    .login-container {
      width: 100%;
      max-width: 420px;
      background-color: #0a0a0a;
      border-radius: 16px;
      padding: 35px 30px;
      border: 2px solid #222;
      box-shadow: 0 10px 30px rgba(0, 0, 0, 0.9), 0 0 20px rgba(255, 26, 26, 0.15);
      display: flex;
      flex-direction: column;
      align-items: center;
    }

    /* Cabeçalho e Logo */
    .brand-header {
      text-align: center;
      margin-bottom: 25px;
    }

    .brand-logo {
      width: 70px;
      height: 70px;
      background: #ffffff;
      border: 3px solid #1a365d;
      border-radius: 50%;
      display: flex;
      flex-direction: column;
      align-items: center;
      justify-content: center;
      margin: 0 auto 12px auto;
      box-shadow: 0 0 15px rgba(255, 255, 255, 0.2);
    }

    .brand-badge {
      width: 34px;
      height: 34px;
      background: #1a365d;
      border-radius: 50%;
      color: #fff;
      display: flex;
      align-items: center;
      justify-content: center;
      font-weight: 900;
      font-size: 0.75rem;
      border: 2px solid #e53e3e;
    }

    .brand-title {
      font-family: 'Orbitron', monospace;
      font-size: 1.2rem;
      font-weight: 900;
      letter-spacing: 2px;
      color: #fff;
    }

    .brand-subtitle {
      font-size: 0.75rem;
      color: #888;
      text-transform: uppercase;
      letter-spacing: 1px;
      margin-top: 4px;
    }

    /* Form Diagnóstico/Campos */
    .login-form {
      width: 100%;
      display: flex;
      flex-direction: column;
      gap: 18px;
    }

    .input-group {
      display: flex;
      flex-direction: column;
      gap: 6px;
    }

    .input-label {
      font-size: 0.8rem;
      font-weight: 700;
      color: #bbb;
      text-transform: uppercase;
      letter-spacing: 0.5px;
    }

    .input-wrapper {
      position: relative;
      display: flex;
      align-items: center;
    }

    .input-wrapper i {
      position: absolute;
      left: 14px;
      color: #ff1a1a;
      font-size: 1rem;
    }

    .input-field {
      width: 100%;
      padding: 12px 14px 12px 42px;
      background-color: #141414;
      border: 2px solid #333;
      border-radius: 8px;
      color: #fff;
      font-size: 0.95rem;
      outline: none;
      transition: border-color 0.2s, box-shadow 0.2s;
    }

    .input-field:focus {
      border-color: #ff1a1a;
      box-shadow: 0 0 8px rgba(255, 26, 26, 0.4);
    }

    /* Caixas Informativas */
    .credentials-box {
      background: #111;
      border-left: 3px solid #1565c0;
      border-radius: 6px;
      padding: 10px 12px;
      font-size: 0.75rem;
      color: #aaa;
      line-height: 1.4;
    }

    .credentials-box strong {
      color: #fff;
    }

    .credentials-box code {
      background: #222;
      color: #ff4444;
      padding: 2px 5px;
      border-radius: 4px;
      font-family: monospace;
    }

    /* Botão de Entrada */
    .btn-login {
      width: 100%;
      padding: 14px;
      margin-top: 5px;
      background: linear-gradient(180deg, #c62828, #8e0000);
      border: none;
      border-radius: 8px;
      color: #fff;
      font-size: 0.95rem;
      font-weight: 800;
      text-transform: uppercase;
      letter-spacing: 1.5px;
      cursor: pointer;
      box-shadow: 0 4px 10px rgba(0, 0, 0, 0.5);
      transition: filter 0.2s, transform 0.1s;
      display: flex;
      justify-content: center;
      align-items: center;
      gap: 10px;
    }

    .btn-login:hover {
      filter: brightness(1.15);
    }

    .btn-login:active {
      transform: scale(0.98);
    }

    /* Feedback de Erro */
    .error-msg {
      color: #ff4444;
      font-size: 0.8rem;
      text-align: center;
      font-weight: 700;
      display: none;
    }

    .error-msg.active {
      display: block;
    }
  </style>
</head>
<body>

  <div class="login-container">
    <div class="brand-header">
      <div class="brand-logo">
      </div>
      <div class="brand-title">INPROLINK</div>
      <div class="brand-subtitle">Acesso Administrador</div>
    </div>

    <form class="login-form" id="loginForm" onsubmit="handleLogin(event)">
      <div class="input-group">
        <label class="input-label" for="username">Usuário</label>
        <div class="input-wrapper">
          👤
          <input type="text" id="username" class="input-field" placeholder="Digite o usuário" required autocomplete="off">
        </div>
      </div>

      <div class="input-group">
        <label class="input-label" for="password">Senha</label>
        <div class="input-wrapper">
          🔒
          <input type="password" id="password" class="input-field" placeholder="Digite a senha" required>
        </div>
      </div>

      <div class="credentials-box">
        ℹ️ <strong>Acesso Padrão:</strong><br>
      </div>

      <div class="error-msg" id="errorMsg">
        ⚠️ Usuário ou senha incorretos!
      </div>

      <button type="submit" class="btn-login">
        Entrar 🚪
      </button>
    </form>
  </div>

  <script>
    function handleLogin(event) {
      event.preventDefault();
      
      const userVal = document.getElementById('username').value.trim();
      const passVal = document.getElementById('password').value.trim();
      const errorMsg = document.getElementById('errorMsg');

      fetch('/api/login', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ username: userVal, password: passVal })
      })
      .then(response => {
        if (response.ok) {
          return response.json();
        } else {
          throw new Error('Unauthorized');
        }
      })
      .then(data => {
        sessionStorage.setItem('authenticated', 'true');
        sessionStorage.setItem('role', data.role || 'Operador');
        window.location.href = 'painel.html';
      })
      .catch(error => {
        console.warn('API offline. Tentando login local fallback...', error);
        if (userVal === 'inprolink' && passVal === 'link@link') {
          errorMsg.classList.remove('active');
          sessionStorage.setItem('authenticated', 'true');
          sessionStorage.setItem('role', 'Administrador');
          window.location.href = 'painel.html';
        } else {
          errorMsg.classList.add('active');
        }
      });
    }
  </script>
</body>
</html>
)rawliteral";

const char user_adm_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="pt-BR">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Gestão de Usuários - Inprolink System</title>

  <style>
    * {
      box-sizing: border-box;
      margin: 0;
      padding: 0;
      font-family: 'Montserrat', sans-serif;
      user-select: none;
    }

    body {
      background-color: #050505;
      color: #ffffff;
      display: flex;
      justify-content: center;
      align-items: center;
      min-height: 100vh;
      padding: 20px;
    }

    .main-container {
      width: 100%;
      max-width: 900px;
      background-color: #0a0a0a;
      border-radius: 16px;
      padding: 30px;
      border: 2px solid #222;
      box-shadow: 0 10px 30px rgba(0, 0, 0, 0.9), 0 0 20px rgba(255, 26, 26, 0.15);
      display: flex;
      flex-direction: column;
      gap: 25px;
    }

    /* Header */
    .header-bar {
      display: flex;
      justify-content: space-between;
      align-items: center;
      border-bottom: 2px solid #222;
      padding-bottom: 15px;
    }

    .header-title {
      display: flex;
      align-items: center;
      gap: 12px;
    }

    .header-title i {
      color: #ff1a1a;
      font-size: 1.8rem;
    }

    .header-title h1 {
      font-family: 'Orbitron', monospace;
      font-size: 1.3rem;
      letter-spacing: 1px;
    }

    .user-counter {
      background: #141414;
      border: 1px solid #333;
      padding: 8px 16px;
      border-radius: 8px;
      font-size: 0.85rem;
      font-weight: 700;
      display: flex;
      align-items: center;
      gap: 8px;
    }

    .user-counter span {
      color: #ff1a1a;
      font-family: 'Orbitron', monospace;
      font-size: 1.1rem;
    }

    /* Grid layout */
    .content-grid {
      display: grid;
      grid-template-columns: 1fr 1.4fr;
      gap: 25px;
    }

    @media (max-width: 768px) {
      .content-grid {
        grid-template-columns: 1fr;
      }
    }

    /* Form Section */
    .form-card {
      background: #111;
      border: 1px solid #222;
      border-radius: 12px;
      padding: 20px;
      display: flex;
      flex-direction: column;
      gap: 15px;
    }

    .card-title {
      font-size: 0.95rem;
      font-weight: 800;
      text-transform: uppercase;
      letter-spacing: 1px;
      color: #ff1a1a;
      display: flex;
      align-items: center;
      gap: 8px;
      margin-bottom: 5px;
    }

    .input-group {
      display: flex;
      flex-direction: column;
      gap: 6px;
    }

    .input-group label {
      font-size: 0.75rem;
      font-weight: 700;
      color: #aaa;
      text-transform: uppercase;
    }

    .input-field {
      width: 100%;
      padding: 10px 12px;
      background-color: #1a1a1a;
      border: 1px solid #333;
      border-radius: 6px;
      color: #fff;
      font-size: 0.85rem;
      outline: none;
      transition: border-color 0.2s;
    }

    .input-field:focus {
      border-color: #ff1a1a;
    }

    .btn-submit {
      padding: 12px;
      background: linear-gradient(180deg, #2e7d32, #1b5e20);
      border: none;
      border-radius: 6px;
      color: #fff;
      font-weight: 800;
      font-size: 0.85rem;
      text-transform: uppercase;
      letter-spacing: 1px;
      cursor: pointer;
      display: flex;
      justify-content: center;
      align-items: center;
      gap: 8px;
      margin-top: 5px;
      transition: filter 0.2s;
    }

    .btn-submit:hover { filter: brightness(1.15); }
    .btn-cancel { background: #333; display: none; }

    /* List Section */
    .list-card {
      background: #111;
      border: 1px solid #222;
      border-radius: 12px;
      padding: 20px;
      display: flex;
      flex-direction: column;
      gap: 15px;
    }

    .users-list {
      display: flex;
      flex-direction: column;
      gap: 10px;
      max-height: 380px;
      overflow-y: auto;
    }

    .user-item {
      background: #181818;
      border: 1px solid #2a2a2a;
      border-radius: 8px;
      padding: 12px;
      display: flex;
      justify-content: space-between;
      align-items: center;
    }

    .user-info {
      display: flex;
      flex-direction: column;
      gap: 2px;
    }

    .user-name {
      font-size: 0.85rem;
      font-weight: 800;
      color: #fff;
    }

    .user-login {
      font-size: 0.75rem;
      color: #888;
      font-family: monospace;
    }

    .user-role {
      display: inline-block;
      font-size: 0.65rem;
      font-weight: 800;
      padding: 2px 6px;
      border-radius: 4px;
      text-transform: uppercase;
      width: fit-content;
      margin-top: 4px;
    }

    .role-admin { background: #8e0000; color: #ffcccc; }
    .role-manager { background: #d84315; color: #ffccbc; }
    .role-operator { background: #1565c0; color: #cce5ff; }

    .user-actions {
      display: flex;
      gap: 8px;
    }

    .btn-icon {
      width: 32px;
      height: 32px;
      border-radius: 6px;
      border: none;
      color: #fff;
      cursor: pointer;
      display: flex;
      align-items: center;
      justify-content: center;
      font-size: 0.85rem;
    }

    .btn-edit { background: #f57f17; color: #000; }
    .btn-delete { background: #c62828; }
    .btn-icon:disabled { opacity: 0.3; cursor: not-allowed; }

    /* Footer Nav */
    .footer-bar {
      display: flex;
      justify-content: space-between;
      border-top: 2px solid #222;
      padding-top: 15px;
    }

    /* Toast Notification */
    .toast-notification {
      position: fixed;
      top: -100px;
      left: 50%;
      transform: translateX(-50%);
      background: #333;
      color: #fff;
      padding: 12px 24px;
      border-radius: 8px;
      box-shadow: 0 4px 12px rgba(0,0,0,0.3);
      font-weight: 500;
      z-index: 9999;
      transition: top 0.4s cubic-bezier(0.68, -0.55, 0.265, 1.55);
      display: flex;
      align-items: center;
      gap: 10px;
    }
    .toast-notification.show { top: 20px; }
    .toast-success { border-left: 5px solid #4CAF50; }
    .toast-error { border-left: 5px solid #F44336; }
    .toast-info { border-left: 5px solid #2196F3; }

    .btn-nav {
      padding: 10px 18px;
      border-radius: 6px;
      border: none;
      color: #fff;
      font-weight: 700;
      font-size: 0.8rem;
      cursor: pointer;
      text-transform: uppercase;
      display: flex;
      align-items: center;
      gap: 8px;
      background: #222;
      text-decoration: none;
    }
  </style>
</head>
<body>

  <div class="main-container">
    <!-- Top Header -->
    <div class="header-bar">
      <div class="header-title">
        🧑‍🔧
        <h1>Gestão de Acessos</h1>
      </div>
      <div class="user-counter">
        Cadastrados: <span id="count-display">1 / 10</span>
      </div>
    </div>

    <!-- Content Grid -->
    <div class="content-grid">
      <!-- Form Cadastrar / Editar -->
      <div class="form-card">
        <div class="card-title" id="form-title">
          👤➕ Novo Usuário
        </div>

        <form id="userForm" onsubmit="handleSave(event)">
          <input type="hidden" id="userIndex" value="-1">

          <div class="input-group">
            <label for="fullName">Nome Completo</label>
            <input type="text" id="fullName" class="input-field" placeholder="Ex: Operador " required autocomplete="off">
          </div>

          <div class="input-group">
            <label for="username">Usuário</label>
            <input type="text" id="username" class="input-field" placeholder="Ex: operador1" required autocomplete="off">
          </div>

          <div class="input-group">
            <label for="password">Senha</label>
            <input type="password" id="password" class="input-field" placeholder="Digite a senha" required>
          </div>

          <div class="input-group">
            <label for="role">Nível de Permissão</label>
            <select id="role" class="input-field">
              <option value="Operador">Operador (Apenas Placar)</option>
              <option value="Gerente">Gerente (Placar e Automação)</option>
              <option value="Administrador">Administrador (Total)</option>
            </select>
          </div>

          <button type="submit" class="btn-submit" id="btnSave">
            💾 Salvar Usuário
          </button>
          <button type="button" class="btn-submit btn-cancel" id="btnCancel" onclick="resetForm()">
            Cancelar
          </button>
        </form>
      </div>

      <!-- User List -->
      <div class="list-card">
        <div class="card-title">
          📋 Usuários Ativos
        </div>

        <div class="users-list" id="usersContainer">
          <!-- Renderizado via JS -->
        </div>
      </div>
    </div>

    <!-- Footer -->
    <div class="footer-bar">
      <a href="painel.html" class="btn-nav">⬅️ Voltar ao Painel</a>
    </div>
  </div>

  <div id="toast" class="toast-notification">
    <span id="toast-icon">ℹ️</span>
    <span id="toast-message">Mensagem</span>
  </div>

  <script>
    function showToast(msg, type = 'info') {
      const toast = document.getElementById('toast');
      const toastMsg = document.getElementById('toast-message');
      const toastIcon = document.getElementById('toast-icon');
      toastMsg.innerText = msg;
      toast.className = 'toast-notification show';
      if (type === 'success') { toast.classList.add('toast-success'); toastIcon.innerText = '✅'; }
      else if (type === 'error') { toast.classList.add('toast-error'); toastIcon.innerText = '❌'; }
      else { toast.classList.add('toast-info'); toastIcon.innerText = 'ℹ️'; }
      setTimeout(() => toast.classList.remove('show'), 3000);
    }
    if (sessionStorage.getItem('authenticated') !== 'true') {
      window.location.href = 'login.html';
    }

    let users = [];
    const MAX_USERS = 10;

    function render() {
      const container = document.getElementById('usersContainer');
      const countDisplay = document.getElementById('count-display');
      
      countDisplay.innerText = `${users.length} / ${MAX_USERS}`;
      container.innerHTML = '';

      users.forEach((u, idx) => {
        const item = document.createElement('div');
        item.className = 'user-item';

        let roleClass = 'role-operator';
        if (u.role === 'Administrador') roleClass = 'role-admin';
        else if (u.role === 'Gerente') roleClass = 'role-manager';
        const isDefaultAdmin = u.username === 'inprolink';

        item.innerHTML = `
          <div class="user-info">
            <div class="user-name">${u.name}</div>
            <div class="user-login">@${u.username}</div>
            <span class="user-role ${roleClass}">${u.role}</span>
          </div>
          <div class="user-actions">
            <button class="btn-icon btn-edit" onclick="editUser(${idx})" title="Editar">✏️</button>
            <button class="btn-icon btn-delete" onclick="deleteUser(${idx})" ${isDefaultAdmin ? 'disabled' : ''} title="Excluir">🗑️</button>
          </div>
        `;
        container.appendChild(item);
      });

      // Desabilitar form se atingir o limite no modo criação
      const editIdx = parseInt(document.getElementById('userIndex').value, 10);
      if (users.length >= MAX_USERS && editIdx === -1) {
        document.getElementById('btnSave').disabled = true;
        document.getElementById('btnSave').style.opacity = '0.5';
      } else {
        document.getElementById('btnSave').disabled = false;
        document.getElementById('btnSave').style.opacity = '1';
      }
    }

    // Carregar usuários do ESP32 via API
    function loadUsers() {
      fetch('/api/users')
      .then(r => {
        if (!r.ok) throw new Error('Falha ao obter usuários');
        return r.json();
      })
      .then(data => {
        users = data;
        render();
      })
      .catch(err => {
        console.warn('API offline, usando fallback local...', err);
        users = JSON.parse(localStorage.getItem('inprolink_users')) || [
          { name: 'Administrador Inprolink', username: 'inprolink', pass: 'link@link', role: 'Administrador' }
        ];
        render();
      });
    }

    function handleSave(e) {
      e.preventDefault();
      const idx = parseInt(document.getElementById('userIndex').value, 10);
      const name = document.getElementById('fullName').value.trim();
      const username = document.getElementById('username').value.trim();
      const pass = document.getElementById('password').value.trim();
      const role = document.getElementById('role').value;

      // Validação de duplicidade de usuário local
      const exists = users.some((u, i) => u.username === username && i !== idx);
      if (exists) {
        showToast('Nome de usuário já cadastrado!', 'error');
        return;
      }

      const userData = { index: idx, name, username, password: pass, role };

      fetch('/api/users', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify(userData)
      })
      .then(response => {
        if (!response.ok) throw new Error('Falha ao salvar usuário');
        return response.json();
      })
      .then(data => {
        users = data;
        render();
        resetForm();
      })
      .catch(error => {
        console.warn('API offline, salvando localmente...', error);
        if (idx === -1) {
          if (users.length >= MAX_USERS) {
            showToast('Limite máximo de 10 usuários atingido!', 'error');
            return;
          }
          users.push({ name, username, role });
        } else {
          users[idx] = { name, username, role };
        }
        localStorage.setItem('inprolink_users', JSON.stringify(users));
        render();
        resetForm();
      });
    }

    function editUser(idx) {
      const u = users[idx];
      document.getElementById('userIndex').value = idx;
      document.getElementById('fullName').value = u.name;
      document.getElementById('username').value = u.username;
      document.getElementById('password').value = '';
      document.getElementById('role').value = u.role;

      document.getElementById('form-title').innerHTML = '✏️ Editar Usuário';
      document.getElementById('btnCancel').style.display = 'flex';
      document.getElementById('btnSave').disabled = false;
      document.getElementById('btnSave').style.opacity = '1';
    }

    function deleteUser(idx) {
      if (users[idx].username === 'inprolink') {
        showToast('O usuário administrador padrão não pode ser removido.', 'error');
        return;
      }

      if (confirm(`Deseja remover o usuário ${users[idx].username}?`)) {
        fetch('/api/users/delete', {
          method: 'POST',
          headers: { 'Content-Type': 'application/json' },
          body: JSON.stringify({ index: idx })
        })
        .then(response => {
          if (!response.ok) throw new Error('Falha ao remover usuário');
          return response.json();
        })
        .then(data => {
          users = data;
          render();
          resetForm();
        })
        .catch(error => {
          console.warn('API offline, removendo localmente...', error);
          users.splice(idx, 1);
          localStorage.setItem('inprolink_users', JSON.stringify(users));
          render();
          resetForm();
        });
      }
    }

    function resetForm() {
      document.getElementById('userForm').reset();
      document.getElementById('userIndex').value = -1;
      document.getElementById('form-title').innerHTML = '👤➕ Novo Usuário';
      document.getElementById('btnCancel').style.display = 'none';
      render();
    }

    // Inicialização
    loadUsers();
  </script>
</body>
</html>
)rawliteral";

const char lan_config_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="pt-BR">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Configuração de Rede - Inprolink System</title>

  <style>
    * {
      box-sizing: border-box;
      margin: 0;
      padding: 0;
      font-family: 'Montserrat', sans-serif;
      user-select: none;
    }

    body {
      background-color: #050505;
      color: #ffffff;
      display: flex;
      justify-content: center;
      align-items: center;
      min-height: 100vh;
      padding: 20px;
    }

    .main-container {
      width: 100%;
      max-width: 900px;
      background-color: #0a0a0a;
      border-radius: 16px;
      padding: 30px;
      border: 2px solid #222;
      box-shadow: 0 10px 30px rgba(0, 0, 0, 0.9), 0 0 20px rgba(255, 26, 26, 0.15);
      display: flex;
      flex-direction: column;
      gap: 25px;
    }

    /* Header */
    .header-bar {
      display: flex;
      justify-content: space-between;
      align-items: center;
      border-bottom: 2px solid #222;
      padding-bottom: 15px;
    }

    .header-title {
      display: flex;
      align-items: center;
      gap: 12px;
    }

    .header-title i {
      color: #ff1a1a;
      font-size: 1.8rem;
    }

    .header-title h1 {
      font-family: 'Orbitron', monospace;
      font-size: 1.3rem;
      letter-spacing: 1px;
    }

    .badge-status {
      background: #111;
      border: 1px solid #2e7d32;
      padding: 6px 14px;
      border-radius: 20px;
      font-size: 0.75rem;
      font-weight: 700;
      color: #81c784;
      display: flex;
      align-items: center;
      gap: 8px;
    }

    .dot-online {
      width: 8px;
      height: 8px;
      background-color: #4caf50;
      border-radius: 50%;
      box-shadow: 0 0 8px #4caf50;
    }

    /* Status Diagnostic Bar */
    .status-card {
      background: #111;
      border: 1px solid #222;
      border-radius: 12px;
      padding: 15px 20px;
      display: grid;
      grid-template-columns: repeat(auto-fit, minmax(180px, 1fr));
      gap: 15px;
    }

    .status-item {
      display: flex;
      flex-direction: column;
      gap: 4px;
    }

    .status-label {
      font-size: 0.7rem;
      color: #888;
      text-transform: uppercase;
      font-weight: 700;
    }

    .status-value {
      font-size: 0.9rem;
      font-weight: 800;
      color: #fff;
      font-family: 'Orbitron', monospace;
    }

    /* Tabs Selector */
    .tab-selector {
      display: flex;
      gap: 10px;
      background: #111;
      padding: 6px;
      border-radius: 10px;
      border: 1px solid #222;
    }

    .tab-btn {
      flex: 1;
      padding: 10px;
      border: none;
      background: transparent;
      color: #888;
      font-weight: 800;
      font-size: 0.8rem;
      text-transform: uppercase;
      border-radius: 6px;
      cursor: pointer;
      display: flex;
      align-items: center;
      justify-content: center;
      gap: 8px;
      transition: all 0.2s;
    }

    .tab-btn.active {
      background: #1e1e1e;
      color: #ff1a1a;
      box-shadow: 0 2px 8px rgba(0,0,0,0.5);
    }

    /* Config Sections */
    .section-card {
      background: #111;
      border: 1px solid #222;
      border-radius: 12px;
      padding: 20px;
      display: flex;
      flex-direction: column;
      gap: 18px;
    }

    .card-title {
      font-size: 0.9rem;
      font-weight: 800;
      text-transform: uppercase;
      letter-spacing: 1px;
      color: #ff1a1a;
      display: flex;
      align-items: center;
      gap: 8px;
    }

    .grid-2col {
      display: grid;
      grid-template-columns: 1fr 1fr;
      gap: 15px;
    }

    @media (max-width: 600px) {
      .grid-2col { grid-template-columns: 1fr; }
    }

    .input-group {
      display: flex;
      flex-direction: column;
      gap: 6px;
    }

    .input-group label {
      font-size: 0.75rem;
      font-weight: 700;
      color: #aaa;
      text-transform: uppercase;
      display: flex;
      justify-content: space-between;
    }

    .input-wrapper {
      position: relative;
      display: flex;
      align-items: center;
    }

    .input-field {
      width: 100%;
      padding: 10px 12px;
      background-color: #1a1a1a;
      border: 1px solid #333;
      border-radius: 6px;
      color: #fff;
      font-size: 0.85rem;
      outline: none;
      transition: border-color 0.2s;
    }

    .input-field:focus {
      border-color: #ff1a1a;
    }

    .btn-inline {
      padding: 10px 14px;
      background: #222;
      border: 1px solid #333;
      border-radius: 6px;
      color: #fff;
      font-size: 0.8rem;
      font-weight: 700;
      cursor: pointer;
      display: flex;
      align-items: center;
      gap: 6px;
      white-space: nowrap;
      margin-left: 8px;
      transition: background 0.2s;
    }

    .btn-inline:hover { background: #333; }

    /* Switch Component */
    .switch-container {
      display: flex;
      align-items: center;
      justify-content: space-between;
      background: #181818;
      padding: 12px 15px;
      border-radius: 8px;
      border: 1px solid #2a2a2a;
    }

    .switch-label {
      font-size: 0.8rem;
      font-weight: 700;
      color: #ddd;
    }

    .switch-sub {
      font-size: 0.7rem;
      color: #777;
      display: block;
      margin-top: 2px;
    }

    .switch {
      position: relative;
      display: inline-block;
      width: 44px;
      height: 24px;
    }

    .switch input { opacity: 0; width: 0; height: 0; }

    .slider {
      position: absolute;
      cursor: pointer;
      top: 0; left: 0; right: 0; bottom: 0;
      background-color: #333;
      transition: .3s;
      border-radius: 24px;
    }

    .slider:before {
      position: absolute;
      content: "";
      height: 18px;
      width: 18px;
      left: 3px;
      bottom: 3px;
      background-color: white;
      transition: .3s;
      border-radius: 50%;
    }

    input:checked + .slider { background-color: #2e7d32; }
    input:checked + .slider:before { transform: translateX(20px); }

    /* Footer Buttons */
    .footer-bar {
      display: flex;
      justify-content: space-between;
      gap: 12px;
      border-top: 2px solid #222;
      padding-top: 18px;
      flex-wrap: wrap;
    }

    /* Toast Notification */
    .toast-notification {
      position: fixed;
      top: -100px;
      left: 50%;
      transform: translateX(-50%);
      background: #333;
      color: #fff;
      padding: 12px 24px;
      border-radius: 8px;
      box-shadow: 0 4px 12px rgba(0,0,0,0.3);
      font-weight: 500;
      z-index: 9999;
      transition: top 0.4s cubic-bezier(0.68, -0.55, 0.265, 1.55);
      display: flex;
      align-items: center;
      gap: 10px;
    }
    .toast-notification.show { top: 20px; }
    .toast-success { border-left: 5px solid #4CAF50; }
    .toast-error { border-left: 5px solid #F44336; }
    .toast-info { border-left: 5px solid #2196F3; }

    .btn-nav {
      padding: 12px 20px;
      border-radius: 8px;
      border: none;
      color: #fff;
      font-weight: 700;
      font-size: 0.85rem;
      cursor: pointer;
      text-transform: uppercase;
      display: flex;
      align-items: center;
      gap: 8px;
      text-decoration: none;
    }

    .btn-back { background: #222; }
    .btn-save { background: linear-gradient(180deg, #2e7d32, #1b5e20); }
    .btn-test { background: linear-gradient(180deg, #1565c0, #0d47a1); }

    /* Static IP Fields Toggle */
    #staticIpFields {
      display: none;
      flex-direction: column;
      gap: 15px;
      border-top: 1px dashed #333;
      padding-top: 15px;
    }

    #staticIpFields.active {
      display: flex;
    }
  </style>
</head>
<body>

  <div class="main-container">
    <!-- Top Header -->
    <div class="header-bar">
      <div class="header-title">
        🛜
        <h1>Configuração de Rede</h1>
      </div>
      <div class="badge-status">
        <div class="dot-online"></div> Conectado (STA)
      </div>
    </div>

    <!-- Status Diagnostic Bar -->
    <div class="status-card">
      <div class="status-item">
        <span class="status-label">IP Atual</span>
        <span class="status-value" id="disp-ip">192.168.1.105</span>
      </div>
      <div class="status-item">
        <span class="status-label">Rede Wi-Fi</span>
        <span class="status-value" id="disp-ssid">Clube_Membros</span>
      </div>
      <div class="status-item">
        <span class="status-label">Sinal (RSSI)</span>
        <span class="status-value" id="disp-rssi">-64 dBm</span>
      </div>
      <div class="status-item">
        <span class="status-label">Endereço MAC</span>
        <span class="status-value" id="disp-mac">24:DC:C3:A1:B2:C3</span>
      </div>
    </div>

    <!-- Mode Selector Tabs -->
    <div class="tab-selector">
      <button class="tab-btn active" onclick="selectMode('sta')">
        🏠📶 Wi-Fi Estação (STA)
      </button>
      <button class="tab-btn" onclick="selectMode('ap')">
        📡 Ponto de Acesso (AP)
      </button>
      <button class="tab-btn" onclick="selectMode('ports')">
        🔌 Portas & Serviços
      </button>
    </div>

    <!-- Form Section: STA Mode -->
    <div class="section-card" id="section-sta">
      <div class="card-title">
        📶 Conexão Wi-Fi Local
      </div>

      <div class="input-group">
        <label>Rede Wi-Fi (SSID)</label>
        <div class="input-wrapper">
          <select id="wifiSsid" class="input-field" style="flex: 1;">
           
          </select>
          <button type="button" class="btn-inline" onclick="scanNetworks()">
            <span id="iconScan">🔄</span> Escanear
          </button>
        </div>
      </div>

      <div class="input-group">
        <label>Senha da Rede</label>
        <input type="password" id="wifiPass" class="input-field" value="12345678" placeholder="Digite a senha do Wi-Fi">
      </div>

      <!-- Switch DHCP / Static IP -->
      <div class="switch-container">
        <div>
          <span class="switch-label">Endereço IP Automático (DHCP)</span>
          <span class="switch-sub">Obter IP, Gateway e DNS automaticamente do roteador</span>
        </div>
        <label class="switch">
          <input type="checkbox" id="dhcpToggle" checked onchange="toggleDhcp()">
          <span class="slider"></span>
        </label>
      </div>

      <!-- Static IP fields -->
      <div id="staticIpFields">
        <div class="grid-2col">
          <div class="input-group">
            <label>Endereço IP Fixado</label>
            <input type="text" id="staticIp" class="input-field" value="192.168.1.200">
          </div>
          <div class="input-group">
            <label>Mascara de Subrede</label>
            <input type="text" id="staticSubnet" class="input-field" value="255.255.255.0">
          </div>
        </div>
        <div class="grid-2col">
          <div class="input-group">
            <label>Gateway Padrão</label>
            <input type="text" id="staticGateway" class="input-field" value="192.168.1.1">
          </div>
          <div class="input-group">
            <label>Servidor DNS</label>
            <input type="text" id="staticDns" class="input-field" value="8.8.8.8">
          </div>
        </div>
      </div>
    </div>

    <!-- Form Section: AP Mode -->
    <div class="section-card" id="section-ap" style="display: none;">
      <div class="card-title">
        🛜 Ponto de Acesso Local (ESP32 Hotspot)
      </div>

      <div class="input-group">
        <label>Nome do AP (SSID)</label>
        <input type="text" id="apSsid" class="input-field" value="INPROLINK-PLACAR-AP">
      </div>

      <div class="input-group">
        <label>Senha do AP</label>
        <input type="text" id="apPass" class="input-field" value="inprolink123" placeholder="Mínimo 8 caracteres">
      </div>

      <div class="grid-2col">
        <div class="input-group">
          <label>IP do Hotspot</label>
          <input type="text" id="apIp" class="input-field" value="192.168.4.1" readonly>
        </div>
        <div class="input-group">
          <label>Canal Wi-Fi</label>
          <select id="apChannel" class="input-field">
            <option value="1">Canal 1</option>
            <option value="6" selected>Canal 6</option>
            <option value="11">Canal 11</option>
          </select>
        </div>
      </div>
    </div>

    <!-- Form Section: Ports & Services -->
    <div class="section-card" id="section-ports" style="display: none;">
      <div class="card-title">
        🔌 Configuração de Serviços & Portas
      </div>

      <div class="grid-2col">
        <div class="input-group">
          <label>Porta Servidor Web (HTTP)</label>
          <input type="number" id="httpPort" class="input-field" value="80">
        </div>
        <div class="input-group">
          <label>Porta WebSocket</label>
          <input type="number" id="wsPort" class="input-field" value="81">
        </div>
      </div>

      <div class="switch-container">
        <div>
          <span class="switch-label">Reconexão Automática</span>
          <span class="switch-sub">Tentar reconectar ao Wi-Fi em caso de queda de sinal</span>
        </div>
        <label class="switch">
          <input type="checkbox" id="autoReconnect" checked>
          <span class="slider"></span>
        </label>
      </div>
    </div>

    <!-- Footer Bar -->
    <div class="footer-bar">
      <a href="painel.html" class="btn-nav btn-back">⬅️ Painel</a>
      <div style="display: flex; gap: 10px;">
        <button type="button" class="btn-nav btn-test" onclick="testConnection()">
          🧪 Testar
        </button>
        <button type="button" class="btn-nav btn-save" onclick="saveSettings()">
          💾 Salvar & Reiniciar
        </button>
      </div>
    </div>
  </div>

  <div id="toast" class="toast-notification">
    <span id="toast-icon">ℹ️</span>
    <span id="toast-message">Mensagem</span>
  </div>

  <script>
    function showToast(msg, type = 'info') {
      const toast = document.getElementById('toast');
      const toastMsg = document.getElementById('toast-message');
      const toastIcon = document.getElementById('toast-icon');
      toastMsg.innerText = msg;
      toast.className = 'toast-notification show';
      if (type === 'success') { toast.classList.add('toast-success'); toastIcon.innerText = '✅'; }
      else if (type === 'error') { toast.classList.add('toast-error'); toastIcon.innerText = '❌'; }
      else { toast.classList.add('toast-info'); toastIcon.innerText = 'ℹ️'; }
      setTimeout(() => toast.classList.remove('show'), 3000);
    }
    if (sessionStorage.getItem('authenticated') !== 'true') {
      window.location.href = 'login.html';
    }

    let isScanPending = false;

    function selectMode(mode) {
      const tabs = document.querySelectorAll('.tab-btn');
      tabs.forEach(t => t.classList.remove('active'));

      document.getElementById('section-sta').style.display = 'none';
      document.getElementById('section-ap').style.display = 'none';
      document.getElementById('section-ports').style.display = 'none';

      if (mode === 'sta') {
        tabs[0].classList.add('active');
        document.getElementById('section-sta').style.display = 'flex';
      } else if (mode === 'ap') {
        tabs[1].classList.add('active');
        document.getElementById('section-ap').style.display = 'flex';
      } else if (mode === 'ports') {
        tabs[2].classList.add('active');
        document.getElementById('section-ports').style.display = 'flex';
      }
    }

    function toggleDhcp() {
      const isDhcp = document.getElementById('dhcpToggle').checked;
      const staticFields = document.getElementById('staticIpFields');
      if (isDhcp) {
        staticFields.classList.remove('active');
      } else {
        staticFields.classList.add('active');
      }
    }

    function loadWifiStatus() {
      fetch('/api/wifi/status')
      .then(r => {
        if (!r.ok) throw new Error('Falha ao obter status de rede');
        return r.json();
      })
      .then(data => {
        document.getElementById('disp-ip').innerText = data.ip || '---';
        document.getElementById('disp-ssid').innerText = data.ssid || '---';
        document.getElementById('disp-rssi').innerText = (data.rssi || 0) + ' dBm';
        document.getElementById('disp-mac').innerText = data.mac || '---';

        // Carregar campos
        const wifiSsidSelect = document.getElementById('wifiSsid');
        if (data.wifiSsid) {
          wifiSsidSelect.innerHTML = `<option value="${data.wifiSsid}">${data.wifiSsid}</option>`;
        }
        document.getElementById('wifiPass').value = data.wifiPass || '';
        document.getElementById('dhcpToggle').checked = data.dhcp;
        document.getElementById('staticIp').value = data.staticIp || '';
        document.getElementById('staticSubnet').value = data.staticSubnet || '';
        document.getElementById('staticGateway').value = data.staticGateway || '';
        document.getElementById('staticDns').value = data.staticDns || '';

        document.getElementById('apSsid').value = data.apSsid || '';
        document.getElementById('apPass').value = data.apPass || '';
        document.getElementById('apChannel').value = data.apChannel || '6';

        document.getElementById('httpPort').value = data.httpPort || 80;
        document.getElementById('wsPort').value = data.wsPort || 81;
        document.getElementById('autoReconnect').checked = data.autoReconnect;

        toggleDhcp();
      })
      .catch(err => {
        console.warn('API offline, usando fallback local de visualização...', err);
        const saved = localStorage.getItem('inprolink_wifi_config');
        if (saved) {
          const config = JSON.parse(saved);
          document.getElementById('wifiSsid').value = config.ssid;
          document.getElementById('dhcpToggle').checked = config.dhcp;
          document.getElementById('staticIp').value = config.staticIp;
          document.getElementById('apSsid').value = config.apSsid;
          document.getElementById('wsPort').value = config.wsPort;
        }
      });
    }

    function scanNetworks() {
      if (isScanPending) return;
      const icon = document.getElementById('iconScan');
      icon.classList.add('fa-spin');
      isScanPending = true;

      fetch('/api/wifi/scan')
      .then(r => {
        if (!r.ok) throw new Error('Falha no escaneamento');
        return r.json();
      })
      .then(networks => {
        icon.classList.remove('fa-spin');
        isScanPending = false;
        
        const select = document.getElementById('wifiSsid');
        select.innerHTML = '';
        if (networks.length === 0) {
          select.innerHTML = '<option value="">Nenhuma rede encontrada</option>';
        } else {
          networks.forEach(net => {
            const opt = document.createElement('option');
            opt.value = net.ssid;
            opt.innerText = `${net.ssid} (${net.rssi} dBm)`;
            select.appendChild(opt);
          });
        }
        showToast(`Busca concluída! ${networks.length} redes encontradas.`, 'success');
      })
      .catch(err => {
        icon.classList.remove('fa-spin');
        isScanPending = false;
        console.warn('API offline, simulando redes para demonstração...', err);
        const select = document.getElementById('wifiSsid');
        select.innerHTML = `
          <option value="Clube_Membros">Clube_Membros (-64 dBm)</option>
          <option value="Inprolink_Tech">Inprolink_Tech (-72 dBm)</option>
        `;
        showToast('Busca concluída! 3 redes simuladas.', 'success');
      });
    }

    function testConnection() {
      fetch('/api/wifi/test')
      .then(r => r.text())
      .then(txt => {
        showToast(txt, 'success');
      })
      .catch(err => {
        console.warn('API offline.', err);
        showToast('Enviando pacote de teste ao ESP32... Conexão estável! (Simulado)', 'success');
      });
    }

    function saveSettings() {
      const config = {
        wifiSsid: document.getElementById('wifiSsid').value,
        wifiPass: document.getElementById('wifiPass').value,
        dhcp: document.getElementById('dhcpToggle').checked,
        staticIp: document.getElementById('staticIp').value,
        staticSubnet: document.getElementById('staticSubnet').value,
        staticGateway: document.getElementById('staticGateway').value,
        staticDns: document.getElementById('staticDns').value,
        apSsid: document.getElementById('apSsid').value,
        apPass: document.getElementById('apPass').value,
        apChannel: parseInt(document.getElementById('apChannel').value, 10) || 6,
        httpPort: parseInt(document.getElementById('httpPort').value, 10) || 80,
        wsPort: parseInt(document.getElementById('wsPort').value, 10) || 81,
        autoReconnect: document.getElementById('autoReconnect').checked
      };

      fetch('/api/wifi/config', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify(config)
      })
      .then(response => {
        if (!response.ok) throw new Error('Erro ao salvar configurações');
        showToast('Configurações salvas no ESP32! O dispositivo será reiniciado.', 'success');
      })
      .catch(error => {
        console.warn('API offline, simulando salvamento...', error);
        localStorage.setItem('inprolink_wifi_config', JSON.stringify({
          ssid: config.wifiSsid,
          dhcp: config.dhcp,
          staticIp: config.staticIp,
          apSsid: config.apSsid,
          wsPort: config.wsPort
        }));
        showToast('Configurações salvas no localStorage (Simulado)!', 'success');
      });
    }

    // Inicialização
    loadWifiStatus();
  </script>
</body>
</html>
)rawliteral";

const char panel_config_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="pt-BR">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Wizard de Configuração Geral - Inprolink System</title>

  <style>
    * {
      box-sizing: border-box;
      margin: 0;
      padding: 0;
      font-family: 'Montserrat', sans-serif;
      user-select: none;
    }

    body {
      background-color: #050505;
      color: #ffffff;
      display: flex;
      justify-content: center;
      align-items: center;
      min-height: 100vh;
      padding: 20px;
    }

    .main-container {
      width: 100%;
      max-width: 850px;
      background-color: #0a0a0a;
      border-radius: 16px;
      padding: 30px;
      border: 2px solid #222;
      box-shadow: 0 10px 30px rgba(0, 0, 0, 0.9), 0 0 20px rgba(255, 26, 26, 0.15);
      display: flex;
      flex-direction: column;
      gap: 25px;
    }

    /* Header */
    .header-bar {
      display: flex;
      justify-content: space-between;
      align-items: center;
      border-bottom: 2px solid #222;
      padding-bottom: 15px;
    }

    .header-title {
      display: flex;
      align-items: center;
      gap: 12px;
    }

    .header-title i {
      color: #ff1a1a;
      font-size: 1.8rem;
    }

    .header-title h1 {
      font-family: 'Orbitron', monospace;
      font-size: 1.3rem;
      letter-spacing: 1px;
    }

    .wizard-status {
      font-size: 0.75rem;
      font-weight: 700;
      color: #888;
      text-transform: uppercase;
      letter-spacing: 1px;
    }

    /* Stepper Header Bar */
    .stepper-bar {
      display: flex;
      justify-content: space-between;
      align-items: center;
      position: relative;
      padding: 0 5px;
      margin-bottom: 10px;
    }

    .stepper-bar::before {
      content: '';
      position: absolute;
      top: 50%;
      left: 20px;
      right: 20px;
      height: 2px;
      background: #222;
      z-index: 1;
      transform: translateY(-50%);
    }

    .step-indicator {
      position: relative;
      z-index: 2;
      background: #0a0a0a;
      display: flex;
      flex-direction: column;
      align-items: center;
      gap: 4px;
      padding: 0 4px;
    }

    .step-circle {
      width: 32px;
      height: 32px;
      border-radius: 50%;
      background: #141414;
      border: 2px solid #333;
      color: #888;
      display: flex;
      align-items: center;
      justify-content: center;
      font-weight: 800;
      font-size: 0.8rem;
      transition: all 0.3s;
    }

    .step-indicator.active .step-circle {
      border-color: #ff1a1a;
      background: #ff1a1a;
      color: #fff;
      box-shadow: 0 0 10px rgba(255, 26, 26, 0.5);
    }

    .step-indicator.completed .step-circle {
      border-color: #2e7d32;
      background: #2e7d32;
      color: #fff;
    }

    .step-label {
      font-size: 0.65rem;
      font-weight: 700;
      color: #666;
      text-transform: uppercase;
    }

    .step-indicator.active .step-label { color: #fff; }

    /* Step Content Area */
    .step-content {
      display: none;
      flex-direction: column;
      gap: 18px;
      background: #111;
      border: 1px solid #222;
      border-radius: 12px;
      padding: 25px;
      min-height: 260px;
    }

    .step-content.active { display: flex; }

    .card-title {
      font-size: 0.95rem;
      font-weight: 800;
      text-transform: uppercase;
      letter-spacing: 1px;
      color: #ff1a1a;
      display: flex;
      align-items: center;
      gap: 8px;
      margin-bottom: 5px;
    }

    .input-group {
      display: flex;
      flex-direction: column;
      gap: 6px;
    }

    .input-group label {
      font-size: 0.75rem;
      font-weight: 700;
      color: #aaa;
      text-transform: uppercase;
    }

    .input-field {
      width: 100%;
      padding: 12px 14px;
      background-color: #1a1a1a;
      border: 1px solid #333;
      border-radius: 6px;
      color: #fff;
      font-size: 0.9rem;
      outline: none;
      transition: border-color 0.2s;
    }

    .input-field:focus { border-color: #ff1a1a; }

    /* Cards Grid */
    .options-grid {
      display: grid;
      grid-template-columns: repeat(auto-fit, minmax(180px, 1fr));
      gap: 15px;
      margin-top: 5px;
    }

    .option-card {
      background: #181818;
      border: 2px solid #2a2a2a;
      border-radius: 10px;
      padding: 20px;
      display: flex;
      flex-direction: column;
      align-items: center;
      justify-content: center;
      gap: 10px;
      cursor: pointer;
      transition: all 0.2s;
    }

    .option-card:hover { border-color: #444; }

    .option-card.selected {
      border-color: #ff1a1a;
      background: #1a0a0a;
      box-shadow: 0 0 12px rgba(255, 26, 26, 0.25);
    }

    .option-card i {
      font-size: 2rem;
      color: #666;
    }

    .option-card.selected i { color: #ff1a1a; }

    .option-card span {
      font-weight: 800;
      font-size: 0.85rem;
      text-transform: uppercase;
      color: #ddd;
    }

    /* Footer Nav */
    .footer-bar {
      display: flex;
      justify-content: space-between;
      border-top: 2px solid #222;
      padding-top: 18px;
    }

    .btn-action {
      padding: 12px 22px;
      border-radius: 8px;
      border: none;
      color: #fff;
      font-weight: 800;
      font-size: 0.85rem;
      cursor: pointer;
      text-transform: uppercase;
      display: flex;
      align-items: center;
      gap: 8px;
      transition: filter 0.2s;
    }

    .btn-action:hover { filter: brightness(1.15); }
    .btn-prev { background: #222; }
    .btn-next { background: linear-gradient(180deg, #1565c0, #0d47a1); }
    .btn-finish { background: linear-gradient(180deg, #2e7d32, #1b5e20); display: none; }
    .btn-action:disabled { opacity: 0.3; cursor: not-allowed; }
    /* Toast Notification */
    .toast-notification {
      position: fixed; top: -100px; left: 50%; transform: translateX(-50%);
      background: #333; color: #fff; padding: 12px 24px; border-radius: 8px;
      box-shadow: 0 4px 12px rgba(0,0,0,0.3); font-weight: 500; z-index: 9999;
      transition: top 0.4s cubic-bezier(0.68, -0.55, 0.265, 1.55);
      display: flex; align-items: center; gap: 10px;
    }
    .toast-notification.show { top: 20px; }
    .toast-success { border-left: 5px solid #4CAF50; }
    .toast-error { border-left: 5px solid #F44336; }
    .toast-info { border-left: 5px solid #2196F3; }
  </style>
</head>
<body>

  <div class="main-container">
    <!-- Header -->
    <div class="header-bar">
      <div class="header-title">
        🎚️
        <h1>Configuração do Placar</h1>
      </div>
      <div style="display: flex; align-items: center; gap: 15px;">
        <div class="wizard-status" id="step-status-text">Passo 1 de 6</div>
        <button class="btn-action" style="background: #e53935; padding: 6px 12px; font-size: 14px; border-radius: 6px;" onclick="window.location.href='painel.html'">❌ Fechar</button>
      </div>
    </div>

    <!-- Mode Selection -->
    <div class="mode-selector" style="text-align: center; margin-bottom: 20px;">
      <label style="margin-right: 20px; cursor: pointer; color: #fff; font-size: 1.1em;">
        <input type="radio" name="automationMode" value="automatico" checked onchange="toggleMode()"> 🤖 Automático (Via API)
      </label>
      <label style="cursor: pointer; color: #fff; font-size: 1.1em;">
        <input type="radio" name="automationMode" value="manual" onchange="toggleMode()"> ✍️ Manual (Local)
      </label>
    </div>

    <!-- Stepper Navigation Header -->
    <div id="wizard-container">
      <div class="stepper-bar">
      <div class="step-indicator active" id="ind-1">
        <div class="step-circle">1</div>
        <span class="step-label">Domínio</span>
      </div>
      <div class="step-indicator" id="ind-2">
        <div class="step-circle">2</div>
        <span class="step-label">Modalidade</span>
      </div>
      <div class="step-indicator" id="ind-3">
        <div class="step-circle">3</div>
        <span class="step-label">Campeonato</span>
      </div>
      <div class="step-indicator" id="ind-4">
        <div class="step-circle">4</div>
        <span class="step-label">Partida</span>
      </div>
      <div class="step-indicator" id="ind-5">
        <div class="step-circle">5</div>
        <span class="step-label">Etapa</span>
      </div>
      <div class="step-indicator" id="ind-6">
        <div class="step-circle">6</div>
        <span class="step-label">Rodada</span>
      </div>
    </div>

    <!-- Step 1: Domínio -->
    <div class="step-content active" id="step-1">
      <div class="card-title">
        🌐 Informar Domínio do Sistema
      </div>
      <div class="input-group">
        <label for="domainInput">Endereço do Domínio / IP do Servidor</label>
        <input type="text" id="domainInput" class="input-field" placeholder="Ex: placar.inprolink.com.br ou 192.168.1.100" value="placar.inprolink.com.br">
      </div>
    </div>

    <!-- Step 2: Modalidade -->
    <div class="step-content" id="step-2">
      <div class="card-title">
        🏆 Selecionar Modalidade
      </div>
      <div class="options-grid">
        <div class="option-card selected" onclick="selectCard('modalidade', 'Futebol', this)">
          ⚽
          <span>Futebol</span>
        </div>
        <div class="option-card" onclick="selectCard('modalidade', 'Vôlei', this)">
          🏐
          <span>Vôlei</span>
        </div>
        <div class="option-card" onclick="selectCard('modalidade', 'Natação', this)">
          🏊
          <span>Natação</span>
        </div>
        <div class="option-card" onclick="selectCard('modalidade', 'Corrida', this)">
          🏃‍♀️
          <span>Corrida</span>
        </div>
      </div>
    </div>

    <!-- Step 3: Campeonato -->
    <div class="step-content" id="step-3">
      <div class="card-title">
        🏅 Selecionar Campeonato
      </div>
      <div class="options-grid">
        <div class="option-card selected" onclick="selectCard('campeonato', 'Campeonato 1', this)">
          🥇
          <span>Campeonato 1</span>
        </div>
        <div class="option-card" onclick="selectCard('campeonato', 'Campeonato 2', this)">
          🥇
          <span>Campeonato 2</span>
        </div>
      </div>
    </div>

    <!-- Step 4: Partida -->
    <div class="step-content" id="step-4">
      <div class="card-title">
        🎮 Selecionar Partida
      </div>
      <div class="options-grid">
        <div class="option-card selected" onclick="selectCard('partida', 'Partida 1', this)">
          🏁
          <span>Partida 1</span>
        </div>
        <div class="option-card" onclick="selectCard('partida', 'Partida 2', this)">
          🏁
          <span>Partida 2</span>
        </div>
      </div>
    </div>

    <!-- Step 5: Etapa -->
    <div class="step-content" id="step-5">
      <div class="card-title">
        🗂️ Selecionar Etapa
      </div>
      <div class="options-grid">
        <div class="option-card selected" onclick="selectCard('etapa', 'Etapa 1', this)">
          🗃️
          <span>Etapa 1</span>
        </div>
        <div class="option-card" onclick="selectCard('etapa', 'Etapa 2', this)">
          🗃️
          <span>Etapa 2</span>
        </div>
      </div>
    </div>

    <!-- Step 6: Rodada -->
    <div class="step-content" id="step-6">
      <div class="card-title">
        📅 Selecionar Rodada
      </div>
      <div class="options-grid">
        <div class="option-card selected" onclick="selectCard('rodada', 'Rodada 1', this)">
          🔢
          <span>Rodada 1</span>
        </div>
        <div class="option-card" onclick="selectCard('rodada', 'Rodada 2', this)">
          🔢
          <span>Rodada 2</span>
        </div>
      </div>
    </div>

    <!-- Footer Controls -->
    <div class="footer-bar">
      <button class="btn-action btn-prev" id="btnPrev" onclick="changeStep(-1)" disabled>
        ◀️ Anterior
      </button>

      <div style="display: flex; gap: 10px;">
        <button class="btn-action btn-next" id="btnNext" onclick="changeStep(1)">
          Próximo ▶️
        </button>
        <button class="btn-action btn-finish" id="btnFinish" onclick="finishWizard()">
          ✅ Concluir
        </button>
      </div>
    </div>
    </div> <!-- End wizard-container -->

    <!-- Container do Manual -->
    <div id="manual-container" style="display: none; padding: 20px; background: #1a1a1a; border-radius: 12px; margin-top: 15px;">
     
      <button class="btn-action btn-finish" style="width: 100%; margin-top: 20px; justify-content: center;" onclick="saveManualConfig()">
        ✅ Salvar Configuração Manual
      </button>
    </div>

  </div>

  <div id="toast" class="toast-notification">
    <span id="toast-icon">ℹ️</span>
    <span id="toast-message">Mensagem</span>
  </div>

  <script>
    function showToast(msg, type = 'info') {
      const toast = document.getElementById('toast');
      const toastMsg = document.getElementById('toast-message');
      const toastIcon = document.getElementById('toast-icon');
      toastMsg.innerText = msg;
      toast.className = 'toast-notification show';
      if (type === 'success') { toast.classList.add('toast-success'); toastIcon.innerText = '✅'; }
      else if (type === 'error') { toast.classList.add('toast-error'); toastIcon.innerText = '❌'; }
      else { toast.classList.add('toast-info'); toastIcon.innerText = 'ℹ️'; }
      setTimeout(() => toast.classList.remove('show'), 3000);
    }
    if (sessionStorage.getItem('authenticated') !== 'true') {
      window.location.href = 'login.html';
    }

    let currentStep = 1;
    const totalSteps = 6;
    let currentMode = 'automatico';

    function toggleMode() {
      const mode = document.querySelector('input[name="automationMode"]:checked').value;
      currentMode = mode;
      
      wizardData.mode = mode;
      fetch('/api/automation/config', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify(wizardData)
      }).catch(e => console.log(e));

      if (mode === 'automatico') {
        document.getElementById('wizard-container').style.display = 'block';
        document.getElementById('manual-container').style.display = 'none';
      } else {
        document.getElementById('wizard-container').style.display = 'none';
        document.getElementById('manual-container').style.display = 'block';
      }
    }

    // Estado da seleção do Wizard
    const wizardData = {
      dominio: 'placar.inprolink.com.br',
      modalidade: '',
      campeonato: '',
      partida: '',
      etapa: '',
      rodada: ''
    };

    function selectCard(field, value, el) {
      wizardData[field] = value;
      const parent = el.parentElement;
      const cards = parent.querySelectorAll('.option-card');
      cards.forEach(c => c.classList.remove('selected'));
      el.classList.add('selected');
    }

    function populateStepOptions(stepId, field, items, iconClass = '⚪') {
      const stepEl = document.getElementById(stepId);
      const grid = stepEl.querySelector('.options-grid');
      grid.innerHTML = '';
      
      if (!items || items.length === 0) {
        grid.innerHTML = '<div style="grid-column: 1/-1; text-align: center; color: #888; padding: 20px;">Nenhuma opção encontrada</div>';
        return;
      }
      
      items.forEach((item, idx) => {
        const card = document.createElement('div');
        card.className = 'option-card';
        if (idx === 0) {
          card.classList.add('selected');
          wizardData[field] = item.id;
        }
        
        let displayIcon = iconClass;
        if (field === 'modalidade') {
          const lowerName = item.nome.toLowerCase();
          if (lowerName.includes('futebol') || lowerName.includes('soccer')) displayIcon = '⚽';
          else if (lowerName.includes('vôlei') || lowerName.includes('volei') || lowerName.includes('volley')) displayIcon = '🏐';
          else if (lowerName.includes('nata') || lowerName.includes('swim')) displayIcon = '🏊';
          else if (lowerName.includes('corri') || lowerName.includes('run')) displayIcon = '🏃';
          else if (lowerName.includes('basque') || lowerName.includes('basket')) displayIcon = '🏀';
        }
        
        card.onclick = () => selectCard(field, item.id, card);
        card.innerHTML = `
          <span style="font-size: 24px;">${displayIcon}</span>
          <span>${item.nome}</span>
        `;
        grid.appendChild(card);
      });
    }

    function fetchModalidades(domain, callback) {
      fetch(`/api/proxy/modalidades?domain=${encodeURIComponent(domain)}`)
      .then(r => {
        if (!r.ok) throw new Error('API erro');
        return r.json();
      })
      .then(data => {
        populateStepOptions('step-2', 'modalidade', data, 'fa-solid fa-futbol');
        callback();
      })
      .catch(err => {
        console.warn('API offline, usando fallback de modalidades...', err);
        const data = [
          { id: 'Futebol', nome: 'Futebol' },
          { id: 'Vôlei', nome: 'Vôlei' },
          { id: 'Natação', nome: 'Natação' },
          { id: 'Corrida', nome: 'Corrida' }
        ];
        populateStepOptions('step-2', 'modalidade', data);
        callback();
      });
    }

    // Proxy endpoints
    function fetchCampeonatos(domain, mod, callback) {
      fetch(`/api/proxy/campeonatos?domain=${encodeURIComponent(domain)}&modalidade=${encodeURIComponent(mod)}`)
      .then(r => {
        if (!r.ok) throw new Error('API erro');
        return r.json();
      })
      .then(data => {
        populateStepOptions('step-3', 'campeonato', data, 'fa-solid fa-medal');
        callback();
      })
      .catch(err => {
        console.warn('API offline, usando fallback de campeonatos...', err);
        const data = [
          { id: 'Campeonato 1', nome: 'Campeonato 1' },
          { id: 'Campeonato 2', nome: 'Campeonato 2' }
        ];
        populateStepOptions('step-3', 'campeonato', data, 'fa-solid fa-medal');
        callback();
      });
    }

    function fetchPartidas(domain, camp, callback) {
      fetch(`/api/proxy/partidas?domain=${encodeURIComponent(domain)}&campeonato=${encodeURIComponent(camp)}`)
      .then(r => {
        if (!r.ok) throw new Error('API erro');
        return r.json();
      })
      .then(data => {
        populateStepOptions('step-4', 'partida', data, 'fa-solid fa-flag-checkered');
        callback();
      })
      .catch(err => {
        console.warn('API offline, usando fallback de partidas...', err);
        const data = [
          { id: 'Partida 1', nome: 'Partida 1' },
          { id: 'Partida 2', nome: 'Partida 2' }
        ];
        populateStepOptions('step-4', 'partida', data, 'fa-solid fa-flag-checkered');
        callback();
      });
    }

    function fetchEtapas(domain, part, callback) {
      fetch(`/api/proxy/etapas?domain=${encodeURIComponent(domain)}&partida=${encodeURIComponent(part)}`)
      .then(r => {
        if (!r.ok) throw new Error('API erro');
        return r.json();
      })
      .then(data => {
        populateStepOptions('step-5', 'etapa', data, 'fa-solid fa-sitemap');
        callback();
      })
      .catch(err => {
        console.warn('API offline, usando fallback de etapas...', err);
        const data = [
          { id: 'Etapa 1', nome: 'Etapa 1' },
          { id: 'Etapa 2', nome: 'Etapa 2' }
        ];
        populateStepOptions('step-5', 'etapa', data, 'fa-solid fa-sitemap');
        callback();
      });
    }

    function fetchRodadas(domain, etapa, callback) {
      fetch(`/api/proxy/rodadas?domain=${encodeURIComponent(domain)}&etapa=${encodeURIComponent(etapa)}`)
      .then(r => {
        if (!r.ok) throw new Error('API erro');
        return r.json();
      })
      .then(data => {
        populateStepOptions('step-6', 'rodada', data, 'fa-solid fa-list-ol');
        callback();
      })
      .catch(err => {
        console.warn('API offline, usando fallback de rodadas...', err);
        const data = [
          { id: 'Rodada 1', nome: 'Rodada 1' },
          { id: 'Rodada 2', nome: 'Rodada 2' }
        ];
        populateStepOptions('step-6', 'rodada', data, 'fa-solid fa-list-ol');
        callback();
      });
    }

    function changeStep(delta) {
      const newStep = currentStep + delta;
      if (newStep < 1 || newStep > totalSteps) return;

      if (delta > 0) {
        const domain = document.getElementById('domainInput').value.trim();
        if (!domain) {
          showToast('Por favor, informe o domínio.', 'error');
          return;
        }
        wizardData.dominio = domain;

        if (currentStep === 1) {
          fetchModalidades(domain, () => proceed());
          return;
        } else if (currentStep === 2) {
          fetchCampeonatos(domain, wizardData.modalidade, () => proceed());
          return;
        } else if (currentStep === 3) {
          fetchPartidas(domain, wizardData.campeonato, () => proceed());
          return;
        } else if (currentStep === 4) {
          fetchEtapas(domain, wizardData.partida, () => proceed());
          return;
        } else if (currentStep === 5) {
          fetchRodadas(domain, wizardData.etapa, () => proceed());
          return;
        }
      }

      proceed();

      function proceed() {
        document.getElementById(`step-${currentStep}`).classList.remove('active');
        document.getElementById(`ind-${currentStep}`).classList.remove('active');

        if (delta > 0) {
          document.getElementById(`ind-${currentStep}`).classList.add('completed');
        } else {
          document.getElementById(`ind-${newStep}`).classList.remove('completed');
        }

        currentStep = newStep;

        document.getElementById(`step-${currentStep}`).classList.add('active');
        document.getElementById(`ind-${currentStep}`).classList.add('active');

        updateButtons();
      }
    }

    function updateButtons() {
      document.getElementById('step-status-text').innerText = `Passo ${currentStep} de ${totalSteps}`;
      document.getElementById('btnPrev').disabled = (currentStep === 1);

      if (currentStep === totalSteps) {
        document.getElementById('btnNext').style.display = 'none';
        document.getElementById('btnFinish').style.display = 'flex';
      } else {
        document.getElementById('btnNext').style.display = 'flex';
        document.getElementById('btnFinish').style.display = 'none';
      }
    }

    function finishWizard() {
      wizardData.mode = "automatico";
      fetch('/api/automation/config', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify(wizardData)
      })
      .then(r => {
        if (!r.ok) throw new Error('Erro ao salvar automação');
        showToast('Configuração de automação salva com sucesso no ESP32!', 'success');
        window.location.href = 'painel.html';
      })
      .catch(err => {
        console.warn('API offline, salvando localmente...', err);
        localStorage.setItem('inprolink_wizard_setup', JSON.stringify(wizardData));
        showToast('Configuração concluída (Simulado)!', 'success');
        window.location.href = 'painel.html';
      });
    }

    function saveManualConfig() {
      const data = {
        mode: "manual",
        dominio: document.getElementById('manual_dominio').value.trim(),
        modalidade: document.getElementById('manual_modalidade').value.trim(),
        campeonato: document.getElementById('manual_campeonato').value.trim(),
        partida: document.getElementById('manual_partida').value.trim(),
        etapa: document.getElementById('manual_etapa').value.trim(),
        rodada: document.getElementById('manual_rodada').value.trim()
      };
      
      fetch('/api/automation/config', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify(data)
      })
      .then(r => {
        if (!r.ok) throw new Error('Erro ao salvar');
        showToast('Configuração manual salva com sucesso no ESP32!', 'success');
        window.location.href = 'painel.html';
      })
      .catch(err => {
        showToast('Erro ao salvar. Verifique a conexão com o ESP32.', 'error');
      });
    }
  </script>
</body>
</html>
)rawliteral";

const char painel_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="pt-BR">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Placar Eletrônico - Inprolink System</title>

  <style>
    * {
      box-sizing: border-box;
      margin: 0;
      padding: 0;
      user-select: none;
    }

    body {
      background-color: #050505;
      color: #ffffff;
      font-family: 'Montserrat', sans-serif;
      display: flex;
      justify-content: center;
      align-items: center;
      min-height: 100vh;
      padding: 20px;
    }

    .scoreboard-container {
      width: 100%;
      max-width: 1100px;
      background-color: #0a0a0a;
      border-radius: 16px;
      padding: 25px;
      border: 3px solid #222;
      box-shadow: 0 10px 30px rgba(0, 0, 0, 0.8);
      display: flex;
      flex-direction: column;
      gap: 20px;
    }

    /* Grid Layouts */
    .row-top, .row-bottom {
      display: grid;
      grid-template-columns: 1fr auto 1fr;
      gap: 20px;
      align-items: center;
    }

    .row-middle {
      display: flex;
      flex-direction: column;
      align-items: center;
      gap: 10px;
    }

    /* Module Box Styling */
    .module-card {
      display: flex;
      flex-direction: column;
      align-items: center;
    }

    .module-title {
      font-size: 1.2rem;
      font-weight: 800;
      letter-spacing: 1.5px;
      margin-bottom: 6px;
      text-transform: uppercase;
    }

    .module-subtitle {
      font-size: 0.9rem;
      font-weight: 700;
      letter-spacing: 1px;
      margin-top: 6px;
      color: #ccc;
    }

    .display-group {
      display: flex;
      align-items: center;
      gap: 10px;
    }

    /* LED Digital Display */
    .led-frame {
      background: #111;
      border: 4px solid #333;
      border-radius: 12px;
      padding: 10px 20px;
      box-shadow: inset 0 0 15px rgba(0, 0, 0, 0.9), 0 4px 10px rgba(0,0,0,0.5);
      display: flex;
      justify-content: center;
      align-items: center;
    }

    .led-text {
      font-family: 'Orbitron', monospace;
      color: #ff1a1a;
      text-shadow: 0 0 12px rgba(255, 26, 26, 0.8), 0 0 25px rgba(255, 0, 0, 0.4);
      line-height: 1;
    }

    .digits-2 { font-size: 3.8rem; letter-spacing: 4px; }
    .digits-timer { font-size: 5rem; letter-spacing: 6px; padding: 10px 30px; }

    input.led-text {
      background: transparent;
      border: none;
      outline: none;
      text-align: center;
      width: 1.5em;
    }
    input.led-text[readonly] { pointer-events: none; }

    /* Mode Selector */
    .mode-selector {
      display: flex;
      justify-content: center;
      gap: 20px;
      padding-bottom: 15px;
      border-bottom: 2px solid #222;
    }
    .radio-label {
      display: flex;
      align-items: center;
      gap: 8px;
      font-size: 0.95rem;
      font-weight: 700;
      color: #aaa;
      cursor: pointer;
      text-transform: uppercase;
      transition: color 0.2s;
    }
    .radio-label:hover { color: #fff; }
    .radio-label input[type="radio"] {
      width: 18px;
      height: 18px;
      accent-color: #ff1a1a;
      cursor: pointer;
    }

    /* Control Buttons (+ / -) */
    .btn-controls {
      display: flex;
      flex-direction: column;
      gap: 8px;
    }

    .btn-step {
      width: 44px;
      height: 44px;
      border-radius: 8px;
      border: none;
      color: #fff;
      font-size: 1.5rem;
      font-weight: bold;
      cursor: pointer;
      display: flex;
      align-items: center;
      justify-content: center;
      box-shadow: 0 4px 6px rgba(0,0,0,0.4);
      transition: transform 0.1s, filter 0.2s;
    }

    .btn-step:active { transform: scale(0.92); }
    .btn-plus { background: linear-gradient(180deg, #2e7d32, #1b5e20); }
    .btn-minus { background: linear-gradient(180deg, #c62828, #8e0000); }

    /* Central Logo */
    .logo-container {
      width: 140px;
      height: 140px;
      border-radius: 50%;
      background: #ffffff;
      border: 4px solid #1a365d;
      display: flex;
      flex-direction: column;
      justify-content: center;
      align-items: center;
      text-align: center;
      padding: 10px;
      box-shadow: 0 0 15px rgba(255,255,255,0.2);
    }

    .logo-badge {
      width: 60px;
      height: 60px;
      background: #1a365d;
      border-radius: 50%;
      color: #fff;
      display: flex;
      align-items: center;
      justify-content: center;
      font-weight: 900;
      font-size: 1.1rem;
      border: 2px solid #e53e3e;
      margin-bottom: 4px;
    }

    .logo-text {
      color: #000;
      font-size: 0.55rem;
      font-weight: 800;
      line-height: 1.1;
      text-transform: uppercase;
    }

    /* Timer Action Buttons */
    .timer-actions {
      display: flex;
      gap: 15px;
      margin-top: 5px;
    }

    .btn-timer {
      padding: 8px 18px;
      border-radius: 8px;
      border: none;
      color: #fff;
      font-weight: 700;
      font-size: 0.85rem;
      cursor: pointer;
      display: flex;
      align-items: center;
      gap: 8px;
      box-shadow: 0 4px 8px rgba(0,0,0,0.4);
      text-transform: uppercase;
    }

    .btn-start { background: linear-gradient(180deg, #2e7d32, #1b5e20); }
    .btn-pause { background: linear-gradient(180deg, #f57f17, #fbc02d); color: #000; }
    .btn-reset-time { background: linear-gradient(180deg, #1565c0, #0d47a1); }

    /* Footer Action Bar */
    .row-footer {
      display: grid;
      grid-template-columns: repeat(4, 1fr);
      gap: 12px;
      margin-top: 10px;
    }

    .btn-action {
      padding: 12px 10px;
      border-radius: 8px;
      border: none;
      color: #fff;
      font-weight: 700;
      font-size: 0.85rem;
      cursor: pointer;
      display: flex;
      align-items: center;
      justify-content: center;
      gap: 10px;
      text-transform: uppercase;
      box-shadow: 0 4px 8px rgba(0,0,0,0.4);
    }

    .btn-purple { background: linear-gradient(180deg, #8e24aa, #4a148c); }
    .btn-orange { background: linear-gradient(180deg, #ef6c00, #e65100); }
    .btn-teal { background: linear-gradient(180deg, #00838f, #006064); }
    .btn-blue { background: linear-gradient(180deg, #1565c0, #0d47a1); }

    /* Overlay / Modal */
    .overlay {
      position: fixed;
      top: 0;
      left: 0;
      width: 100vw;
      height: 100vh;
      background: rgba(0, 0, 0, 0.85);
      backdrop-filter: blur(5px);
      z-index: 9999;
      display: flex;
      align-items: center;
      justify-content: center;
      opacity: 0;
      visibility: hidden;
      transition: opacity 0.25s ease, visibility 0.25s ease;
    }

    .overlay.active {
      opacity: 1;
      visibility: visible;
    }

    .modal-box {
      background: #141414;
      border: 2px solid #333;
      border-radius: 16px;
      padding: 30px;
      max-width: 450px;
      width: 90%;
      box-shadow: 0 0 25px rgba(0, 0, 0, 0.9), 0 0 10px rgba(255, 26, 26, 0.2);
      text-align: center;
      transform: scale(0.85);
      transition: transform 0.25s cubic-bezier(0.175, 0.885, 0.32, 1.275);
    }

    .overlay.active .modal-box {
      transform: scale(1);
    }

    .modal-icon {
      font-size: 2.8rem;
      color: #ff1a1a;
      margin-bottom: 15px;
    }

    .modal-title {
      font-size: 1.4rem;
      font-weight: 800;
      margin-bottom: 10px;
      letter-spacing: 1px;
    }

    .modal-message {
      font-size: 1rem;
      color: #bbb;
      margin-bottom: 25px;
      line-height: 1.4;
    }

    .modal-buttons {
      display: flex;
      gap: 12px;
      justify-content: center;
    }

    .btn-modal {
      padding: 10px 22px;
      border-radius: 8px;
      border: none;
      font-weight: 700;
      font-size: 0.9rem;
      cursor: pointer;
      text-transform: uppercase;
      transition: transform 0.1s;
    }

    .btn-modal:active { transform: scale(0.95); }
    .btn-modal-confirm { background: #e53e3e; color: #fff; }
    .btn-modal-cancel { background: #333; color: #fff; }
    .btn-modal-ok { background: #2b6cb0; color: #fff; }

    /* Responsividade */
    @media (max-width: 850px) {
      .digits-2 { font-size: 2.8rem; }
      .digits-timer { font-size: 3.2rem; }
      .row-footer { grid-template-columns: repeat(2, 1fr); }
      .logo-container { width: 100px; height: 100px; }
      .logo-badge { width: 40px; height: 40px; font-size: 0.8rem; }
      .logo-text { font-size: 0.45rem; }
    }
  </style>
</head>
<body>

  <div class="scoreboard-container">
    <!-- Seletor de Modo -->
    <div class="mode-selector">
      <label class="radio-label">
        <input type="radio" name="panelMode" value="automatico" onchange="setPanelMode(this.value)" checked>
        🤖 Automático API
      </label>
      <label class="radio-label">
        <input type="radio" name="panelMode" value="manual" onchange="setPanelMode(this.value)">
        🛠️ Manual Local
      </label>
    </div>

    <!-- Linha Superior: Time A, Logo, Time B -->
    <div class="row-top">
      <!-- Time A (2 dígitos) -->
      <div class="module-card">
        <span class="module-title" id="title-team-a">TIME A</span>
        <div class="display-group">
          <div class="led-frame">
            <input type="text" class="led-text digits-2" id="score-a" value="00" maxlength="2" onchange="manualInputChanged('score-a')">
          </div>
          <div class="btn-controls">
            <button class="btn-step btn-plus" onclick="changeValue('score-a', 1)">+</button>
            <button class="btn-step btn-minus" onclick="changeValue('score-a', -1)">-</button>
          </div>
        </div>
        <span class="module-subtitle">PONTOS</span>
      </div>

      <!-- Logo Central -->
      <div class="logo-container">
      </div>

      <!-- Time B (2 dígitos) -->
      <div class="module-card">
        <span class="module-title" id="title-team-b">TIME B</span>
        <div class="display-group">
          <div class="led-frame">
            <input type="text" class="led-text digits-2" id="score-b" value="00" maxlength="2" onchange="manualInputChanged('score-b')">
          </div>
          <div class="btn-controls">
            <button class="btn-step btn-plus" onclick="changeValue('score-b', 1)">+</button>
            <button class="btn-step btn-minus" onclick="changeValue('score-b', -1)">-</button>
          </div>
        </div>
        <span class="module-subtitle">PONTOS</span>
      </div>
    </div>

    <!-- Linha Central: Cronômetro (6 dígitos) -->
    <div class="row-middle">
      <div class="led-frame">
        <input type="text" class="led-text digits-timer" id="timer-display" value="00:00:00" maxlength="8" placeholder="HH:MM:SS" onchange="timerInputChanged()" readonly>
      </div>
      <div class="timer-actions">
        <button class="btn-timer btn-start" onclick="startTimer()">▶️ Iniciar</button>
        <button class="btn-timer btn-pause" onclick="pauseTimer()">⏸️ Pausar</button>
        <button class="btn-timer btn-reset-time" onclick="resetTimer()">↩️ Zerar Tempo</button>
      </div>
    </div>

    <!-- Linha Inferior: Faltas A, Período, Faltas B -->
    <div class="row-bottom">
      <!-- Faltas A (2 dígitos) -->
      <div class="module-card">
        <span class="module-title" id="title-fouls-a">FALTAS A</span>
        <div class="display-group">
          <div class="led-frame">
            <input type="text" class="led-text digits-2" id="fouls-a" value="00" maxlength="2" onchange="manualInputChanged('fouls-a')">
          </div>
          <div class="btn-controls">
            <button class="btn-step btn-plus" onclick="changeValue('fouls-a', 1)">+</button>
            <button class="btn-step btn-minus" onclick="changeValue('fouls-a', -1)">-</button>
          </div>
        </div>
        <span class="module-subtitle">FALTAS</span>
      </div>

      <!-- Período (2 dígitos) -->
      <div class="module-card">
        <span class="module-title">PERÍODO</span>
        <div class="display-group">
          <div class="led-frame">
            <input type="text" class="led-text digits-2" id="period" value="00" maxlength="2" onchange="manualInputChanged('period')">
          </div>
          <div class="btn-controls">
            <button class="btn-step btn-plus" onclick="changeValue('period', 1)">+</button>
            <button class="btn-step btn-minus" onclick="changeValue('period', -1)">-</button>
          </div>
        </div>
        <span class="module-subtitle">PERÍODO</span>
      </div>

      <!-- Faltas B (2 dígitos) -->
      <div class="module-card">
        <span class="module-title" id="title-fouls-b">FALTAS B</span>
        <div class="display-group">
          <div class="led-frame">
            <input type="text" class="led-text digits-2" id="fouls-b" value="00" maxlength="2" onchange="manualInputChanged('fouls-b')">
          </div>
          <div class="btn-controls">
            <button class="btn-step btn-plus" onclick="changeValue('fouls-b', 1)">+</button>
            <button class="btn-step btn-minus" onclick="changeValue('fouls-b', -1)">-</button>
          </div>
        </div>
        <span class="module-subtitle">FALTAS</span>
      </div>
    </div>

    <!-- Barra de Ações Inferior -->
    <div class="row-footer">
      <button class="btn-action" style="background:#d32f2f" onclick="logout()">🚪 Sair</button>
      <button class="btn-action btn-purple" onclick="confirmResetScoreboard()">↩️ Zerar Placar</button>
      <button class="btn-action btn-orange" onclick="swapSides()">🔀 Trocar Lado</button>
      <button id="btn-settings" class="btn-action btn-teal" onclick="openSettings()">⚙️ Configurações</button>
      <button class="btn-action btn-blue" onclick="toggleFullscreen()">↕️↔️ Tela Cheia</button>
    </div>
  </div>

  <!-- OVERLAY / MODAL -->
  <div id="modal-overlay" class="overlay">
    <div class="modal-box">
      <div class="modal-icon" id="modal-icon">⚠️</div>
      <h3 class="modal-title" id="modal-title">Atenção</h3>
      <p class="modal-message" id="modal-message">Mensagem de confirmação...</p>
      <div class="modal-buttons" id="modal-buttons"></div>
    </div>
  </div>

  <script>
    if (sessionStorage.getItem('authenticated') !== 'true') {
      window.location.href = 'login.html';
    }

    let ws = null;
    let timerInterval = null;
    let totalSeconds = 0;
    let swapped = false;

    function connectWs() {
      const host = window.location.hostname || '192.168.4.1';
      ws = new WebSocket(`ws://${host}:81/`);

      ws.onopen = () => {
        console.log('WebSocket conectado!');
      };

      ws.onmessage = (event) => {
        try {
          const data = JSON.parse(event.data);
          if (data.type === 'state') {
            const setVal = (id, val) => {
              const el = document.getElementById(id);
              if (document.activeElement !== el) el.value = String(val).padStart(2, '0');
            };
            setVal('score-a', data.scoreA);
            setVal('score-b', data.scoreB);
            setVal('fouls-a', data.foulsA);
            setVal('fouls-b', data.foulsB);
            setVal('period', data.period);
            const timerEl = document.getElementById('timer-display');
            if (document.activeElement !== timerEl) timerEl.value = data.timer;
            
            // Sincronizar contador local caso ws desconecte depois
            const parts = data.timer.split(':');
            if (parts.length === 3) {
              totalSeconds = parseInt(parts[0], 10) * 3600 + parseInt(parts[1], 10) * 60 + parseInt(parts[2], 10);
            }
          }
        } catch (e) {
          console.error('Erro ao processar JSON do WebSocket:', e);
        }
      };

      ws.onclose = () => {
        console.warn('WebSocket desconectado. Tentando reconectar...');
        setTimeout(connectWs, 2000);
      };
    }

    // Lógica de Contadores (Manual)
    function changeValue(id, amount) {
      if (ws && ws.readyState === WebSocket.OPEN) {
        ws.send(JSON.stringify({
          action: 'change',
          target: id,
          amount: amount
        }));
      } else {
        // Fallback local se offline
        const el = document.getElementById(id);
        let val = parseInt(el.value, 10) + amount;
        if (isNaN(val)) val = 0;
        if (val < 0) val = 0;
        if (val > 99) val = 99;
        el.value = String(val).padStart(2, '0');
      }
    }

    function manualInputChanged(id) {
      const el = document.getElementById(id);
      let val = parseInt(el.value, 10);
      if (isNaN(val)) val = 0;
      if (val < 0) val = 0;
      if (val > 99) val = 99;
      el.value = String(val).padStart(2, '0');
      if (ws && ws.readyState === WebSocket.OPEN) {
        ws.send(JSON.stringify({ action: 'set', target: id, value: val }));
      }
    }

    function setPanelMode(mode) {
      const isAuto = (mode === 'automatico');
      fetch('/api/automation/mode', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ mode: mode })
      }).catch(e => console.warn('Falha ao salvar modo', e));

      document.querySelectorAll('.btn-controls').forEach(el => {
        el.style.display = isAuto ? 'none' : 'flex';
      });
      document.querySelectorAll('.timer-actions button').forEach(btn => {
        btn.disabled = isAuto;
        btn.style.opacity = isAuto ? '0.5' : '1';
        btn.style.cursor = isAuto ? 'not-allowed' : 'pointer';
      });
      document.querySelectorAll('input.led-text').forEach(input => {
        if (isAuto) input.setAttribute('readonly', 'true');
        else input.removeAttribute('readonly');
      });

      // Habilitar/Desabilitar timer input separadamente
      const timerEl = document.getElementById('timer-display');
      if (isAuto) timerEl.setAttribute('readonly', 'true');
      else timerEl.removeAttribute('readonly');
    }

    function timerInputChanged() {
      const el = document.getElementById('timer-display');
      const raw = el.value.trim();
      // Accept HH:MM:SS or MM:SS or raw seconds
      const parts = raw.split(':').map(p => parseInt(p, 10) || 0);
      let secs = 0;
      if (parts.length === 3) secs = parts[0] * 3600 + parts[1] * 60 + parts[2];
      else if (parts.length === 2) secs = parts[0] * 60 + parts[1];
      else secs = parts[0];
      if (secs < 0) secs = 0;
      totalSeconds = secs;
      updateTimerDisplay();
      if (ws && ws.readyState === WebSocket.OPEN) {
        ws.send(JSON.stringify({ action: 'timer', command: 'set', value: totalSeconds }));
      }
    }

    // Lógica do Cronômetro Local (Fallback)
    function updateTimerDisplay() {
      const hrs = String(Math.floor(totalSeconds / 3600)).padStart(2, '0');
      const mins = String(Math.floor((totalSeconds % 3600) / 60)).padStart(2, '0');
      const secs = String(totalSeconds % 60).padStart(2, '0');
      const el = document.getElementById('timer-display');
      if (document.activeElement !== el) {
        el.value = `${hrs}:${mins}:${secs}`;
      }
    }

    function startTimerLocal() {
      if (timerInterval) return;
      timerInterval = setInterval(() => {
        totalSeconds++;
        updateTimerDisplay();
      }, 1000);
    }

    function pauseTimerLocal() {
      clearInterval(timerInterval);
      timerInterval = null;
    }

    function resetTimerLocal() {
      pauseTimerLocal();
      totalSeconds = 0;
      updateTimerDisplay();
    }

    // Controle do Cronômetro
    function startTimer() {
      if (ws && ws.readyState === WebSocket.OPEN) {
        ws.send(JSON.stringify({ action: 'timer', command: 'start' }));
      } else {
        startTimerLocal();
      }
    }

    function pauseTimer() {
      if (ws && ws.readyState === WebSocket.OPEN) {
        ws.send(JSON.stringify({ action: 'timer', command: 'pause' }));
      } else {
        pauseTimerLocal();
      }
    }

    function resetTimer() {
      if (ws && ws.readyState === WebSocket.OPEN) {
        ws.send(JSON.stringify({ action: 'timer', command: 'reset' }));
      } else {
        resetTimerLocal();
      }
    }

    // Lógica de Troca de Lados
    function swapSides() {
      swapped = !swapped;
      
      const titleTeamA = document.getElementById('title-team-a');
      const titleTeamB = document.getElementById('title-team-b');
      const titleFoulsA = document.getElementById('title-fouls-a');
      const titleFoulsB = document.getElementById('title-fouls-b');

      if (swapped) {
        titleTeamA.innerText = 'TIME B';
        titleTeamB.innerText = 'TIME A';
        titleFoulsA.innerText = 'FALTAS B';
        titleFoulsB.innerText = 'FALTAS A';
      } else {
        titleTeamA.innerText = 'TIME A';
        titleTeamB.innerText = 'TIME B';
        titleFoulsA.innerText = 'FALTAS A';
        titleFoulsB.innerText = 'FALTAS B';
      }
    }

    // Alternar Tela Cheia
    function toggleFullscreen() {
      if (!document.fullscreenElement) {
        document.documentElement.requestFullscreen().catch(err => {
          console.warn('Erro ao solicitar tela cheia:', err);
        });
      } else {
        if (document.exitFullscreen) {
          document.exitFullscreen();
        }
      }
    }

    // Gerenciamento do Modal Overlay
    const overlay = document.getElementById('modal-overlay');
    const modalTitle = document.getElementById('modal-title');
    const modalMessage = document.getElementById('modal-message');
    const modalButtons = document.getElementById('modal-buttons');
    const modalIcon = document.getElementById('modal-icon');

    function closeModal() {
      overlay.classList.remove('active');
    }

    function showAlert(title, message, iconClass = 'ℹ️') {
      modalIcon.innerHTML = `<span style="font-size: 24px;">${iconClass}</span>`;
      modalTitle.innerText = title;
      modalMessage.innerText = message;
      modalButtons.innerHTML = `<button class="btn-modal btn-modal-ok" onclick="closeModal()">OK</button>`;
      overlay.classList.add('active');
    }

    function showConfirm(title, message, onConfirm, iconClass = '⚠️') {
      modalIcon.innerHTML = `<span style="font-size: 24px;">${iconClass}</span>`;
      modalTitle.innerText = title;
      modalMessage.innerText = message;
      modalButtons.innerHTML = `
        <button class="btn-modal btn-modal-cancel" onclick="closeModal()">Cancelar</button>
        <button class="btn-modal btn-modal-confirm" id="btn-confirm-action">Confirmar</button>
      `;
      overlay.classList.add('active');

      document.getElementById('btn-confirm-action').onclick = () => {
        closeModal();
        onConfirm();
      };
    }

    function confirmResetScoreboard() {
      showConfirm(
        'Zerar Placar Completo',
        'Tem certeza de que deseja zerar todos os pontos, faltas, período e o cronômetro?',
        () => {
          if (ws && ws.readyState === WebSocket.OPEN) {
            ws.send(JSON.stringify({ action: 'reset_all' }));
          } else {
            // Fallback local
            document.getElementById('score-a').value = '00';
            document.getElementById('score-b').value = '00';
            document.getElementById('fouls-a').value = '00';
            document.getElementById('fouls-b').value = '00';
            document.getElementById('period').value = '00';
            resetTimerLocal();
          }
        }
      );
    }

    function logout() {
      fetch('/api/logout', { method: 'POST' })
        .then(() => {
          sessionStorage.removeItem('authenticated');
          window.location.href = 'login.html';
        }).catch(err => {
          sessionStorage.removeItem('authenticated');
          window.location.href = 'login.html';
        });
    }

    function factoryReset() {
      showConfirm(
        'ATENÇÃO: Reset de Fábrica',
        'Isso irá apagar todos os usuários, senhas e configurações. O ESP32 será reiniciado. Deseja continuar?',
        () => {
          fetch('/api/factory_reset', { method: 'POST' })
            .then(() => {
              showAlert('Reset de Fábrica', 'As configurações foram apagadas. O sistema está sendo reiniciado...', '⚠️');
              setTimeout(() => { window.location.href = 'login.html'; }, 3000);
            });
        },
        '⚠️'
      );
    }

    function openSettings() {
      const role = sessionStorage.getItem('role') || 'Operador';
      showConfirm(
        'Configurações do Sistema',
        'Selecione a seção que deseja configurar no ESP32:',
        () => {},
        '⚙️'
      );
      const buttonsContainer = document.getElementById('modal-buttons');
      buttonsContainer.style.flexWrap = 'wrap';
      
      if (role === 'Gerente') {
        buttonsContainer.innerHTML = `
          <button class="btn-modal btn-modal-cancel" style="padding:10px 14px;" onclick="closeModal()">Cancelar</button>
          <button class="btn-modal btn-modal-ok" style="padding:10px 14px; background:#8e24aa;" onclick="window.location.href='panel_config.html.html'">Automação API</button>
        `;
      } else {
        buttonsContainer.innerHTML = `
          <button class="btn-modal btn-modal-cancel" style="padding:10px 14px;" onclick="closeModal()">Cancelar</button>
          <button class="btn-modal btn-modal-ok" style="padding:10px 14px; background:#1b5e20;" onclick="window.location.href='lan_config.html'">Wi-Fi & Rede</button>
          <button class="btn-modal btn-modal-confirm" style="padding:10px 14px; background:#0d47a1;" onclick="window.location.href='user_adm.html'">Usuários</button>
          <button class="btn-modal btn-modal-ok" style="padding:10px 14px; background:#8e24aa;" onclick="window.location.href='panel_config.html.html'">Automação API</button>
          <button class="btn-modal btn-modal-confirm" style="padding:10px 14px; background:#b71c1c; flex: 1 1 100%; margin-top:5px;" onclick="factoryReset()">⚠️ Restaurar Padrões de Fábrica</button>
        `;
      }
    }

    // Inicialização
    connectWs();

    // Obter modo salvo no ESP32
    fetch('/api/automation/status')
      .then(r => r.json())
      .then(data => {
        const mode = data.mode || 'automatico';
        const radio = document.querySelector(`input[name="panelMode"][value="${mode}"]`);
        if (radio) radio.checked = true;
        setPanelMode(mode);
      })
      .catch(() => setPanelMode('automatico'));

    const role = sessionStorage.getItem('role') || 'Operador';
    if (role === 'Operador') {
      const btnSettings = document.getElementById('btn-settings');
      if (btnSettings) btnSettings.style.display = 'none';
      const modeSel = document.querySelector('.mode-selector');
      if (modeSel) modeSel.style.display = 'none';
    }
  </script>
</body>
</html>
)rawliteral";
const char ssid_config_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="pt-BR">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Configuração de Wi-Fi</title>
  <style>
    * { box-sizing: border-box; margin: 0; padding: 0; font-family: 'Montserrat', sans-serif; }
    body { background-color: #050505; color: #ffffff; display: flex; justify-content: center; align-items: center; min-height: 100vh; padding: 20px; }
    .main-container { width: 100%; max-width: 500px; background-color: #0a0a0a; border-radius: 16px; padding: 30px; border: 2px solid #222; box-shadow: 0 10px 30px rgba(0, 0, 0, 0.9); display: flex; flex-direction: column; gap: 20px; }
    .header-bar { border-bottom: 2px solid #222; padding-bottom: 15px; text-align: center; }
    .header-title h1 { color: #fff; font-size: 1.5rem; }
    .input-group { display: flex; flex-direction: column; gap: 8px; }
    .input-group label { font-size: 0.85rem; font-weight: 600; color: #aaa; text-transform: uppercase; }
    .input-wrapper { display: flex; gap: 10px; }
    .input-field { width: 100%; padding: 12px; border-radius: 8px; border: 1px solid #333; background: #111; color: #fff; font-size: 1rem; outline: none; }
    .input-field:focus { border-color: #ff1a1a; box-shadow: 0 0 8px rgba(255,26,26,0.3); }
    .btn-inline { background: #333; border: none; color: #fff; padding: 0 15px; border-radius: 8px; cursor: pointer; font-weight: bold; }
    .btn-inline:hover { background: #444; }
    .btn-save { background: #2e7d32; color: #fff; padding: 14px; border: none; border-radius: 8px; font-weight: 700; font-size: 1rem; cursor: pointer; text-transform: uppercase; margin-top: 10px; }
    .btn-save:hover { background: #1b5e20; }
    .nav-footer { text-align: center; margin-top: 10px; }
    .nav-footer a { color: #888; text-decoration: none; font-size: 0.9rem; }
    .nav-footer a:hover { color: #fff; }
    /* Toast Notification */
    .toast-notification {
      position: fixed; top: -100px; left: 50%; transform: translateX(-50%);
      background: #333; color: #fff; padding: 12px 24px; border-radius: 8px;
      box-shadow: 0 4px 12px rgba(0,0,0,0.3); font-weight: 500; z-index: 9999;
      transition: top 0.4s cubic-bezier(0.68, -0.55, 0.265, 1.55);
      display: flex; align-items: center; gap: 10px;
    }
    .toast-notification.show { top: 20px; }
    .toast-success { border-left: 5px solid #4CAF50; }
    .toast-error { border-left: 5px solid #F44336; }
    .toast-info { border-left: 5px solid #2196F3; }
  </style>
</head>
<body>

  <div class="main-container">
    <div class="header-bar">
      <div class="header-title">
        <h1>Configuração Rápida de Wi-Fi</h1>
      </div>
    </div>

    <form id="wifiForm" onsubmit="saveWifi(event)">
      <div class="input-group" style="margin-bottom: 15px;">
        <label>Rede Wi-Fi (SSID)</label>
        <div class="input-wrapper">
          <select id="wifiSsid" class="input-field" required>
            <option value="">Selecione uma rede...</option>
          </select>
          <button type="button" class="btn-inline" onclick="scanNetworks()">
            <span id="iconScan">🔄</span> Escanear
          </button>
        </div>
      </div>

      <div class="input-group" style="margin-bottom: 25px;">
        <label>Senha da Rede</label>
        <input type="password" id="wifiPass" class="input-field" placeholder="Digite a senha do Wi-Fi">
      </div>

      <button type="submit" class="btn-save" style="width: 100%;">Salvar e Conectar</button>
    </form>
    
    <div class="nav-footer">
      <a href="painel.html">Voltar ao Painel</a>
    </div>
  </div>

  <div id="toast" class="toast-notification">
    <span id="toast-icon">ℹ️</span>
    <span id="toast-message">Mensagem</span>
  </div>

  <script>
    function showToast(msg, type = 'info') {
      const toast = document.getElementById('toast');
      const toastMsg = document.getElementById('toast-message');
      const toastIcon = document.getElementById('toast-icon');
      toastMsg.innerText = msg;
      toast.className = 'toast-notification show';
      if (type === 'success') { toast.classList.add('toast-success'); toastIcon.innerText = '✅'; }
      else if (type === 'error') { toast.classList.add('toast-error'); toastIcon.innerText = '❌'; }
      else { toast.classList.add('toast-info'); toastIcon.innerText = 'ℹ️'; }
      setTimeout(() => toast.classList.remove('show'), 3000);
    }
    let isScanPending = false;

    function scanNetworks() {
      if (isScanPending) return;
      isScanPending = true;
      const icon = document.getElementById('iconScan');
      icon.innerHTML = '⏳';

      fetch('/api/wifi/scan')
      .then(r => r.json())
      .then(networks => {
        icon.innerHTML = '🔄';
        isScanPending = false;
        const select = document.getElementById('wifiSsid');
        select.innerHTML = '';
        if (networks.length === 0) {
          select.innerHTML = '<option value="">Nenhuma rede encontrada</option>';
        } else {
          networks.forEach(net => {
            const opt = document.createElement('option');
            opt.value = net.ssid;
            opt.innerText = `${net.ssid} (${net.rssi} dBm)`;
            select.appendChild(opt);
          });
        }
      })
      .catch(err => {
        icon.innerHTML = '🔄';
        isScanPending = false;
        showToast("Erro ao buscar redes. Verifique a conexão com o ESP32.", "error");
      });
    }

    function saveWifi(e) {
      e.preventDefault();
      const ssid = document.getElementById('wifiSsid').value;
      const pass = document.getElementById('wifiPass').value;
      
      if (!ssid) {
        showToast("Selecione uma rede Wi-Fi.", "error");
        return;
      }

      fetch('/api/wifi/config', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({
          wifiSsid: ssid,
          wifiPass: pass,
          dhcp: true,
          autoReconnect: true
        })
      })
      .then(r => r.json())
      .then(data => {
        if (data.status === 'success') {
          showToast('Configurações de Wi-Fi salvas com sucesso! O ESP32 será reiniciado.', 'success');
        } else {
          showToast('Erro ao salvar as configurações.', 'error');
        }
      })
      .catch(err => {
        showToast("Erro ao salvar as configurações.", "error");
      });
    }

    window.onload = scanNetworks;
  </script>
</body>
</html>
)rawliteral";

#endif // WEB_PAGES_H
