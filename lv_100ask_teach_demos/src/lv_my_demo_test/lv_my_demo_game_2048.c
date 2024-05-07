#include "../../lv_100ask_teach_demos.h"

#if LV_MY_DEMO_GAME == 2048
#include "lv_my_demo_game.h"
#include "lv_drivers/win32drv/win32drv.h" /* 使用键盘就必须要包含该头文件 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define VIEW_SIZE 4
#define NUM_SIZE VIEW_SIZE*VIEW_SIZE
#define BLOCK_SIZE LV_PCT(100/VIEW_SIZE)
#define RANGE_JUDGMENT 80

#ifndef LV_LOG
#define LV_LOG(...)
#endif
typedef struct lv_my_demo_game_2048_t
{
    lv_obj_t* score_obj;
    lv_obj_t* view;
    lv_obj_t* max_score_obj;
    uint32_t score;
    uint32_t max_score;
    lv_point_t point;
    uint32_t num_data[NUM_SIZE];
    uint8_t num_size;
    // lv_indev_t* keypad;
    // lv_indev_t* touch;
    lv_group_t*  g;
} lv_my_demo_game_2048_t;

typedef enum {
    NONE_MOVE,
    LEFT_MOVE,
    RIGHT_MOVE,
    UP_MOVE,
    DOWN_MOVE,

/* 键盘控制的标志 */
    UP_KEY = 17,
    DOWN_KEY,
    RIGHT_KEY,
    LEFT_KEY,
} move_confg_t;


lv_my_demo_game_2048_t lv_my_demo_game_2048_x;


void update_rand_num(uint32_t* array, uint8_t size, uint8_t cnt);

static void view_obj_init(lv_obj_t* view)
{
    lv_my_demo_game_2048_t* ctx = &lv_my_demo_game_2048_x;
    while (lv_obj_get_child_cnt(view) < NUM_SIZE )
    {
        uint8_t num = lv_obj_get_child_cnt(view);
        lv_obj_t* obj = lv_obj_create(view);
        lv_label_t* label = lv_label_create(obj);
        lv_obj_add_flag(obj, LV_OBJ_FLAG_EVENT_BUBBLE);
        lv_obj_set_size(obj, LV_PCT(100/VIEW_SIZE), LV_PCT(100/VIEW_SIZE));
        if (num % 4) {
            lv_obj_align_to(obj, lv_obj_get_child(view, num-1), LV_ALIGN_OUT_RIGHT_MID, 0, 0);
        } else if (num){
            lv_obj_align_to(obj, lv_obj_get_child(view, num - 4), LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
        }

        lv_label_set_text_fmt(label, "%d", ctx->num_data[num]);
        lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, 0);
        lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
    }
}

void refresh_screen_view()
{
    lv_my_demo_game_2048_t* ctx = &lv_my_demo_game_2048_x;
    uint8_t cnt = lv_obj_get_child_cnt(ctx->view);
    LV_LOG("Updata view\n");
    for (uint8_t i = 0; i < cnt; i++) {
        lv_obj_t* obj = lv_obj_get_child(ctx->view, i);
        lv_label_t* label = lv_obj_get_child(obj, 0);
        // LV_LOG("obj %p, label %p\n", obj, label);
        lv_obj_set_style_bg_color(obj, lv_color_hex(~ctx->num_data[i]), 0);
        lv_label_set_text_fmt(label, "%d", ctx->num_data[i]);
    }
}

void printf_num_s(uint32_t* array)
{
    uint32_t* ary = NULL;
    lv_my_demo_game_2048_t* ctx = &lv_my_demo_game_2048_x;
    if (array == NULL) {
        ary = ctx->num_data;
    } else {
        ary = array;
    }
    for (uint8_t i = 0; i < 16; i++) {
        if (i > 0 && (i % 4) == 0) {
            LV_LOG_W("\n");
        }
        // LV_LOG_W("[%d]%d %p", i, ary[i], &ary[i]);
        LV_LOG_W("[%d]", ary[i]);
    }
    LV_LOG_W("\n");
    LV_LOG_W("_____________________\n");
}

