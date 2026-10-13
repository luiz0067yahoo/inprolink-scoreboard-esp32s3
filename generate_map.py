import matplotlib.pyplot as plt
import matplotlib.patches as patches
import numpy as np

def generate_v4(filename, dark_theme=True):
    fig_w, fig_h = 760, 1080
    dpi = 120
    fig = plt.figure(figsize=(fig_w / dpi, fig_h / dpi), dpi=dpi)
    ax = fig.add_axes([0, 0, 1, 1])
    ax.set_xlim(0, fig_w)
    ax.set_ylim(0, fig_h)
    ax.axis('off')

    if dark_theme:
        card_bg = '#0f172a'         # Deep sleek slate
        card_border = '#334155'
        panel_bg = '#090d16'        # Dark scoreboard acrylic
        panel_border = '#1e293b'
        
        # Segment colors (LED illuminated red)
        seg_fill = '#e11d48'        # Ruby crimson
        seg_edge = '#fb7185'
        seg_glow = '#be123c'
        
        # WS2812B LEDs
        smd_bg = '#1c0508'
        smd_border = '#4c0d15'
        lens_outer = '#e11d48'
        lens_glow = '#f43f5e'
        lens_core = '#ffffff'
        
        # Badges & Labels
        badge_bg = '#1e293b'
        badge_border = '#38bdf8'
        badge_letter = '#38bdf8'
        badge_sub = '#cbd5e1'
        
        # Header / Footer
        header_title = '#f8fafc'
        header_tag = '#38bdf8'
        tag_bg = '#0c2847'
        tag_border = '#0284c7'
        footer_text = '#94a3b8'
    else:
        card_bg = '#ffffff'
        card_border = '#cbd5e1'
        panel_bg = '#f8fafc'
        panel_border = '#e2e8f0'
        
        seg_fill = '#dc2626'
        seg_edge = '#b91c1c'
        seg_glow = '#fca5a5'
        
        smd_bg = '#7f1d1d'
        smd_border = '#991b1b'
        lens_outer = '#dc2626'
        lens_glow = '#ef4444'
        lens_core = '#ffffff'
        
        badge_bg = '#ffffff'
        badge_border = '#0284c7'
        badge_letter = '#0284c7'
        badge_sub = '#475569'
        
        header_title = '#0f172a'
        header_tag = '#0369a1'
        tag_bg = '#e0f2fe'
        tag_border = '#38bdf8'
        footer_text = '#64748b'

    # Outer Card (with subtle rounded corners)
    cm = 16
    card = patches.FancyBboxPatch(
        (cm, cm), fig_w - 2*cm, fig_h - 2*cm,
        boxstyle="round,pad=0,rounding_size=24",
        facecolor=card_bg, edgecolor=card_border, linewidth=2, zorder=1
    )
    ax.add_patch(card)

    # Header section
    ax.text(fig_w/2, fig_h - 48, "MAPEAMENTO DOS SEGMENTOS",
            ha='center', va='center', fontsize=20, fontweight='bold',
            color=header_title, family='sans-serif', zorder=2)
    
    # Header tag pill
    tw, th = 340, 26
    tag_patch = patches.FancyBboxPatch(
        (fig_w/2 - tw/2, fig_h - 88), tw, th,
        boxstyle="round,pad=0,rounding_size=8",
        facecolor=tag_bg, edgecolor=tag_border, linewidth=1.2, zorder=2
    )
    ax.add_patch(tag_patch)
    ax.text(fig_w/2, fig_h - 75, "WS2812B • 35 LEDs (5 LEDs POR SEGMENTO)",
            ha='center', va='center', fontsize=10.5, fontweight='bold',
            color=header_tag, family='sans-serif', zorder=3)

    # Inner acrylic panel
    px, py = 38, 76
    pw, ph = fig_w - 76, fig_h - 176
    panel = patches.FancyBboxPatch(
        (px, py), pw, ph,
        boxstyle="round,pad=0,rounding_size=18",
        facecolor=panel_bg, edgecolor=panel_border, linewidth=1.5, zorder=2
    )
    ax.add_patch(panel)

    # 7-Segment Dimensions
    cx = fig_w / 2        # 380
    cy = py + ph / 2      # 526
    
    dw = 400              # digit width
    dh = 720              # digit height
    T = 76                # thickness
    g = 7.5               # gap
    
    XL = cx - dw / 2      # 180
    XR = cx + dw / 2      # 580
    YB = cy - dh / 2      # 166
    YT = cy + dh / 2      # 886
    YM = cy               # 526

    # Geometric Polygons
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
            'lbl_pos': (cx, YT + 44),
            'badge_style': 'horizontal'
        },
        'a': {
            'poly': poly_a,
            'range': '0 — 4',
            'led_coords': [(XL + T/2, y) for y in np.linspace(YT - T*1.15, YM + T*0.8, 5)],
            'lbl_pos': (XL - 72, (YT + YM) / 2),
            'badge_style': 'vertical'
        },
        'c': {
            'poly': poly_c,
            'range': '10 — 14',
            'led_coords': [(XR - T/2, y) for y in np.linspace(YT - T*1.15, YM + T*0.8, 5)],
            'lbl_pos': (XR + 72, (YT + YM) / 2),
            'badge_style': 'vertical'
        },
        'd': {
            'poly': poly_d,
            'range': '15 — 19',
            'led_coords': [(x, YM) for x in np.linspace(XL + T*1.35, XR - T*1.35, 5)],
            'lbl_pos': (cx, YM + 62),
            'badge_style': 'center'
        },
        'e': {
            'poly': poly_e,
            'range': '20 — 24',
            'led_coords': [(XL + T/2, y) for y in np.linspace(YM - T*0.8, YB + T*1.15, 5)],
            'lbl_pos': (XL - 72, (YM + YB) / 2),
            'badge_style': 'vertical'
        },
        'g': {
            'poly': poly_g,
            'range': '30 — 34',
            'led_coords': [(XR - T/2, y) for y in np.linspace(YM - T*0.8, YB + T*1.15, 5)],
            'lbl_pos': (XR + 72, (YM + YB) / 2),
            'badge_style': 'vertical'
        },
        'f': {
            'poly': poly_f,
            'range': '25 — 29',
            'led_coords': [(x, YB + T/2) for x in np.linspace(XL + T*1.35, XR - T*1.35, 5)],
            'lbl_pos': (cx, YB - 44),
            'badge_style': 'horizontal'
        }
    }

    # Draw Segments
    for seg_key, sdata in segments.items():
        p = sdata['poly']
        
        if dark_theme:
            # Soft radial-like glow under segment
            ax.add_patch(patches.Polygon(p, closed=True, facecolor=seg_glow, edgecolor='none', alpha=0.35, zorder=3))
        
        # Segment body
        ax.add_patch(patches.Polygon(
            p, closed=True,
            facecolor=seg_fill, edgecolor=seg_edge,
            linewidth=2.2, zorder=4
        ))

        # Render 5 LEDs per segment
        for lx, ly in sdata['led_coords']:
            # Square SMD package
            smd_size = 24
            ax.add_patch(patches.Rectangle(
                (lx - smd_size/2, ly - smd_size/2), smd_size, smd_size,
                facecolor=smd_bg, edgecolor=smd_border, linewidth=1.2, zorder=5
            ))
            # Outer LED lens ring
            ax.add_patch(patches.Circle((lx, ly), 9.5, facecolor=lens_outer, edgecolor='none', zorder=6))
            # Glowing emitter ring
            ax.add_patch(patches.Circle((lx, ly), 6.5, facecolor=lens_glow, edgecolor='none', zorder=7))
            # Bright core
            ax.add_patch(patches.Circle((lx, ly), 3.5, facecolor=lens_core, edgecolor='none', zorder=8))

    # Render Badges
    for seg_key, sdata in segments.items():
        lx, ly = sdata['lbl_pos']
        
        bw, bh = 96, 52
        badge = patches.FancyBboxPatch(
            (lx - bw/2, ly - bh/2), bw, bh,
            boxstyle="round,pad=0,rounding_size=12",
            facecolor=badge_bg, edgecolor=badge_border, linewidth=2, zorder=10
        )
        ax.add_patch(badge)

        # Bold segment letter
        ax.text(lx, ly + 9, f"seg {seg_key}",
                ha='center', va='center', fontsize=18, fontweight='bold',
                color=badge_letter, zorder=11, family='sans-serif')
        
        # LED range
        ax.text(lx, ly - 13, f"LEDs {sdata['range']}",
                ha='center', va='center', fontsize=9.5, fontweight='bold',
                color=badge_sub, zorder=11, family='sans-serif')

    # Footer note with full wiring order
    footer_str = "Ordem física de dados WS2812B (35 LEDs em série):\nSeg a (0-4) → Seg b (5-9) → Seg c (10-14) → Seg d (15-19) → Seg e (20-24) → Seg f (25-29) → Seg g (30-34)"
    ax.text(fig_w/2, 46, footer_str,
            ha='center', va='center', fontsize=8.8, fontweight='500',
            color=footer_text, family='sans-serif', linespacing=1.35, zorder=2)

    plt.savefig(filename, dpi=dpi, transparent=True)
    plt.close()
    print(f"Generated {filename}")

if __name__ == '__main__':
    generate_v4('segment_map_v4_dark.png', dark_theme=True)
    generate_v4('segment_map_v4_light.png', dark_theme=False)
