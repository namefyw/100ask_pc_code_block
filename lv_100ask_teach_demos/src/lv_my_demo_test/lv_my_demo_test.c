#include "../../lv_100ask_teach_demos.h"
#if LV_MY_DEMO_1
#include "lv_my_demo_test.h"
#include <time.h>

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
    lv_obj_t* block[BLOCK_MAX];
    lv_obj_t* label[BLOCK_MAX];
}my_demo_config_t;
lv_style_t block_style[BLOCK_MAX];
my_demo_config_t my_demo_config;

void setting_bg_color(lv_style_t* block_style, uint8_t cnt)
{
    static uint32_t color_hex = 0xFF000000;
    lv_color_t c;
    uint8_t s_cnt = cnt%4;
    printf("[setting_bg_color] s_cnt %d, cnt %d\n", s_cnt, cnt);
    switch (s_cnt) {
        case 0:
            lv_style_set_bg_color(block_style, COLOR_RED);
            break;
        case 1:
            lv_style_set_bg_color(block_style, COLOR_GREEN);
            break;
        case 2:
            lv_style_set_bg_color(block_style, COLOR_BLUE);
            break;
        case 3:
            lv_style_set_bg_color(block_style, COLOR_WHITE);
            break;
        default:
            lv_style_set_bg_color(block_style, lv_color_hex(color_hex));
            break;
    }
    color_hex += 0xFF;
    // printf("color_hex 0x%x\n", color_hex);
    if (color_hex > 0xFFFFFFFF) {
        color_hex = 0xFF000000;
    }
}

void my_demo_test_timer(lv_timer_t* timer)
{
    my_demo_config_t* ctx = &my_demo_config;
    static uint8_t cnt = 0;
    time_t now = time(NULL);
    struct tm *local_time = localtime(&now);
    printf("switch bg_color, now: %04d-%02d-%02d %02d:%02d:%02d\n",\
             local_time->tm_year+1900, local_time->tm_mon+1, local_time->tm_mday,\
             local_time->tm_hour, local_time->tm_min, local_time->tm_sec);
    for (int i = 0; i < BLOCK_MAX; i++) {
        setting_bg_color(&block_style[i], cnt);
    cnt++;
    }
    cnt++;
}

void lv_my_demo_1()
{
    my_demo_config_t* ctx = &my_demo_config;
    // lv_obj_t* windows = lv_scr_act();
    // lv_obj_t* block1 = lv_obj_create(windows);
    for (int i = 0; i < BLOCK_MAX; i++) {
        ctx->block[i] = lv_obj_create(lv_scr_act());
        lv_obj_set_size(ctx->block[i], LV_PCT(50), LV_PCT(50));
        ctx->label[i] = lv_label_create(ctx->block[i]);
        lv_label_set_text_fmt(ctx->label[i], "block%d", i);

    }

    lv_obj_align(ctx->block[BLOCK1], LV_ALIGN_TOP_LEFT, 0, 0);
    lv_obj_align(ctx->block[BLOCK2], LV_ALIGN_TOP_RIGHT, 0, 0);
    lv_obj_align(ctx->block[BLOCK3], LV_ALIGN_BOTTOM_RIGHT, 0, 0);
    lv_obj_align(ctx->block[BLOCK4], LV_ALIGN_BOTTOM_LEFT, 0, 0);

    for (int i = 0; i < BLOCK_MAX; i++) {
        lv_obj_align(ctx->label[i], LV_ALIGN_CENTER, 0, 0);
        lv_style_init(&block_style[i]);
        setting_bg_color(&block_style[i], i);
        lv_obj_add_style(ctx->block[i], &block_style[i], LV_PART_MAIN);
    }
    lv_timer_create(my_demo_test_timer, 1000, NULL);

}
#endif
