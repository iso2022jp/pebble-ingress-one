/* This software is released under the MIT License, see LICENSE */

#include "modules/offscreen.h"

typedef struct {
	uint8_t *data;
	GBitmapFormat format;
	uint16_t stride;
	GRect bounds;
} BitmapDesc;

static GBitmap *offscreen_begin(BitmapDesc *desc, GContext *context) {

	// Get surface frame buffer & lock
	GBitmap *frame = graphics_capture_frame_buffer(context);

	// Keep buffer info
	desc->data = gbitmap_get_data(frame);	
	desc->format = gbitmap_get_format(frame);
	desc->stride = gbitmap_get_bytes_per_row(frame);
	desc->bounds = gbitmap_get_bounds(frame);

	// Release
	graphics_release_frame_buffer(context, frame);
	
	return frame;

}

static void offscreen_select(GBitmap *frame, GBitmap *bitmap) {
	uint8_t *d = gbitmap_get_data(bitmap);	
	GBitmapFormat f = gbitmap_get_format(bitmap);
	uint16_t s = gbitmap_get_bytes_per_row(bitmap);	

	gbitmap_set_data(frame, d, f, s, false);
}

static void offscreen_end(GBitmap *frame, const BitmapDesc *desc) {
	// restore buffer
	gbitmap_set_data(frame, desc->data, desc->format, desc->stride, false);	
}

void offscreen_draw(GContext *context, OffscreenHandler handler, void *arg) {

	BitmapDesc desc;

	// Start
	GBitmap *frame = offscreen_begin(&desc, context);

	// Create compatible bitmap
	GBitmap *offscreen = gbitmap_create_blank(desc.bounds.size, desc.format);
	gbitmap_set_bounds(offscreen, desc.bounds);

	// Select bitmap to context
	offscreen_select(frame, offscreen);

	// Draw offscreen
	handler(context, arg);

	// End
	offscreen_end(frame, &desc);

	// Transfer
	graphics_context_set_compositing_mode(context, GCompOpAssign);
	graphics_draw_bitmap_in_rect(context, offscreen, desc.bounds);
	
	gbitmap_destroy(offscreen);

}
