/* This software is released under the MIT License, see LICENSE */

#include "panels/calendar.h"

static GRect m_bounds;
static const Config *m_config;

static GFont m_codaFont12;
static GFont m_codaFont24;

//
// Module
//

void panel_calendar_create(GRect bounds, const Config *config) {
	m_bounds = bounds;
	m_config = config;
	
	m_codaFont12 = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_CODA_12));
	m_codaFont24 = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_CODA_24));
}

void panel_calendar_destroy(void) {
	fonts_unload_custom_font(m_codaFont24);
	fonts_unload_custom_font(m_codaFont12);
}

void panel_calendar_reconfigure(void) {
	
}

void panel_calendar_draw(GContext *context, struct tm *local, time_t timestamp) {
	
	graphics_context_set_text_color(context, m_config->foregroundColor);
	// graphics_context_set_stroke_color(context, m_config->foregroundColor);
	// graphics_context_set_stroke_width(context, 1);
	// graphics_context_set_fill_color(context, m_config->backgroundColor);

	char text[9] = "";
	
	// Weekday, Month
	{
		const GRect r = GRect(m_bounds.origin.x, m_bounds.origin.y + m_bounds.size.h / 6, m_bounds.size.w, 12);
		strftime(text, sizeof text, "%a, %b", local);
		graphics_draw_text(context, text, m_codaFont12, r, GTextOverflowModeFill, GTextAlignmentCenter, NULL);
	}

	// Day
	{
		const GRect r = GRect(m_bounds.origin.x, m_bounds.origin.y + m_bounds.size.h / 4, m_bounds.size.w, 24);
		strftime(text, sizeof text, "%d", local);
		graphics_draw_text(context, text, m_codaFont24, r, GTextOverflowModeFill, GTextAlignmentCenter, NULL);
	}

}
