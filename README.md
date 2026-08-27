# 🏀 Inprolink System — Placar Eletrônico ESP32-S3

![ESP32-S3](https://img.shields.io/badge/Hardware-ESP32--S3-blue?style=flat-square&logo=espressif)
![C++](https://img.shields.io/badge/Language-C%2B%2B-00599C?style=flat-square&logo=c%2B%2B)
![PlatformIO](https://img.shields.io/badge/Toolchain-PlatformIO-orange?style=flat-square&logo=platformio)
![License](https://img.shields.io/badge/License-MIT-green?style=flat-square)

Sistema embarcado para gerenciamento e controle de placar eletrônico esportivo composto por **20 dígitos independentes** de 7 segmentos em fita de LED **WS2812B** (700 LEDs no total). 

O projeto combina uma interface web responsiva embarcada, resolução de nomes em rede local, persistência de dados em memória Flash (NVS) e atualização automática de placares através do consumo dinâmico de APIs JSON.

---

### 🌟 Destaques do Projeto

* **Controle Independente de 16 Dígitos:** Mapeamento dedicado de 16 saídas GPIO do ESP32-S3 para renderização de pontos, faltas, período e cronômetro.
* **Acesso Simplificado:** Navegação direta por endereço IP (`192.168.4.1`) ou hostname mDNS (`http://inprolink_system`).
* **Autenticação Embarcada:** Sistema de login com credenciais mestre e suporte a até 10 usuários adicionais na memória NVS.
* **Consumo de API JSON:** Fluxo encadeado em 5 etapas para seleção automática da partida (Site → Modalidade → Campeonato → Partida → Rodada).
* **Reset de Fábrica Físico:** Restauração das configurações de fábrica mantendo a GPIO 0 pressionada por 5 segundos.
