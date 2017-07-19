/* This software is released under the MIT License, see LICENSE */

#include "./status.h"
#include "../misc.h"

static GRect m_bounds;
static const Config *m_config;

static BatteryChargeState m_state;
static bool m_connected;

static GFont m_codaFont12;
static GBitmap *m_power;
static GBitmap *m_bluetooth;

//
// Module
//

void panel_status_create(GRect bounds, const Config *config) {
	m_bounds = bounds;
	m_config = config;

	m_codaFont12 = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_CODA_12));
	m_power = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_POWER);
	m_bluetooth = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BLUETOOTH);

	m_state = battery_state_service_peek();
	m_connected = connection_service_peek_pebble_app_connection();
}

void panel_status_destroy(void) {
	gbitmap_destroy(m_bluetooth);
	gbitmap_destroy(m_power);
	fonts_unload_custom_font(m_codaFont12);
}

void panel_status_reconfigure(void) {
	
}

void panel_status_draw(GContext *context, struct tm *local, time_t timestamp) {

	graphics_context_set_text_color(context, COLOR_FALLBACK(m_config->powerReserveColor, m_config->foregroundColor));
	graphics_context_set_stroke_color(context, m_config->foregroundColor);
	graphics_context_set_stroke_width(context, 1);
	graphics_context_set_fill_color(context, m_config->backgroundColor);

	#ifdef PBL_COLOR
	const GRect dial = grect_crop(m_bounds, 3);
	#else
	const GRect dial = m_bounds;
	#endif
	
	#ifdef PBL_COLOR
	// Background
	{
		// Fill background
		graphics_context_set_fill_color(context, GColorBlack);
		graphics_fill_radial(context, m_bounds, GOvalScaleModeFitCircle, MAX(m_bounds.size.w, m_bounds.size.h) / 2, 0, TRIG_MAX_ANGLE);	

		// Shadow
		graphics_fill_radial(context, m_bounds, GOvalScaleModeFitCircle, 2, HOUR_TO_TRIGANGLE(8), HOUR_TO_TRIGANGLE(13));

		// Light
		graphics_context_set_fill_color(context, GColorDukeBlue);
		graphics_fill_radial(context, m_bounds, GOvalScaleModeFitCircle, 2, HOUR_TO_TRIGANGLE(2), HOUR_TO_TRIGANGLE(7));

		// Middle
		graphics_context_set_fill_color(context, GColorOxfordBlue);
		graphics_fill_radial(context, m_bounds, GOvalScaleModeFitCircle, 2, HOUR_TO_TRIGANGLE(1), HOUR_TO_TRIGANGLE(2));
		graphics_fill_radial(context, m_bounds, GOvalScaleModeFitCircle, 2, HOUR_TO_TRIGANGLE(7), HOUR_TO_TRIGANGLE(8));

		// Border
		graphics_fill_radial(context, m_bounds, GOvalScaleModeFitCircle, 1, 0, TRIG_MAX_ANGLE);
	}
	#endif


	// Power Reserve Meter
	{
		const GRect base = grect_crop(dial, 3);
		const GRect gauge1 = grect_crop(base, -3);
		const GRect gauge2 = grect_crop(base, -5);

		graphics_context_set_stroke_color(context, m_config->foregroundColor);
		for (int i = 0; i < 10; ++i) {
			const GPoint p1 = gpoint_from_polar(base, GOvalScaleModeFitCircle, TRIG_MAX_ANGLE * i / 10);
			const GPoint p2 = gpoint_from_polar(i % 5 ? gauge1 : gauge2, GOvalScaleModeFitCircle, TRIG_MAX_ANGLE * i / 10);
			graphics_draw_line(context, p1, p2);
		}
		
		graphics_context_set_stroke_width(context, 3);
		graphics_context_set_stroke_color(context, COLOR_FALLBACK(m_config->powerReserveColor, m_config->foregroundColor));
		graphics_draw_arc(context, base, GOvalScaleModeFitCircle, 0, TRIG_MAX_ANGLE * m_state.charge_percent / 100);
				
	}

	// Status icons
	{
		GRect r = m_bounds;
		r.origin.y += (r.size.h - 34) / 2;
		r.size.h = 12;
		
		char text[8];
		
		graphics_context_set_text_color(context, COLOR_FALLBACK(GColorYellow, m_config->foregroundColor));
		
		snprintf(text, sizeof text, "%d%%", m_state.charge_percent);		
		graphics_draw_text(context, text, m_codaFont12, r, GTextOverflowModeTrailingEllipsis, GTextAlignmentCenter, NULL);

		r.origin.y += 16;
		r.origin.x += (r.size.w - ICON_SIZE * 2) / 2;
		r.size.h = ICON_SIZE; 
		r.size.w = ICON_SIZE;

		#ifdef PBL_COLOR
		graphics_context_set_compositing_mode(context, GCompOpSet);
		#else 
		graphics_context_set_compositing_mode(context, gcolor_equal(m_config->backgroundColor, GColorBlack) ? GCompOpAssign : GCompOpAssignInverted);
		#endif
	
		if (m_state.is_charging) {
			graphics_draw_bitmap_in_rect(context, m_power, r);
		}
		if (m_connected) {
			r.origin.x += ICON_SIZE;
			graphics_draw_bitmap_in_rect(context, m_bluetooth, r);
		}
		
	}

}

void panel_status_on_battery(BatteryChargeState charge) {
	m_state = charge;
}

void panel_status_on_connect(bool connected) {
	m_connected = connected;
}
