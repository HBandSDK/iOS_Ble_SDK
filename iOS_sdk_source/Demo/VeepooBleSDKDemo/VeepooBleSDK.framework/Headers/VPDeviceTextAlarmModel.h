//
//  VPDeviceTextAlarmModel.h
//  VeepooBleSDK
//
//  Created by veepoo-cd on 2021/9/22.
//  Copyright © 2021 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface VPDeviceTextAlarmModel : NSObject

//Alarm hour
//闹钟小时
@property (nonatomic, strong) NSString *alarmHour;

//Alarm minute
//闹钟分钟
@property (nonatomic, strong) NSString *alarmMinute;

//Alarm status, 0 means off 1 means on
//闹钟状态，0代表关闭 1代表开启
@property (nonatomic, strong) NSString *alarmState;

//Alarm clock ID, addition, deletion, and change need to use this
//闹钟ID，增删改查都需要用到这个
@property (nonatomic, strong) NSString *alarmID;

//Alarm repeat state, 0 means not repeat the date to set an alarm reminder, other cases are converted from 8-bit binary to decimal string such as: 00000011, which means that the repeat week is Monday and Tuesday, and the repeatState is 3; Pushing from the back, the first place at the beginning is always 0, the other one is Monday to Sunday, the second is Sunday, the last is Monday, 1 is repeated, 0 is not repeated this week.
//闹钟重复状态，0代表不重复要设置一个闹钟提醒的日期，其他情况是由8位2进制转换成10进制的字符串如：00000011，代表重复星期是周一和周二，repeatState就是3；二进制从后边往前推，开头的第一位一直为0，其他的一次代表周一至周日，第2位是周日，最后一位是周一，1代表重复，0代表这个星期不重复
@property (nonatomic, strong) NSString *repeatState;

//Alarm clock reminder text, 0~60byte
//闹钟提醒的文字，最长支持60字节
@property (nonatomic, strong) NSString *alarmText;

//The date of the alarm reminder is valid for a single reminder. The default reminder for the repeat week is 0000-00-00. All formats are like this.
//闹钟提醒的日期，对单次提醒有效，重复星期提醒的默认给0000-00-00，所有格式都是这样的
@property (nonatomic, strong) NSString *alarmDate;

- (instancetype)initWithAlarmDict:(NSDictionary *)alarmDict;

+ (NSDictionary *)getAlarmDictWithData:(NSData *)data;

+ (NSArray *)changeTextAlarmArray:(NSArray *)saveAlarmArray;

- (NSDictionary *)changeModelToDict;

- (NSArray<NSData *> *)changeModelToSettingAlarmDataWithType:(short)type crc:(NSData *)crc;

- (NSString *)getRepeatWeek;

//Convert dictArray to ModelArray
//把dictArray转换成ModelArray
+ (NSArray *)changeModelArrayWithAlarmDictArray:(NSArray *)alarmArray;

//Convert the week to a binary string for easy display
//把星期转换成二进制的字符串，方便显示
- (NSString *)weekBinaryString;

@end

NS_ASSUME_NONNULL_END
