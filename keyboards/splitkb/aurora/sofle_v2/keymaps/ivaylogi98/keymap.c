#include QMK_KEYBOARD_H

// Add custom gaming layer toggle
enum custom_keycodes  {
  GAMING_ON = SAFE_RANGE,
  GAMING_OFF,
  ENCODER_MODE
};

int right_encoder_mode = 0;

// The first four layers gets a name for readability, which is then used in the OLED below.
enum layers {
  _DEFAULT,
  _LOWER,
  _RAISE,
  _ADJUST,
  _GAMING,
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT(KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_DEL, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC, KC_ESC, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_MUTE, ENCODER_MODE, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_LCTL, KC_LALT, KC_LGUI, MO(1), KC_SPC, KC_ENT, MO(2), KC_RGUI, KC_RALT, KC_RCTL),
	[1] = LAYOUT(_______, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_F12, _______, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PIPE, _______, KC_EQL, KC_MINS, KC_PLUS, KC_LCBR, KC_RCBR, _______, _______, KC_LBRC, KC_RBRC, KC_SCLN, KC_COLN, KC_BSLS, _______, _______, _______, _______, _______, _______, _______, MO(3), _______, _______, _______),
	[2] = LAYOUT(_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_INS, KC_PSCR, KC_APP, XXXXXXX, XXXXXXX, KC_PGUP, C(KC_LEFT), KC_UP, C(KC_RGHT), C(KC_BSPC), KC_BSPC, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_CAPS, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_DEL, KC_BSPC, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, XXXXXXX, KC_HOME, XXXXXXX, KC_END, XXXXXXX, _______, _______, _______, _______, MO(3), _______, _______, _______, _______, _______, _______),
	[3] = LAYOUT(XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, GAMING_ON, ENCODER_MODE, KC_VOLD, KC_MUTE, KC_VOLU, XXXXXXX, XXXXXXX, XXXXXXX, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, AG_TOGG, XXXXXXX, XXXXXXX, XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, XXXXXXX, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______),
	[4] = LAYOUT(KC_5, KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_6, KC_7, KC_8, KC_9, KC_0, KC_DEL, KC_T, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC, KC_G, KC_LSFT, KC_A, KC_S, KC_D, KC_F, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_B, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_MUTE, XXXXXXX, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, GAMING_OFF, KC_LCTL, KC_LALT, KC_LGUI, KC_SPC, KC_T, KC_ENT, MO(2), KC_RGUI, KC_RALT, KC_RCTL)
};

#if defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {

};
#endif // defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)


#ifdef ENCODER_ENABLE
bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) {
        return false;
    }
    // 0 is left-half encoder,
    // 1 is right-half encoder
    if (index == 0) {
        // Volume control
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) {
        if(right_encoder_mode % 3 == 0){
            if (clockwise) {
                tap_code(KC_DOWN);
            } else {
                tap_code(KC_UP);
            }
        }
        else if(right_encoder_mode % 3 == 1){
            if (clockwise) {
                tap_code(KC_PGDN);
            } else {
                tap_code(KC_PGUP);
            }
        }
        else if(right_encoder_mode % 3 == 2){
            if (clockwise) {
                tap_code16(C(KC_TAB));
            } else {
                tap_code16(S(C(KC_TAB)));
            }
        }
    } 
    return true;
}
#endif


void keyboard_pre_init_user(void) {
  // Set our LED pin as output
  setPinOutput(24);
  // Turn the LED off
  // (Due to technical reasons, high is off and low is on)
  writePinHigh(24);
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case GAMING_ON:
            if (record->event.pressed) {
                #ifdef AUDIO_ENABLE
                    PLAY_NOTE_ARRAY(tone_plover, false, 0);
                #endif        
                layer_off(_RAISE);
                layer_off(_LOWER);
                layer_off(_ADJUST);
                layer_on(_GAMING);
            }
            return false; // Skip all further processing of this key
        case GAMING_OFF:
            if (record->event.pressed) {
                #ifdef AUDIO_ENABLE
                    PLAY_NOTE_ARRAY(tone_plover_gb, false, 0);
                #endif
                layer_off(_GAMING);
            }
            return false; // Skip all further processing of this key
            break;
        case ENCODER_MODE:
            if (record->event.pressed) {
                #ifdef AUDIO_ENABLE
                    PLAY_NOTE_ARRAY(tone_plover_gb, false, 0);
                #endif
                right_encoder_mode += 1;
            }
            return false; // Skip all further processing of this key
            break;
    }
    return true;
}

