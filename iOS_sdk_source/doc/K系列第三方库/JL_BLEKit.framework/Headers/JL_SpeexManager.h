//
//  JL_SpeexManager.h
//  JL_BLEKit
//
//  Created by 杰理科技 on 2021/12/17.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JL_FunctionBaseManager.h"
#import "JL_TypeEnum.h"
#import "JL_Tools.h"

NS_ASSUME_NONNULL_BEGIN

@interface JL_SpeexManager : JL_FunctionBaseManager

#pragma mark ---> SPEEX语音
/**
    语音操作状态
    kJL_MANAGER_KEY_OBJECT  ==>  JLModel_SPEEX
*/
extern NSString *kJL_MANAGER_SPEEX;

/**
    语音数据
    kJL_MANAGER_KEY_OBJECT  ==>  NSData
*/
extern NSString *kJL_MANAGER_SPEEX_DATA;

/**
 发送命令给音箱，允许音箱端开始接收语音，音箱收到这个消息后会发一个提示音
 */
-(void)cmdAllowSpeak;

/** 拒绝录音
 发送命令给音箱，不允许接收语音
 */
-(void)cmdRejectSpeak;

/** 停止语音
 发发送命令给音箱，停止接收数据，即检测到断句
 */
-(void)cmdSpeakingDone;

@end

NS_ASSUME_NONNULL_END
