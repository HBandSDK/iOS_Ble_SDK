//
//  DFNetPlayer.h
//  Test
//
//  Created by DFung on 2018/2/2.
//  Copyright © 2018年 DFung. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import <UIKit/UIKit.h>


typedef enum : NSUInteger {
    DFNetPlayer_STATUS_PENDING,
    DFNetPlayer_STATUS_PLAY,
    DFNetPlayer_STATUS_PAUSE,
    DFNetPlayer_STATUS_STOP,
} DFNetPlayer_STATUS;


@class DFNetPlayer;
@protocol DFNetPlayerDelegate <NSObject>
-(void)onDFNetPlayer:(DFNetPlayer*)player ChangeStatus:(DFNetPlayer_STATUS)status;
-(void)onDFNetPlayer:(DFNetPlayer*)player CachedProgress:(float)progress;
-(void)onDFNetPlayer:(DFNetPlayer*)player Speed:(float)speed TimeGap:(NSTimeInterval)timeGap;
-(void)onDFNetPlayer:(DFNetPlayer*)player PlayTime:(float)time;
-(void)onDFNetPlayer:(DFNetPlayer*)player PlayFinished:(float)ret;

@end



@interface DFNetPlayer : NSObject
@property (assign,nonatomic)id delegate;
@property (strong,nonatomic)AVPlayer *mPlayer;
@property (strong,nonatomic)AVPlayerItem *mSongItem;
@property (assign,nonatomic)DFNetPlayer_STATUS status;
@property (assign,nonatomic)float time_cached;
@property (assign,nonatomic)float time_total;
@property (assign,nonatomic)float time_play;

-(void)setVolume:(float)volume;
-(float)getVolume;

-(void)didPlayUrl:(NSString*)url;
-(void)didContinue;
-(void)didPause;
-(void)didStop;
-(void)clearObservers;

@end
