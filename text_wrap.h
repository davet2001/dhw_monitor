#pragma once

#include "esphome/components/display/display_buffer.h"

void wrap_text_box2(esphome::display::Display *it, int x, int y, int width, int height,
                    esphome::display::BaseFont *font, esphome::display::TextAlign align, float line_height,
                    const char *format, ...) __attribute__((format(wrap_text_box2, 10, 11)));
