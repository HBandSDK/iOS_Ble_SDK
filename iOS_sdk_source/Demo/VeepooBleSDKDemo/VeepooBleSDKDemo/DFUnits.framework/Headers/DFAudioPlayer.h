//
//  DFAudioPlayer.h
//  AiRuiSheng
//
//  Created by DFung on 2017/2/22.
//  Copyright © 2017年 DFung. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import "MusicOfPhoneMode.h"
#import "DFNetPlayer.h"

#pragma mark --> 【状态】回调
#define kDFAudioPlayer_PLAY             @"DF_PLAY"
#define kDFAudioPlayer_CONTINUE         @"DF_CONTINUE"
#define kDFAudioPlayer_PAUSE            @"DF_PAUSE"
#define kDFAudioPlayer_FINISH           @"DF_FINISH"
#define kDFAudioPlayer_ERROR            @"DF_ERROR"
#define kDFAudioPlayer_UPDATE           @"DF_UPDATE"
/**
 *  note object @param NSString --> @"PLAY" @"FINISH" @"ERROR"
 */
#define kDFAudioPlayer_NOTE             @"DF_AU_NOTE"

#pragma mark --> 【音量】回调
#define kDFAudioPlayer_VOLUME_CHANGE    @"DF_AU_VOLUME_CHANGE"

#pragma mark --> 【进度】回调
/**
 *  note object @param NSDictionary --> @{@"TIME_NOW":当前时间,
 *                                        @"TIME_END":结束时间,
 *                                        @"PROGRESS":播放进度}
 */
#define kDFAudioPlayer_PROGRESS         @"DF_AU_PROGRESS"

#pragma mark --> 【网络加载速度】回调
#define kDFAudioPlayer_NET_SPEED        @"DF_AU_NET_SPEED"

#pragma mark --> 【网络加载时间差】回调
#define kDFAudioPlayer_NET_TIMEGAP      @"DF_AU_NET_TIMEGAP"

typedef enum : NSUInteger {
    DFAudioPlayer_ALL_LOOP,
    DFAudioPlayer_ONE_LOOP,
    DFAudioPlayer_RANDOM,
    DFAudioPlayer_ROUND
} DFAudioPlayer_MODE;

typedef enum : NSUInteger {
    DFAudioPlayer_STOP,
    DFAudioPlayer_PLAYING,
    DFAudioPlayer_PAUSE,
    DFAudioPlayer_PENDING,
} DFAudioPlayer_STATE;

typedef enum : NSUInteger {
    DFAudioPlayer_TYPE_IPOD,
    DFAudioPlayer_TYPE_PATHS,
    DFAudioPlayer_TYPE_NET,
    DFAudioPlayer_TYPE_NONE
} DFAudioPlayer_TYPE;

@interface DFAudioPlayer : NSObject

@property(nonatomic,strong) AVAudioPlayer        *mPlayer;
@property(nonatomic,strong) DFNetPlayer          *mNetPlayer;
@property(nonatomic,strong) NSMutableArray       *mList; //MusicOfPhoneMode
@property(nonatomic,weak  ) MusicOfPhoneMode     *mNowItem;
@property(nonatomic,assign) DFAudioPlayer_MODE   mMode;
@property(nonatomic,assign) DFAudioPlayer_STATE  mState;
@property(nonatomic,assign) DFAudioPlayer_TYPE   mType;

#pragma mark - 当前播放器的类型
/**
 *  @used 当前播放器的类型。
 */
+(DFAudioPlayer_TYPE)currentType;

#pragma mark - 当前使用的播放器
/**
 *  @used 当前播放器的类型。
 */
+(DFAudioPlayer*)currentPlayer;

#pragma mark - ipod（实例_0）
/**
 *  @used iPod音乐播放器。
 */
+(id)sharedMe;

/**
 *  @used 重新读取iPod歌曲。
 */
-(void)reloadPhoneMusic;

/**
 *  @used 筛选ipod歌曲。
 */
+(NSArray*)filterMusic:(NSString*)name;



#pragma mark - 音乐文件（实例_1）
/**
 *  @used 文件音乐播放器。
 */
+(id)sharedMe_1;

/**
 *  @used 文件音乐播放器并传入歌曲路径。
 */
+(id)sharedMeByPaths:(NSArray*)paths;

/**
 *  @used 重新设置传入的歌曲路径。
 */
-(void)resetPaths:(NSArray*)paths;


#pragma mark - 网络音频（实例_2）
/**
 *  @used 网络音乐播放器。
 */
+(id)sharedMe_2;

/**
 *  @used 导入网络url的mode。
 */
-(void)setNetPaths:(NSArray*)paths;

#pragma mark - 操作方法
/**
 *  @used 设置手机音量。
 *  @param  volume（音量）
 */
-(void)setPhoneVolume:(float)volume;

/**
 *  @used 获取手机音量。
 *  @param  volume（音量）
 */
+(float)getPhoneVolume;

/**
 *  @used 获取播放器音量。
 *  @param  volume（音量）
 */
+(float)getPlayerVolume;

/**
 *  1、找到APPDelegate中的以下两个方法：
 *  @see - application:didFinishLaunchingWithOptions:
 *       键入代码：[application beginReceivingRemoteControlEvents];
 *
 *  @see - applicationWillTerminate:
 *       键入代码：[application endReceivingRemoteControlEvents];
 *  
 *  2、并在APPDelegate实现以下方法：
 *       -(void)remoteControlReceivedWithEvent:(UIEvent*)event{
 *          if (event) {
 *              [DFAudioPlayer receiveRemoteEvent:event];
 *          }
 *       }
 *
 *  @used 响应远程事件，用于锁频切歌等功能。
 *  @param  event（事件类）
 */
+(void)receiveRemoteEvent:(UIEvent*)event;


/**
 获取当前播放音乐的时间

 @param path 音乐存放路径
 @return 时间
 */
-(uint32_t)songTimePath:(NSString*)path;

/**
 *  @used 获取当前播放音乐的旋律。
 *  @return 旋律数据
 */
-(NSData*)didRhythmData;

/**
 *  @used 选择播放对应序号的音乐。
 *  @param  index（序号 0...N）
 */
-(void)didPlay:(NSInteger)index;

/**
 *  @used 继续播放音乐。
 */
-(void)didContinue;

/**
 *  @used 继续播放上一个播放器的音乐。
 */
+(void)didContinueLast;

/**
 *  @used 暂停音乐。
 */
-(void)didPause;

/**
 *  @used 暂停所有音乐。
 */
+(void)didAllPause;

/**
 *  @used 暂停播放上一个播放器的音乐。
 */
+(void)didPauseLast;

/**
 *  @used 播放器之前的状态。
 */
+(DFAudioPlayer_STATE)didLastState;

/**
 *  @used 停止音乐。
 */
-(void)didStop;

/**
 *  @used 下一首音乐。
 */
-(void)didNext;

/**
 *  @used 上一首音乐。
 */
-(void)didBefore;

/**
 *  @used 重来一次。
 */
-(void)didRepeat;



@end
