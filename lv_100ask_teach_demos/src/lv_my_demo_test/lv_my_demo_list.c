#include "../../lv_100ask_teach_demos.h"

#if LV_MY_DEMO_LIST
#include "lv_my_demo_list.h"
#include <time.h>

typedef struct lv_my_demo_list_t{
    lv_obj_t* list_parent;
} lv_my_demo_list_t;

lv_my_demo_list_t lv_my_demo_list_x;

static lv_style_t label_box_style;

void lable_style_init(void)
{
    lv_style_init(&label_box_style);
    lv_style_set_width(&label_box_style, LV_PCT(100));
    lv_style_set_height(&label_box_style, LV_PCT(20));
    lv_style_set_border_color(&label_box_style, lv_color_hex(0xff181818));
}

static lv_obj_t* create_lable_obj(lv_obj_t* parent)
{
    lv_obj_t* label_box =  lv_obj_create(parent);
    lv_obj_add_style(label_box, &label_box_style, LV_PART_MAIN);
    lv_label_t* label = lv_label_create(label_box);
    lv_obj_set_size(label, LV_PCT(80), LV_PCT(100));
    return label_box;
}

static lv_obj_t* clone_label_obj(lv_obj_t* label, lv_align_t align)
{
    lv_obj_t* parent = lv_obj_get_parent(label);
    uint32_t id = lv_obj_get_child_id(parent);
    lv_obj_t* obj = lv_obj_get_child(parent, id-1);
    lv_obj_t* clone = create_lable_obj(parent);
    lv_obj_align_to(clone, obj, align, 0, 10);
    return clone;
}

void label_event_cb(lv_event_t * e)
{
    lv_obj_t* obj = lv_event_get_target(e);
    uint32_t i = lv_event_get_user_data(e);
    lv_event_code_t event = lv_event_get_code(e);
    lv_label_t* label = lv_obj_get_child(obj, 0);

    switch (event)
    {
    case LV_EVENT_PRESSED:
        lv_label_set_text_fmt(label, "LV_EVENT_PRESSED label %d\n", i);
        lv_obj_set_style_bg_color(obj, lv_palette_main(LV_PALETTE_RED), 0);
        break;
    case LV_EVENT_PRESSING:
        lv_label_set_text_fmt(label, "LV_EVENT_PRESSING label %d\n", i);
        lv_obj_set_style_bg_color(obj, lv_palette_main(LV_PALETTE_LIGHT_BLUE), 0);
        break;
    case LV_EVENT_CLICKED:
        lv_label_set_text_fmt(label, "LV_EVENT_CLICKED label %d\n", i);
        lv_obj_set_style_bg_color(obj, lv_palette_main(LV_PALETTE_LIGHT_GREEN), 0);
        break;
    case LV_EVENT_LONG_PRESSED:
        lv_label_set_text_fmt(label, "LV_EVENT_LONG_PRESSED label %d\n", i);
        lv_obj_set_style_bg_color(obj, lv_palette_main(LV_PALETTE_DEEP_ORANGE), 0);
        break;
    default:
        break;
    }
}

void lv_my_demo_list(void)
{
    lv_my_demo_list_t* ctx = &lv_my_demo_list_x;
    ctx->list_parent = lv_obj_create(lv_scr_act());
    lv_obj_set_size(ctx->list_parent, LV_PCT(100), LV_PCT(100));
    lv_obj_align(ctx->list_parent, LV_ALIGN_CENTER, 0, 0);
    lable_style_init();
    lv_obj_t* label1 = create_lable_obj(ctx->list_parent);
    for (uint8_t i = 0; i < 10; i++) {
        lv_obj_t* obj = clone_label_obj(label1, LV_ALIGN_OUT_BOTTOM_MID);
        lv_label_t* label = lv_obj_get_child(obj, 0);
        lv_label_set_text_fmt(label, "list label%d\n", i);
    }
    uint32_t cnt = lv_obj_get_child_cnt(ctx->list_parent);
    for (uint8_t i = 0; i < cnt; i++){
        lv_obj_t* obj = lv_obj_get_child(ctx->list_parent, i);
        lv_obj_add_event_cb(obj, label_event_cb, LV_EVENT_ALL, (void*)i);
    }
}

#endif