bool right_move_view(uint32_t* array, uint8_t size, uint8_t index)
{
    bool ret = false;
    uint32_t* flag = NULL;

    // 向右合并相同的数字
    for (int8_t i = size - 1; i >= 0; i--) {
        if (flag) {
            if (*flag == array[i]) {
                *flag += array[i];
                array[i] = 0;
                flag = NULL;
                ret = true;
            } else if (array[i] > 0){
                flag = &array[i];
            }
        } else if(array[i] > 0) {
            flag = &array[i];
        }
        if ((i % 4) == 0) {
            flag = NULL;
        }
    }

    // 向右移动非零的数字
    flag = NULL;
    for (int8_t i = size - 1; i >= 0; i--) {
        if (flag) {
            if (array[i] > 0) {
                *flag = array[i];
                array[i] = 0;
                if ((i + 1) % 4 != 0) {
                    flag = &array[i+1];
                }
                ret = true;
            }
        } else if(array[i] == 0) {
            flag = &array[i];
        }
        if ((i % 4) == 0) {
            flag = NULL;
        }
    }

    return ret;
}

bool left_move_view(uint32_t* array, uint8_t size, uint8_t index)
{
    bool ret = false;
    uint32_t* flag = NULL;

    for (uint8_t row = 0; row < 4; row++) {
        flag = NULL;
        for (uint8_t col = 0; col < 4; col++) {
            uint8_t i = row * 4 + col;
            if (flag) {
                if (*flag == array[i] && array[i] != 0) {
                    *flag += array[i];
                    array[i] = 0;
                    flag = NULL;
                    ret = true;
                } else if (array[i] > 0) {
                    flag = &array[i];
                }
            } else if (array[i] > 0) {
                flag = &array[i];
            }
        }
    }

    // 向左移动非零的数字
    for (uint8_t row = 0; row < 4; row++) {
        flag = NULL;
        for (uint8_t col = 0; col < 4; col++) {
            uint8_t i = row * 4 + col;
            if (flag) {
                if (array[i] > 0) {
                    *flag = array[i];
                    array[i] = 0;
                    if (col > 0) {
                        flag = &array[row * 4 + col - 1];
                    }
                    ret = true;
                }
            } else if (array[i] == 0) {
                flag = &array[i];
            }
        }
    }

    return ret;
}

bool up_move_view(uint32_t* array, uint8_t size, uint8_t index)
{
    bool ret = false;
    uint32_t* flag = NULL;

    // 向上合并相同的数字
    for (uint8_t col = 0; col < 4; col++) {
        flag = NULL;
        for (int8_t row = 0; row < 4; row++) {
            uint8_t i = row * 4 + col;
            if (flag) {
                if (*flag == array[i] && array[i] != 0) {
                    *flag += array[i];
                    array[i] = 0;
                    flag = NULL;
                    ret = true;
                } else if (array[i] > 0) {
                    flag = &array[i];
                }
            } else if (array[i] > 0) {
                flag = &array[i];
            }
        }
    }

    // 向上移动非零的数字
    for (uint8_t col = 0; col < 4; col++) {
        flag = NULL;
        for (int8_t row = 0; row < 4; row++) {
            uint8_t i = row * 4 + col;
            if (flag) {
                if (array[i] > 0) {
                    *flag = array[i];
                    array[i] = 0;
                    if (row > 0) {
                        flag = &array[(row - 1) * 4 + col];
                    }
                    ret = true;
                }
            } else if (array[i] == 0) {
                flag = &array[i];
            }
        }
    }

    return ret;
}

bool down_move_view(uint32_t* array, uint8_t size, uint8_t index)
{
    bool ret = false;
    uint32_t* flag = NULL;

    // 向下合并相同的数字
    for (int8_t col = 0; col < 4; col++) {
        flag = NULL;
        for (int8_t row = 3; row >= 0; row--) {
            uint8_t i = row * 4 + col;
            if (flag) {
                if (*flag == array[i] && array[i] != 0) {
                    *flag += array[i];
                    array[i] = 0;
                    flag = NULL;
                    ret = true;
                } else if (array[i] > 0) {
                    flag = &array[i];
                }
            } else if (array[i] > 0) {
                flag = &array[i];
            }
        }
    }

    // 向下移动非零的数字
    for (int8_t col = 0; col < 4; col++) {
        flag = NULL;
        for (int8_t row = 3; row >= 0; row--) {
            uint8_t i = row * 4 + col;
            if (flag) {
                if (array[i] > 0) {
                    *flag = array[i];
                    array[i] = 0;
                    if (row < 3) {
                        flag = &array[(row + 1) * 4 + col];
                    }
                    ret = true;
                }
            } else if (array[i] == 0) {
                flag = &array[i];
            }
        }
    }

    return ret;
}

