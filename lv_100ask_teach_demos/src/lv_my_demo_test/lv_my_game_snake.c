#include "../../lv_100ask_teach_demos.h"

#if LV_MY_DEMO_GAME == 1
#include "lv_my_demo_game.h"
#include "lv_drivers/win32drv/win32drv.h" /* 使用键盘就必须要包含该头文件 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifndef LV_LOG
#define LV_LOG(...)
#endif

#define FOOD_SIZE 1

typedef struct game_snake
{
    lv_obj_t* view;
    lv_obj_t* food;
    uint16_t score;
    lv_timer_t* timer;
} lv_my_game_snake_t;

typedef enum {
    UP_KEY = 17,
    DOWN_KEY,
    RIGHT_KEY,
    LEFT_KEY,
} key_move_t;

lv_my_game_snake_t lv_game_snake_x;

void snake_add_size(lv_my_game_snake_t* ctx)
{
}

void snake_game_view_init()
{
    lv_my_game_snake_t* ctx = &lv_game_snake_x;
    ctx->view = lv_obj_create(lv_scr_act());
    lv_obj_set_size(ctx->view, LV_PCT(100), LV_PCT(100));
    ctx->food = lv_obj_create(ctx->view);
    lv_obj_set_style_bg_color(ctx->food, lv_color_hex(0), 0);
    lv_obj_set_size(ctx->food, LV_PCT(FOOD_SIZE), LV_PCT(FOOD_SIZE));
    LV_LOG("food size w = %d, h = %d\n", LV_PCT(FOOD_SIZE), LV_PCT(FOOD_SIZE));
    // lv_obj_set_style_x(ctx->food, 0, 0);
}

void snake_timer_cb(lv_timer_t* timer)
{
    lv_my_game_snake_t* ctx = timer->user_data;
    lv_coord_t x = rand()%100;
    lv_coord_t y = rand()%100;
    lv_obj_align_to(ctx->food, ctx->view, LV_ALIGN_TOP_LEFT, LV_PCT(x), LV_PCT(y));
    LV_LOG("x %d == %02d%, y %02d == %06d%\n", x, LV_PCT(x), y, LV_PCT(y));

}

void lv_my_demo_game(void)
{
    lv_my_game_snake_t* ctx = &lv_game_snake_x;
    snake_game_view_init();
    ctx->timer = lv_timer_create(snake_timer_cb, 1000, ctx);
}
#endif
