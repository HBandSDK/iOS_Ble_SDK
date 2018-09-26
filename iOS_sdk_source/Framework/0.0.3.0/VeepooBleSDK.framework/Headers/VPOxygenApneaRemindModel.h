//
//  VPOxygenApneaRemindModel.h
//  VeepooBleSDK
//
//  Created by 张冲 on 2018/9/14.
//  Copyright © 2018年 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface VPOxygenApneaRemindModel : NSObject<NSCopying>

@property (nonatomic, assign) NSInteger startH;
@property (nonatomic, assign) NSInteger startM;
@property (nonatomic, assign) NSInteger endH;
@property (nonatomic, assign) NSInteger endM;
//持续低氧时间
@property (nonatomic, assign) NSInteger durationTime;
//提醒用户的振动时间
@property (nonatomic, assign) NSInteger remindTime;
//当出现呼吸暂停且低于此值的时候提醒
@property (nonatomic, assign) NSInteger lowOxygenValue;
//是否使用手环默认时间，如果使用，App端设置的时间无效，这个参数暂时都给YES
@property (nonatomic, assign) BOOL defaultTime;
//是否提醒的开关状态，1代表开启，2代表关闭
@property (nonatomic, assign) NSInteger state;

- (instancetype)initWithData:(NSData *)data;

- (NSData *)getSettingDataWithType:(NSInteger)type;

@end
