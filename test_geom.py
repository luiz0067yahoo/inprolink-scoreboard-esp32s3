import numpy as np

def get_segment_polygons(cx, cy, dw, dh, T, g):
    hw = dw / 2
    hh = dh / 2
    XL = cx - hw
    XR = cx + hw
    YB = cy - hh
    YT = cy + hh
    YM = cy

    # Segment b (Top)
    poly_b = np.array([
        [XL + g + T*0.3, YT],
        [XR - g - T*0.3, YT],
        [XR - T - g, YT - T],
        [XL + T + g, YT - T]
    ])

    # Segment f (Bottom)
    poly_f = np.array([
        [XL + T + g, YB + T],
        [XR - T - g, YB + T],
        [XR - g - T*0.3, YB],
        [XL + g + T*0.3, YB]
    ])

    # Segment d (Middle)
    poly_d = np.array([
        [XL + g + T*0.5, YM],
        [XL + T + g, YM + T/2],
        [XR - T - g, YM + T/2],
        [XR - g - T*0.5, YM],
        [XR - T - g, YM - T/2],
        [XL + T + g, YM - T/2]
    ])

    # Segment a (Top-Left)
    poly_a = np.array([
        [XL, YT - g - T*0.3],
        [XL + T, YT - T - g],
        [XL + T, YM + T/2 + g],
        [XL, YM + g]
    ])

    # Segment c (Top-Right)
    poly_c = np.array([
        [XR - T, YT - T - g],
        [XR, YT - g - T*0.3],
        [XR, YM + g],
        [XR - T, YM + T/2 + g]
    ])

    # Segment e (Bottom-Left)
    poly_e = np.array([
        [XL, YM - g],
        [XL + T, YM - T/2 - g],
        [XL + T, YB + T + g],
        [XL, YB + g + T*0.3]
    ])

    # Segment g (Bottom-Right)
    poly_g = np.array([
        [XR - T, YM - T/2 - g],
        [XR, YM - g],
        [XR, YB + g + T*0.3],
        [XR - T, YB + T + g]
    ])

    return {
        'b': poly_b,
        'f': poly_f,
        'd': poly_d,
        'a': poly_a,
        'c': poly_c,
        'e': poly_e,
        'g': poly_g
    }

print("Geometry logic loaded successfully")
