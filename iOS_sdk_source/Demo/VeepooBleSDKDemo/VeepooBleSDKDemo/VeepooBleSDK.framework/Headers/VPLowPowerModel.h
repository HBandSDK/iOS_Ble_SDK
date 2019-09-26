//
//  VPLowPowerModel.h
//  WYPHealthyThird
//
//  Created by 张冲 on 2019/9/7.
//  Copyright © 2019 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface VPLowPowerModel : NSObject

@property (nonatomic, assign) int state;//低功耗开关状态1是开, 2是关
@property (nonatomic, assign) int messageDuration;//消息亮屏时长
@property (nonatomic, assign) int turnWristDuration;//转腕亮屏时长
@property (nonatomic, assign) int mainScreenDuration;//触摸主界面亮屏时长
@property (nonatomic, assign) int messageDelayMotorDuration;//消息延迟震动时长
@property (nonatomic, assign) int callMotorDuration;//来电马达震动时长

+ (instancetype)modelWithData:(NSData *)data;

- (void)updateWithData:(NSData *)data;

- (NSData *)dataWithState:(int)state;

@end


