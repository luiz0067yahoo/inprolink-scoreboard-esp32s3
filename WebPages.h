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
  <title>Login Administrador - Esporte7 System</title>

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
      <div class="brand-title">ESPORTE7</div>
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
        if (userVal === 'esporte7' && passVal === 'link@link') {
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
  <title>Gestão de Usuários - Esporte7 System</title>

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
        const isDefaultAdmin = u.username === 'esporte7';

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
        users = JSON.parse(localStorage.getItem('esporte7_users')) || [
          { name: 'Administrador Esporte7', username: 'esporte7', pass: 'link@link', role: 'Administrador' }
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
        localStorage.setItem('esporte7_users', JSON.stringify(users));
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
      if (users[idx].username === 'esporte7') {
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
          localStorage.setItem('esporte7_users', JSON.stringify(users));
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
  <title>Configuração de Rede - Esporte7 System</title>

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
    .btn-inline:disabled { opacity: 0.6; cursor: not-allowed; }
    .spin { display: inline-block; animation: spin 1s linear infinite; }
    @keyframes spin { 100% { transform: rotate(360deg); } }

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
    .btn-forget { background: linear-gradient(180deg, #c62828, #b71c1c); }

    /* Network Config Fields (exibido tanto em DHCP quanto em IP Fixo) */
    #staticIpFields {
      display: flex;
      flex-direction: column;
      gap: 15px;
      border-top: 1px dashed #333;
      padding-top: 15px;
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
          <select id="wifiSsid" class="input-field" style="flex: 1;" onchange="handleSsidChange()">
            <option value="">Aguarde ou clique em Escanear...</option>
          </select>
          <button type="button" class="btn-inline" id="btnScan" onclick="scanNetworks()">
            <span id="iconScan">🔄</span> <span id="textScan">Escanear</span>
          </button>
        </div>
      </div>

      <div class="input-group" id="manualSsidGroup" style="display: none; margin-top: 10px;">
        <label>Digitar Nome da Rede (SSID Manual)</label>
        <input type="text" id="wifiSsidManual" class="input-field" placeholder="Ex: MinhaRede_2.4G">
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

      <!-- Configurações de Rede (IP, Máscara, Gateway, DNS) -->
      <div id="staticIpFields">
        <div style="display: flex; justify-content: space-between; align-items: center; margin-bottom: 4px;">
          <span style="font-size: 0.8rem; font-weight: 800; text-transform: uppercase; letter-spacing: 0.5px; color: #ddd;">
            🌐 Configurações de Rede (TCP/IP)
          </span>
          <span id="dhcpStatusBadge" style="font-size: 0.72rem; padding: 4px 10px; border-radius: 12px; background: #1b5e20; color: #81c784; font-weight: 700;">
            Atribuído via DHCP (Automático)
          </span>
        </div>

        <div class="grid-2col">
          <div class="input-group">
            <label id="lblIp">Endereço IP (DHCP)</label>
            <input type="text" id="staticIp" class="input-field" value="---" readonly>
          </div>
          <div class="input-group">
            <label id="lblSubnet">Máscara de Sub-rede</label>
            <input type="text" id="staticSubnet" class="input-field" value="---" readonly>
          </div>
        </div>
        <div class="grid-2col">
          <div class="input-group">
            <label id="lblGateway">Gateway Padrão</label>
            <input type="text" id="staticGateway" class="input-field" value="---" readonly>
          </div>
          <div class="input-group">
            <label id="lblDns">Servidor DNS</label>
            <input type="text" id="staticDns" class="input-field" value="---" readonly>
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
        <input type="text" id="apSsid" class="input-field" value="ESPORTE7-PLACAR-AP">
      </div>

      <div class="input-group">
        <label>Senha do AP</label>
        <input type="text" id="apPass" class="input-field" value="Esporte7@" placeholder="Mínimo 8 caracteres">
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
      <div style="display: flex; gap: 10px; flex-wrap: wrap;">
        <button type="button" class="btn-nav btn-forget" onclick="forgetWifi()">
          🗑️ Esquecer Rede
        </button>
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

    let currentNetworkStatus = null;

    function toggleDhcp() {
      const isDhcp = document.getElementById('dhcpToggle').checked;
      const ipInput = document.getElementById('staticIp');
      const subnetInput = document.getElementById('staticSubnet');
      const gatewayInput = document.getElementById('staticGateway');
      const dnsInput = document.getElementById('staticDns');
      const badge = document.getElementById('dhcpStatusBadge');
      const lblIp = document.getElementById('lblIp');

      if (isDhcp) {
        // Modo DHCP: Mostrar configurações obtidas automaticamente pelo roteador
        if (badge) {
          badge.innerText = 'Atribuído via DHCP (Automático)';
          badge.style.background = '#1b5e20';
          badge.style.color = '#81c784';
        }
        if (lblIp) lblIp.innerText = 'Endereço IP (DHCP)';

        if (currentNetworkStatus) {
          ipInput.value = currentNetworkStatus.currentIp || currentNetworkStatus.ip || '---';
          subnetInput.value = currentNetworkStatus.currentSubnet || currentNetworkStatus.subnet || '255.255.255.0';
          gatewayInput.value = currentNetworkStatus.currentGateway || currentNetworkStatus.gateway || '0.0.0.0';
          dnsInput.value = currentNetworkStatus.currentDns || currentNetworkStatus.dns || '0.0.0.0';
        }

        ipInput.readOnly = true;
        subnetInput.readOnly = true;
        gatewayInput.readOnly = true;
        dnsInput.readOnly = true;

        [ipInput, subnetInput, gatewayInput, dnsInput].forEach(el => {
          if (el) {
            el.style.backgroundColor = '#141414';
            el.style.borderColor = '#2a2a2a';
            el.style.color = '#81c784';
          }
        });
      } else {
        // Modo Estático (Manual): Permitir edição de IP Fixo
        if (badge) {
          badge.innerText = 'IP Fixo (Manual)';
          badge.style.background = '#e65100';
          badge.style.color = '#ffcc80';
        }
        if (lblIp) lblIp.innerText = 'Endereço IP Fixado (Manual)';

        if (currentNetworkStatus && currentNetworkStatus.staticIp) {
          ipInput.value = currentNetworkStatus.staticIp;
          subnetInput.value = currentNetworkStatus.staticSubnet || '255.255.255.0';
          gatewayInput.value = currentNetworkStatus.staticGateway || '192.168.1.1';
          dnsInput.value = currentNetworkStatus.staticDns || '8.8.8.8';
        }

        ipInput.readOnly = false;
        subnetInput.readOnly = false;
        gatewayInput.readOnly = false;
        dnsInput.readOnly = false;

        [ipInput, subnetInput, gatewayInput, dnsInput].forEach(el => {
          if (el) {
            el.style.backgroundColor = '#1a1a1a';
            el.style.borderColor = '#333';
            el.style.color = '#ffffff';
          }
        });
        if (ipInput) ipInput.style.borderColor = '#ff1a1a';
      }
    }

    function loadWifiStatus() {
      fetch('/api/wifi/status')
      .then(r => {
        if (!r.ok) throw new Error('Falha ao obter status de rede');
        return r.json();
      })
      .then(data => {
        currentNetworkStatus = data;
        document.getElementById('disp-ip').innerText = data.ip || '---';
        document.getElementById('disp-ssid').innerText = data.ssid || '---';
        document.getElementById('disp-rssi').innerText = (data.rssi || 0) + ' dBm';
        document.getElementById('disp-mac').innerText = data.mac || '---';

        // Carregar campos
        const wifiSsidSelect = document.getElementById('wifiSsid');
        if (data.wifiSsid) {
          wifiSsidSelect.innerHTML = `<option value="${data.wifiSsid}" selected>⭐ ${data.wifiSsid} (Salva)</option>`;
        }
        document.getElementById('wifiPass').value = data.wifiPass || '';
        document.getElementById('dhcpToggle').checked = data.dhcp;

        document.getElementById('apSsid').value = data.apSsid || '';
        document.getElementById('apPass').value = data.apPass || '';
        document.getElementById('apChannel').value = data.apChannel || '6';

        document.getElementById('httpPort').value = data.httpPort || 80;
        document.getElementById('wsPort').value = data.wsPort || 81;
        document.getElementById('autoReconnect').checked = data.autoReconnect;

        toggleDhcp();
        // Escanear redes automaticamente após carregar status
        setTimeout(scanNetworks, 350);
      })
      .catch(err => {
        console.warn('API offline, usando fallback local de visualização...', err);
        const saved = localStorage.getItem('esporte7_wifi_config');
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

    function handleSsidChange() {
      const select = document.getElementById('wifiSsid');
      const manualGroup = document.getElementById('manualSsidGroup');
      if (select && manualGroup) {
        if (select.value === '__manual__') {
          manualGroup.style.display = 'block';
          const input = document.getElementById('wifiSsidManual');
          if (input) input.focus();
        } else {
          manualGroup.style.display = 'none';
        }
      }
    }

    function populateWifiList(networks, keepSelected) {
      const select = document.getElementById('wifiSsid');
      if (!select) return;
      select.innerHTML = '';

      const defaultOpt = document.createElement('option');
      defaultOpt.value = '';
      defaultOpt.innerText = '-- Selecione uma Rede Wi-Fi --';
      select.appendChild(defaultOpt);

      let foundSelected = false;

      // Filtrar vazios e duplicatas mantendo o sinal mais forte
      const map = new Map();
      if (Array.isArray(networks)) {
        networks.forEach(net => {
          if (net && net.ssid && net.ssid.trim().length > 0) {
            const existing = map.get(net.ssid);
            if (!existing || net.rssi > existing.rssi) {
              map.set(net.ssid, net);
            }
          }
        });
      }

      const uniqueNets = Array.from(map.values());
      uniqueNets.sort((a, b) => (b.rssi || -100) - (a.rssi || -100));

      uniqueNets.forEach(net => {
        const opt = document.createElement('option');
        opt.value = net.ssid;
        let sig = '📶';
        if (net.rssi < -80) sig = ' ▂';
        else if (net.rssi < -67) sig = ' ▂▄';
        else sig = ' ▂▄▆█';
        const lock = net.secure ? ' 🔒' : '';
        opt.innerText = `${sig} ${net.ssid} (${net.rssi} dBm)${lock}`;
        if (net.ssid === keepSelected) {
          opt.selected = true;
          foundSelected = true;
        }
        select.appendChild(opt);
      });

      if (uniqueNets.length === 0 && (!keepSelected || keepSelected === '__manual__')) {
        const emptyOpt = document.createElement('option');
        emptyOpt.value = '';
        emptyOpt.innerText = '⚠️ Nenhuma rede 2.4 GHz detectada';
        select.appendChild(emptyOpt);
      }

      // Se havia rede salva anteriormente que não apareceu no scan, mantê-la disponível
      if (keepSelected && !foundSelected && keepSelected !== '__manual__') {
        const opt = document.createElement('option');
        opt.value = keepSelected;
        opt.innerText = `⭐ ${keepSelected} (Salva/Atual)`;
        opt.selected = true;
        select.insertBefore(opt, select.children[1] || null);
      }

      // Opção para digitar manualmente caso a rede seja oculta ou não apareça
      const manualOpt = document.createElement('option');
      manualOpt.value = '__manual__';
      manualOpt.innerText = '✏️ Digitar outra rede manualmente...';
      if (keepSelected === '__manual__') {
        manualOpt.selected = true;
      }
      select.appendChild(manualOpt);

      handleSsidChange();
    }

    function scanNetworks() {
      if (isScanPending) return;
      const icon = document.getElementById('iconScan');
      const text = document.getElementById('textScan');
      const btn = document.getElementById('btnScan');

      isScanPending = true;
      if (icon) icon.classList.add('spin');
      if (text) text.innerText = 'Buscando...';
      if (btn) btn.disabled = true;

      const currentSelected = (document.getElementById('wifiSsid') ? document.getElementById('wifiSsid').value : '') || '';

      fetch('/api/wifi/scan')
      .then(r => {
        if (!r.ok) throw new Error('Falha no escaneamento (' + r.status + ')');
        return r.json();
      })
      .then(networks => {
        finishScan();
        populateWifiList(networks, currentSelected);
        if (Array.isArray(networks) && networks.length > 0) {
          showToast(`Busca concluída! ${networks.length} rede(s) encontrada(s).`, 'success');
        } else {
          showToast('Nenhuma rede 2.4 GHz detectada. Tente novamente ou digite manualmente.', 'error');
        }
      })
      .catch(err => {
        finishScan();
        console.warn('API de scan indisponível ou falhou:', err);
        if (window.location.protocol === 'file:' || window.location.hostname.includes('github.io')) {
          populateWifiList([
            { ssid: 'Clube_Membros', rssi: -64, secure: true },
            { ssid: 'Esporte7_Tech', rssi: -72, secure: true },
            { ssid: 'TFC_Visitantes', rssi: -80, secure: false }
          ], currentSelected);
          showToast('Busca concluída! 3 redes simuladas (Modo Demo).', 'success');
        } else {
          showToast('Não foi possível obter redes do ESP32. Tente novamente.', 'error');
        }
      });

      function finishScan() {
        isScanPending = false;
        if (icon) icon.classList.remove('spin');
        if (text) text.innerText = 'Escanear';
        if (btn) btn.disabled = false;
      }
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
      let ssid = document.getElementById('wifiSsid').value;
      if (ssid === '__manual__') {
        const manualInput = document.getElementById('wifiSsidManual');
        ssid = manualInput ? manualInput.value.trim() : '';
      }
      if (!ssid) {
        showToast('Por favor, selecione ou digite a rede Wi-Fi.', 'error');
        return;
      }

      const config = {
        wifiSsid: ssid,
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
        localStorage.setItem('esporte7_wifi_config', JSON.stringify({
          ssid: config.wifiSsid,
          dhcp: config.dhcp,
          staticIp: config.staticIp,
          apSsid: config.apSsid,
          wsPort: config.wsPort
        }));
        showToast('Configurações salvas no localStorage (Simulado)!', 'success');
      });
    }

    function forgetWifi() {
      if (!confirm('Deseja realmente esquecer a rede Wi-Fi configurada?\nO ESP32 desconectará da rede e reiniciará no modo Ponto de Acesso (Hotspot).')) {
        return;
      }
      showToast('Esquecendo rede Wi-Fi...', 'info');
      fetch('/api/wifi/forget', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' }
      })
      .then(r => r.json())
      .then(data => {
        if (data.status === 'success') {
          showToast('Rede esquecida! O dispositivo reiniciará no modo Ponto de Acesso.', 'success');
          setTimeout(() => {
            const select = document.getElementById('wifiSsid');
            if (select) select.innerHTML = '<option value="">Selecione uma rede...</option>';
            const pass = document.getElementById('wifiPass');
            if (pass) pass.value = '';
          }, 1000);
        } else {
          showToast(data.error || 'Erro ao esquecer rede.', 'error');
        }
      })
      .catch(err => {
        console.warn('API offline, simulando esquecimento...', err);
        const saved = localStorage.getItem('esporte7_wifi_config');
        if (saved) {
          const cfg = JSON.parse(saved);
          cfg.ssid = '';
          localStorage.setItem('esporte7_wifi_config', JSON.stringify(cfg));
        }
        showToast('Rede esquecida! O dispositivo desconectará e reiniciará no modo Ponto de Acesso.', 'success');
        const select = document.getElementById('wifiSsid');
        if (select) select.innerHTML = '<option value="">Selecione uma rede...</option>';
        const pass = document.getElementById('wifiPass');
        if (pass) pass.value = '';
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
  <title>Wizard de Configuração Geral - Esporte7 System</title>

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

    /* Cards Grid (Modalidade, Campeonato, Rodada) */
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
      text-align: center;
    }

    /* MATCH CARD LAYOUT - FIEL AO PRINT DO USUÁRIO */
    .matches-list-grid {
      display: flex;
      flex-direction: column;
      gap: 16px;
      margin-top: 10px;
    }

    .match-card-wrapper {
      background: #ffffff;
      border: 1px solid #e5e7eb;
      border-radius: 12px;
      overflow: hidden;
      box-shadow: 0 4px 15px rgba(0, 0, 0, 0.3);
      cursor: pointer;
      position: relative;
      transition: all 0.25s ease;
      color: #111827;
    }

    .match-card-wrapper:hover {
      transform: translateY(-2px);
      box-shadow: 0 8px 24px rgba(0, 0, 0, 0.45);
      border-color: #ff4d4f;
    }

    .match-card-wrapper.selected {
      border: 2px solid #ef4444;
      box-shadow: 0 0 18px rgba(239, 68, 68, 0.55);
    }

    .match-card-top-bar {
      height: 4px;
      background: #ff5252;
      width: 100%;
    }

    .match-card-inner {
      padding: 16px 20px;
      display: flex;
      flex-direction: column;
      gap: 14px;
    }

    .match-card-header {
      display: flex;
      justify-content: space-between;
      align-items: center;
      font-size: 0.8rem;
      color: #6b7280;
      font-weight: 600;
    }

    .match-date-time {
      display: flex;
      align-items: center;
      gap: 6px;
    }

    .m-dot {
      color: #9ca3af;
      margin: 0 2px;
    }

    .match-location {
      display: flex;
      align-items: center;
      gap: 5px;
      color: #6b7280;
      max-width: 45%;
      white-space: nowrap;
      overflow: hidden;
      text-overflow: ellipsis;
    }

    .match-confronto {
      display: grid;
      grid-template-columns: 1fr auto 1fr;
      align-items: center;
      gap: 15px;
      padding: 4px 0;
    }

    .match-team {
      display: flex;
      flex-direction: column;
      align-items: center;
      gap: 8px;
      text-align: center;
    }

    .team-logo-badge {
      width: 58px;
      height: 58px;
      border-radius: 50%;
      background: #f9fafb;
      border: 2px solid #f3f4f6;
      box-shadow: 0 2px 8px rgba(0, 0, 0, 0.08);
      display: flex;
      align-items: center;
      justify-content: center;
      overflow: hidden;
    }

    .team-logo-badge img {
      width: 100%;
      height: 100%;
      object-fit: cover;
    }

    .team-name {
      font-size: 0.95rem;
      font-weight: 800;
      color: #111827;
      max-width: 140px;
      overflow: hidden;
      text-overflow: ellipsis;
      white-space: nowrap;
    }

    .match-center {
      display: flex;
      flex-direction: column;
      align-items: center;
      gap: 5px;
      min-width: 110px;
    }

    .match-score {
      display: flex;
      align-items: center;
      justify-content: center;
      gap: 12px;
      line-height: 1;
    }

    .score-num {
      font-size: 1.85rem;
      font-weight: 900;
      color: #111827;
      font-family: 'Montserrat', sans-serif;
    }

    .score-x {
      font-size: 1.15rem;
      color: #9ca3af;
      font-weight: 700;
    }

    .match-status-badge {
      font-size: 0.65rem;
      font-weight: 800;
      text-transform: uppercase;
      letter-spacing: 0.5px;
      padding: 2px 9px;
      border-radius: 10px;
      background: #fee2e2;
      color: #dc2626;
    }

    .match-status-badge.finished {
      background: #f3f4f6;
      color: #6b7280;
    }

    .match-status-badge.scheduled {
      background: #e0f2fe;
      color: #0284c7;
    }

    .match-clock {
      font-size: 0.85rem;
      font-weight: 900;
      color: #dc2626;
      font-family: 'Orbitron', monospace;
      letter-spacing: 1px;
    }

    .match-card-footer {
      display: flex;
      justify-content: center;
      margin-top: 2px;
    }

    .btn-match-select {
      background: #fff1f0;
      border: 1px solid #ffccc7;
      color: #cf1322;
      padding: 7px 24px;
      border-radius: 20px;
      font-size: 0.82rem;
      font-weight: 800;
      cursor: pointer;
      display: flex;
      align-items: center;
      gap: 8px;
      transition: all 0.2s;
    }

    .match-card-wrapper.selected .btn-match-select {
      background: #dc2626;
      color: #ffffff;
      border-color: #dc2626;
      box-shadow: 0 2px 10px rgba(220, 38, 38, 0.4);
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
        <div class="wizard-status" id="step-status-text">Passo 1 de 5</div>
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

    <!-- Stepper Navigation Header (Passo 4: Rodada, Passo 5: Partida) -->
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
          <span class="step-label">Rodada</span>
        </div>
        <div class="step-indicator" id="ind-5">
          <div class="step-circle">5</div>
          <span class="step-label">Partida</span>
        </div>
      </div>

      <!-- Step 1: Domínio -->
      <div class="step-content active" id="step-1">
        <div class="card-title">
          🌐 Informar Domínio do Sistema
        </div>
        <div class="input-group">
          <label for="domainInput">Endereço do Domínio / IP do Servidor</label>
          <input type="text" id="domainInput" class="input-field" placeholder="Ex: esportes7.com.br ou 192.168.1.100" value="esportes7.com.br">
        </div>
        <div class="input-group" style="margin-top: 15px;">
          <label for="portInput">Porta do Servidor (Opcional)</label>
          <input type="number" id="portInput" class="input-field" placeholder="Padrão: Vazio (HTTPS 443 / HTTP 80)" value="">
        </div>
        <div class="input-group" style="margin-top: 15px;">
          <label for="prefixInput">Prefixo da API</label>
          <input type="text" id="prefixInput" class="input-field" placeholder="Ex: /api/" value="/api/">
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
        </div>
      </div>

      <!-- Step 3: Campeonato -->
      <div class="step-content" id="step-3">
        <div class="card-title">
          🏆 Selecionar Campeonato
        </div>
        <div class="options-grid">
          <div class="option-card selected" onclick="selectCard('campeonato', '10', this)">
            🏆
            <span>Campeonato Principal</span>
          </div>
        </div>
      </div>

      <!-- Step 4: Rodada (Antes da Partida) -->
      <div class="step-content" id="step-4">
        <div class="card-title">
          🔢 Passo 4: Selecionar Rodada
        </div>
        <p style="font-size: 0.85rem; color: #888; margin-top: -10px; margin-bottom: 5px;">Selecione a rodada do campeonato para filtrar as partidas no próximo passo:</p>
        <div class="options-grid">
          <div class="option-card selected" onclick="selectCard('rodada', 'Todas as Rodadas', this)">
            🔢
            <span>Todas as Rodadas</span>
          </div>
        </div>
      </div>

      <!-- Step 5: Partida (Depois da Rodada) -->
      <div class="step-content" id="step-5">
        <div class="card-title" style="justify-content: space-between; flex-wrap: wrap; gap: 8px;">
          <span>⚽ Passo 5: Selecionar Partida</span>
          <span id="matchRoundBadge" style="font-size: 0.75rem; color: #fff; background: #dc2626; padding: 4px 12px; border-radius: 12px; font-weight: 700; box-shadow: 0 0 8px rgba(220, 38, 38, 0.4);">Todas as Rodadas</span>
        </div>
        <p style="font-size: 0.85rem; color: #888; margin-top: -10px; margin-bottom: 5px;">Confrontos da rodada selecionada. Clique no botão da partida para acompanhar no placar:</p>
        <div id="matchesContainer" class="matches-list-grid">
          <!-- Cards de partidas inseridos dinamicamente aqui -->
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

    <!-- Container do Manual (Rodada antes da Partida) -->
    <div id="manual-container" style="display: none; padding: 20px; background: #1a1a1a; border-radius: 12px; margin-top: 15px;">
      <div class="card-title" style="margin-bottom: 20px; text-align: center;">✍️ Configuração Manual do Placar</div>
      
      <div class="input-group">
        <label>Endereço do Domínio / IP (Opcional)</label>
        <input type="text" id="manual_dominio" class="input-field" value="esportes7.com.br">
      </div>
      <div class="input-group" style="margin-top: 15px;">
        <label>Modalidade</label>
        <input type="text" id="manual_modalidade" class="input-field" placeholder="Ex: Futebol">
      </div>
      <div class="input-group" style="margin-top: 15px;">
        <label>Campeonato</label>
        <input type="text" id="manual_campeonato" class="input-field" placeholder="Ex: Campeonato Regional">
      </div>
      <div class="input-group" style="margin-top: 15px;">
        <label>Rodada</label>
        <input type="text" id="manual_rodada" class="input-field" placeholder="Ex: Rodada 1 ou Final">
      </div>
      <div class="input-group" style="margin-top: 15px;">
        <label>Partida</label>
        <input type="text" id="manual_partida" class="input-field" placeholder="Ex: Time A x Time B">
      </div>

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
    const totalSteps = 5;
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
      dominio: 'https://esportes7.com.br/',
      modalidade: '',
      campeonato: '',
      rodada: 'Todas as Rodadas',
      partida: ''
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
          const lowerName = (item.nome || '').toLowerCase();
          if (lowerName.includes('futebol 7')) displayIcon = '⚽';
          else if (lowerName.includes('futsal') || lowerName.includes('futebol') || lowerName.includes('soccer')) displayIcon = '⚽';
          else if (lowerName.includes('futev')) displayIcon = '🏐';
          else if (lowerName.includes('praia') && lowerName.includes('vôlei')) displayIcon = '🏖️';
          else if (lowerName.includes('vôlei') || lowerName.includes('volei') || lowerName.includes('volley')) displayIcon = '🏐';
          else if (lowerName.includes('beach')) displayIcon = '🏖️';
          else if (lowerName.includes('mesa')) displayIcon = '🏓';
          else if (lowerName.includes('tênis') || lowerName.includes('tenis')) displayIcon = '🎾';
          else if (lowerName.includes('nata') || lowerName.includes('swim')) displayIcon = '🏊';
          else if (lowerName.includes('corri') || lowerName.includes('run')) displayIcon = '🏃';
          else if (lowerName.includes('basque') || lowerName.includes('basket')) displayIcon = '🏀';
          else if (lowerName.includes('hand')) displayIcon = '🤾';
          else if (lowerName.includes('jiu')) displayIcon = '🥋';
          else if (lowerName.includes('cicl') || lowerName.includes('bike') || lowerName.includes('mtb')) displayIcon = '🚴';
        } else if (field === 'campeonato') {
          displayIcon = '🏆';
        } else if (field === 'rodada') {
          displayIcon = '🔢';
        }
        
        card.onclick = () => selectCard(field, item.id, card);
        card.innerHTML = `
          <span style="font-size: 24px;">${displayIcon}</span>
          <span>${item.nome}</span>
        `;
        grid.appendChild(card);
      });
    }

    function cleanDomain(d, port = '') {
      if (!d || d === 'esporte7.com.br') d = 'esportes7.com.br';
      d = d.trim();
      d = d.replace(/^https?:\/\//i, '');
      d = d.replace(/\/+$/, '');
      d = d.replace(/\/api$/, '');
      d = d.replace(/\/+$/, '');
      if (port && port !== '' && port !== '0' && port !== '80' && port !== '443' && port !== '8080' && !d.includes(':')) {
        d = d + ':' + port;
      }
      return d;
    }

    function getApiBaseUrl() {
      let dom = document.getElementById('domainInput') ? document.getElementById('domainInput').value.trim() : 'esportes7.com.br';
      let port = document.getElementById('portInput') ? document.getElementById('portInput').value.trim() : '';
      let prefix = document.getElementById('prefixInput') ? document.getElementById('prefixInput').value.trim() : '/api/';

      if (!dom || dom === 'esporte7.com.br') dom = 'esportes7.com.br';
      let protocol = 'https:';
      if (dom.startsWith('http://')) {
        protocol = 'http:';
        dom = dom.replace(/^http:\/\//i, '');
      } else if (dom.startsWith('https://')) {
        protocol = 'https:';
        dom = dom.replace(/^https:\/\//i, '');
      }

      if (dom.includes(':')) {
        const parts = dom.split(':');
        dom = parts[0];
        if (parts[1]) port = parts[1].replace(/\/.*$/, '');
      }
      dom = dom.replace(/\/+$/, '');

      if (dom.endsWith('/api')) {
        dom = dom.substring(0, dom.length - 4);
        dom = dom.replace(/\/+$/, '');
      }

      if (!prefix.startsWith('/')) prefix = '/' + prefix;
      if (!prefix.endsWith('/')) prefix = prefix + '/';

      let hostPort = dom;
      if (port && port !== '' && port !== '0' && port !== '80' && port !== '443' && port !== '8080') {
        hostPort += ':' + port;
      }
      return `${protocol}//${hostPort}${prefix}`;
    }

    function fetchApiResource(targetUrl) {
      // 1. Tentar primeiro o link direto
      return fetch(targetUrl)
        .then(r => {
          if (!r.ok) throw new Error('API direta erro: ' + r.status);
          return r.json();
        })
        .catch(directErr => {
          console.warn('Acesso direto indisponível (CORS), tentando proxy do ESP32:', directErr);
          // 2. Se falhar no acesso direto (CORS), tenta o proxy local do ESP32
          return fetch(`/api/proxy?url=${encodeURIComponent(targetUrl)}`)
            .then(r => {
              if (!r.ok) throw new Error('Proxy ESP32 erro: ' + r.status);
              return r.json();
            })
            .catch(proxyErr => {
              console.warn('Proxy ESP32 indisponível (ESP32 sem internet), tentando proxy CORS web alternativo:', proxyErr);
              // 3. Fallback inteligente: Proxy CORS público
              return fetch(`https://api.allorigins.win/raw?url=${encodeURIComponent(targetUrl)}`)
                .then(r => {
                  if (!r.ok) throw new Error('CORS web proxy erro: ' + r.status);
                  return r.json();
                });
            });
        });
    }

    function fetchModalidades(callback) {
      const url = `${getApiBaseUrl()}sports`;
      console.log('Requisitando modalidades em:', url);
      fetchApiResource(url)
      .then(data => {
        const list = Array.isArray(data) ? data : (data.data || data.modalidades || data.sports || []);
        const mapped = list.map(item => ({ id: item.id, nome: item.name || item.nome || 'Modalidade' }));
        populateStepOptions('step-2', 'modalidade', mapped, '⚽');
        callback();
      })
      .catch(err => {
        console.warn('Usando fallback local de modalidades...', err);
        const data = [
          { id: 1, nome: 'Futebol' },
          { id: 2, nome: 'Vôlei' },
          { id: 3, nome: 'Corrida' },
          { id: 4, nome: 'Tênis' },
          { id: 5, nome: 'Futsal' },
          { id: 6, nome: 'Basquete' },
          { id: 7, nome: 'Handebol' },
          { id: 8, nome: 'Futebol 7' },
          { id: 9, nome: 'Futevôlei' },
          { id: 10, nome: 'Beach Tennis' },
          { id: 11, nome: 'Tênis de Mesa' },
          { id: 12, nome: 'Vôlei de Praia' },
          { id: 13, nome: 'Jiu-Jitsu' },
          { id: 14, nome: 'Ciclismo' },
          { id: 15, nome: 'MTB' },
          { id: 16, nome: 'Natação' }
        ];
        populateStepOptions('step-2', 'modalidade', data, '⚽');
        callback();
      });
    }

    function fetchCampeonatos(mod, callback) {
      let queryParam = mod ? `?sport_id=${encodeURIComponent(mod)}` : '';
      const url = `${getApiBaseUrl()}clubs/1/championships${queryParam}`;
      console.log('Requisitando campeonatos em:', url);
      fetchApiResource(url)
      .then(data => {
        const list = Array.isArray(data) ? data : (data.data || data.campeonatos || data.championships || []);
        const mapped = list.map(item => ({ id: item.id, nome: item.name || item.nome || item.title || 'Campeonato' }));
        populateStepOptions('step-3', 'campeonato', mapped, '🏆');
        callback();
      })
      .catch(err => {
        console.warn('Usando fallback local de campeonatos...', err);
        const data = [
          { id: 10, nome: 'Campeonato Listão' },
          { id: 88, nome: 'TESTE FUTSAL-FUT7' }
        ];
        populateStepOptions('step-3', 'campeonato', data, '🏆');
        callback();
      });
    }

    // Armazenamento em memória das partidas do campeonato atual
    let allMatchesList = [];

    // Passo 4: Buscar Partidas e extrair Rodadas (Rodada antes da Partida)
    function fetchRoundsForChampionship(campId, callback) {
      const url = `${getApiBaseUrl()}championships/${encodeURIComponent(campId)}/matches`;
      console.log('Requisitando partidas e rodadas em:', url);
      fetchApiResource(url)
      .then(data => {
        const list = Array.isArray(data) ? data : (data.data || data.partidas || data.matches || []);
        allMatchesList = list;

        // Extrair rodadas únicas das partidas
        const roundSet = new Set();
        list.forEach(m => {
          if (m.round_name && m.round_name.trim()) roundSet.add(m.round_name.trim());
          else if (m.round_number) roundSet.add(`Rodada ${m.round_number}`);
          else if (m.group_name && m.group_name.trim()) roundSet.add(m.group_name.trim());
        });

        const roundsList = [{ id: 'Todas as Rodadas', nome: 'Todas as Rodadas' }];
        roundSet.forEach(r => {
          roundsList.push({ id: r, nome: r });
        });

        if (roundsList.length === 1) {
          // Se o campeonato não tiver nomes de rodada cadastrados nas partidas, fornecer opções padrão
          ['Rodada 1', 'Rodada 2', 'Rodada 3', 'Fase de Grupos', 'Oitavas de Final', 'Quartas de Final', 'Semifinal', 'Final'].forEach(r => {
            roundsList.push({ id: r, nome: r });
          });
        }

        populateStepOptions('step-4', 'rodada', roundsList, '🔢');
        callback();
      })
      .catch(err => {
        console.warn('Erro ao buscar partidas/rodadas da API, usando padrão...', err);
        allMatchesList = [];
        const roundsList = [
          { id: 'Todas as Rodadas', nome: 'Todas as Rodadas' },
          { id: 'Rodada 1', nome: 'Rodada 1' },
          { id: 'Rodada 2', nome: 'Rodada 2' },
          { id: 'Rodada 3', nome: 'Rodada 3' },
          { id: 'Semifinal', nome: 'Semifinal' },
          { id: 'Final', nome: 'Final' }
        ];
        populateStepOptions('step-4', 'rodada', roundsList, '🔢');
        callback();
      });
    }

    function formatMatchDateTime(dtString) {
      if (!dtString) return { date: '01/02/2026', time: '21:00' };
      try {
        const d = new Date(dtString);
        if (isNaN(d.getTime())) return { date: '01/02/2026', time: '21:00' };
        const day = String(d.getDate()).padStart(2, '0');
        const month = String(d.getMonth() + 1).padStart(2, '0');
        const year = d.getFullYear();
        const hours = String(d.getHours()).padStart(2, '0');
        const mins = String(d.getMinutes()).padStart(2, '0');
        return {
          date: `${day}/${month}/${year}`,
          time: `${hours}:${mins}`
        };
      } catch (e) {
        return { date: '01/02/2026', time: '21:00' };
      }
    }

    function getTeamLogoHtml(logoUrl, teamName) {
      if (logoUrl && (logoUrl.startsWith('http://') || logoUrl.startsWith('https://'))) {
        return `<img src="${logoUrl}" alt="${teamName}" onerror="this.onerror=null; this.src='https://ui-avatars.com/api/?name=${encodeURIComponent(teamName || 'TM')}&background=111827&color=ffffff&bold=true';" />`;
      }
      return `<img src="https://ui-avatars.com/api/?name=${encodeURIComponent(teamName || 'TM')}&background=111827&color=ffffff&bold=true" alt="${teamName}" />`;
    }

    function selectMatchCard(matchId, cardEl) {
      wizardData.partida = String(matchId);
      wizardData.partidaId = String(matchId);
      const container = document.getElementById('matchesContainer');
      if (container) {
        const cards = container.querySelectorAll('.match-card-wrapper');
        cards.forEach(c => {
          c.classList.remove('selected');
          const btn = c.querySelector('.btn-match-select');
          if (btn) btn.innerHTML = '<span class="btn-icon">👁️</span> Acompanhar Ao Vivo';
        });
      }
      if (cardEl) {
        cardEl.classList.add('selected');
        const btn = cardEl.querySelector('.btn-match-select');
        if (btn) btn.innerHTML = '<span class="btn-icon">✓</span> Partida Selecionada';
      }
    }

    // Passo 5: Renderizar Partidas com o Layout Solicitado
    function renderMatchesForSelectedRound(selectedRound) {
      const badge = document.getElementById('matchRoundBadge');
      if (badge) badge.innerText = selectedRound || 'Todas as Rodadas';

      let filtered = allMatchesList;
      if (selectedRound && selectedRound !== 'Todas as Rodadas') {
        const f = allMatchesList.filter(m => {
          const rName = (m.round_name || '').trim();
          const rNum = m.round_number ? `Rodada ${m.round_number}` : '';
          const gName = (m.group_name || '').trim();
          return rName === selectedRound || rNum === selectedRound || gName === selectedRound;
        });
        if (f.length > 0) filtered = f;
      }

      // Se a API não retornou partidas cadastradas no campeonato, exibir partidas com o modelo visual exato do print
      if (!filtered || filtered.length === 0) {
        filtered = [
          {
            id: '2026_cam_mar',
            start_time: '2026-02-01T21:00:00.000000Z',
            location: 'A definir',
            home_team: {
              name: 'Camarões',
              logo_url: 'https://flagcdn.com/w160/cm.png'
            },
            away_team: {
              name: 'Marrocos',
              logo_url: 'https://flagcdn.com/w160/ma.png'
            },
            home_score: 3,
            away_score: 2,
            status: 'in_progress',
            clock: '00:00'
          },
          {
            id: '2026_lib_boc',
            start_time: '2026-02-02T19:30:00.000000Z',
            location: 'Arena Principal',
            home_team: {
              name: 'Libertad',
              logo_url: 'https://sgce.clubetoledao.com.br/assets/logos/bra_1755011784.png'
            },
            away_team: {
              name: 'Boca Juniors',
              logo_url: 'https://sgce.clubetoledao.com.br/assets/logos/bra_1755010583.png'
            },
            home_score: 5,
            away_score: 5,
            status: 'finished',
            clock: 'FIM'
          }
        ];
      }

      const container = document.getElementById('matchesContainer');
      container.innerHTML = '';

      filtered.forEach((m, idx) => {
        const isSelected = wizardData.partida ? (String(wizardData.partida) === String(m.id)) : (idx === 0);
        if (isSelected) {
          wizardData.partida = String(m.id);
          wizardData.partidaId = String(m.id);
        }

        const dt = formatMatchDateTime(m.start_time);
        const homeName = (m.home_team && m.home_team.name) ? m.home_team.name : (m.home_team_name || 'Mandante');
        const awayName = (m.away_team && m.away_team.name) ? m.away_team.name : (m.away_team_name || 'Visitante');
        const homeLogo = (m.home_team && m.home_team.logo_url) ? m.home_team.logo_url : '';
        const awayLogo = (m.away_team && m.away_team.logo_url) ? m.away_team.logo_url : '';
        const homeScore = (m.home_score !== null && m.home_score !== undefined) ? m.home_score : 0;
        const awayScore = (m.away_score !== null && m.away_score !== undefined) ? m.away_score : 0;
        const loc = m.location || 'A definir';

        let statusText = 'AO VIVO';
        let statusClass = '';
        let clockText = m.clock || '00:00';

        if (m.status === 'finished') {
          statusText = 'ENCERRADO';
          statusClass = 'finished';
          clockText = 'FIM';
        } else if (m.status === 'scheduled') {
          statusText = 'AGENDADO';
          statusClass = 'scheduled';
          clockText = dt.time || '--:--';
        }

        const card = document.createElement('div');
        card.className = `match-card-wrapper ${isSelected ? 'selected' : ''}`;
        card.onclick = () => selectMatchCard(m.id, card);

        card.innerHTML = `
          <div class="match-card-top-bar"></div>
          <div class="match-card-inner">
            <div class="match-card-header">
              <div class="match-date-time">
                <span>📅</span> <span>${dt.date}</span>
                <span class="m-dot">•</span>
                <span>🕒</span> <span>${dt.time}</span>
              </div>
              <div class="match-location">
                <span>📍</span> <span>${loc}</span>
              </div>
            </div>

            <div class="match-confronto">
              <div class="match-team home-team">
                <div class="team-logo-badge">
                  ${getTeamLogoHtml(homeLogo, homeName)}
                </div>
                <span class="team-name" title="${homeName}">${homeName}</span>
              </div>

              <div class="match-center">
                <div class="match-score">
                  <span class="score-num">${homeScore}</span>
                  <span class="score-x">x</span>
                  <span class="score-num">${awayScore}</span>
                </div>
                <div class="match-status-badge ${statusClass}">
                  ${statusText}
                </div>
                <div class="match-clock">
                  ${clockText}
                </div>
              </div>

              <div class="match-team away-team">
                <div class="team-logo-badge">
                  ${getTeamLogoHtml(awayLogo, awayName)}
                </div>
                <span class="team-name" title="${awayName}">${awayName}</span>
              </div>
            </div>

            <div class="match-card-footer">
              <button type="button" class="btn-match-select">
                <span class="btn-icon">${isSelected ? '✓' : '👁️'}</span>
                <span>${isSelected ? 'Partida Selecionada' : 'Acompanhar Ao Vivo'}</span>
              </button>
            </div>
          </div>
        `;

        container.appendChild(card);
      });
    }

    function changeStep(delta) {
      const newStep = currentStep + delta;
      if (newStep < 1 || newStep > totalSteps) return;

      if (delta > 0) {
        const domain = document.getElementById('domainInput').value.trim();
        const port = document.getElementById('portInput') ? document.getElementById('portInput').value.trim() : '';
        const prefix = document.getElementById('prefixInput') ? document.getElementById('prefixInput').value.trim() : '/api/';
        if (!domain) {
          showToast('Por favor, informe o domínio.', 'error');
          return;
        }
        wizardData.dominio = cleanDomain(domain, port);
        wizardData.porta = (port && port !== '0' && port !== '80' && port !== '443' && port !== '8080') ? parseInt(port, 10) : 0;
        wizardData.prefixo = prefix || '/api/';

        if (currentStep === 1) {
          fetchModalidades(() => proceed());
          return;
        } else if (currentStep === 2) {
          fetchCampeonatos(wizardData.modalidade, () => proceed());
          return;
        } else if (currentStep === 3) {
          // Do Passo 3 (Campeonato) para o Passo 4 (Rodada)
          fetchRoundsForChampionship(wizardData.campeonato, () => proceed());
          return;
        } else if (currentStep === 4) {
          // Do Passo 4 (Rodada) para o Passo 5 (Partida)
          renderMatchesForSelectedRound(wizardData.rodada);
          proceed();
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
      wizardData.active = true;
      wizardData.campeonato = String(wizardData.campeonato || '');
      wizardData.campeonatoId = wizardData.campeonato;
      wizardData.partida = String(wizardData.partida || '');
      wizardData.partidaId = wizardData.partida;
      wizardData.rodada = String(wizardData.rodada || '');
      wizardData.rodadaId = wizardData.rodada;
      wizardData.modalidade = String(wizardData.modalidade || '');
      const port = document.getElementById('portInput') ? document.getElementById('portInput').value.trim() : '';
      const prefix = document.getElementById('prefixInput') ? document.getElementById('prefixInput').value.trim() : '/api/';
      wizardData.porta = (port && port !== '0' && port !== '80' && port !== '443' && port !== '8080') ? parseInt(port, 10) : 0;
      wizardData.prefixo = prefix || '/api/';

      // Salva imediatamente no localStorage
      try {
        localStorage.setItem('esporte7_wizard_setup', JSON.stringify(wizardData));
      } catch(e) {}

      fetch('/api/automation/config', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify(wizardData)
      })
      .then(r => {
        showToast('Configuração de automação salva com sucesso no ESP32!', 'success');
        setTimeout(() => { window.location.href = 'painel.html'; }, 300);
      })
      .catch(err => {
        console.warn('API offline, salvando localmente...', err);
        showToast('Configuração concluída!', 'success');
        setTimeout(() => { window.location.href = 'painel.html'; }, 300);
      });
    }

    function saveManualConfig() {
      const camp = document.getElementById('manual_campeonato').value.trim();
      const rod = document.getElementById('manual_rodada').value.trim();
      const part = document.getElementById('manual_partida').value.trim();
      const data = {
        mode: "manual",
        active: false,
        dominio: document.getElementById('manual_dominio').value.trim(),
        modalidade: document.getElementById('manual_modalidade').value.trim(),
        campeonato: camp,
        rodada: rod,
        partida: part,
        campeonatoId: camp,
        rodadaId: rod,
        partidaId: part
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

    // Carregar configurações de domínio, porta e prefixo salvas no ESP32
    fetch('/api/automation/status')
      .then(r => r.json())
      .then(data => {
        if (data && data.dominio) {
          let dom = data.dominio;
          if (dom === 'esporte7.com.br') dom = 'esportes7.com.br';
          let p = (data.porta && data.porta != 8080 && data.porta != 443 && data.porta != 80 && data.porta != 0) ? data.porta : '';
          let pref = data.prefixo || '/api/';
          if (dom.includes(':')) {
            const parts = dom.split(':');
            dom = parts[0];
            p = parseInt(parts[1], 10) || p;
          }
          const domInput = document.getElementById('domainInput');
          if (domInput) domInput.value = dom;
          const portInput = document.getElementById('portInput');
          if (portInput) portInput.value = p;
          const prefInput = document.getElementById('prefixInput');
          if (prefInput) prefInput.value = pref;
        }
      })
      .catch(e => {});
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
  <title>Placar Eletrônico - Esporte7 System</title>

  <link rel="icon" href="data:,">
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
      padding: 8px 18px;
      box-shadow: inset 0 0 15px rgba(0, 0, 0, 0.9), 0 4px 10px rgba(0,0,0,0.5);
      display: flex;
      justify-content: center;
      align-items: center;
      box-sizing: border-box;
      min-height: 80px;
    }

    .row-middle .led-frame {
      min-height: 110px;
      padding: 10px 24px;
    }

    .led-text {
      font-family: 'Orbitron', 'Consolas', 'Courier New', 'Roboto Mono', monospace;
      font-variant-numeric: tabular-nums;
      -webkit-font-feature-settings: "tnum" 1;
      font-feature-settings: "tnum" 1;
      color: #ff1a1a;
      text-shadow: 0 0 12px rgba(255, 26, 26, 0.8), 0 0 25px rgba(255, 0, 0, 0.4);
      line-height: 1.1;
    }

    .digits-2 { font-size: 3.8rem; letter-spacing: 3px; }
    .digits-3 { font-size: 3.5rem; letter-spacing: 2px; }
    .digits-timer { font-size: 5rem; letter-spacing: 3px; }

    input.led-text {
      background: transparent;
      border: none;
      outline: none;
      text-align: center;
      font-variant-numeric: tabular-nums;
      -webkit-font-feature-settings: "tnum" 1;
      font-feature-settings: "tnum" 1;
      overflow: hidden;
      white-space: nowrap;
      text-overflow: clip;
      padding: 0;
      margin: 0;
      box-sizing: border-box;
    }
    input.led-text.digits-2 {
      width: 2.3ch;
    }
    input.led-text.digits-3 {
      width: 3.4ch;
    }
    /* Timer input needs wider width for HH:MM:SS */
    input.led-text.digits-timer {
      width: 9.2ch;
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

    <!-- Banner de Partida Sincronizada com Filtro -->
    <div id="active-match-banner" style="display: none; background: #111; border: 1px solid #222; border-left: 4px solid #e53935; border-radius: 8px; padding: 10px 16px; margin-bottom: 15px; align-items: center; justify-content: space-between; font-size: 0.85rem;">
      <div style="display: flex; align-items: center; gap: 10px; flex-wrap: wrap;">
        <span style="background: #fee2e2; color: #dc2626; padding: 2px 8px; border-radius: 6px; font-weight: 800; font-size: 0.72rem; letter-spacing: 0.5px;">AO VIVO</span>
        <span id="banner-mod-name" style="color: #60a5fa; font-weight: 700;">Modalidade</span>
        <span style="color: #666;">•</span>
        <span id="banner-camp-name" style="color: #fff; font-weight: 700;">Campeonato</span>
        <span style="color: #666;">•</span>
        <span id="banner-round-name" style="color: #aaa; font-weight: 600;">Rodada</span>
        <span style="color: #666;">•</span>
        <span id="banner-match-name" style="color: #4caf50; font-weight: 700;">Partida</span>
      </div>
      <div style="display: flex; align-items: center; gap: 10px;">
        <span style="color: #888; font-size: 0.75rem;">● Sincronizado via API</span>
        <button onclick="window.location.href='panel_config.html.html'" style="background: #222; border: 1px solid #444; color: #fff; padding: 4px 10px; border-radius: 6px; font-size: 0.75rem; cursor: pointer; font-weight: 600;">⚙️ Trocar</button>
      </div>
    </div>

    <!-- Linha Superior: Time A, Logo, Time B -->
    <div class="row-top">
      <!-- Time A (3 dígitos) -->
      <div class="module-card">
        <span class="module-title" id="title-team-a">TIME A</span>
        <div class="display-group">
          <div class="led-frame">
            <input type="text" class="led-text digits-3" id="score-a" value="000" maxlength="3" onchange="manualInputChanged('score-a')">
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

      <!-- Time B (3 dígitos) -->
      <div class="module-card">
        <span class="module-title" id="title-team-b">TIME B</span>
        <div class="display-group">
          <div class="led-frame">
            <input type="text" class="led-text digits-3" id="score-b" value="000" maxlength="3" onchange="manualInputChanged('score-b')">
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
        <input type="text" class="led-text digits-timer" id="timer-display"
          value="00:00:00" maxlength="8" placeholder="HH:MM:SS"
          oninput="timerMask(this)" onchange="timerInputChanged()" readonly>

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
    let totalSeconds = 0;
    let swapped = false;
    let currentPanelMode = 'automatico';

    // Atualização dos campos da interface mantendo campos em foco intactos e evitando re-renderização desnecessária
    function applyScoreboardState(data) {
      if (!data) return;
      const setVal = (id, val) => {
        const el = document.getElementById(id);
        if (el && document.activeElement !== el) {
          const padLen = (id === 'score-a' || id === 'score-b') ? 3 : 2;
          const newVal = String(val).padStart(padLen, '0');
          if (el.value !== newVal) {
            el.value = newVal;
          }
        }
      };
      if (data.scoreA !== undefined) setVal('score-a', data.scoreA);
      if (data.scoreB !== undefined) setVal('score-b', data.scoreB);
      if (data.foulsA !== undefined) setVal('fouls-a', data.foulsA);
      if (data.foulsB !== undefined) setVal('fouls-b', data.foulsB);
      if (data.period !== undefined) setVal('period', data.period);

      const timerEl = document.getElementById('timer-display');
      if (timerEl && document.activeElement !== timerEl && data.timer) {
        if (timerEl.value !== data.timer) {
          timerEl.value = data.timer;
        }
      }
      
      if (data.teamNameA) {
        const titleA = document.getElementById('title-team-a');
        if (titleA) titleA.innerText = data.teamNameA.toUpperCase();
      }
      if (data.teamNameB) {
        const titleB = document.getElementById('title-team-b');
        if (titleB) titleB.innerText = data.teamNameB.toUpperCase();
      }
      
      if (data.totalSeconds !== undefined) {
        totalSeconds = data.totalSeconds;
      } else if (data.timer) {
        const parts = data.timer.split(':');
        if (parts.length === 3) {
          totalSeconds = parseInt(parts[0], 10) * 3600 + parseInt(parts[1], 10) * 60 + parseInt(parts[2], 10);
        }
      }
    }

    // Cache da configuração salva no ESP32
    let autoConfigCache = null;
    try {
      const local = localStorage.getItem('esporte7_wizard_setup');
      if (local) autoConfigCache = JSON.parse(local);
    } catch(e) {}

    function refreshAutoConfig() {
      fetch('/api/automation/status')
        .then(r => r.json())
        .then(data => {
          if (data && typeof data === 'object') {
            autoConfigCache = Object.assign({}, autoConfigCache || {}, data);
          }
        })
        .catch(() => {});
    }
    refreshAutoConfig();

    // Atualização automática via rota externa da API (via Proxy ESP32) a cada 1 segundo (SOMENTE no modo automático)
    let isFetchingState = false;
    function pollScoreboardAjax() {
      if (currentPanelMode !== 'automatico') return;
      if (isFetchingState) return;
      isFetchingState = true;

      // Recupera configuração do cache ou localStorage
      let cfg = autoConfigCache;
      if (!cfg) {
        try {
          const local = localStorage.getItem('esporte7_wizard_setup');
          if (local) cfg = JSON.parse(local);
        } catch(e) {}
      }

      // Rota externa configurada do campeonato (padrão 76)
      const campId = (cfg && (cfg.campeonato || cfg.campeonatoId) && (cfg.campeonato !== '10' && cfg.campeonatoId !== '10'))
                     ? String(cfg.campeonato || cfg.campeonatoId) : '76';
      const targetApiUrl = `https://esportes7.com.br/api/championships/${encodeURIComponent(campId)}/matches`;
      const proxyUrl = `/api/proxy?url=${encodeURIComponent(targetApiUrl)}`;

      fetch(proxyUrl)
        .then(response => {
          if (!response.ok) throw new Error('HTTP ' + response.status);
          return response.json();
        })
        .then(matchesList => {
          if (currentPanelMode === 'automatico' && Array.isArray(matchesList) && matchesList.length > 0) {
            const targetMod = cfg && (cfg.modalidade || cfg.sport_id) ? String(cfg.modalidade || cfg.sport_id).trim() : '';
            const targetCamp = cfg && (cfg.campeonato || cfg.campeonatoId) ? String(cfg.campeonato || cfg.campeonatoId).trim() : campId;
            const targetRodada = cfg && (cfg.rodada || cfg.rodadaId) ? String(cfg.rodada || cfg.rodadaId).trim() : '';
            const targetPartida = cfg && (cfg.partida || cfg.partidaId) ? String(cfg.partida || cfg.partidaId).trim() : '';

            // 1. Filtrar pelo campeonato selecionado
            let candidates = matchesList;
            if (targetCamp) {
              const byCamp = candidates.filter(m => String(m.championship_id) === targetCamp);
              if (byCamp.length > 0) candidates = byCamp;
            }

            // 2. Filtrar pela modalidade selecionada (se houver correspondência com category_id, sport_id ou modalidade)
            if (targetMod) {
              const byMod = candidates.filter(m => {
                if (m.sport_id !== undefined && String(m.sport_id) === targetMod) return true;
                if (m.sport && (String(m.sport.id) === targetMod || (m.sport.name && m.sport.name.toLowerCase() === targetMod.toLowerCase()))) return true;
                if (m.category_id !== undefined && String(m.category_id) === targetMod) return true;
                if (m.modalidade && String(m.modalidade).toLowerCase() === targetMod.toLowerCase()) return true;
                return false;
              });
              if (byMod.length > 0) candidates = byMod;
            }

            // 3. Filtrar pela rodada selecionada (se especificada e diferente de 'Todas as Rodadas')
            if (targetRodada && targetRodada !== 'Todas as Rodadas') {
              const byRound = candidates.filter(m => {
                const rNum = m.round_number !== undefined && m.round_number !== null ? String(m.round_number).trim() : '';
                const rName = (m.round_name || '').trim().toLowerCase();
                const gName = (m.group_name || '').trim().toLowerCase();
                const tRod = targetRodada.trim().toLowerCase();

                if (rNum && (tRod === rNum || tRod === `rodada ${rNum}`)) return true;
                if (rName && (rName === tRod || tRod.includes(rName) || rName.includes(tRod))) return true;
                if (gName && (gName === tRod || tRod.includes(gName))) return true;

                const digits = tRod.replace(/\D/g, '');
                if (digits && rNum === digits) return true;
                return false;
              });
              if (byRound.length > 0) candidates = byRound;
            }

            // 4. Filtrar pela partida selecionada
            let match = null;
            if (targetPartida) {
              match = candidates.find(m => String(m.id) === targetPartida);
            }
            if (!match) {
              // Se não encontrou pelo ID específico, busca partida ao vivo ('live' ou 'in_progress') dentro dos candidatos filtrados
              match = candidates.find(m => m.status === 'live' || m.status === 'in_progress');
            }
            if (!match && candidates.length > 0) {
              // Fallback para a primeira partida dos candidatos filtrados
              match = candidates[0];
            }

            if (match) {
              const stateData = {
                scoreA: match.home_score !== undefined ? match.home_score : 0,
                scoreB: match.away_score !== undefined ? match.away_score : 0,
                teamNameA: match.home_team ? match.home_team.name : 'TIME A',
                teamNameB: match.away_team ? match.away_team.name : 'TIME B',
                period: match.round_number || 1
              };

              // Processa cronômetro a partir de match_details (ex: current_timer_value: 555)
              if (match.match_details && match.match_details.current_timer_value !== undefined) {
                const secs = parseInt(match.match_details.current_timer_value, 10);
                const hrs = Math.floor(secs / 3600);
                const mins = Math.floor((secs % 3600) / 60);
                const s = secs % 60;
                stateData.timer = `${String(hrs).padStart(2, '0')}:${String(mins).padStart(2, '0')}:${String(s).padStart(2, '0')}`;
                stateData.totalSeconds = secs;
                stateData.timerRunning = match.match_details.timer_running || false;
              } else if (match.events && Array.isArray(match.events)) {
                const timerEvents = match.events.filter(e => e.event_type === 'timer_control' || e.type === 'timer_control');
                if (timerEvents.length > 0) {
                  const lastTimer = timerEvents[timerEvents.length - 1];
                  const gTime = lastTimer.game_time || lastTimer.minute || '';
                  if (gTime) stateData.timer = gTime;
                }
              }

              // Processa faltas dos times a partir dos eventos
              if (match.events && Array.isArray(match.events)) {
                const homeId = match.home_team_id || (match.home_team ? match.home_team.id : null);
                const awayId = match.away_team_id || (match.away_team ? match.away_team.id : null);
                let fA = 0, fB = 0;
                match.events.forEach(ev => {
                  const evType = ev.type || ev.event_type || '';
                  if (evType.includes('foul') || evType.includes('falta')) {
                    if (ev.team_id === homeId) fA++;
                    else if (ev.team_id === awayId) fB++;
                  }
                });
                stateData.foulsA = fA;
                stateData.foulsB = fB;
              }

              applyScoreboardState(stateData);

              // Atualiza o banner informativo da partida ativa
              const banner = document.getElementById('active-match-banner');
              if (banner) {
                banner.style.display = 'flex';
                const bMod = document.getElementById('banner-mod-name');
                const bCamp = document.getElementById('banner-camp-name');
                const bRound = document.getElementById('banner-round-name');
                const bMatch = document.getElementById('banner-match-name');
                if (bMod) bMod.innerText = targetMod ? `Mod: ${targetMod}` : (match.sport ? match.sport.name : 'Modalidade');
                if (bCamp) bCamp.innerText = `Camp #${targetCamp || '76'}`;
                if (bRound) bRound.innerText = targetRodada || (match.round_number ? `Rodada ${match.round_number}` : 'Rodada 1');
                if (bMatch) bMatch.innerText = `${stateData.teamNameA} vs ${stateData.teamNameB}`;
              }

              // Atualiza sincronização com os LEDs físicos do ESP32
              sendScoreboardAction({
                action: 'sync_external',
                scoreA: stateData.scoreA,
                scoreB: stateData.scoreB,
                foulsA: stateData.foulsA !== undefined ? stateData.foulsA : 0,
                foulsB: stateData.foulsB !== undefined ? stateData.foulsB : 0,
                period: stateData.period,
                totalSeconds: stateData.totalSeconds !== undefined ? stateData.totalSeconds : totalSeconds,
                timerRunning: stateData.timerRunning !== undefined ? stateData.timerRunning : false
              });
            }
          }
        })
        .catch(err => {
          // Fallback para estado interno local se a requisição externa falhar
          fetch('/api/scoreboard/state')
            .then(r => r.json())
            .then(data => {
              if (currentPanelMode === 'automatico') applyScoreboardState(data);
            })
            .catch(() => {});
        })
        .finally(() => {
          isFetchingState = false;
        });
    }

    // Envio de comandos de atualização (via WebSocket ou AJAX POST como contingência)
    function sendScoreboardAction(payload) {
      if (ws && ws.readyState === WebSocket.OPEN) {
        ws.send(JSON.stringify(payload));
      } else {
        fetch('/api/scoreboard/action', {
          method: 'POST',
          headers: { 'Content-Type': 'application/json' },
          body: JSON.stringify(payload)
        })
        .then(r => r.json())
        .then(data => applyScoreboardState(data))
        .catch(e => {});
      }
    }

    function connectWs() {
      if (window.location.protocol === 'https:') {
        console.log('Painel conectado via HTTPS: sincronização automática do placar operando via AJAX seguro a cada 1s.');
        return;
      }
      const host = window.location.hostname || '192.168.4.1';
      try {
        ws = new WebSocket(`ws://${host}:81/`);
      } catch (e) {
        console.warn('WebSocket não pôde ser iniciado em contexto seguro:', e);
        return;
      }

      ws.onopen = () => {
        console.log('WebSocket conectado!');
      };

      ws.onmessage = (event) => {
        try {
          const data = JSON.parse(event.data);
          if (data.type === 'state') {
            applyScoreboardState(data);
          }
        } catch (e) {
          console.error('Erro ao processar JSON do WebSocket:', e);
        }
      };

      ws.onclose = () => {
        setTimeout(connectWs, 5000);
      };
    }

    // Lógica de Contadores (Manual)
    function changeValue(id, amount) {
      const el = document.getElementById(id);
      let val = parseInt(el.value, 10) + amount;
      if (isNaN(val)) val = 0;
      if (val < 0) val = 0;
      const maxVal = (id === 'score-a' || id === 'score-b') ? 999 : 99;
      if (val > maxVal) val = maxVal;
      const padLen = (id === 'score-a' || id === 'score-b') ? 3 : 2;
      el.value = String(val).padStart(padLen, '0');

      sendScoreboardAction({
        action: 'change',
        target: id,
        amount: amount
      });
    }

    function manualInputChanged(id) {
      const el = document.getElementById(id);
      let val = parseInt(el.value, 10);
      if (isNaN(val)) val = 0;
      if (val < 0) val = 0;
      const maxVal = (id === 'score-a' || id === 'score-b') ? 999 : 99;
      if (val > maxVal) val = maxVal;
      const padLen = (id === 'score-a' || id === 'score-b') ? 3 : 2;
      el.value = String(val).padStart(padLen, '0');
      
      sendScoreboardAction({ action: 'set', target: id, value: val });
    }

    function setPanelMode(mode, saveToServer = true) {
      currentPanelMode = mode;
      const isAuto = (mode === 'automatico');
      if (saveToServer) {
        fetch('/api/automation/mode', {
          method: 'POST',
          headers: { 'Content-Type': 'application/json' },
          body: JSON.stringify({ mode: mode })
        }).catch(e => console.warn('Falha ao salvar modo', e));
      }

      // Manter botões no layout (sem display: none) para evitar tremor/salto estrutural na tela
      document.querySelectorAll('.btn-step').forEach(btn => {
        btn.disabled = isAuto;
        btn.style.opacity = isAuto ? '0.35' : '1';
        btn.style.cursor = isAuto ? 'not-allowed' : 'pointer';
        btn.style.pointerEvents = isAuto ? 'none' : 'auto';
      });
      document.querySelectorAll('.timer-actions button').forEach(btn => {
        btn.disabled = isAuto;
        btn.style.opacity = isAuto ? '0.4' : '1';
        btn.style.cursor = isAuto ? 'not-allowed' : 'pointer';
        btn.style.pointerEvents = isAuto ? 'none' : 'auto';
      });
      document.querySelectorAll('input.led-text').forEach(input => {
        if (isAuto) input.setAttribute('readonly', 'true');
        else input.removeAttribute('readonly');
      });

      // Habilitar/Desabilitar timer input separadamente
      const timerEl = document.getElementById('timer-display');
      if (isAuto) timerEl.setAttribute('readonly', 'true');
      else timerEl.removeAttribute('readonly');

      if (isAuto) {
        pollScoreboardAjax();
      }
    }

    // Máscara automática HH:MM:SS
    function timerMask(el) {
      let v = el.value.replace(/[^0-9]/g, '').substring(0, 6);
      let out = '';
      if (v.length > 4) out = v.substring(0,2) + ':' + v.substring(2,4) + ':' + v.substring(4,6);
      else if (v.length > 2) out = v.substring(0,2) + ':' + v.substring(2);
      else out = v;
      el.value = out;
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
      // Normalizar display (ex: 90:00 -> 01:30:00)
      updateTimerDisplay();
      // Sincronizar com ESP32
      sendScoreboardAction({ action: 'timer', command: 'set', value: totalSeconds });
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

    // Controle do Cronômetro
    function startTimer() {
      timerInputChanged();
      sendScoreboardAction({ action: 'timer', command: 'start' });
    }

    function pauseTimer() {
      sendScoreboardAction({ action: 'timer', command: 'pause' });
    }

    function resetTimer() {
      totalSeconds = 0;
      updateTimerDisplay();
      sendScoreboardAction({ action: 'timer', command: 'reset' });
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
          sendScoreboardAction({ action: 'reset_all' });
          document.getElementById('score-a').value = '000';
          document.getElementById('score-b').value = '000';
          document.getElementById('fouls-a').value = '00';
          document.getElementById('fouls-b').value = '00';
          document.getElementById('period').value = '00';
          totalSeconds = 0;
          updateTimerDisplay();
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
    pollScoreboardAjax();
    setInterval(pollScoreboardAjax, 1000);

    // Obter modo salvo no ESP32 sem reenviar POST redundante
    fetch('/api/automation/status')
      .then(r => r.json())
      .then(data => {
        const mode = data.mode || 'automatico';
        const radio = document.querySelector(`input[name="panelMode"][value="${mode}"]`);
        if (radio) radio.checked = true;
        setPanelMode(mode, false);
      })
      .catch(() => setPanelMode('automatico', false));

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
    .btn-forget { background: #c62828; color: #fff; padding: 14px; border: none; border-radius: 8px; font-weight: 700; font-size: 1rem; cursor: pointer; text-transform: uppercase; margin-top: 10px; width: 100%; }
    .btn-forget:hover { background: #b71c1c; }
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
      <button type="button" class="btn-forget" onclick="forgetWifi()">🗑️ Esquecer Rede Wi-Fi</button>
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

    function forgetWifi() {
      if (!confirm('Deseja realmente esquecer a rede Wi-Fi configurada?\nO ESP32 desconectará da rede e reiniciará no modo Ponto de Acesso (Hotspot).')) {
        return;
      }
      showToast('Esquecendo rede Wi-Fi...', 'info');
      fetch('/api/wifi/forget', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' }
      })
      .then(r => r.json())
      .then(data => {
        if (data.status === 'success') {
          showToast('Rede esquecida! O dispositivo reiniciará no modo Ponto de Acesso.', 'success');
          setTimeout(() => {
            const select = document.getElementById('wifiSsid');
            if (select) select.innerHTML = '<option value="">Selecione uma rede...</option>';
            const pass = document.getElementById('wifiPass');
            if (pass) pass.value = '';
          }, 1000);
        } else {
          showToast(data.error || 'Erro ao esquecer rede.', 'error');
        }
      })
      .catch(err => {
        showToast('Rede esquecida! O dispositivo desconectará e reiniciará no modo Ponto de Acesso.', 'success');
        const select = document.getElementById('wifiSsid');
        if (select) select.innerHTML = '<option value="">Selecione uma rede...</option>';
        const pass = document.getElementById('wifiPass');
        if (pass) pass.value = '';
      });
    }

    window.onload = scanNetworks;
  </script>
</body>
</html>
)rawliteral";

#endif
