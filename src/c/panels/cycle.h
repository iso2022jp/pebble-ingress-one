/* This software is released under the MIT License, see LICENSE */

#pragma once

#include <pebble.h>
#include "../modules/config.h"

void panel_cycle_create(GRect bounds, const Config *config);
void panel_cycle_destroy(void);
void panel_cycle_reconfigure(void);
void panel_cycle_draw(GContext *context, struct tm *local, time_t timestamp);
