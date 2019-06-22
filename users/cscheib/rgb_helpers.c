#include QMK_KEYBOARD_H

#define _BASE   0
#define _LAYER1 1
#define _LAYER2 2
#define _LAYER3 3

#ifdef RGB_MATRIX_ENABLE

bool is_keycode_kcno(keypos_t keypos) {
    if(keymap_key_to_keycode(layer_switch_get_layer(keypos), keypos) == KC_NO) {
        return true;
    }
    return false;
}

void rgb_matrix_layer_render_key(uint8_t led_index, uint8_t switch_layer) {
    switch (switch_layer) {
        case _BASE:
        rgb_matrix_set_color(led_index, 0xFF, 0x00, 0x00); break; //TODO: attempt to use the color constants here
        case _LAYER1:
        rgb_matrix_set_color(led_index, 0x00, 0xFF, 0x00); break; //TODO: attempt to use the color constants here
        case _LAYER2:
        rgb_matrix_set_color(led_index, 0x00, 0x00, 0xFF); break; //TODO: attempt to use the color constants here
        case _LAYER3:
        rgb_matrix_set_color(led_index, 0xFF, 0xFF, 0x00); break; //TODO: attempt to use the color constants here
    }
}

void rgb_matrix_switch_layer_helper (void) {

    for(uint8_t row = 0;  row < MATRIX_ROWS; row++) {
        for(uint8_t column = 0;  column < MATRIX_COLS; column++) {

            // actions:
            // * iterate over whole matrix
            // * get keypos_t object for key: (keypos_t){ .row = row, .col = column }
            // * get switch layer: layer_switch_get_layer(keypos_t)
            // * get led id: g_led_config.matrix_co[row][col]
            // * evaluate keycode: keymap_key_to_keycode(layer, keypos_t)
            // * if KC_NO, don't render LED

            keypos_t keypos;
            keypos.row = row;
            keypos.col = column;
            uint8_t led_index = g_led_config.matrix_co[row][column];
            if(!is_keycode_kcno(keypos)) {
                rgb_matrix_layer_render_key(led_index, layer_switch_get_layer(keypos));
            }
            else {
                rgb_matrix_set_color(led_index, 0x00, 0x00, 0x00); //set color to white for now
            }
        }
    }
}

void rgb_matrix_indicators_user(void) {
    // uint8_t this_led = host_keyboard_leds();
    rgb_matrix_switch_layer_helper();
}



#endif
