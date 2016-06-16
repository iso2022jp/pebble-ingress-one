/* This software is released under the MIT License, see LICENSE */

#include "panels/calendar.h"
#include "config.h"

static GRect m_bounds;
static const Config *m_config;

static GBitmap *m_ingressBitmap;

//
// Module
//

void panel_hands_create(GRect bounds, const Config *config) {
	m_bounds = bounds;
	m_config = config;

	m_ingressBitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_INGRESS);
}

void panel_hands_destroy(void) {
	gbitmap_destroy(m_ingressBitmap);
}

void panel_hands_reconfigure(void) {
	
}

void panel_hands_draw(GContext *ctx, struct tm *local, time_t timestamp) {
	
	// graphics_context_set_text_color(ctx, m_config->foregroundColor);
	// graphics_context_set_stroke_color(ctx, m_config->foregroundColor);
	// graphics_context_set_stroke_width(ctx, 1);
	// graphics_context_set_fill_color(ctx, m_config->backgroundColor);

	const GPoint center = grect_center_point(&m_bounds);
	
	// Hour hand
	{
		const GRect r = grect_crop(m_bounds, 40);
		const GPoint p = gpoint_from_polar(r, GOvalScaleModeFitCircle, DEG_TO_TRIGANGLE((local->tm_hour % 12) * 30 + local->tm_min / 2));
		
		graphics_context_set_stroke_color(ctx, m_config->foregroundColor);
		graphics_context_set_stroke_width(ctx, 3);

		graphics_draw_line(ctx, center, p);
		
		graphics_context_set_fill_color(ctx, m_config->foregroundColor);
		graphics_fill_circle(ctx, p, 4);

		graphics_context_set_fill_color(ctx, m_config->backgroundColor);
		graphics_fill_circle(ctx, p, 2);

	}
	
	// Minute hand
	{
		const GRect r = grect_crop(m_bounds, 25);
		const GPoint p = gpoint_from_polar(r, GOvalScaleModeFitCircle, DEG_TO_TRIGANGLE(local->tm_min * 6));

		graphics_context_set_stroke_color(ctx, m_config->foregroundColor);
		graphics_context_set_stroke_width(ctx, 3);

		graphics_draw_line(ctx, center, p);

		graphics_context_set_fill_color(ctx, m_config->backgroundColor);
		graphics_fill_circle(ctx, p, 2);
		graphics_draw_circle(ctx, p, 2);

	}
	
	// Second hand
	if (m_config->showSecondHand) {

		const GRect r = grect_crop(m_bounds, 15);
		const GPoint p = gpoint_from_polar(r, GOvalScaleModeFitCircle, DEG_TO_TRIGANGLE(local->tm_sec * 6));

		graphics_context_set_stroke_color(ctx, COLOR_FALLBACK(m_config->secondHandColor, m_config->foregroundColor));
		graphics_context_set_stroke_width(ctx, 1);
		graphics_draw_line(ctx, center, p);

	}
	
	// Ingress icon in the middle
	{
		GRect r = { .origin = grect_center_point(&m_bounds) };
		r = grect_inset(r, GEdgeInsets(-(ICON_SIZE / 2)));
		graphics_context_set_compositing_mode(ctx, GCompOpSet);
		graphics_draw_bitmap_in_rect(ctx, m_ingressBitmap, r);
	}

}
