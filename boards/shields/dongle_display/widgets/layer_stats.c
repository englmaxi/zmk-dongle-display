/*
 * Copyright (c) 2020 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

#include <zmk/display.h>
#include <zmk/display/widgets/layer_stats.h>
#include <zmk/events/layer_state_changed.h>
#include <zmk/event_manager.h>
#include <zmk/endpoints.h>
#include <zmk/keymap.h>

static sys_slist_t widgets = SYS_SLIST_STATIC_INIT(&widgets);

struct layer_stats_state {
    uint8_t index;
    const char *label;
};

static void set_layer_symbol(lv_obj_t *label, struct layer_stats_state state) {
    if (state.label == NULL) {
        char text[7] = {};

        sprintf(text, "%i", state.index);

        lv_label_set_text(label, text);
    } else {
        char text[13] = {};

        snprintf(text, sizeof(text), "%s", state.label);

        lv_label_set_text(label, text);
    }
}

static void layer_stats_update_cb(struct layer_stats_state state) {
    struct zmk_widget_layer_stats *widget;
    SYS_SLIST_FOR_EACH_CONTAINER(&widgets, widget, node) { set_layer_symbol(widget->obj, state); }
}

static struct layer_stats_state layer_stats_get_state(const zmk_event_t *eh) {
    uint8_t index = zmk_keymap_highest_layer_active();
    return (struct layer_stats_state) {
        .index = index,
        .label = zmk_keymap_layer_name(index)
    };
}

ZMK_DISPLAY_WIDGET_LISTENER(widget_layer_stats, struct layer_stats_state, layer_stats_update_cb,
                            layer_stats_get_state)

ZMK_SUBSCRIPTION(widget_layer_stats, zmk_layer_state_changed);

int zmk_widget_layer_stats_init(struct zmk_widget_layer_stats *widget, lv_obj_t *parent) {
    widget->obj = lv_label_create(parent);

    sys_slist_append(&widgets, &widget->node);

    widget_layer_stats_init();
    return 0;
}

lv_obj_t *zmk_widget_layer_stats_obj(struct zmk_widget_layer_stats *widget) {
    return widget->obj;
}