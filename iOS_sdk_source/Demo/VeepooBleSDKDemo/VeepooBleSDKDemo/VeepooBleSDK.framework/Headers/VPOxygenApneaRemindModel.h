//
//  VPOxygenApneaRemindModel.h
//  VeepooBleSDK
//
//  Created by 张冲 on 2018/9/14.
//  Copyright © 2018年 zc.All rights reserved.
//

#import <Foundation/Foundation.h>

@interface VPOxygenApneaRemindModel : NSObject<NSCopying>

@property (nonatomic, assign) NSInteger startH;
@property (nonatomic, assign) NSInteger startM;
@property (nonatomic, assign) NSInteger endH;
@property (nonatomic, assign) NSInteger endM;

//Continuous hypoxic time
//持续低氧时间
@property (nonatomic, assign) NSInteger durationTime;

//Remind users of the vibration duration
//提醒用户的振动时长
@property (nonatomic, assign) NSInteger remindTime;

//Reminder when apnea occurs and is below this value
//当出现呼吸暂停且低于此值的时候提醒
@property (nonatomic, assign) NSInteger lowOxygenValue;

//Whether to use the default time of the bracelet, if used, the time set by the App is invalid, this parameter is temporarily given to YES
//是否使用手环默认时间，如果使用，App端设置的时间无效，这个参数暂时都给YES
@property (nonatomic, assign) BOOL defaultTime;

//Whether to remind the switch status, 1 means open, 2 means closed
//是否提醒的开关状态，1代表开启，2代表关闭
@property (nonatomic, assign) NSInteger state;

- (instancetype)initWithData:(NSData *)data;

- (NSData *)getSettingDataWithType:(NSInteger)type;

@end
