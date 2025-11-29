#include QMK_KEYBOARD_H

enum layer_names {
    _VALORANT = 0,
    _OBS,
    _RESOLVE,
    _MEDIA
};

enum keycodes {
    KC_CYCLE_LAYERS = SAFE_RANGE,
};

#define LAYER_CYCLE_START 0
#define LAYER_CYCLE_END   3

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case KC_CYCLE_LAYERS:
        if (!record->event.pressed) return false;
        uint8_t current_layer = get_highest_layer(layer_state);
        if (current_layer > LAYER_CYCLE_END || current_layer < LAYER_CYCLE_START) return false;
        uint8_t next_layer = current_layer + 1;
        if (next_layer > LAYER_CYCLE_END) next_layer = LAYER_CYCLE_START;
        layer_move(next_layer);
        return false;
    default:
        return true;
    }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_VALORANT] = LAYOUT_ortho_3x2(
        KC_Q,    KC_E,
        KC_C,    KC_X,
        KC_V,    KC_CYCLE_LAYERS
    ),

    [_OBS] = LAYOUT_ortho_3x2(
        KC_F13,  KC_F14,
        KC_F15,  KC_F16,
        KC_F17,  KC_CYCLE_LAYERS
    ),

    [_RESOLVE] = LAYOUT_ortho_3x2(
        KC_SPC,  KC_T,
        KC_C,    KC_V,
        KC_L,    KC_CYCLE_LAYERS
    ),

    [_MEDIA] = LAYOUT_ortho_3x2(
        KC_MPLY, KC_MNXT,
        KC_MPRV, KC_MUTE,
        KC_VOLU, KC_CYCLE_LAYERS
    )
};

#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_180;
}

bool oled_task_user(void) {
    oled_clear();  

    oled_write_ln_P(PSTR("SlowPad"), false);
    oled_write_P(PSTR("Mode: "), false);

    switch (get_highest_layer(layer_state)) {
        case _VALORANT:
            oled_write_ln_P(PSTR("VALORANT"), false);
            break;
        case _OBS:
            oled_write_ln_P(PSTR("OBS/TWITCH"), false);
            break;
        case _RESOLVE:
            oled_write_ln_P(PSTR("RESOLVE"), false);
            break;
        case _MEDIA:
            oled_write_ln_P(PSTR("MEDIA"), false);
            break;
        default:
            oled_write_ln_P(PSTR("UNKNOWN"), false);
            break;
    }

    return false;
}

#endif
