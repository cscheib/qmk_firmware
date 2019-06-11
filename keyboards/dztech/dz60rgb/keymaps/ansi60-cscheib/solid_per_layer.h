// This is an attempt to make per layer colors

#ifndef DISABLE_RGB_MATRIX_SOLID_PER_LAYER
RGB_MATRIX_EFFECT(SOLID_PER_LAYER)
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

bool SOLID_PER_LAYER(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);

  HSV hsv = { rgb_matrix_config.hue, rgb_matrix_config.sat, rgb_matrix_config.val };
  RGB rgb = hsv_to_rgb(hsv);
  for (uint8_t i = led_min; i < led_max; i++) {
    RGB_MATRIX_TEST_LED_FLAGS();
    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
  }
  return led_max < DRIVER_LED_TOTAL;
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif // DISABLE_RGB_MATRIX_CYCLE_DOWN_UP
