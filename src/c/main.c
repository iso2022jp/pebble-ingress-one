/* This software is released under the MIT License, see LICENSE */

#include <pebble.h>
#include "./modules/config.h"
#include "./windows/main.h"

//
// Service Handlers
//

static void on_connect(bool connected) {	
	main_on_connect(connected);
}

static void on_battery(BatteryChargeState charge) {	
	main_on_battery(charge);
}

static void on_focus(bool in_focus) {
	main_on_focus(in_focus);
}

static void on_tap(AccelAxisType axis, int32_t direction) {
	main_on_tap(axis, direction);
}

static void on_tick(struct tm *tick_time, TimeUnits units_changed) {
	main_on_tick(tick_time, units_changed);
}

//
// Main
//

static void init(void) {

	config_init(main_reconfigure);

	main_push();

	app_focus_service_subscribe_handlers((AppFocusHandlers) {
		.will_focus = on_focus,
	});
	battery_state_service_subscribe(on_battery);
	connection_service_subscribe((ConnectionHandlers) {
		.pebble_app_connection_handler = on_connect
	});
	accel_tap_service_subscribe(on_tap);
	tick_timer_service_subscribe(SECOND_UNIT, on_tick);

}

static void deinit(void) {

	tick_timer_service_unsubscribe();
	accel_tap_service_unsubscribe();
	connection_service_unsubscribe();
	battery_state_service_unsubscribe();
	app_focus_service_unsubscribe();
	
	app_message_deregister_callbacks();

	config_deinit();
}

//
// Entry Point
//

int main(void) {
	init();
	app_event_loop();
	deinit();
}
