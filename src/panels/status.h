/* This software is released under the MIT License, see LICENSE */

#pragma once
#include <pebble.h>

#include "modules/config.h"

void panel_status_create(GRect bounds, const Config *config);
void panel_status_destroy(void);
void panel_status_reconfigure(void);
void panel_status_draw(GContext *ctx, struct tm *local, time_t timestamp);

void panel_status_on_battery(BatteryChargeState charge);
void panel_status_on_connect(bool connected);
