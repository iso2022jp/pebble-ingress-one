/* This software is released under the MIT License, see LICENSE */

#include "panels/background.h"
#include "modules/ingress.h"
#include "modules/offscreen.h"

#define HOUR_TO_TRIGANGLE(h)	DEG_TO_TRIGANGLE(h * 30)
#define MAX(p, q)				((p) >= (q) ? (p) : (q))

static GRect m_bounds;
static const Config *m_config;

#ifdef PBL_COLOR
static GRect m_surfaceBounds;
static GBitmap *m_surfaceBitmap;
static int m_surfaceClippingInset;
static GRect m_surfaceClippingBounds;
#endif

//
// Module
//

void panel_background_create(GRect bounds, const Config *config) {
	m_bounds = bounds;
	m_config = config;
	#ifdef PBL_COLOR
	m_surfaceBitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_SURFACE);
	m_surfaceBounds = grect_crop(m_bounds, 16);
	m_surfaceClippingInset = MAX(m_surfaceBounds.size.w, m_surfaceBounds.size.h) >> 2;
	m_surfaceClippingBounds = grect_crop(m_surfaceBounds, -m_surfaceClippingInset);
	#endif
}

void panel_background_destroy(void) {
	#ifdef PBL_COLOR
	gbitmap_destroy(m_surfaceBitmap);
	#endif
}

void panel_background_reconfigure(void) {
}

void panel_background_draw(GContext *context, struct tm *local, time_t timestamp) {

	// 8px inset dial circle (16px border)
	const GRect dial = grect_crop(m_bounds, 8);

	// graphics_context_set_text_color(context, m_config->foregroundColor);
	// graphics_context_set_stroke_color(context, COLOR_FALLBACK(m_config->checkpointColor, m_config->foregroundColor));
	// graphics_context_set_stroke_width(context, 1);
	// graphics_context_set_fill_color(context, m_config->foregroundColor);

	// Surface
	#ifdef PBL_COLOR
	graphics_draw_bitmap_in_rect(context, m_surfaceBitmap, m_surfaceBounds);
	graphics_context_set_fill_color(context, m_config->backgroundColor);
	graphics_fill_radial(context, m_surfaceClippingBounds, GOvalScaleModeFillCircle, m_surfaceClippingInset, 0, TRIG_MAX_ANGLE);
	#endif

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
