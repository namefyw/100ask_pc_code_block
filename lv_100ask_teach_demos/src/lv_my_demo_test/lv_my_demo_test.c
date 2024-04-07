#include "../../lv_100ask_teach_demos.h"
#if LV_MY_DEMO_1
#include "lv_my_demo_test.h"
#include <time.h>
#include <stdbool.h>

#define BLOCK_BG_SET    true

#define COLOR_SWITCH(color) lv_color_hex(color_t[color])
#define DEFAULE_COLOR_HEX   0x8B0000

typedef enum {
    COLOR_RED,
    COLOR_GREEN,
    COLOR_BLUE,
    COLOR_WHITE,
    COLOR_PINK,
    COLOR_BLACK,
    COLOR_MAX
}color_cnt;

uint32_t color_t[COLOR_MAX] = {
    [COLOR_RED]     = 0xFFFF0000,
    [COLOR_GREEN]   = 0xFF008000,
    [COLOR_BLUE]    = 0xFF0000FF,
    [COLOR_WHITE]   = 0xFFFFFFFF,
    [COLOR_BLACK]   = 0x00000000,
    [COLOR_PINK]    = 0xFFFFC0CB,
};

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
    // lv_obj_t* test_box[BLOCK_MAX];
    lv_timer_t* timer1;
    lv_style_t block_style[BLOCK_MAX];  //生命周期的问题所以不能用局部变量，若要使用局部变量只能使用局部静态变量
} my_demo_config_t;

my_demo_config_t my_demo_config;
uint16_t timer_ms;

void setting_bg_color(lv_style_t* block_style, color_cnt cnt)
{
    my_demo_config_t* ctx = &my_demo_config;
    printf("[%s] cnt %d\n",__FUNCTION__, cnt);
    switch (cnt) {
        case COLOR_RED:
            lv_style_set_bg_color(block_style, COLOR_SWITCH(COLOR_RED));    /* 该函数用于可以变换的UI风格 */
            break;
        case COLOR_GREEN:
            lv_style_set_bg_color(block_style, COLOR_SWITCH(COLOR_GREEN));
            break;
        case COLOR_BLUE:
            lv_style_set_bg_color(block_style, COLOR_SWITCH(COLOR_BLUE));
            break;
        case COLOR_WHITE:
            lv_style_set_bg_color(block_style, COLOR_SWITCH(COLOR_WHITE));
            break;
        case COLOR_BLACK:
            lv_style_set_bg_color(block_style, COLOR_SWITCH(COLOR_BLACK));
            break;
        default:
            break;
    }
#if 0
    if (cnt == 255) {
        timer_ms = timer_ms/10;
        if (timer_ms) {
            lv_timer_set_period(ctx->timer1, timer_ms);
        } else {
            lv_timer_pause(ctx->timer1);
        }
    }
#endif
}
/* 设置默认背景颜色 */
void setting_defautl_bg_color(lv_obj_t* obj, color_cnt cnt)
{
    my_demo_config_t* ctx = &my_demo_config;
    lv_color32_t color;
    printf("[%s] cnt %d\n",__FUNCTION__, cnt);
    switch (cnt) {
        case COLOR_RED:
            color = COLOR_SWITCH(COLOR_RED);
            break;
        case COLOR_GREEN:
            color = COLOR_SWITCH(COLOR_GREEN);
            break;
        case COLOR_BLUE:
            color = COLOR_SWITCH(COLOR_BLUE);
            break;
        case COLOR_WHITE:
            color = COLOR_SWITCH(COLOR_WHITE);
            break;
        case COLOR_PINK:
            color = COLOR_SWITCH(COLOR_PINK);
            break;
        case COLOR_BLACK:
            color = COLOR_SWITCH(COLOR_BLACK);
            break;
        default:
            color = lv_color_hex(DEFAULE_COLOR_HEX);
            break;
    }
    lv_obj_set_style_bg_color(obj, color, LV_PART_MAIN);
#if 0
    if (cnt == 255) {
        timer_ms = timer_ms/10;
        if (timer_ms) {
            lv_timer_set_period(ctx->timer1, timer_ms);
        } else {
            lv_timer_pause(ctx->timer1);
        }
    }
#endif
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
        /* 两个颜色的效果相同 */
        // setting_bg_color(&block_style[i], cnt%BLOCK_MAX);
        setting_defautl_bg_color(ctx->block[i], cnt%BLOCK_MAX);
    cnt++;
    }
    cnt++;
}

void lv_my_demo_1()
{
    my_demo_config_t* ctx = &my_demo_config;
    lv_obj_t* test;
    // lv_obj_t* windows = lv_scr_act();
    // lv_obj_t* block1 = lv_obj_create(windows);
    for (int i = 0; i < BLOCK_MAX; i++) {
        ctx->block[i] = lv_obj_create(lv_scr_act());
        lv_obj_set_size(ctx->block[i], LV_PCT(50), LV_PCT(50));
        // ctx->label[i] = lv_label_create(lv_scr_act());
        ctx->label[i] = lv_label_create(ctx->block[i]);
        lv_label_set_text_fmt(ctx->label[i], "block%d", i);
    }

    lv_obj_align(ctx->block[BLOCK1], LV_ALIGN_TOP_LEFT, 0, 0);
    lv_obj_align(ctx->block[BLOCK2], LV_ALIGN_TOP_RIGHT, 0, 0);
    lv_obj_align(ctx->block[BLOCK3], LV_ALIGN_BOTTOM_RIGHT, 0, 0);
    lv_obj_align(ctx->block[BLOCK4], LV_ALIGN_BOTTOM_LEFT, 0, 0);
    for (int i = 0; i < BLOCK_MAX; i++) {
        lv_obj_align_to(ctx->label[i], ctx->block[i], LV_ALIGN_CENTER, 0, 0);    /* 该方式可以打印出坐标, 但是打印出来的坐标是相对坐标 */
        // lv_obj_align(ctx->label[i], LV_ALIGN_CENTER, 0, 0); /* 该方式打印不出来坐标 */
        lv_style_init(&ctx->block_style[i]);
        setting_bg_color(&ctx->block_style[i], i);
        lv_style_set_border_color(&ctx->block_style[i], COLOR_SWITCH(COLOR_BLACK));
        lv_obj_add_style(ctx->block[i], &ctx->block_style[i], LV_STATE_PRESSED);
        setting_defautl_bg_color(ctx->block[i], COLOR_PINK);
    }

    timer_ms = 1000;
    // ctx->timer1 = lv_timer_create(my_demo_test_timer, timer_ms, NULL);
    for (int i = 0; i < BLOCK_MAX; i++) {
        printf("block[%d]:\r\n", i);
        printf_obj_data(ctx->block[i]);
        printf("label[%d]:\r\n", i);
        printf_obj_data(ctx->label[i]);
    }

}

/* test function */
void printf_obj_data(lv_obj_t* obj)
{
    printf("x:%d\n", lv_obj_get_x(obj));
    printf("y:%d\n", lv_obj_get_y(obj));
    printf("w:%d\n", lv_obj_get_width(obj));
    printf("h:%d\n", lv_obj_get_height(obj));
}
#endif
