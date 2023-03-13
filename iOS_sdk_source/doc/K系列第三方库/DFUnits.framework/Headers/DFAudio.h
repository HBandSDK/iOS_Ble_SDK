//
//  DFAudio.h
//  DFUnits
//
//  Created by DFung on 16/1/22.
//  Copyright © 2016年 DFung. All rights reserved.
//


/**
 *  科普： 数据量（字节/秒）= (采样频率(Hz) * 采样位数(bit) * 声道数) / 8
 */

#import <Foundation/Foundation.h>
#import <AudioUnit/AudioUnit.h>
#import <AudioToolbox/AudioToolbox.h>
#import <AVFoundation/AVFoundation.h>

#include <stdio.h>
#include <stdlib.h>

/**
 *  【DFAudio】状态回调
 */
#define kDFAudio_ST     @"NOTE_DFAUDIO_ST"

/**
 *  【DFAudio】播放进度（时间）
 */
#define kDFAudio_PG     @"NOTE_DFAUDIO_PG"

/**
 *  【DFAudio】录音数据
 */
#define kDFAudio_REC    @"NOTE_DFAUDIO_REC"

typedef enum : NSUInteger {
    DFAudio_ST_STOP,        //停止状态
    DFAudio_ST_PLAYING,     //播放状态
    DFAudio_ST_PENDING,     //等待状态
    DFAudio_ST_RECORDING,   //录音状态
} DFAudio_ST;

struct DF_Data
{
    int              size;
    unsigned char    *data;
};

@class DFAudioFormat;
@interface DFAudio : NSObject

#pragma mark 播放
/**
 *  用途:初始化【Player】
 *  @param  size    缓存大小
 *  @param  format  (默认 采样率=8000，采样位数=16，声道数=1)
 */
-(void)setPlayerBufferSize:(int32_t)size
                    Format:(DFAudioFormat*)format;
/**
 *  用途:输入音频数据。
 *  @param   data    音频数据
 */
-(void)didPlayerInputBuffer:(NSData*)data;

/**
 PCM缓存可用空间。

 @return 大小
 */
-(uint32_t)didRingUsable;

/**
 *  用途:运行【Player】
 */
-(void)didPlayerStart;

/**
 *  用途:停止【Player】
 */
-(void)didPlayerStop;

/**
 *  用途:关闭并释放【Player】
 */
-(void)didPlayerRelease;


#pragma mark 录音
/**
 *  用途:初始化【Recorder】
 *  @param  format  (默认 采样率=8000，采样位数=16，声道数=1)
 *  @tips   用【kDFAudio_REC】通知回调录音数据。
 */
-(void)setRecorderFormat:(DFAudioFormat*)format;

/**
 *  用途:运行【Recorder】
 */
-(void)didRecorderStart;

/**
 *  用途:停止【Recorder】
 */
-(void)didRecorderStop;

/**
 *  用途:完成【Recorder】
 */
-(void)didRecorderFinished;

/**
 *  用途:关闭并释放【Recorder】
 */
-(void)didRecorderRelease;



#pragma mark PCM <-> WAV 互转
/**
 *  用途:wav转换成pcm
 */
+(NSString*)wavToPcm:(NSString*)wavPath;

/**
 *  用途:pcm转换成Wav
 */
+(NSString*)pcmToWav:(NSString*)pcmPath Format:(DFAudioFormat*)format;


#pragma mark 检测PCM数据 音量分贝
+(double)checkPcmDB:(NSData*)pcmData;


#pragma mark super vad
/**
 *  return
 *  --> 0 : vad prepare.
 *  --> 1 : vad start.
 *  --> 2 : vad end.
 */
+(int)vadPcm:(NSData*)pcm MinDB:(float)db;

#pragma mark super vad + path
/**
 *  return
 *  --> 0 : vad prepare.
 *  --> 1 : vad start.
 *  --> 2 : vad end. (此时path为断句路径)
 */
+(int)vadPcm:(NSData*)pcm MinDB:(float)db Path:(NSString*)path;

/**
 *  clean vad cache
 */
+(void)vadClean;

@end


@interface DFAudioFormat : NSObject
@property(nonatomic,assign)Float64 mSampleRate;
@property(nonatomic,assign)UInt32  mBitsPerChannel;
@property(nonatomic,assign)UInt32  mChannelsPerFrame;
@property(nonatomic,assign)AudioFormatID mFormatID;

@end



