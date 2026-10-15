# Sync panel_config_html
with open('demo/panel_config.html.html', 'r', encoding='utf-8') as f:
    config_content = f.read()

with open('demo/panel_config.html', 'w', encoding='utf-8') as f:
    f.write(config_content)

# Sync painel_html
with open('demo/painel.html', 'r', encoding='utf-8') as f:
    painel_content = f.read()

with open('WebPages.h', 'r', encoding='utf-8') as f:
    h = f.read()

# 1. Update panel_config_html
cfg_start = 'const char panel_config_html[] PROGMEM = R"rawliteral('
cfg_end = ')rawliteral";'
c_s = h.find(cfg_start)
c_e = h.find(cfg_end, c_s + len(cfg_start))
if c_s != -1 and c_e != -1:
    h = h[:c_s + len(cfg_start)] + "\n" + config_content + "\n" + h[c_e:]

# 2. Update painel_html
painel_start = 'const char painel_html[] PROGMEM = R"rawliteral('
painel_end = ')rawliteral";'
p_s = h.find(painel_start)
p_e = h.find(painel_end, p_s + len(painel_start))
if p_s != -1 and p_e != -1:
    h = h[:p_s + len(painel_start)] + "\n" + painel_content + "\n" + h[p_e:]

with open('WebPages.h', 'w', encoding='utf-8') as f:
    f.write(h)

print("Synchronized all web pages to WebPages.h successfully!")
