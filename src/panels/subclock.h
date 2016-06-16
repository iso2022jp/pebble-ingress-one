/* This software is released under the MIT License, see LICENSE */

#pragma once
#include <pebble.h>

#include "modules/config.h"

void panel_subclock_create(GRect bounds, const Config *config);
void panel_subclock_destroy(void);
void panel_subclock_reconfigure(void);
void panel_subclock_draw(GContext *ctx, struct tm *local, time_t timestamp);
