/* This software is released under the MIT License, see LICENSE */

#include "panels/background.h"
#include "modules/ingress.h"

static GRect m_bounds;
static const Config *m_config;

//
// Module
//

void panel_background_create(GRect bounds, const Config *config) {
	m_bounds = bounds;
	m_config = config;
}

void panel_background_destroy(void) {

}

void panel_background_reconfigure(void) {
	
}

void panel_background_draw(GContext *context, struct tm *local, time_t timestamp) {

	//graphics_context_set_text_color(context, m_config->foregroundColor);
	graphics_context_set_stroke_color(context, COLOR_FALLBACK(m_config->checkpointColor, m_config->foregroundColor));
	// graphics_context_set_stroke_width(context, 1);
	graphics_context_set_fill_color(context, m_config->foregroundColor);

	// 8px Padding
	const GRect dial = grect_crop(m_bounds, 8);

	// Indices
	{
		for (int i = 0; i <= 360; i += 6) {
			const GPoint p = gpoint_from_polar(dial, GOvalScaleModeFitCircle, DEG_TO_TRIGANGLE(i));
			graphics_fill_circle(context, p, i % 30 ? 1 : 2);
		}
	}

	// Highlight checkpoints & cycles
	for (int i = 1; i <= 12; ++i) {
		const int t = timestamp + i * SECONDS_PER_HOUR;
		if (ingress_is_checkpoint(t)) {

			const bool cycle = ingress_is_cycle(t);

			const GPoint p = gpoint_from_polar(dial, GOvalScaleModeFitCircle, DEG_TO_TRIGANGLE((local->tm_hour + i) * 30));
			
			graphics_context_set_fill_color(context, COLOR_FALLBACK(m_config->checkpointColor, m_config->foregroundColor));
			graphics_fill_circle(context, p, 5);
			
			if (!cycle) {
				graphics_context_set_fill_color(context, m_config->backgroundColor);
				graphics_fill_circle(context, p, 3);
			}

		}
	}

}
