import matplotlib.pyplot as plt
import matplotlib.patches as patches
import numpy as np

def generate_clean_diagram(filename, dark_theme=True):
    # 720 x 1000 canvas
    fig_w, fig_h = 720, 1000
    dpi = 130
    fig = plt.figure(figsize=(fig_w / dpi, fig_h / dpi), dpi=dpi)
    ax = fig.add_axes([0, 0, 1, 1])
    ax.set_xlim(0, fig_w)
    ax.set_ylim(0, fig_h)
    ax.axis('off')

    if dark_theme:
        card_bg = '#090d16'         # Dark matte scoreboard acrylic
        card_border = '#1e293b'     # Subtle slate frame
        inner_bg = '#06080f'
        inner_border = '#141c2e'
        
        # Segment colors
        seg_fill = '#ef233c'        # Vivid digital scoreboard red
        seg_edge = '#ff4d6d'        # Crisp edge highlight
        seg_glow = '#d90429'
        
        # LEDs
        smd_bg = '#1f0407'
        smd_border = '#4c0d16'
        lens_glow = '#ff758f'
        lens_core = '#ffffff'
        
        # Badges
        badge_bg = '#0f172a'
        badge_border = '#38bdf8'
        letter_color = '#38bdf8'
        sub_color = '#cbd5e1'
    else:
        card_bg = '#ffffff'
        card_border = '#cbd5e1'
        inner_bg = '#f8fafc'
        inner_border = '#e2e8f0'
        
        seg_fill = '#dc2626'
        seg_edge = '#b91c1c'
        seg_glow = '#fca5a5'
        
        smd_bg = '#7f1d1d'
        smd_border = '#991b1b'
        lens_glow = '#ef4444'
        lens_core = '#ffffff'
        
        badge_bg = '#ffffff'
        badge_border = '#0284c7'
        letter_color = '#0284c7'
        sub_color = '#334155'

    # Outer Card (Transparent margin around card)
    m = 12
    card = patches.FancyBboxPatch(
        (m, m), fig_w - 2*m, fig_h - 2*m,
        boxstyle="round,pad=0,rounding_size=24",
        facecolor=card_bg, edgecolor=card_border, linewidth=2, zorder=1
    )
    ax.add_patch(card)

    # Inner display recess
    im = 30
    inner_panel = patches.FancyBboxPatch(
        (im, im), fig_w - 2*im, fig_h - 2*im,
        boxstyle="round,pad=0,rounding_size=18",
        facecolor=inner_bg, edgecolor=inner_border, linewidth=1.5, zorder=2
    )
    ax.add_patch(inner_panel)

    # 7-Segment Dimensions - Centered and Large
    cx = fig_w / 2        # 360
    cy = fig_h / 2        # 500
    
    dw = 400              # digit width
    dh = 780              # digit height
    T = 78                # segment thickness
    g = 7.5               # gap between segments
    
    XL = cx - dw / 2      # 160
    XR = cx + dw / 2      # 560
    YB = cy - dh / 2      # 110
    YT = cy + dh / 2      # 890
    YM = cy               # 500

    # Polygons with exact 45-degree chamfers
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
            'range': '5 — 9',
            'led_coords': [(x, YT - T/2) for x in np.linspace(XL + T*1.35, XR - T*1.35, 5)],
            'lbl_pos': (cx, YT + 48),
        },
        'a': {
            'poly': poly_a,
            'range': '0 — 4',
            'led_coords': [(XL + T/2, y) for y in np.linspace(YT - T*1.15, YM + T*0.8, 5)],
            'lbl_pos': (XL - 68, (YT + YM) / 2),
        },
        'c': {
            'poly': poly_c,
            'range': '10 — 14',
            'led_coords': [(XR - T/2, y) for y in np.linspace(YT - T*1.15, YM + T*0.8, 5)],
            'lbl_pos': (XR + 68, (YT + YM) / 2),
        },
        'd': {
            'poly': poly_d,
            'range': '15 — 19',
            'led_coords': [(x, YM) for x in np.linspace(XL + T*1.35, XR - T*1.35, 5)],
            'lbl_pos': (cx, YM + 80),
        },
        'e': {
            'poly': poly_e,
            'range': '20 — 24',
            'led_coords': [(XL + T/2, y) for y in np.linspace(YM - T*0.8, YB + T*1.15, 5)],
            'lbl_pos': (XL - 68, (YM + YB) / 2),
        },
        'g': {
            'poly': poly_g,
            'range': '30 — 34',
            'led_coords': [(XR - T/2, y) for y in np.linspace(YM - T*0.8, YB + T*1.15, 5)],
            'lbl_pos': (XR + 68, (YM + YB) / 2),
        },
        'f': {
            'poly': poly_f,
            'range': '25 — 29',
            'led_coords': [(x, YB + T/2) for x in np.linspace(XL + T*1.35, XR - T*1.35, 5)],
            'lbl_pos': (cx, YB - 48),
        }
    }

    # Render segments
    for seg_key, sdata in segments.items():
        p = sdata['poly']
        
        if dark_theme:
            # Radial-like glow halo
            ax.add_patch(patches.Polygon(p, closed=True, facecolor=seg_glow, edgecolor='none', alpha=0.35, zorder=3))
        
        # Segment body
        ax.add_patch(patches.Polygon(
            p, closed=True,
            facecolor=seg_fill, edgecolor=seg_edge,
            linewidth=2.2, zorder=4
        ))

        # 5 LEDs
        for lx, ly in sdata['led_coords']:
            # Square WS2812B SMD package
            smd_w = 24
            ax.add_patch(patches.Rectangle(
                (lx - smd_w/2, ly - smd_w/2), smd_w, smd_w,
                facecolor=smd_bg, edgecolor=smd_border, linewidth=1.2, zorder=5
            ))
            # Glowing lens outer ring
            ax.add_patch(patches.Circle((lx, ly), 10, facecolor=lens_glow, edgecolor='none', zorder=6))
            # Intense white core
            ax.add_patch(patches.Circle((lx, ly), 5, facecolor=lens_core, edgecolor='none', zorder=7))

    # Render Segment Badges
    for seg_key, sdata in segments.items():
        lx, ly = sdata['lbl_pos']
        
        bw, bh = 104, 58
        badge = patches.FancyBboxPatch(
            (lx - bw/2, ly - bh/2), bw, bh,
            boxstyle="round,pad=0,rounding_size=14",
            facecolor=badge_bg, edgecolor=badge_border, linewidth=2, zorder=10
        )
        ax.add_patch(badge)

        # Prominent Segment Letter
        ax.text(lx, ly + 10, seg_key,
                ha='center', va='center', fontsize=26, fontweight='bold',
                color=letter_color, zorder=11, family='sans-serif')
        
        # Subtitle with LED range
        ax.text(lx, ly - 14, f"LEDs {sdata['range']}",
                ha='center', va='center', fontsize=10, fontweight='bold',
                color=sub_color, zorder=11, family='sans-serif')

    # For segment d: add a small pointer from the badge down to the middle bar
    d_x, d_y = segments['d']['lbl_pos']
    pointer = patches.Polygon([
        (d_x - 7, d_y - 29),
        (d_x + 7, d_y - 29),
        (d_x, d_y - 41)
    ], closed=True, facecolor=badge_border, edgecolor='none', zorder=10)
    ax.add_patch(pointer)

    plt.savefig(filename, dpi=dpi, transparent=True)
    plt.close()
    print(f"Generated {filename}")

if __name__ == '__main__':
    generate_clean_diagram('segment_map_clean_dark.png', dark_theme=True)
    generate_clean_diagram('segment_map_clean_light.png', dark_theme=False)
