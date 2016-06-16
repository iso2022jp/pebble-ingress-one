/* This software is released under the MIT License, see LICENSE */

#pragma once
#include <pebble.h>

#include "modules/config.h"

void panel_calendar_create(GRect bounds, const Config *config);
void panel_calendar_destroy(void);
void panel_calendar_reconfigure(void);
void panel_calendar_draw(GContext *context, struct tm *local, time_t timestamp);
