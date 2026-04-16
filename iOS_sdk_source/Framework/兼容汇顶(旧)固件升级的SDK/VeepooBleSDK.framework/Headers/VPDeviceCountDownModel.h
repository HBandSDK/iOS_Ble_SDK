//
//  VPDeviceCountDownModel.h
//  VeepooBleSDK
//
//  Created by 张冲 on 17/6/15.
//  Copyright © 2017年 zc.All rights reserved.
//

#import <Foundation/Foundation.h>

@interface VPDeviceCountDownModel : NSObject
//Repeat time (click the countdown duration of the bracelet countdown interface), and can also be used as a universal time when setting
//重复时长（点击手环倒计时界面的倒计时时长），在设置的时候也可当做通用的时长
@property (nonatomic, assign) NSUInteger repeatTime;

//Current countdown time
//当前倒计时时间
@property (nonatomic, assign) NSUInteger currentCountDownTime;

//Repeated countdown ID, currently a group, the default is 0, temporarily useless
//重复倒计时的ID，目前就一组，默认为0，暂时没有用
@property (nonatomic, assign) NSUInteger countDownID;

//Whether the countdown interface is displayed on the bracelet
//手环上是否显示倒计时界面
@property (nonatomic, assign) BOOL isShow;

//Countdown status, 0 is canceled, 1 is set, 2 is read, 3 is the device is counting down, 4 is the countdown just ended
//倒计时状态，0是取消，1是设置，2是读取，3是设备正在进行倒计时，4是倒计时刚好结束
@property (nonatomic, assign) NSUInteger countDownState;

//0 is to close the resident interface, 1 is to open the resident interface, 2 is to perform a single countdown immediately
//0是关闭常驻界面，1是开启常驻界面，2是立即执行单次倒计时
@property (nonatomic, assign) NSUInteger settingOperation;

- (instancetype)initWithTbyte:(const uint8_t *)tbyte;

- (NSData *)changeSettingCountDownDataWithSettingMode:(NSUInteger)settingMode;

@end







