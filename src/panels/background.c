/* This software is released under the MIT License, see LICENSE */

#include "panels/background.h"
#include "modules/ingress.h"

#define HOUR_TO_TRIGANGLE(h)	DEG_TO_TRIGANGLE(h * 30)

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

	// graphics_context_set_text_color(context, m_config->foregroundColor);
	// graphics_context_set_stroke_color(context, COLOR_FALLBACK(m_config->checkpointColor, m_config->foregroundColor));
	// graphics_context_set_stroke_width(context, 1);
	// graphics_context_set_fill_color(context, m_config->foregroundColor);

	// 8px Padding
	const GRect dial = grect_crop(m_bounds, 8);

	// Current checkpoint indicator
	{
		const int elapsed = ingress_get_elapsed(timestamp);
		const int from = local->tm_hour % 12 - (elapsed / SECONDS_PER_HOUR);
		const int to = from + HOURS_PER_CHECKPOINT;

		#if defined(PBL_COLOR)
		graphics_context_set_stroke_color(context, GColorMidnightGreen);
		graphics_context_set_stroke_width(context, 7);
		graphics_draw_arc(context, dial, GOvalScaleModeFitCircle, HOUR_TO_TRIGANGLE(from), HOUR_TO_TRIGANGLE(to));
		graphics_context_set_fill_color(context, GColorMidnightGreen);
		#else
		graphics_context_set_fill_color(context, m_config->foregroundColor);
		graphics_fill_radial(context, m_bounds, GOvalScaleModeFitCircle, 2, HOUR_TO_TRIGANGLE(from), HOUR_TO_TRIGANGLE(to));
		#endif
	
	}

	// Indices
	{
		graphics_context_set_fill_color(context, m_config->foregroundColor);
		for (int i = 0; i <= 360; i += 6) {
			const GPoint p = gpoint_from_polar(dial, GOvalScaleModeFitCircle, DEG_TO_TRIGANGLE(i));
			graphics_fill_circle(context, p, i % 30 ? 1 : 2);
		}
	}

	// Highlight checkpoints & cycles
	{
		const int elapsed = ingress_get_elapsed(timestamp);

		int i, h;
		time_t t;
		for (
			// Origin of current checkpoint 
			i = 0, h = local->tm_hour - (elapsed / SECONDS_PER_HOUR), t = timestamp - elapsed;
			i < 12;
			++i, ++h, t += SECONDS_PER_HOUR
		) {
			
			if (!ingress_is_checkpoint(t)) {
				continue;
			}

			const bool cycle = ingress_is_cycle(t);
			const GPoint p = gpoint_from_polar(dial, GOvalScaleModeFitCircle, HOUR_TO_TRIGANGLE(h));

			graphics_context_set_fill_color(context, COLOR_FALLBACK(m_config->checkpointColor, m_config->foregroundColor));
			graphics_fill_circle(context, p, 5);

			if (!cycle) {
				graphics_context_set_fill_color(context, m_config->backgroundColor);
				graphics_fill_circle(context, p, 3);
			}
	
		}

	}
	
}
