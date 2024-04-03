#include "../../lv_100ask_teach_demos.h"
#if LV_MY_DEMO_1
#include "lv_my_demo_test.h"
#define COLOR_RED lv_color_hex(0xFFFF0000)
#define COLOR_GREEN lv_color_hex(0xFF008000)
#define COLOR_BLUE lv_color_hex(0xFF0000FF)
#define COLOR_WHITE lv_color_hex(0xFFFFFFFF)
typedef enum {
    BLOCK1,
    BLOCK2,
    BLOCK3,
    BLOCK4,
    BLOCK_MAX
}obj_count;

typedef struct my_demo_config_x{
    lv_obj_t* obj[BLOCK_MAX];
}my_demo_config_t;
lv_style_t style[BLOCK_MAX];
my_demo_config_t my_demo_config;

void setting_bg_color(lv_style_t* style, uint8_t cnt)
{
    lv_color_t c;
    switch (cnt)
    {
    case 1:
        lv_style_set_bg_color(style, COLOR_RED);
        break;
    case 2:
        lv_style_set_bg_color(style, COLOR_GREEN);
        break;
    case 3:
        lv_style_set_bg_color(style, COLOR_BLUE);
        break;
    case 4:
        lv_style_set_bg_color(style, COLOR_WHITE);
        break;
    default:
        break;
    }
}

void my_demo_test_timer(lv_timer_t* timer)
{
    my_demo_config_t* ctx = &my_demo_config;
    static uint8_t cnt = 0;
    for (int i = 0; i < BLOCK_MAX; i++) {
        setting_bg_color(&style[i], cnt%5);
    }
    cnt++;
    printf("[my_demo_test_timer] cnt %d\n", cnt);
}

void lv_my_demo_1()
{
    my_demo_config_t* ctx = &my_demo_config;
    // lv_obj_t* windows = lv_scr_act();
    // lv_obj_t* block1 = lv_obj_create(windows);
    for (int i = 0; i < BLOCK_MAX; i++) {
        ctx->obj[i] = lv_obj_create(lv_scr_act());
        lv_obj_t* label = lv_label_create(ctx->obj[i]);
        lv_label_set_text_fmt(label, "block%d", i);
        lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
    }

    lv_obj_set_size(ctx->obj[BLOCK1], LV_PCT(50), LV_PCT(50));
    lv_obj_align(ctx->obj[BLOCK1], LV_ALIGN_TOP_LEFT, 0, 0);
    lv_obj_set_size(ctx->obj[BLOCK2], LV_PCT(50), LV_PCT(50));
    lv_obj_align(ctx->obj[BLOCK2], LV_ALIGN_TOP_RIGHT, 0, 0);
    lv_obj_set_size(ctx->obj[BLOCK3], LV_PCT(50), LV_PCT(50));
    lv_obj_align(ctx->obj[BLOCK3], LV_ALIGN_BOTTOM_LEFT, 0, 0);
    lv_obj_set_size(ctx->obj[BLOCK4], LV_PCT(50), LV_PCT(50));
    lv_obj_align(ctx->obj[BLOCK4], LV_ALIGN_BOTTOM_RIGHT, 0, 0);

    lv_style_init(&style[BLOCK1]);
    lv_style_set_bg_color(&style[BLOCK1], COLOR_RED);
    lv_style_init(&style[BLOCK2]);
    lv_style_set_bg_color(&style[BLOCK2], COLOR_GREEN);
    lv_style_init(&style[BLOCK3]);
    lv_style_set_bg_color(&style[BLOCK3], COLOR_BLUE);
    lv_style_init(&style[BLOCK4]);
    lv_style_set_bg_color(&style[BLOCK4], COLOR_WHITE);

    for (int i = 0; i < BLOCK_MAX; i++) {
        lv_obj_add_style(ctx->obj[i], &style[i], LV_PART_MAIN);
    }
    lv_timer_create(my_demo_test_timer, 100, NULL);

}
#endif
