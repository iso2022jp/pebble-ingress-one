/* This software is released under the MIT License, see LICENSE */

#include "panels/subclock.h"
#include "modules/ingress.h"

static GRect m_bounds;
static const Config *m_config;

static GFont m_codaFont10;
static GFont m_codaFont12;

//
// Module
//

void panel_cycle_create(GRect bounds, const Config *config) {
	m_bounds = bounds;
	m_config = config;
	
	m_codaFont10 = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_CODA_10));
	m_codaFont12 = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_CODA_12));
}

void panel_cycle_destroy(void) {
	fonts_unload_custom_font(m_codaFont12);
	fonts_unload_custom_font(m_codaFont10);
}

void panel_cycle_reconfigure(void) {
	
}

void panel_cycle_draw(GContext *ctx, struct tm *local, time_t timestamp) {
	
	// graphics_context_set_text_color
	graphics_context_set_stroke_color(ctx, m_config->foregroundColor);
	graphics_context_set_stroke_width(ctx, 1);
	// graphics_context_set_fill_color(ctx, m_config->backgroundColor);

	Cycle cycle;
	ingress_get_cycle(timestamp, &cycle);

	// cycle
	{
		const GRect dial = grect_crop(m_bounds, 4);
		const GRect gauge1 = grect_crop(dial, -3);
		const GRect gauge2 = grect_crop(dial, -6);

		for (int i = 0; i < 35; ++i) {
			const GPoint p1 = gpoint_from_polar(dial, GOvalScaleModeFitCircle, TRIG_MAX_ANGLE * i / 35);
			const GPoint p2 = gpoint_from_polar(i % 5 ? gauge1 : gauge2, GOvalScaleModeFitCircle, TRIG_MAX_ANGLE * i / 35);
			graphics_draw_line(ctx, p1, p2);
		}
		
		graphics_context_set_stroke_width(ctx, 3);
		graphics_context_set_stroke_color(ctx, COLOR_FALLBACK(m_config->checkpointColor, m_config->foregroundColor));
		graphics_draw_arc(ctx, dial, GOvalScaleModeFitCircle, 0, TRIG_MAX_ANGLE * cycle.checkpoint / 35);
	}

	// 
	{
		GRect r = m_bounds;
		r.origin.y += (r.size.h - 34) / 2;
		r.size.h = 12;
		
		char text[8];
		
		graphics_context_set_text_color(ctx, COLOR_FALLBACK(m_config->checkpointColor, m_config->foregroundColor));
		
		snprintf(text, sizeof text, "#%d", cycle.checkpoint + 1);
		graphics_draw_text(ctx, text, m_codaFont12, r, GTextOverflowModeTrailingEllipsis, GTextAlignmentCenter, NULL);

		r.origin.y += 16;
		//snprintf(text, sizeof text, "%d.%02d", cycle.year, cycle.cycle + 1);
		snprintf(text, sizeof text, "%d.%02d", cycle.year, cycle.cycle + 1);
		graphics_draw_text(ctx, text, m_codaFont10, r, GTextOverflowModeTrailingEllipsis, GTextAlignmentCenter, NULL);
	}

}
