//
//  VPDeviceCountDownModel.h
//  VeepooBleSDK
//
//  Created by 张冲 on 17/6/15.
//  Copyright © 2017年 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface VPDeviceCountDownModel : NSObject
//重复时长（点击手环倒计时界面的倒计时时长），在设置的时候也可当做通用的时长
@property (nonatomic, assign) NSUInteger repeatTime;

//当前倒计时时间
@property (nonatomic, assign) NSUInteger currentCountDownTime;

//重复倒计时的ID，目前就一组，默认为0，暂时没有用
@property (nonatomic, assign) NSUInteger countDownID;

//手环上是否显示倒计时界面
@property (nonatomic, assign) BOOL isShow;

//倒计时状态，0是取消，1是设置，2是读取，3是设备正在进行倒计时，4是倒计时刚好结束
@property (nonatomic, assign) NSUInteger countDownState;

//0是关闭常驻界面，1是开启常驻界面，2是立即执行单次倒计时
@property (nonatomic, assign) NSUInteger settingOperation;

- (instancetype)initWithTbyte:(const uint8_t *)tbyte;

- (NSData *)changeSettingCountDownDataWithSettingMode:(NSUInteger)settingMode;

@end







