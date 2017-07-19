/* This software is released under the MIT License, see LICENSE */

#pragma once

#include <pebble.h>
#include "../modules/config.h"

void main_push(void);
void main_invalidate(void);

void main_reconfigure();

void main_on_connect(bool connected);
void main_on_battery(BatteryChargeState charge);
void main_on_focus(bool in_focus);
void main_on_tap(AccelAxisType axis, int32_t direction);
void main_on_tick(struct tm *tick_time, TimeUnits units_changed);
