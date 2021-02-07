#include QMK_KEYBOARD_H

#define _BL  0
#define _FL  1

enum {
    TD_ESC_GRV,
};

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for g
    [TD_ESC_GRV] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_GRV),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Keymap _BL: (Base Layer) Default Layer
     * ,----------------------------------------------------------------.
     * |~ ` | 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |Home|
     * |----------------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \  |Lock|
     * |----------------------------------------------------------------|
     * |CAPS   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return |Home|
     * |----------------------------------------------------------------|
     * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift | Up|End |
     * |----------------------------------------------------------------|
     * |Ctrl|Alt|Code |        Space          |FN |Alt|Ctrl|Lef|Dow|Rig |
     * `----------------------------------------------------------------'
     */
    [_BL] = LAYOUT_65_ansi(
        TD(TD_ESC_GRV),  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, C(G(KC_Q)),
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_HOME,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   KC_END,
        KC_LCTL, KC_LALT, KC_LGUI,                            KC_SPC,                    MO(_FL), KC_RALT, KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    /* Keymap _FL: Function Layer
     * ,----------------------------------------------------------------.
     * |Esc | F1|F2 |F3 |F4 |F5 |F6 |F7 |F8 |F9 |F10|F11|F12|Del    |Ins|
     * |----------------------------------------------------------------|
     * |_WL| Play|V+ |Mut|B- |B+ |   |   |   |   |SCR|   |   |     |    |
     * |----------------------------------------------------------------|
     * |RESET |<M |V- |M> |FUL|   |   |   |   |   |   |   |        |    |
     * |----------------------------------------------------------------|
     * |         |   |   |   |   |   |   |   |   |   |   |     |   |    |
     * |----------------------------------------------------------------|
     * |    |    |    |                        |   |   |   |   |   |    |
     * `----------------------------------------------------------------'
     */
    [_FL] = LAYOUT_65_ansi(
        KC_ESC,    KC_F1,   KC_F2,   KC_F3,      KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,        KC_F10,  KC_F11,  KC_F12,  KC_DEL,  KC_INS,
        _______, KC_MPLY, KC_VOLU, KC_MUTE,    KC_BRID, KC_BRIU, _______, _______, _______, _______, G(C(S(KC_4))), _______, _______, _______, _______,
          RESET, KC_MPRV, KC_VOLD, KC_MNXT, C(G(KC_F)), _______, _______, _______, _______, _______,       _______, _______,          _______, _______,
        _______,          _______, _______,    _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______,
        _______, _______, _______,                               _______,                   _______,       _______, KC_TRNS, KC_TRNS, _______, KC_TRNS
    ),
};


/*
 * Manage layers colors
 */

// Light LEDs when keyboard layer 0 is active
const rgblight_segment_t PROGMEM layer0_color[] = RGBLIGHT_LAYER_SEGMENTS({0, 7, HSV_GREEN});

// Light LEDs when keyboard layer 1 is active
const rgblight_segment_t PROGMEM layer1_color[] = RGBLIGHT_LAYER_SEGMENTS({0, 7, HSV_BLUE});

// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    layer0_color,
    layer1_color
);

// Enable the LED layers
void keyboard_post_init_user(void) {
    rgblight_layers = rgb_layers;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, 0));
    rgblight_set_layer_state(1, layer_state_cmp(state, 1));
    return state;
}
