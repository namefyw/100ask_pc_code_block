/**
 ******************************************************************************
 * @file    lv_100ask_demo_course_3_12_2.c
 * @author  百问科技
 * @version V1.0
 * @date    2022-06-16
 * @brief	3_12_2 课的课堂代码
 ******************************************************************************
 * Change Logs:
 * Date           Author          Notes
 * 2022-06-16     zhouyuebiao     First version
 ******************************************************************************
 * @attention
 *
 * Copyright (C) 2008-2022 深圳百问网科技有限公司<https://www.100ask.net>
 * All rights reserved
 *
 ******************************************************************************
 */


/*********************
 *      INCLUDES
 *********************/
#include "../../lv_100ask_teach_demos.h"

#if LV_AVI_PLAY_DEMO

#include "lv_avi_play_demo.h"
#include "../../../media_lib/avi/avilib.h"
#include <unistd.h>


/*********************
 *      DEFINES
 *********************/
#define DISP_VER_RES  1024  /* 以屏幕宽度为x轴，每一个像素为一个整数点 */
#define SIN_POINT_MAX 600   /* 以屏幕高度为y轴，每一个像素为一个整数点 */
#define PI 3.1415926
#define AVI_SIZE      20*1024

/**********************
 *      TYPEDEFS
 **********************/


/**********************
 *  STATIC VARIABLES
 **********************/
/* 以屏幕宽度为x轴，每一个像素为一个整数点 */
static lv_point_t line_points[DISP_VER_RES] = { 0 };

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void sin_timer(lv_timer_t * timer);

void lv_example_avi_1(void);
/**********************
 *   GLOBAL FUNCTIONS
 **********************/



/**********************
 *   STATIC FUNCTIONS
 **********************/



static lv_img_dsc_t IMG1 = {
    .header.cf = LV_IMG_CF_RAW,
    .header.always_zero = 0,
    .header.reserved = 0,
    .header.w = 0,
    .header.h = 0,
    .data_size = 0,
    .data = NULL,
};
lv_obj_t * objpg;
const	unsigned char JFIF_INFO[18]=
{0XFF ,0XE0 ,0X00 ,0X10 ,0X4A ,0X46 ,0X49 ,0X46 ,0X00 ,0X01 ,0X01 ,0X01 ,0X00 ,0X60 ,0X00 ,0X60 ,0X00 ,0X00};

lv_obj_t * g_scr;
int avi_file_is_opened=0;
char frameBuffer[AVI_SIZE];
int frameSize = 0;      //单帧的字节数
int keyFrame = 0;       //是否关键帧
int pos;                //帧索引
int frames;             //帧总数

avi_t * avi = NULL;
static void pic_timer(void)
{
    //lv_obj_t* bg = timer->user_data;
    if(avi_file_is_opened){
        pos++;
        if(pos<frames){
            //  avi->pos  会自动增加，不用下面的函数
            //AVI_set_video_position((avi_t *) avi,pos);
            frameSize = AVI_read_frame((avi_t *) avi, frameBuffer, &keyFrame);
            //  图片的尺寸不能大于分配的空间
            if(frameSize > sizeof(frameBuffer))     return;
            printf("pos:%d,frameSize: %d",pos, frameSize);

            IMG1.data_size = frameSize;
            memcpy(frameBuffer+2,JFIF_INFO,sizeof(JFIF_INFO));
            IMG1.data = (const uint8_t *)frameBuffer;

            lv_img_set_src(g_scr,&IMG1);
        }else{
            printf("avi file close.");
            avi_file_is_opened = 0;
            AVI_close((avi_t *) avi);

        }
    }

}
void lv_avi_play_demo(void)
{

    char file_path[1024] = {0};
    if (getcwd(file_path, sizeof(file_path)) != NULL) {
        printf("path: %s\n", file_path);
    } else {
        return;
    }
    char *ff="./video_file/avi/hanfu03.avi";
    avi = AVI_open_input_file(ff, 1);
    printf("avi adder %p\n", avi);
    if(avi != NULL){
        avi_file_is_opened = 1;
        printf("W: %d,H: %d\n", (uint32_t)(avi->width),(uint32_t)(avi->height));
        //将avi帧byte读取到bitmap中
        pos = 10;
        frames=AVI_video_frames(avi);

        AVI_set_video_position((avi_t *) avi,pos);
            frameSize = AVI_read_frame((avi_t *) avi, frameBuffer, &keyFrame);
        printf("pos:%d,frameSize: %d\n",pos, frameSize);


    }else{
        printf("open avi fail.");

        AVI_close((avi_t *) avi);
        return;
    }

        IMG1.data_size = frameSize;
        //memcpy(frameBuffer+2,JFIF_INFO,sizeof(JFIF_INFO));
        IMG1.data = (const uint8_t *)frameBuffer;


        g_scr =  lv_img_create(lv_scr_act());
        lv_img_set_src(g_scr,&IMG1);

    lv_timer_t * timer = lv_timer_create(pic_timer, 35,  g_scr);
    lv_timer_set_repeat_count(timer, frames+1);
}

void    hwd_disp_jpg(void)
{

#if  1
FILE *pFile;
    long lSize;

    pFile = fopen("D:/avi/1.jpg", "rb");

    /* 获取文件大小 */
    fseek(pFile, 0, SEEK_END);
    lSize = ftell(pFile);
    rewind(pFile);

    uint8_t *buffer = malloc(lSize);

    /* 将文件拷贝到buffer中 */
    fread(buffer, 1, lSize, pFile);
    fclose(pFile);

    IMG1.data_size = lSize;
    IMG1.data = buffer;

    //ESP_LOG_BUFFER_HEX(TAG, buffer, 10);
    lv_obj_t *scr = lv_scr_act();
    lv_obj_set_style_bg_img_src(scr, &IMG1, LV_PART_MAIN);
    lv_obj_set_style_bg_img_opa(scr, LV_OPA_COVER, LV_PART_MAIN);
    free(buffer);
#endif // 0

//    lv_timer_t * timer = lv_timer_create(pic_timer, 500,  NULL);
//    lv_timer_set_repeat_count(timer, 15);

}
#endif /* LV_USE_100ASK_DEMO_COURSE_3_12_2 */
