#include "../../lv_100ask_teach_demos.h"

#if LV_MY_DEMO_GAME == 2048
#include "lv_my_demo_game_2048.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define VIEW_SIZE 4
#define NUM_SIZE VIEW_SIZE*VIEW_SIZE
#define BLOCK_SIZE LV_PCT(100/VIEW_SIZE)
#define RANGE_JUDGMENT 80
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
} lv_my_demo_game_2048_t;
lv_my_demo_game_2048_t lv_my_demo_game_2048_x;

typedef enum {
    NONE_MOVE,
    LEFT_MOVE = 1 << 0,
    RIGHT_MOVE = 1 << 1,
    UP_MOVE = 1 << 2,
    DOWN_MOVE = 1 << 3,
} move_confg_t;

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
        lv_obj_set_size(label, LV_PCT(50), LV_PCT(50));
        lv_obj_set_size(obj, LV_PCT(100/VIEW_SIZE), LV_PCT(100/VIEW_SIZE));
        if (num % 4) {
            lv_obj_align_to(obj, lv_obj_get_child(view, num-1), LV_ALIGN_OUT_RIGHT_MID, 0, 0);
        } else if (num){
            lv_obj_align_to(obj, lv_obj_get_child(view, num - 4), LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
        }

        lv_label_set_text_fmt(label, "%d", ctx->num_data[num]);
        lv_obj_align(label, LV_ALIGN_TOP_LEFT, 0, 0);
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
        lv_label_set_text_fmt(label, "%d", ctx->num_data[i]);
        lv_obj_invalidate(label);
    }
}

void printf_num_s()
{
    lv_my_demo_game_2048_t* ctx = &lv_my_demo_game_2048_x;
    for (uint8_t i = 0; i < 16; i++) {
        if (i > 0 && (i % 4) == 0) {
            LV_LOG_W("\n");
        }
        LV_LOG_W("%d ", ctx->num_data[i]);
    }
    LV_LOG_W("\n");
    LV_LOG_W("_____________________\n");

}

bool right_move_view(uint32_t* array)
{
    bool ret = false;

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

void select_move_direction(const lv_point_t* point)
{
    lv_my_demo_game_2048_t* ctx = &lv_my_demo_game_2048_x;
    lv_coord_t diff_x = point->x - ctx->point.x;
    lv_coord_t diff_y = point->y - ctx->point.y;
    bool flag = false;
    switch (move_direction_select(diff_x, diff_y))
    {
    case LEFT_MOVE:
        LV_LOG("LEFT_MOVE\n");
        break;
    case RIGHT_MOVE:
        LV_LOG("RIGHT_MOVE\n");
        printf_num_s();
        flag = right_move_view(ctx->num_data);
        printf_num_s();
        break;
    case UP_MOVE:
        LV_LOG("UP_MOVE\n");
        break;
    case DOWN_MOVE:
        LV_LOG("DOWN_MOVE\n");
        break;
    default:
        break;
    }
    if (flag) {
        update_rand_num(ctx->num_data, ctx->num_size, 1);
        refresh_screen_view();
    }
}

void game_move_select(lv_event_t * e)
{
    lv_my_demo_game_2048_t* ctx = &lv_my_demo_game_2048_x;
    lv_obj_t* obj = lv_event_get_target(e);
    lv_event_code_t event = lv_event_get_code(e);
    lv_indev_t * indev = lv_indev_get_act();
    lv_point_t* point;
    switch (event)
    {
        case LV_EVENT_KEY:
            LV_LOG("LV_EVENT_KEY\n");
            break;
        case LV_EVENT_PRESSED:
            lv_indev_get_point(indev, point);
            ctx->point.x = point->x;
            ctx->point.y = point->y;
            break;
        case LV_EVENT_RELEASED:
            lv_indev_get_point(indev, point);
            select_move_direction(point);
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
        LV_LOG("[B] NUM %d\n", num);
        for (uint8_t i = 0; i < size; i++) {
            if ((num > 0) && (array[i] == 0)) {
                num--;
            } else if (array[i] == 0){
                LV_LOG("NUM %d\n", num);
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
    srand(time(NULL));
    lv_obj_set_size(obj, LV_PCT(100), LV_PCT(100));
    ctx->num_size = sizeof(ctx->num_data)/sizeof(ctx->num_data[0]);
    memset(ctx->num_data, 0, ctx->num_size);
    update_rand_num(ctx->num_data, ctx->num_size, 2);
    ctx->view = lv_obj_create(obj);
    lv_obj_set_size(ctx->view, LV_PCT(70), LV_PCT(70));
    lv_obj_align(ctx->view, LV_ALIGN_CENTER, 0, 0);
    view_obj_init(ctx->view);
    lv_obj_add_event_cb(ctx->view, game_move_select, LV_EVENT_ALL, NULL);
}
#endif
