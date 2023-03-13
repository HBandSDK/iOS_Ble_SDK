//
//  OPenALM.h
//  OpenALForPCM
//
//  Created by 陈冠杰 on 16/2/15.
//  Copyright © 2016年 zh-JieLi. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AudioToolbox/AudioToolbox.h>
#import <AudioToolbox/ExtendedAudioFile.h>
#import <OpenAL/al.h>
#import <OpenAL/alc.h>

#include "queue.h"


struct AL_Data{
    int size;
    unsigned char *data;
};



/**
 *  【OPenALM】播放停止
 */
#define kOPenALM_STOP    @"OPenALM_STOP"



@interface OPenALM : NSObject
{
    ALCcontext *mContext;
    ALCdevice *mDevicde;
    ALuint outSourceId;
    ALuint buff;
}

@property(nonatomic)ALCcontext *mContext;
@property(nonatomic)ALCdevice *mDevice;

/**
 *  Need Import <OpenAL.frameworks>
 *              <AudioToolBox.frameworks>
 */
-(void)inputAudioBuffer:(struct AL_Data*)pkg;

-(BOOL)updataQueueBuffer;

-(void)playSound;

-(void)stopSound;

-(void)cleanUpOpenAL;

-(void)cleanMe;

@end
