import matplotlib.pyplot as plt
import matplotlib.patches as patches
import numpy as np

def generate_perfect_diagram(filename, theme='dark'):
    fig_w, fig_h = 760, 1040
    dpi = 130
    fig = plt.figure(figsize=(fig_w / dpi, fig_h / dpi), dpi=dpi)
    ax = fig.add_axes([0, 0, 1, 1])
    ax.set_xlim(0, fig_w)
    ax.set_ylim(0, fig_h)
    ax.axis('off')

    if theme == 'dark':
        # Dark scoreboard stadium aesthetic
        bg_canvas = '#07090e'
        card_bg = '#0f1422'
        card_border = '#1e293b'
        panel_bg = '#080c16'
        panel_border = '#1a2336'
        
        # 7-Segment illuminated red
        seg_fill = '#ef233c'
        seg_edge = '#ff4d6d'
        seg_glow = '#d90429'
        
        # WS2812B LED pixels
        smd_body = '#180406'
        smd_edge = '#400c12'
        lens_ring = '#ff2a51'
        lens_core = '#ffffff'
        
        # Badges
        badge_bg = '#141d30'
        badge_border = '#0284c7'
        badge_accent = '#38bdf8'
        letter_color = '#38bdf8'
        sub_color = '#cbd5e1'
    else:
        # Clean technical schematic aesthetic
        bg_canvas = '#f8fafc'
        card_bg = '#ffffff'
        card_border = '#cbd5e1'
        panel_bg = '#f1f5f9'
        panel_border = '#e2e8f0'
        
        seg_fill = '#dc2626'
        seg_edge = '#b91c1c'
        seg_glow = '#fca5a5'
        
        smd_body = '#7f1d1d'
        smd_edge = '#991b1b'
        lens_ring = '#ef4444'
        lens_core = '#ffffff'
        
        badge_bg = '#ffffff'
        badge_border = '#0284c7'
        badge_accent = '#0284c7'
        letter_color = '#0284c7'
        sub_color = '#334155'

    # Transparent canvas, rounded outer card
    m = 12
    card = patches.FancyBboxPatch(
        (m, m), fig_w - 2*m, fig_h - 2*m,
        boxstyle="round,pad=0,rounding_size=24",
        facecolor=card_bg, edgecolor=card_border, linewidth=2.2, zorder=1
    )
    ax.add_patch(card)

    # Recessed display bezel
    im = 28
    panel = patches.FancyBboxPatch(
        (im, im), fig_w - 2*im, fig_h - 2*im,
        boxstyle="round,pad=0,rounding_size=18",
        facecolor=panel_bg, edgecolor=panel_border, linewidth=1.5, zorder=2
    )
    ax.add_patch(panel)

    # 7-Segment Dimensions
    cx = fig_w / 2        # 380
    cy = fig_h / 2        # 520
    
    dw = 400              # digit width
    dh = 780              # digit height
    T = 78                # segment thickness
    g = 7.5               # gap between segments
    
    XL = cx - dw / 2      # 180
    XR = cx + dw / 2      # 580
    YB = cy - dh / 2      # 130
    YT = cy + dh / 2      # 910
    YM = cy               # 520

    # Chamfered Polygons
    poly_b = np.array([
        [XL + g + T*0.35, YT],
        [XR - g - T*0.35, YT],
        [XR - T - g, YT - T],
        [XL + T + g, YT - T]
    ])

    poly_f = np.array([
        [XL + T + g, YB + T],
        [XR - T - g, YB + T],
        [XR - g - T*0.35, YB],
        [XL + g + T*0.35, YB]
    ])

    poly_d = np.array([
        [XL + g + T*0.5, YM],
        [XL + T + g, YM + T/2],
        [XR - T - g, YM + T/2],
        [XR - g - T*0.5, YM],
        [XR - T - g, YM - T/2],
        [XL + T + g, YM - T/2]
    ])

    poly_a = np.array([
        [XL, YT - g - T*0.35],
        [XL + T, YT - T - g],
        [XL + T, YM + T/2 + g],
        [XL, YM + g]
    ])

    poly_c = np.array([
        [XR - T, YT - T - g],
        [XR, YT - g - T*0.35],
        [XR, YM + g],
        [XR - T, YM + T/2 + g]
    ])

    poly_e = np.array([
        [XL, YM - g],
        [XL + T, YM - T/2 - g],
        [XL + T, YB + T + g],
        [XL, YB + g + T*0.35]
    ])

    poly_g = np.array([
        [XR - T, YM - T/2 - g],
        [XR, YM - g],
        [XR, YB + g + T*0.35],
        [XR - T, YB + T + g]
    ])

    segments = {
        'b': {
            'poly': poly_b,
            'range': 'LEDs 5-9',
            'led_coords': [(x, YT - T/2) for x in np.linspace(XL + T*1.35, XR - T*1.35, 5)],
            'lbl_pos': (cx, YT + 52),
        },
        'a': {
            'poly': poly_a,
            'range': 'LEDs 0-4',
            'led_coords': [(XL + T/2, y) for y in np.linspace(YT - T*1.15, YM + T*0.8, 5)],
            'lbl_pos': (XL - 86, (YT + YM) / 2),
        },
        'c': {
            'poly': poly_c,
            'range': 'LEDs 10-14',
            'led_coords': [(XR - T/2, y) for y in np.linspace(YT - T*1.15, YM + T*0.8, 5)],
            'lbl_pos': (XR + 86, (YT + YM) / 2),
        },
        'd': {
            'poly': poly_d,
            'range': 'LEDs 15-19',
            'led_coords': [(x, YM) for x in np.linspace(XL + T*1.35, XR - T*1.35, 5)],
            'lbl_pos': (cx, YM + 88),
        },
        'e': {
            'poly': poly_e,
            'range': 'LEDs 20-24',
            'led_coords': [(XL + T/2, y) for y in np.linspace(YM - T*0.8, YB + T*1.15, 5)],
            'lbl_pos': (XL - 86, (YM + YB) / 2),
        },
        'g': {
            'poly': poly_g,
            'range': 'LEDs 30-34',
            'led_coords': [(XR - T/2, y) for y in np.linspace(YM - T*0.8, YB + T*1.15, 5)],
            'lbl_pos': (XR + 86, (YM + YB) / 2),
        },
        'f': {
            'poly': poly_f,
            'range': 'LEDs 25-29',
            'led_coords': [(x, YB + T/2) for x in np.linspace(XL + T*1.35, XR - T*1.35, 5)],
            'lbl_pos': (cx, YB - 52),
        }
    }

    # Render segments
    for seg_key, sdata in segments.items():
        p = sdata['poly']
        
        if theme == 'dark':
            # Soft radial glow behind segment
            ax.add_patch(patches.Polygon(p, closed=True, facecolor=seg_glow, edgecolor='none', alpha=0.35, zorder=3))
        
        # Segment body
        ax.add_patch(patches.Polygon(
            p, closed=True,
            facecolor=seg_fill, edgecolor=seg_edge,
            linewidth=2.2, zorder=4
        ))

        # 5 LEDs per segment
        for lx, ly in sdata['led_coords']:
            smd_size = 24
            # SMD package
            ax.add_patch(patches.Rectangle(
                (lx - smd_size/2, ly - smd_size/2), smd_size, smd_size,
                facecolor=smd_body, edgecolor=smd_edge, linewidth=1.2, zorder=5
            ))
            # Lens ring
            ax.add_patch(patches.Circle((lx, ly), 10, facecolor=lens_ring, edgecolor='none', zorder=6))
            # Hot white core
            ax.add_patch(patches.Circle((lx, ly), 5, facecolor=lens_core, edgecolor='none', zorder=7))

    # Render badges with plenty of width for text
    bw = 126
    bh = 60
    for seg_key, sdata in segments.items():
        lx, ly = sdata['lbl_pos']
        
        badge = patches.FancyBboxPatch(
            (lx - bw/2, ly - bh/2), bw, bh,
            boxstyle="round,pad=0,rounding_size=14",
            facecolor=badge_bg, edgecolor=badge_border, linewidth=2.2, zorder=10
        )
        ax.add_patch(badge)

        # Bold segment letter
        ax.text(lx, ly + 11, seg_key,
                ha='center', va='center', fontsize=26, fontweight='bold',
                color=letter_color, zorder=11, family='sans-serif')
        
        # Subtitle with LED range
        ax.text(lx, ly - 14, sdata['range'],
                ha='center', va='center', fontsize=11, fontweight='bold',
                color=sub_color, zorder=11, family='sans-serif')

    # Pointer arrow for segment d
    d_x, d_y = segments['d']['lbl_pos']
    pointer = patches.Polygon([
        (d_x - 8, d_y - bh/2),
        (d_x + 8, d_y - bh/2),
        (d_x, d_y - bh/2 - 13)
    ], closed=True, facecolor=badge_accent, edgecolor='none', zorder=10)
    ax.add_patch(pointer)

    plt.savefig(filename, dpi=dpi, transparent=True)
    plt.close()
    print(f"Generated {filename}")

if __name__ == '__main__':
    generate_perfect_diagram('segment_map_dark_final.png', theme='dark')
    generate_perfect_diagram('segment_map_light_final.png', theme='light')
