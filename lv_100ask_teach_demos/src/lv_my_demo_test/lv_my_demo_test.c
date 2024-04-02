#include "../../lv_100ask_teach_demos.h"
#if LV_MY_DEMO_1
#include "lv_my_demo_test.h"
#define COLOR_RED lv_color_hex(0xFFFF0000)
#define COLOR_GREEN lv_color_hex(0xFF008000)
#define COLOR_BLUE lv_color_hex(0xFF0000FF)
#define COLOR_WHITE lv_color_hex(0xFFFFFFFF)
typedef enum {
    FUNC1,
    FUNC2,
    FUNC3,
    FUNC4,
    FUNC_MAX
}obj_count;

typedef struct my_demo_config_x{
    lv_obj_t* obj[FUNC_MAX];
}my_demo_config_t;
lv_style_t style[FUNC_MAX];
my_demo_config_t my_demo_config;

void lv_my_demo_1()
{
    my_demo_config_t* ctx = &my_demo_config;
    // lv_obj_t* windows = lv_scr_act();
    // lv_obj_t* block1 = lv_obj_create(windows);
    for (int i = 0; i < FUNC_MAX; i++) {
        ctx->obj[i] = lv_obj_create(lv_scr_act());
        lv_obj_t* label = lv_label_create(ctx->obj[i]);
        lv_label_set_text_fmt(label, "block%d", i);
        lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
    }

    lv_obj_set_size(ctx->obj[FUNC1], LV_PCT(50), LV_PCT(50));
    lv_obj_align(ctx->obj[FUNC1], LV_ALIGN_TOP_LEFT, 0, 0);
    lv_obj_set_size(ctx->obj[FUNC2], LV_PCT(50), LV_PCT(50));
    lv_obj_align(ctx->obj[FUNC2], LV_ALIGN_TOP_RIGHT, 0, 0);
    lv_obj_set_size(ctx->obj[FUNC3], LV_PCT(50), LV_PCT(50));
    lv_obj_align(ctx->obj[FUNC3], LV_ALIGN_BOTTOM_LEFT, 0, 0);
    lv_obj_set_size(ctx->obj[FUNC4], LV_PCT(50), LV_PCT(50));
    lv_obj_align(ctx->obj[FUNC4], LV_ALIGN_BOTTOM_RIGHT, 0, 0);

    lv_style_init(&style[FUNC1]);
    lv_style_set_bg_color(&style[FUNC1], COLOR_RED);
    lv_style_init(&style[FUNC2]);
    lv_style_set_bg_color(&style[FUNC2], COLOR_GREEN);
    lv_style_init(&style[FUNC3]);
    lv_style_set_bg_color(&style[FUNC3], COLOR_BLUE);
    lv_style_init(&style[FUNC4]);
    lv_style_set_bg_color(&style[FUNC4], COLOR_WHITE);

    for (int i = 0; i < FUNC_MAX; i++) {
        lv_obj_add_style(ctx->obj[i], &style[i], LV_PART_MAIN);
    }

}
#endif