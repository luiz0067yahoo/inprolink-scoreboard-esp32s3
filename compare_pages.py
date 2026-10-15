import difflib

with open('demo/panel_config.html.html', 'r', encoding='utf-8') as f:
    demo_content = f.read().strip()

with open('WebPages.h', 'r', encoding='utf-8') as f:
    h_content = f.read()

start_marker = 'const char panel_config_html[] PROGMEM = R"rawliteral('
end_marker = ')rawliteral";'

start_idx = h_content.find(start_marker)
if start_idx != -1:
    content_start = start_idx + len(start_marker)
    end_idx = h_content.find(end_marker, content_start)
    extracted = h_content[content_start:end_idx].strip()
    print('Lengths: extracted=', len(extracted), 'demo=', len(demo_content))
    print('Identical:', extracted == demo_content)
    if extracted != demo_content:
        for line in difflib.unified_diff(extracted.splitlines()[:30], demo_content.splitlines()[:30]):
            print(line)
else:
    print('Marker not found')
