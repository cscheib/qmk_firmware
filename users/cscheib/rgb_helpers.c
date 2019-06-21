#include QMK_KEYBOARD_H

#define _BASE   0
#define _LAYER1 1
#define _LAYER2 2
#define _LAYER3 3

#ifdef RGB_MATRIX_ENABLE

void rgb_matrix_layer_helper (uint8_t red, uint8_t green, uint8_t blue, bool default_layer) {
  for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
    if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_KEYLIGHT)) {
        rgb_matrix_set_color( i, red, green, blue );
    }
  }
}

void rgb_matrix_switch_layer_helper (void) {

    for(int row = 0;  row < MATRIX_ROWS; row++) {
        for(int column = 0;  column < MATRIX_COLS; column++) {
            // convert ROW COL pair to LED ID
            int key_id = layer_switch_get_layer(row, col); //TODO: determine order in which to row, col go
            rgb_matrix_layer_render_key(key_id); // TODO: remove key_id and pass result directly from get_layer
        }
    }
    layer_switch_get_layer(ROW, COL);
}

void rgb_matrix_layer_render_key(int key_id) {
    switch (led_id) {
        case _BASE:
        rgb_matrix_set_color(led_id, 0xFF, 0x00, 0x00); break; //TODO: attempt to use the color constants here
        case _LAYER1:
        rgb_matrix_set_color(led_id, 0x00, 0xFF, 0x00); break; //TODO: attempt to use the color constants here
        case _LAYER2:
        rgb_matrix_set_color(led_id, 0x00, 0x00, 0xFF); break; //TODO: attempt to use the color constants here
        case _LAYER3:
        rgb_matrix_set_color(led_id, 0xFF, 0xFF, 0x00); break; //TODO: attempt to use the color constants here
    }
}

void rgb_matrix_indicators_user(void) {
    uint8_t this_led = host_keyboard_leds();
    if (!g_suspend_state) {
        // switch (biton32(layer_state)) {
        //     case _BASE:
        //     rgb_matrix_layer_helper(0xFF, 0x00, 0x00, false); break;
        //     case _LAYER1:
        //     rgb_matrix_layer_helper(0x00, 0xFF, 0x00, false); break;
        //     case _LAYER2:
        //     rgb_matrix_layer_helper(0x00, 0x00, 0xFF, false); break;
        //     case _LAYER3:
        //     rgb_matrix_layer_helper(0xFF, 0xFF, 0x00, false); break;
        // }

        rgb_matrix_switch_layer_helper();
    }
    if ( this_led & (1<<USB_LED_CAPS_LOCK)) {
        rgb_matrix_set_color(40, 0xFF, 0xFF, 0xFF);
    }
}

#endif
