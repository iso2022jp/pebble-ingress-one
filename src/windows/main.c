/* This software is released under the MIT License, see LICENSE */

#include "windows/main.h"

#include "panels/background.h"
#include "panels/cycle.h"
#include "panels/status.h"
#include "panels/subclock.h"
#include "panels/calendar.h"
#include "panels/hands.h"

#include "modules/ingress.h"
// #include "modules/offscreen.h"

static Window *m_window;

static GRect m_bounds;
static const Config *m_config;
static int m_tapTimeout = 0;

static void on_draw(GContext *ctx, void *arg) {

	//
	// Prepare
	//

	time_t timestamp = time(NULL);
	struct tm *local = localtime(&timestamp); 

	// Workaround: aplite timestamp is local time
	if (!clock_is_timezone_set()) {
		timestamp += m_config->detectedTimeZoneOffset;
	}

	graphics_context_set_antialiased(ctx, true);
	graphics_context_set_compositing_mode(ctx, PBL_IF_COLOR_ELSE(GCompOpSet, GCompOpAssign));

	//
	// Draw
	//

	// Paint background
	graphics_context_set_fill_color(ctx, m_config->backgroundColor);
	graphics_fill_rect(ctx, m_bounds, 0, GCornerNone);	

	// Dial
	panel_background_draw(ctx, local, timestamp);

	// Cycle indial
	if (m_config->showCyclePanel) {
		panel_cycle_draw(ctx, local, timestamp);
	}

	// Status indial
	if (m_config->showStatusPanel) {
		panel_status_draw(ctx, local, timestamp);
	}

	// Subclock indial
	if (m_config->showSubclock) {
		panel_subclock_draw(ctx, local, timestamp);
	}

	// Calendar
	panel_calendar_draw(ctx, local, timestamp);

	// Hands
	panel_hands_draw(ctx, local, timestamp);

}

//
// Window Handlers
//

static void on_update(Layer *layer, GContext *ctx) {

	//offscreen_draw(ctx, on_draw, NULL);
	on_draw(ctx, NULL);

	//APP_LOG(APP_LOG_LEVEL_DEBUG, "Free: %d, Used: %d: End", heap_bytes_free(), heap_bytes_used());

}

static void on_load(Window *window) {

	Layer *const root = window_get_root_layer(window);	

	m_bounds = layer_get_bounds(root);
	m_config = config_get();

	layer_set_update_proc(root, on_update);
	
	const GRect base = grect_crop(m_bounds, PBL_IF_ROUND_ELSE(0, -8));

	panel_background_create(base, m_config);

	// indial ring
	{
		const int width = base.size.w / 3;
		const GSize size = GSize(width, width);

		const GRect ring = grect_crop(base, base.size.w >> 2);

		{
			const GRect r = grect_centered_from_polar(ring, GOvalScaleModeFitCircle, DEG_TO_TRIGANGLE(90), size);
			panel_cycle_create(r, m_config);
		}
		{
			const GRect r = grect_centered_from_polar(ring, GOvalScaleModeFitCircle, DEG_TO_TRIGANGLE(270), size);
			panel_status_create(r, m_config);
		}
		{
			const GRect r = grect_centered_from_polar(ring, GOvalScaleModeFitCircle, DEG_TO_TRIGANGLE(180), size);
			panel_subclock_create(r, m_config);
		}

	}

	panel_calendar_create(base, m_config);
	panel_hands_create(base, m_config);

}

static void on_unload(Window *window) {

	panel_hands_destroy();

	panel_calendar_destroy();
	panel_subclock_destroy();
	panel_status_destroy();
	panel_cycle_destroy();

	panel_background_destroy();

	window_destroy(m_window);
}

//
//
//

static void notify_checkpoint() {

	time_t timestamp = time(NULL);
	//struct tm *local = localtime(&timestamp); 

	// Aplite uses local timestamp
	if (!clock_is_timezone_set()) {
		timestamp += m_config->detectedTimeZoneOffset;
	}

	timestamp = timestamp / SECONDS_PER_MINUTE * SECONDS_PER_MINUTE;

	if (ingress_is_cycle(timestamp)) {

		static const uint32_t const segments[] = { 500, 500, 500, 500, 500 };
		VibePattern pattern = {
			.durations = segments,
			.num_segments = ARRAY_LENGTH(segments),
		};
		vibes_enqueue_custom_pattern(pattern);

	} else if (ingress_is_checkpoint(timestamp)) {

		static const uint32_t const segments[] = { 500, 500, 500 };
		VibePattern pattern = {
			.durations = segments,
			.num_segments = ARRAY_LENGTH(segments),
		};
		vibes_enqueue_custom_pattern(pattern);

	}

}

//
// Module
//

static Window *m_window;

void main_push(void) {
	if (!m_window) {
		m_window = window_create();
		window_set_window_handlers(m_window, (WindowHandlers) {
			.load = on_load,
			.unload = on_unload,
		});
	}
	window_stack_push(m_window, true);
}

void main_invalidate(void) {
	Layer *const root = window_get_root_layer(m_window);
	layer_mark_dirty(root);
}

void main_reconfigure() {

	panel_background_reconfigure();

	panel_cycle_reconfigure();
	panel_status_reconfigure();
	panel_subclock_reconfigure();
	panel_calendar_reconfigure();

	panel_hands_reconfigure();

	main_invalidate();
}

void main_on_connect(bool connected) {
	panel_status_on_connect(connected);
}

void main_on_battery(BatteryChargeState charge) {
	panel_status_on_battery(charge);
}

void main_on_focus(bool in_focus) {
}

void main_on_tap(AccelAxisType axis, int32_t direction) {
	m_tapTimeout = 3;
}

void main_on_tick(struct tm *tick_time, TimeUnits units_changed) {

	if (units_changed & MINUTE_UNIT || config_get()->showSecondHand) {
		main_invalidate();
	}

// 	if (units_changed & MINUTE_UNIT) {
// 		notify_checkpoint();
// 	}	

}
