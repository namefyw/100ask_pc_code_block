#include "../../lv_100ask_teach_demos.h"
#if LV_MY_DEMO_1
#include "lv_my_demo_test.h"
#define COLOR_RED lv_color_hex(0xFFFF0000)
#define COLOR_GREEN lv_color_hex(0xFF008000)
#define COLOR_BLUE lv_color_hex(0xFF0000FF)
#define COLOR_WHITE lv_color_hex(0xFFFFFFFF)
static lv_style_t style1, style2, style3, style4;
// lv_style_t style1, style2, style3, style4;
void lv_my_demo_1()
{
    // lv_obj_t* windows = lv_scr_act();
    // lv_obj_t* block1 = lv_obj_create(windows);
    lv_obj_t* block1 = lv_obj_create(lv_scr_act());
    lv_obj_t* block2 = lv_obj_create(lv_scr_act());
    lv_obj_t* block3 = lv_obj_create(lv_scr_act());
    lv_obj_t* block4 = lv_obj_create(lv_scr_act());

    lv_obj_set_size(block1, LV_PCT(50), LV_PCT(50));
    lv_obj_align(block1, LV_ALIGN_TOP_LEFT, 0, 0);
    lv_obj_set_size(block2, LV_PCT(50), LV_PCT(50));
    lv_obj_align(block2, LV_ALIGN_TOP_RIGHT, 0, 0);
    lv_obj_set_size(block3, LV_PCT(50), LV_PCT(50));
    lv_obj_align(block3, LV_ALIGN_BOTTOM_LEFT, 0, 0);
    lv_obj_set_size(block4, LV_PCT(50), LV_PCT(50));
    lv_obj_align(block4, LV_ALIGN_BOTTOM_RIGHT, 0, 0);

    lv_obj_t* label1 = lv_label_create(block1);
    lv_obj_t* label2 = lv_label_create(block2);
    lv_obj_t* label3 = lv_label_create(block3);
    lv_obj_t* label4 = lv_label_create(block4);

    lv_label_set_text(label1, "block1");
    lv_obj_align(label1, LV_ALIGN_CENTER, 0, 0);
    lv_label_set_text(label2, "block2");
    lv_obj_align(label2, LV_ALIGN_CENTER, 0, 0);
    lv_label_set_text(label3, "block3");
    lv_obj_align(label3, LV_ALIGN_CENTER, 0, 0);
    lv_label_set_text(label4, "block4");
    lv_obj_align(label4, LV_ALIGN_CENTER, 0, 0);


    lv_style_init(&style1);
    lv_style_set_bg_color(&style1, COLOR_RED);
    lv_style_init(&style2);
    lv_style_set_bg_color(&style2, COLOR_GREEN);
    lv_style_init(&style3);
    lv_style_set_bg_color(&style3, COLOR_BLUE);
    lv_style_init(&style4);
    lv_style_set_bg_color(&style4, COLOR_WHITE);

    lv_obj_add_style(block1, &style1, LV_PART_MAIN);
    lv_obj_add_style(block2, &style2, LV_PART_MAIN);
    lv_obj_add_style(block3, &style3, LV_PART_MAIN);
    lv_obj_add_style(block4, &style4, LV_PART_MAIN);

}
#endif