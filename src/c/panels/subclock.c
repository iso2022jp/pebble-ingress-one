/* This software is released under the MIT License, see LICENSE */

#include "./subclock.h"
#include "../misc.h"

static GRect m_bounds;
static const Config *m_config;

//
// Module
//

void panel_subclock_create(GRect bounds, const Config *config) {
	m_bounds = bounds;
	m_config = config;
}

void panel_subclock_destroy(void) {
	
}

void panel_subclock_reconfigure(void) {
	
}

void panel_subclock_draw(GContext *context, struct tm *local, time_t timestamp) {
	
	// graphics_context_set_text_color
	graphics_context_set_stroke_color(context, m_config->foregroundColor);
	graphics_context_set_stroke_width(context, 1);
	// graphics_context_set_fill_color(context, m_config->backgroundColor);

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
	
	const GRect gauge = grect_crop(dial, 2);

	// Indices	
	graphics_context_set_stroke_color(context, m_config->foregroundColor);
	for (int i = 0; i <= 360; i += 30) {
		const GPoint p1 = gpoint_from_polar(dial, GOvalScaleModeFitCircle, DEG_TO_TRIGANGLE(i));
		const GPoint p2 = gpoint_from_polar(gauge, GOvalScaleModeFitCircle, DEG_TO_TRIGANGLE(i));
		graphics_draw_line(context, p1, p2);
	}

	// Hands (UTC)
	const struct tm *const utc = gmtime(&timestamp);
	{
		const GRect h1 = grect_crop(gauge, 10);
		const GRect h2 = grect_crop(gauge, (gauge.size.w >> 1) - 4);
		const GPoint p1 = gpoint_from_polar(h1, GOvalScaleModeFitCircle, DEG_TO_TRIGANGLE(utc->tm_hour * 30 + (utc->tm_min >> 1)));
		const GPoint p2 = gpoint_from_polar(h2, GOvalScaleModeFitCircle, DEG_TO_TRIGANGLE(utc->tm_hour * 30 + (utc->tm_min >> 1) + 180));
		graphics_draw_line(context, p1, p2);
	}
	{
		const GRect h1 = grect_crop(gauge, 5);
		const GRect h2 = grect_crop(gauge, (gauge.size.w >> 1) - 6);
		const GPoint p1 = gpoint_from_polar(h1, GOvalScaleModeFitCircle, DEG_TO_TRIGANGLE(utc->tm_min * 6));
		const GPoint p2 = gpoint_from_polar(h2, GOvalScaleModeFitCircle, DEG_TO_TRIGANGLE(utc->tm_min * 6 + 180));
		graphics_draw_line(context, p1, p2);
	}

}
