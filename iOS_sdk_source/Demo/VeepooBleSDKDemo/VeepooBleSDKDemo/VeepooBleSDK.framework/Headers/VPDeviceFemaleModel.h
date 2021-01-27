//
//  VPDeviceFemaleModel.h
//  VeepooBleSDK
//
//  Created by 张冲 on 17/6/13.
//  Copyright © 2017年 zc.All rights reserved.
//

#import <Foundation/Foundation.h>
#import "VPPublicDefine.h"
@interface VPDeviceFemaleModel : NSObject
//Which physiological period is in
//处于哪个生理期
@property (nonatomic, assign) VPDeviceFemaleState femaleState;

//Last menstrual date format yyyy-MM-dd
//最后经期日期格式yyyy-MM-dd
@property (nonatomic, strong) NSString *lastMenstrualDate;

//Menstrual cycle
//经期周期
@property (nonatomic, assign) NSInteger menstrualCircle;

//Menstrual days
//经期天数
@property (nonatomic, assign) NSInteger menstrualDays;

//The number of days in the current menstrual period, menstrualDays is a person's regular menstrual days, such as 5 days, but this month may be one day less or more than one day, so all of this attribute, this attribute is valid on the color screen project
//当前经期的时间天数，menstrualDays是一个人常规的经期天数，比如5天，但是这个月可能少一天也可能多一天，所以都了个此属性，此属性在彩屏项目上有效
@property (nonatomic, assign) NSInteger currentMenstrualDays;

//Expected date
//预产期expectedDateOfChildbirth
@property (nonatomic, strong) NSString *expectedDateOfChildbirth;

//Baby's birthday
//宝宝的生日格式yyyy-MM-dd
@property (nonatomic, strong) NSString *babyBirthday;

//Is the baby a woman?
//宝宝是否为女
@property (nonatomic, assign) BOOL isGirl;

- (instancetype)initWithTbyte:(const uint8_t *)tbyte;

- (NSData *)changeSelfToSettingData;

@end
