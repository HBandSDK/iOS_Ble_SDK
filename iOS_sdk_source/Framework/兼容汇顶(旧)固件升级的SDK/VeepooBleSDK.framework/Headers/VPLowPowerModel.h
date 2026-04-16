//
//  VPLowPowerModel.h
//  WYPHealthyThird
//
//  Created by 张冲 on 2019/9/7.
//  Copyright © 2019 zc.All rights reserved.
//

#import <Foundation/Foundation.h>


@interface VPLowPowerModel : NSObject

//Low power switch state 1 is on, 2 is off
//低功耗开关状态1是开, 2是关
@property (nonatomic, assign) int state;

//Message brightness time
//消息亮屏时长
@property (nonatomic, assign) int messageDuration;

//Turning the wrist screen
//转腕亮屏时长
@property (nonatomic, assign) int turnWristDuration;

//Touch the main interface to brighten the screen
//触摸主界面亮屏时长
@property (nonatomic, assign) int mainScreenDuration;

//Message delay vibration duration
//消息延迟震动时长
@property (nonatomic, assign) int messageDelayMotorDuration;

//Caller motor vibration duration
//来电马达震动时长
@property (nonatomic, assign) int callMotorDuration;

+ (instancetype)modelWithData:(NSData *)data;

- (void)updateWithData:(NSData *)data;

- (NSData *)dataWithState:(int)state;

@end


