#include <pebble.h>

Window *window;
TextLayer *text_layer;
int step = 0;


static void tap_handler(AccelAxisType axis, int32_t direction) {
	step = step + 1;
	static char* step_text = "Steps: XXXXXXXX";
	snprintf(step_text, sizeof(step_text), "Steps: %d", step);
	text_layer_set_text(text_layer, step_text);
// 	switch (axis) {
//   case ACCEL_AXIS_X:
//     if (direction > 0) {
//       APP_LOG(APP_LOG_LEVEL_INFO, "X axis positive.");
//     } else {
//       APP_LOG(APP_LOG_LEVEL_INFO, "X axis negative.");
//     }
//     break;
//   case ACCEL_AXIS_Y:
//     if (direction > 0) {
//       APP_LOG(APP_LOG_LEVEL_INFO, "Y axis positive.");
//     } else {
//       APP_LOG(APP_LOG_LEVEL_INFO, "Y axis negative.");
//     }
//     break;
//   case ACCEL_AXIS_Z:
//     if (direction > 0) {
//       APP_LOG(APP_LOG_LEVEL_INFO, "Z axis positive.");
//     } else {
//       APP_LOG(APP_LOG_LEVEL_INFO, "Z axis negative.");
//     }
//     break;
//   }
}

void handle_init(void) {
	accel_tap_service_subscribe(tap_handler);
	// Create a window and text layer
	window = window_create();
	text_layer = text_layer_create(GRect(0, 0, 144, 154));
	
	// Set the text, font, and text alignment
	text_layer_set_text(text_layer, "Hi, I'm a Pebble!");
	text_layer_set_font(text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
	text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
	
	// Add the text layer to the window
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(text_layer));

	// Push the window
	window_stack_push(window, true);
	
	// App Logging!
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Just pushed a window!");
}

void handle_deinit(void) {
	// Destroy the text layer
	text_layer_destroy(text_layer);
	
	// Destroy the window
	window_destroy(window);
}

int main(void) {
	handle_init();
	app_event_loop();
	handle_deinit();
}
