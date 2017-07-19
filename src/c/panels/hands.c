/* This software is released under the MIT License, see LICENSE */

#include "./hands.h"
#include "../misc.h"

static const GPathInfo m_hourLocatorPath = {
	.num_points = 3,
	.points = (GPoint[]){
		{ .x = -5, .y = -5 },
		{ .x = 10, .y =  0 },
		{ .x = -5, .y =  5 }
	}
};

static GRect m_bounds;
static const Config *m_config;

static GBitmap *m_ingressBitmap;
static GPath *m_hourLocator;

//
// Module
//

void panel_hands_create(GRect bounds, const Config *config) {
	m_bounds = bounds;
	m_config = config;

	m_ingressBitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_INGRESS);
	m_hourLocator = gpath_create(&m_hourLocatorPath);
}

void panel_hands_destroy(void) {
	gpath_destroy(m_hourLocator);
	gbitmap_destroy(m_ingressBitmap);
}

void panel_hands_reconfigure(void) {

}

void panel_hands_draw(GContext *context, struct tm *local, time_t timestamp) {

	// graphics_context_set_text_color(context, m_config->foregroundColor);
	// graphics_context_set_stroke_color(context, m_config->foregroundColor);
	// graphics_context_set_stroke_width(context, 1);
	// graphics_context_set_fill_color(context, m_config->backgroundColor);

	const GPoint center = grect_center_point(&m_bounds);

	int hourTrigangle = DEG_TO_TRIGANGLE((local->tm_hour % 12) * 30 + local->tm_min / 2);
	
	// Hour hand
	{
		const GRect r = grect_crop(m_bounds, 50);
		const GPoint p = gpoint_from_polar(r, GOvalScaleModeFitCircle, hourTrigangle);

		graphics_context_set_stroke_color(context, m_config->foregroundColor);
		graphics_context_set_stroke_width(context, 3);

		graphics_draw_line(context, center, p);

		graphics_context_set_fill_color(context, m_config->foregroundColor);
		graphics_fill_circle(context, p, 4);

		graphics_context_set_fill_color(context, m_config->backgroundColor);
		graphics_fill_circle(context, p, 2);
	}
	
	// Locator
	{
		const GRect r = grect_crop(m_bounds, 8);
		const GPoint p = gpoint_from_polar(r, GOvalScaleModeFitCircle, hourTrigangle);
		gpath_rotate_to(m_hourLocator, hourTrigangle);

		#if PBL_COLOR
		gpath_move_to(m_hourLocator, GPoint(p.x + 2, p.y + 2));
		graphics_context_set_fill_color(context, COLOR_FALLBACK(m_config->locationMarkerBorderColor, m_config->foregroundColor));
		gpath_draw_filled(context, m_hourLocator);
		#endif
		
		gpath_move_to(m_hourLocator, p);
		graphics_context_set_fill_color(context, COLOR_FALLBACK(m_config->locationMarkerColor, m_config->backgroundColor));
		gpath_draw_filled(context, m_hourLocator);
		graphics_context_set_stroke_color(context, COLOR_FALLBACK(m_config->locationMarkerBorderColor, m_config->foregroundColor));
		graphics_context_set_stroke_width(context, 1);
		gpath_draw_outline(context, m_hourLocator);

	}	

	// Minute hand
	{
		const GRect r = grect_crop(m_bounds, 25);
		const GPoint p = gpoint_from_polar(r, GOvalScaleModeFitCircle, DEG_TO_TRIGANGLE(local->tm_min * 6));

		graphics_context_set_stroke_color(context, m_config->foregroundColor);
		graphics_context_set_stroke_width(context, 3);

		graphics_draw_line(context, center, p);

		graphics_context_set_fill_color(context, m_config->backgroundColor);
		graphics_fill_circle(context, p, 2);
		graphics_draw_circle(context, p, 2);

	}

	// Second hand
	if (m_config->showSecondHand) {

		const GRect r = grect_crop(m_bounds, 15);
		const GPoint p = gpoint_from_polar(r, GOvalScaleModeFitCircle, DEG_TO_TRIGANGLE(local->tm_sec * 6));

		graphics_context_set_stroke_color(context, COLOR_FALLBACK(m_config->secondHandColor, m_config->foregroundColor));
		graphics_context_set_stroke_width(context, 1);
		graphics_draw_line(context, center, p);

	}

	// Ingress icon in the middle
	{
		GRect r = { .origin = grect_center_point(&m_bounds) };
		r = grect_inset(r, GEdgeInsets(-(ICON_SIZE / 2)));
		graphics_context_set_compositing_mode(context, GCompOpSet);
		graphics_draw_bitmap_in_rect(context, m_ingressBitmap, r);
	}

}
