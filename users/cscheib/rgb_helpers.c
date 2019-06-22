#include QMK_KEYBOARD_H

#define _BASE   0
#define _LAYER1 1
#define _LAYER2 2
#define _LAYER3 3

#ifdef RGB_MATRIX_ENABLE

void rgb_matrix_layer_render_key(uint8_t led_index, uint8_t switch_layer) {
    dprintf("rendering led index: %u, switch layer: %u", led_index, switch_layer);
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
            dprintf("scanning switch layer: row: %u, column %u\n", row, column);

            // actions:
            // * iterate over whole matrix [x]
            // * get keypos_t object for key: (keypos_t){ .row = row, .col = column } [x]
            // * get switch layer: layer_switch_get_layer(keypos_t)
            // * get led id: g_led_config.matrix_co[row][col]
            keypos_t keypos;
            keypos.row = row;
            keypos.col = column;
            uint8_t led_index = g_led_config.matrix_co[row][column];
            rgb_matrix_layer_render_key(led_index, layer_switch_get_layer(keypos));
        }
    }
}

void rgb_matrix_indicators_user(void) {
    // uint8_t this_led = host_keyboard_leds();
    rgb_matrix_switch_layer_helper();
}



#endif
