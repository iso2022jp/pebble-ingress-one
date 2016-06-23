/* This software is released under the MIT License, see LICENSE */

// #include "modules/vector.h"

// typedef struct {
// 	GSize from;
// 	GSize to;
// } ScaleContext;

// static bool scale_image_callback(GDrawCommand *command, uint32_t index, void *context) {

// 	const ScaleContext *const scale = context;
// 	const int points = gdraw_command_get_num_points(command);

// 	for (int i = 0; i < points; ++i) {
// 		GPoint p = gdraw_command_get_point(command, i);
// 		p.x = p.x * scale->to.w / scale->from.w;
// 		p.y = p.y * scale->to.h / scale->from.h;
// 		gdraw_command_set_point(command, i, p);
// 		APP_LOG(APP_LOG_LEVEL_DEBUG, "Scaled: (%d, %d)", p.x, p.y);
// 	}
	
// 	if (gdraw_command_get_type(command) == GDrawCommandTypeCircle) {
// 		const uint16_t radius = gdraw_command_get_radius(command);
// 		gdraw_command_set_radius(command, radius * scale->to.w / scale->from.w); // TODO
// 	}

// 	return true;

// }

// //
// // Module
// //

// void vector_scale_image(GDrawCommandImage *image, GSize size) {

// 	GDrawCommandList *list = gdraw_command_image_get_command_list(image);
// 	GSize original = gdraw_command_image_get_bounds_size(image);

// 	ScaleContext context = {
// 		.from = original,
// 		.to = size,
// 	};

// 	gdraw_command_list_iterate(list, scale_image_callback, &context);
// 	gdraw_command_image_set_bounds_size(image, size);

// }
