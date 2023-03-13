//
//  JL_vad.h
//  Test
//
//  Created by DFung on 2018/2/28.
//  Copyright © 2018年 DFung. All rights reserved.
//

#ifndef JL_vad_h
#define JL_vad_h



#define CONT_AD_ADFRMSIZE         16
#define DEFAULT_RADIX 12
#define SMOOTH_WINDOW 4
#define MIN_FIXLOG -2829416
#define KWSNUM 1                //¥˝ ∂±¥ ∏ˆ ˝


//typedef  long long __int64;
typedef int        int32;
typedef short        int16;
typedef signed char    int8;
typedef unsigned int    uint32;
typedef unsigned short    uint16;
typedef unsigned char    uint8;
typedef long long int64;
typedef int32 fixed32;
typedef float        float32;




struct noise_stats_s {
    /* Smoothed power */
    int power[40];
    int max_power[40];
    /* Noise estimate */
    int noise[40];
    int max_noise[40];
    /* Signal floor estimate */
    int floor[40];
    int max_floor[40];
    /* Peak for temporal masking */
    int peak[40];
    int max_peak[40];
    
    int signal[40];
    int gain[40];
    char remove_noi;
    /* Initialize it next time */
    uint8 undefined;
    /* Number of items to process */
    uint32 num_filters;
    
    /* Sum of slow peaks for VAD */
    int64 slow_peak_sum;
    int64 max_slow_peak_sum;
    
    /* Precomputed constants */
    int lambda_power;
    int comp_lambda_power;
    int lambda_a;
    int comp_lambda_a;
    int lambda_b;
    int comp_lambda_b;
    int lambda_t;
    int mu_t;
    int max_gain;
    int inv_max_gain;
    
    int smooth_scaling[2 * 4 + 3];
};
typedef struct noise_stats_s noise_stats_t;
struct htk_fe_s
{
    unsigned short pow_hist[98];
    noise_stats_t *noise_stats;
    
    
    int fe_prior;
    uint32 int_frame;
    char int_flag;
    
    
    unsigned char sum_cnt;
    
    uint8 voice_state;
    uint8 in_speech;
    int16 pre_speech_frames;
    int16 post_speech_frames;
    
    int16 inout_spch[410];
    int fe_tmp_spch[250];
    int fe_fft_buf[512];
    int fe_mfspec[40];
    int cmn_sum[13];
    int mfcc_fifo[9][13];
    int *cmn_mfcc_fifo[9];
    //int fe_prior;
    char speech_fifo[16];
    char init_speech_n;
    char vad_cnt;
    int  buf_cep[21][13];
    int buf_pow[21];
    uint8 speech_indexw;
    uint8 speech_indexr;
    uint8 speech_cnt;
    
    
    int16 sp_threshold;
    int16 nsp_threshold;
};

typedef struct htk_fe_s htk_fe_t;
/*
 *  How to use? See follow...
 *
 *  1、开启录音前：
 *      /--- 开启Vad ---/
 *      int need_buf_size = vad_get_need_buf_size();
 *      vad_hdl = malloc(need_buf_size);
 *      vad_init(vad_hdl, 10, 51);
 *
 *  2、结束录音后：
 *      /--- 关闭Vad ---/
 *      free(vad_hdl);
 *
 *  3、录音数据回调：
 *      buf：录音数据 ，需要320Bytes！
 *      ret：0->静音状态  1->正在说话   2->结束说话
 *      int ret = vad_main(vad_hdl, (int*)buf);
 */
int vad_get_need_buf_size(void);
int vad_init(void *p, short sp_threshold, short nsp_threshold);
int vad_main(void  *p,int *inout_spch);

fixed32 fe_log_add(fixed32 x, fixed32 y);
fixed32 fe_log_sub(fixed32 x, fixed32 y);
int32 fixlog2(uint32 x);
int fixlog(uint32 x);

#endif /* JL_vad_h */