move_confg_t move_direction_select(const lv_coord_t x, const lv_coord_t y)
{
    move_confg_t move = NONE_MOVE;
    if (LV_ABS(x) > LV_ABS(y)) {
        if (x > 0) {
            move = RIGHT_MOVE;
        } else if (x < 0) {
            move = LEFT_MOVE;
        }
    } else {
        if (y > 0) {
            move = DOWN_MOVE;
        } else if (y < 0)
        {
            move = UP_MOVE;
        }
    }
    return move;
}

void select_move_direction(move_confg_t move)
{
    lv_my_demo_game_2048_t* ctx = &lv_my_demo_game_2048_x;
    bool flag = false;
    printf_num_s(ctx->num_data);
    switch (move)
    {
    case LEFT_MOVE:
    case LEFT_KEY:
        LV_LOG("LEFT_MOVE\n");
        flag = left_move_view(ctx->num_data, ctx->num_size, 0);
        break;
    case RIGHT_MOVE:
    case RIGHT_KEY:
        LV_LOG("RIGHT_MOVE\n");
        flag = right_move_view(ctx->num_data, ctx->num_size, 0);
        break;
    case UP_MOVE:
    case UP_KEY:
        LV_LOG("UP_MOVE\n");
        flag = up_move_view(ctx->num_data, ctx->num_size, 0);
        break;
    case DOWN_MOVE:
    case DOWN_KEY:
        LV_LOG("DOWN_MOVE\n");
        flag = down_move_view(ctx->num_data, ctx->num_size, 0);
        break;
    default:
        break;
    }
    printf_num_s(ctx->num_data);
    if (flag) {
        update_rand_num(ctx->num_data, ctx->num_size, 1);
        refresh_screen_view();
    }
}

void game_move_select(lv_event_t * e)
{
    lv_my_demo_game_2048_t* ctx = lv_event_get_user_data(e);
    lv_obj_t* obj = lv_event_get_target(e);
    lv_event_code_t event = lv_event_get_code(e);
    lv_indev_t* indev = lv_indev_get_act();
    lv_point_t* point;
    switch (event)
    {
        case LV_EVENT_KEY:
            LV_LOG("LV_EVENT_KEY\n");
            select_move_direction(lv_indev_get_key(indev));
            break;
        case LV_EVENT_PRESSED:
            lv_indev_get_point(indev, point);
            ctx->point.x = point->x;
            ctx->point.y = point->y;
            break;
        case LV_EVENT_RELEASED:
            lv_indev_get_point(indev, point);
            lv_coord_t diff_x = point->x - ctx->point.x;
            lv_coord_t diff_y = point->y - ctx->point.y;
            select_move_direction(move_direction_select(diff_x, diff_y));
            break;
        default:
            break;
    }
}

void update_rand_num(uint32_t* array, uint8_t size, uint8_t cnt)
{
    uint8_t flag = 0;
    LV_LOG("SIZE %d\n", size);
    for (uint8_t i = 0; i < size; i++) {
        if (array[i] == 0) {
            flag++;
        }
    }
    if (flag > 0){
        uint8_t num = rand() % flag;
        for (uint8_t i = 0; i < size; i++) {
            if ((num > 0) && (array[i] == 0)) {
                num--;
            } else if (array[i] == 0){
                uint32_t val = (rand() % 10 == 1) ? 4 : 2;
                array[i] = val;
                cnt--;
                break;
            }
        }
        if (cnt > 0) {
            update_rand_num(array, size, cnt);
        }
    }

}

void lv_my_demo_game(void)
{
    lv_my_demo_game_2048_t* ctx = &lv_my_demo_game_2048_x;
    lv_obj_t* obj = lv_obj_create(lv_scr_act());

    ctx->g = lv_group_create();
    lv_group_set_default(ctx->g);
    lv_indev_set_group(lv_win32_keypad_device_object, ctx->g);     // 键盘

    srand(time(NULL));
    lv_obj_set_size(obj, LV_PCT(100), LV_PCT(100));
    ctx->num_size = sizeof(ctx->num_data)/sizeof(ctx->num_data[0]);
    LV_LOG("num_size %d\n", ctx->num_size);
    memset(ctx->num_data, 0, ctx->num_size);
    update_rand_num(ctx->num_data, ctx->num_size, 2);
    ctx->view = lv_obj_create(obj);
    lv_obj_set_size(ctx->view, LV_PCT(70), LV_PCT(70));
    lv_obj_align(ctx->view, LV_ALIGN_CENTER, 0, 0);
    view_obj_init(ctx->view);
    lv_obj_add_event_cb(ctx->view, game_move_select, LV_EVENT_ALL, ctx);
    lv_group_add_obj(ctx->g, ctx->view);
}
#endif
