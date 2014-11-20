#include "blub.h"
#include <pebble.h>

static Window *s_window_endday;
static TextLayer *s_endday_layer;
static TextLayer *s_endday_yes_layer;
static TextLayer *s_endday_no_layer;

bool *bThisDoEndDay;

static void window_endday_initialise_ui(void) {
    app_log(APP_LOG_LEVEL_DEBUG,  __FILE_NAME__, __LINE__, "initialise_ui");
    
    s_window_endday = window_create();
    window_set_fullscreen(s_window_endday, true);
    
    // Summery layers
    s_endday_layer = text_layer_create(GRect(0,60, 144, 100));
    text_layer_set_background_color(s_endday_layer, GColorClear);
    text_layer_set_text_color(s_endday_layer, GColorBlack);
    text_layer_set_font(s_endday_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
    text_layer_set_text_alignment(s_endday_layer, GTextAlignmentCenter);
    text_layer_set_text(s_endday_layer, "End of day\n???");
    
    s_endday_yes_layer = text_layer_create(GRect(0,3, 140, 20));
    text_layer_set_background_color(s_endday_yes_layer, GColorClear);
    text_layer_set_text_color(s_endday_yes_layer, GColorBlack);
    text_layer_set_font(s_endday_yes_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
    text_layer_set_text_alignment(s_endday_yes_layer, GTextAlignmentRight);
    text_layer_set_text(s_endday_yes_layer, "Yes");
    
    s_endday_no_layer = text_layer_create(GRect(0,140, 140, 20));
    text_layer_set_background_color(s_endday_no_layer, GColorClear);
    text_layer_set_text_color(s_endday_no_layer, GColorBlack);
    text_layer_set_font(s_endday_no_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
    text_layer_set_text_alignment(s_endday_no_layer, GTextAlignmentRight);
    text_layer_set_text(s_endday_no_layer, "No");
    
    layer_add_child(window_get_root_layer(s_window_endday), text_layer_get_layer(s_endday_layer));
    layer_add_child(window_get_root_layer(s_window_endday), text_layer_get_layer(s_endday_yes_layer));
    layer_add_child(window_get_root_layer(s_window_endday), text_layer_get_layer(s_endday_no_layer));
}

static void window_endday_destroy_ui(void) {
    app_log(APP_LOG_LEVEL_DEBUG,  __FILE_NAME__, __LINE__, "destroy_ui");
    
    window_destroy(s_window_endday);
    text_layer_destroy(s_endday_layer);
    text_layer_destroy(s_endday_yes_layer);
    text_layer_destroy(s_endday_no_layer);
}

static void window_endday_handle_window_unload(Window* window) {
    app_log(APP_LOG_LEVEL_DEBUG,  __FILE_NAME__, __LINE__, "handle_window_unload");
    
    window_endday_destroy_ui();
}

void select_click_handler_endday_window(ClickRecognizerRef recognizer, void *context) {
    app_log(APP_LOG_LEVEL_DEBUG,  __FILE_NAME__, __LINE__, "select_click_handler_endday_window");
 
    const uint16_t button = click_recognizer_get_button_id(recognizer);
    
    if(button==BUTTON_ID_UP)
    {
        *bThisDoEndDay = true;
        app_log(APP_LOG_LEVEL_DEBUG,  __FILE_NAME__, __LINE__, "UP");
        hide_blub();
    }
    else if(button==BUTTON_ID_DOWN)
    {
        *bThisDoEndDay = false;
        app_log(APP_LOG_LEVEL_DEBUG,  __FILE_NAME__, __LINE__, "DOWN");
        hide_blub();
    }
    else if(button==BUTTON_ID_BACK)
    {
        // Do nothing
    }
}

void window_endday_config_provider(void *context) {
    app_log(APP_LOG_LEVEL_DEBUG,  __FILE_NAME__, __LINE__, "window_endday_config_provider");
    
    window_single_click_subscribe(BUTTON_ID_UP, select_click_handler_endday_window);
    window_single_click_subscribe(BUTTON_ID_DOWN, select_click_handler_endday_window);
}

void show_blub(bool *bDoEndDay) {
    app_log(APP_LOG_LEVEL_DEBUG,  __FILE_NAME__, __LINE__, "show_window_endday");
    window_endday_initialise_ui();
    
    window_set_window_handlers(s_window_endday, (WindowHandlers) {
        .unload = window_endday_handle_window_unload,
    });
    
    bThisDoEndDay = bDoEndDay;
    
    window_set_click_config_provider(s_window_endday, window_endday_config_provider);
    
    window_stack_push(s_window_endday, true);
}

void hide_blub(void) {
    app_log(APP_LOG_LEVEL_DEBUG,  __FILE_NAME__, __LINE__, "hide_window_endday");
    window_stack_remove(s_window_endday, true);
}
