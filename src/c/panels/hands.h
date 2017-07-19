/* This software is released under the MIT License, see LICENSE */

#pragma once
#include <pebble.h>

#include "../modules/config.h"

void panel_hands_create(GRect bounds, const Config *config);
void panel_hands_destroy(void);
void panel_hands_reconfigure(void);
void panel_hands_draw(GContext *context, struct tm *local, time_t timestamp);
