#include <zephyr/kernel.h>

#include <zephyr/logging/log.h>
LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

#include <zmk/display.h>
#include <zmk/event_manager.h>
#include <zmk/events/wpm_state_changed.h>

#include "wpm_status.h"
//#include <fonts.h>

#ifndef LV_ATTRIBUTE_IMG_SPEEDOMETER
#define LV_ATTRIBUTE_IMG_SPEEDOMETER
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_SPEEDOMETER uint8_t speedometer_icon_map[] = {
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 0*/
  0x00, 0x00, 0x00, 0xff, 	/*Color of index 1*/

  0x00, 0x00, 
  0x00, 0x00, 
  0x00, 0x00, 
  0x0f, 0x80, 
  0x12, 0x40, 
  0x28, 0xa0, 
  0x40, 0x10, 
  0xa0, 0xa8, 
  0x81, 0x08, 
  0xc2, 0x18, 
  0x82, 0x08, 
  0x80, 0x08, 
  0x40, 0x10, 
  0x20, 0x20, 
};

const lv_img_dsc_t speedometer_icon = {
  .header.cf = LV_IMG_CF_INDEXED_1BIT,
  .header.always_zero = 0,
  .header.reserved = 0,
  .header.w = 14,
  .header.h = 14,
  .data_size = 36,
  .data = speedometer_icon_map,
};

static sys_slist_t widgets = SYS_SLIST_STATIC_INIT(&widgets);
struct wpm_status_state
{
    int wpm;
};

static struct wpm_status_state get_state(const zmk_event_t *_eh)
{
    const struct zmk_wpm_state_changed *ev = as_zmk_wpm_state_changed(_eh);

    return (struct wpm_status_state){
        .wpm = ev ? ev->state : 0};
}

static void set_wpm(struct zmk_widget_wpm_status *widget, struct wpm_status_state state)
{

    char wpm_text[12];
    snprintf(wpm_text, sizeof(wpm_text), "%i", state.wpm);
    lv_label_set_text(widget->wpm_label, wpm_text);
}

static void wpm_status_update_cb(struct wpm_status_state state)
{
    struct zmk_widget_wpm_status *widget;
    SYS_SLIST_FOR_EACH_CONTAINER(&widgets, widget, node)
    {
        set_wpm(widget, state);
    }
}

ZMK_DISPLAY_WIDGET_LISTENER(widget_wpm_status, struct wpm_status_state,
                            wpm_status_update_cb, get_state)
ZMK_SUBSCRIPTION(widget_wpm_status, zmk_wpm_state_changed);

// output_status.c
int zmk_widget_wpm_status_init(struct zmk_widget_wpm_status *widget, lv_obj_t *parent)
{
    widget->obj = lv_obj_create(parent);
    lv_obj_set_size(widget->obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);

    lv_obj_t *speedometer = lv_img_create(widget->obj);
    lv_obj_align(speedometer, LV_ALIGN_TOP_LEFT, 0, 0);
    lv_img_set_src(speedometer, &speedometer_icon);

    widget->wpm_label = lv_label_create(widget->obj);
    lv_obj_align_to(widget->wpm_label, speedometer, LV_ALIGN_OUT_RIGHT_MID, 2, 1);

    sys_slist_append(&widgets, &widget->node);

    widget_wpm_status_init();
    return 0;
}

lv_obj_t *zmk_widget_wpm_status_obj(struct zmk_widget_wpm_status *widget)
{
    return widget->obj;
}