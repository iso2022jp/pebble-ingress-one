/* This software is released under the MIT License, see LICENSE */

#include "./subclock.h"
#include "../modules/ingress.h"
#include "../misc.h"

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

void panel_cycle_draw(GContext *context, struct tm *local, time_t timestamp) {
	
	// graphics_context_set_text_color(context, m_config->foregroundColor);
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
	
	Cycle cycle;
	ingress_get_cycle(timestamp, &cycle);

	// Cycle meter 
	{
		const GRect base = grect_crop(dial, 4);
		const GRect gauge1 = grect_crop(base, -3);
		const GRect gauge2 = grect_crop(base, -5);

		for (int i = 0; i < 35; ++i) {
			const GPoint p1 = gpoint_from_polar(base, GOvalScaleModeFitCircle, TRIG_MAX_ANGLE * i / 35);
			const GPoint p2 = gpoint_from_polar(i % 5 ? gauge1 : gauge2, GOvalScaleModeFitCircle, TRIG_MAX_ANGLE * i / 35);
			graphics_draw_line(context, p1, p2);
		}
		
		graphics_context_set_stroke_width(context, 3);
		graphics_context_set_stroke_color(context, COLOR_FALLBACK(m_config->checkpointColor, m_config->foregroundColor));
		graphics_draw_arc(context, base, GOvalScaleModeFitCircle, 0, TRIG_MAX_ANGLE * cycle.checkpoint / 35);
	}

	// Cycle #, Checkpoint#
	{
		GRect r = m_bounds;
		r.origin.y += (r.size.h - 34) / 2;
		r.size.h = 12;
		
		char text[8];
		
		graphics_context_set_text_color(context, COLOR_FALLBACK(m_config->checkpointColor, m_config->foregroundColor));
		
		snprintf(text, sizeof text, "#%d", cycle.checkpoint + 1);
		graphics_draw_text(context, text, m_codaFont12, r, GTextOverflowModeTrailingEllipsis, GTextAlignmentCenter, NULL);

		r.origin.y += 16;
		snprintf(text, sizeof text, "%d.%02d", cycle.year, cycle.cycle + 1);
		graphics_draw_text(context, text, m_codaFont10, r, GTextOverflowModeTrailingEllipsis, GTextAlignmentCenter, NULL);
	}

}
