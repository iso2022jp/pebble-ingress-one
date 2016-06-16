/* This software is released under the MIT License, see LICENSE */

#include "panels/subclock.h"

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

void panel_subclock_draw(GContext *ctx, struct tm *local, time_t timestamp) {
	
	// graphics_context_set_text_color
	graphics_context_set_stroke_color(ctx, m_config->foregroundColor);
	graphics_context_set_stroke_width(ctx, 1);
	// graphics_context_set_fill_color(ctx, m_config->backgroundColor);

	const GRect dial = grect_crop(m_bounds, 1);
	const GRect gauge = grect_crop(dial, 2);

	// Indices	
	graphics_context_set_stroke_color(ctx, m_config->foregroundColor);
	for (int i = 0; i <= 360; i += 30) {
		const GPoint p = gpoint_from_polar(dial, GOvalScaleModeFitCircle, DEG_TO_TRIGANGLE(i));
		const GPoint p2 = gpoint_from_polar(gauge, GOvalScaleModeFitCircle, DEG_TO_TRIGANGLE(i));
		graphics_draw_line(ctx, p, p2);
	}

	// Hands (UTC)
	const struct tm *const utc = gmtime(&timestamp);
	{
		const GRect h1 = grect_crop(gauge, 10);
		const GRect h2 = grect_crop(gauge, (gauge.size.w >> 1) - 4);
		const GPoint p1 = gpoint_from_polar(h1, GOvalScaleModeFitCircle, DEG_TO_TRIGANGLE(utc->tm_hour * 30 + (utc->tm_min >> 1)));
		const GPoint p2 = gpoint_from_polar(h2, GOvalScaleModeFitCircle, DEG_TO_TRIGANGLE(utc->tm_hour * 30 + (utc->tm_min >> 1) + 180));
		graphics_draw_line(ctx, p1, p2);
	}
	{
		const GRect h1 = grect_crop(gauge, 5);
		const GRect h2 = grect_crop(gauge, (gauge.size.w >> 1) - 6);
		const GPoint p1 = gpoint_from_polar(h1, GOvalScaleModeFitCircle, DEG_TO_TRIGANGLE(utc->tm_min * 6));
		const GPoint p2 = gpoint_from_polar(h2, GOvalScaleModeFitCircle, DEG_TO_TRIGANGLE(utc->tm_min * 6 + 180));
		graphics_draw_line(ctx, p1, p2);
	}

}
