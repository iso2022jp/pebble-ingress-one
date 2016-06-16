/* This software is released under the MIT License, see LICENSE */

// #include "modules/offscreen.h"

// GBitmap *offscreen_create(GSize size) {
// 	return gbitmap_create_blank(size, PBL_IF_COLOR_ELSE(GBitmapFormat8Bit, GBitmapFormat1Bit));
// }

// int offscreen_draw(GContext *context, GBitmap *bitmap, OffscreenHandler handler, void *arg) {

// 	// get reference of frame buffer & lock
// 	GBitmap *frame = graphics_capture_frame_buffer(context);

// 	// keep buffer info
// 	uint8_t *data = gbitmap_get_data(frame);	
// 	GBitmapFormat format = gbitmap_get_format(frame);
// 	uint16_t stride = gbitmap_get_bytes_per_row(frame);	

// 	// release
// 	graphics_release_frame_buffer(context, frame);

// 	// keep buffer info
// 	uint8_t *d = gbitmap_get_data(bitmap);	
// 	GBitmapFormat f = gbitmap_get_format(bitmap);
// 	uint16_t s = gbitmap_get_bytes_per_row(bitmap);	

// 	// select offscreen buffer to context
// 	gbitmap_set_data(frame, d, f, s, false);

// 	// callback
// 	int result = handler(context, arg);

// 	// restore buffer
// 	gbitmap_set_data(frame, data, format, stride, false);

// 	return result;

// }
