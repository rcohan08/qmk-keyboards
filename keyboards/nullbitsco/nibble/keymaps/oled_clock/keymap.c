/* Copyright 2021 Jose Luis Adelantado Torres
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#include "big_led.h"

#ifdef OLED_ENABLE
#    include "oled_display.h"
#endif

enum layer_names { _MA, _FN };

enum custom_keycodes {
    KC_CUST = SAFE_RANGE,
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_MA] = LAYOUT_ansi(
        /* Main layer
                ┏━━━━━┳━━━━━┯━━━━━┯━━━━━┯━━━━━┯━━━━━┳━━━━━┯━━━━━┯━━━━━┯━━━━━┯━━━━━┳━━━━━┯━━━━━┯━━━━━┳━━━━━┓ 
                ┃ ESC ┃  1  │  2  │  3  │  4  │  5  │  6  │  7  │  8  │  9  │  0  │  -  │  +  | BSP ┃ HOM ┃
          ┏━━━━━╉━━━━━╉─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────╊━━━━━┫
          ┃MPLAY┃ TAB ┃  Q  │  W  │  E  │  R  │  T  │  Y  │  U  │  I  │  O  │  P  │  [  │  ]  │  \  ┃ END ┃
          ┣━━━━━╉━━━━━╉─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┷─────╊━━━━━┫
          ┃ LED ┃ CAP ┃  A  │  S  │  D  │  F  │  G  │  H  │  J  │  K  │  L  │  ;  ┃  '  │  RETURN   ┃ PUP ┃
          ┣━━━━━╉━━━━━╉─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┷─────┳─────╊━━━━━┫
          ┃  L  ┃SHIFT┃  Z  │  X  │  C  │  V  │  B  │  N  │  M  │  ,  │  .  │  /  │   SHIFT   │ UPA ┃ PDN ┃
          ┣━━E━━╉━━━━━╉─────┼─────┼─────┷─────┷─────┷─────┷─────┷─────┼─────┼─────┼─────┳─────┼─────╊━━━━━┫
          ┃  D  ┃LCTRL┃ GUI │ ALT │               SPACE               │  FN │ ALT │RCTRL│ LFT │ DWN ┃RIGHT┃
          ┗━━━━━┻━━━━━┻━━━━━┷━━━━━┷━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┷━━━━━┷━━━━━┻━━━━━┷━━━━━┷━━━━━┻━━━━━┛
        */
                 KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_HOME,
        KC_MPLY, KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_END,
        _______, KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_PGUP,
        _______, KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   KC_PGDN,
        _______, KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                    MO(_FN), KC_RALT, KC_RCTL, KC_LEFT,          KC_DOWN, KC_RGHT
    ),
    [_FN] = LAYOUT_ansi(
        /* FN layer
                ┏━━━━━┳━━━━━┯━━━━━┯━━━━━┯━━━━━┯━━━━━┳━━━━━┯━━━━━┯━━━━━┯━━━━━┯━━━━━┳━━━━━┯━━━━━┯━━━━━┳━━━━━┓ 
                ┃RESET┃ _F1 │ _F2 │ _F3 │ _F4 │ _F5 │ _F6 │ _F7 │ _F8 │ _F9 │ F10 │ F11 │ F12 |     ┃PRINT┃
          ┏━━━━━╉━━━━━╉─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────╊━━━━━┫
          ┃TOGGL┃     ┃     │     │     │     │     │     │     │     │     │     │     │     │     ┃ NUM ┃
          ┣━━━━━╉━━━━━╉─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┷─────╊━━━━━┫
          ┃     ┃     ┃     │     │     │     │     │     │     │     │     │     │     │           ┃     ┃
          ┣━━━━━╉━━━━━╉─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┷─────┳─────╊━━━━━┫
          ┃     ┃     ┃     │     │     │     │     │     │     │     │     │     │           │     ┃     ┃
          ┣━━━━━╉━━━━━╉─────┼─────┼─────┷─────┷─────┷─────┷─────┷─────┼─────┼─────┼─────┳─────┼─────╊━━━━━┫
          ┃     ┃     ┃     │     │                                   │     │     │     │     │     ┃     ┃
          ┗━━━━━┻━━━━━┻━━━━━┷━━━━━┷━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┷━━━━━┷━━━━━┻━━━━━┷━━━━━┷━━━━━┻━━━━━┛
        */
                 RESET,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,  KC_PSCR,
        RGB_TOG, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  KC_NLCK,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,  _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______, _______, _______, _______,                   _______,                   _______, _______, _______, _______,          _______, _______
    ),
};
// clang-format on

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_0;
}

bool oled_task_user(void) {
    if (timer_elapsed(oled_timer) >= 3000) {
        set_oled_mode(OLED_MODE_IDLE);
    }
    render_frame();
    return false;
}
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Send keystrokes to host keyboard, if connected (see readme)
    process_record_remote_kb(keycode, record);

    switch (keycode) {
        case RGB_TOG:
            if (record->event.pressed) {
#ifdef OLED_ENABLE
                process_record_keymap_oled(keycode);
#endif
            }
            break;
        case KC_CUST:  // custom macro
            if (record->event.pressed) {
            }
            break;
    }
    return true;
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (clockwise) {
        tap_code(KC_VOLU);
#ifdef OLED_ENABLE
        process_record_encoder_oled(KC_VOLU);
#endif
    } else {
        tap_code(KC_VOLD);
#ifdef OLED_ENABLE
        process_record_encoder_oled(KC_VOLD);
#endif
    }
    return true;
}

void matrix_init_user(void) {
    // Initialize remote keyboard, if connected (see readme)
    matrix_init_remote_kb();
}

void matrix_scan_user(void) {
    // Scan and parse keystrokes from remote keyboard, if connected (see readme)
    matrix_scan_remote_kb();
}

#ifdef RGBLIGHT_ENABLE
void keyboard_post_init_user(void) {
  rgblight_enable_noeeprom(); // Enables RGB, without saving settings
  rgblight_sethsv_noeeprom(255, 235, 255);
  rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
}
#endif

// Use Big LED to show status
bool led_update_user(led_t led_state) {
    set_big_LED_r(led_state.caps_lock ? LED_OFF : LED_ON);
    set_big_LED_g(LED_OFF);
    set_big_LED_b(LED_ON);
    return true;
}