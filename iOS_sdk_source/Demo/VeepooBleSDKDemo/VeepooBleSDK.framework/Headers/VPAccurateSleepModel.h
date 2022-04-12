//
//  VPAccurateSleepModel.h
//  WYPHealthyThird
//
//  Created by 张冲 on 2018/10/11.
//  Copyright © 2018年 zc.All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface VPAccurateSleepModel : NSObject

//Type of sleep, upload A7 command sleep flag(睡眠的类型，上传A7指令睡眠标记位)
@property (nonatomic, strong) NSString *sleepType;
//Sleep time 入睡时间
@property (nonatomic, strong) NSString *sleepTime;
//Wake up time 起床时间
@property (nonatomic, strong) NSString *wakeTime;
//Sleep sign 睡眠标志
@property (nonatomic, strong) NSString *sleepTag;
//get up score 起夜得分
@property (nonatomic, strong) NSString *getUpScore;
//Deep sleep score 深睡得分
@property (nonatomic, strong) NSString *deepScore;
//Sleep efficiency score, efficiency score from night to deep sleep 睡眠效率得分，起夜到深睡的效率得分
@property (nonatomic, strong) NSString *sleepEfficiencyScore;
//Sleeping efficiency score, from the start of sleep to the first time into the deep sleep 入睡效率得分，从开始睡眠到第一次进入深睡的效率
@property (nonatomic, strong) NSString *fallAsleepScore;

//睡眠时长得分
@property (nonatomic, strong) NSString *sleepTimeScore;
//退出睡眠的模式
@property (nonatomic, strong) NSString *exitSleepMode;
//睡眠质量0到4, 依次代表1到5颗星
@property (nonatomic, strong) NSString *sleepQuality;
//起夜次数
@property (nonatomic, strong) NSString *getUpTimes;
//深浅睡眠模式
@property (nonatomic, strong) NSString *deepAndLightMode;
//睡眠总时长，单位分钟
@property (nonatomic, strong) NSString *sleepDuration;
//深睡时间，单位分钟
@property (nonatomic, strong) NSString *deepDuration;
//浅睡时间，单位分钟
@property (nonatomic, strong) NSString *lightDuration;
//起夜时间，单位分钟, 苏醒时长
@property (nonatomic, strong) NSString *getUpDuration;
//其他睡眠时间，单位分钟, 快速眼动期
@property (nonatomic, strong) NSString *otherDuration;
//第一次进入深睡时间，入睡效率
@property (nonatomic, strong) NSString *firstDeepDuration;
//起夜到深睡时间的平均值，睡眠效率
@property (nonatomic, strong) NSString *getUpToDeepAve;
//曲线上一个点代表的时间，单位秒，现在是60s
@property (nonatomic, strong) NSString *onePointDuration;
//精准睡眠类型, 1是精准睡眠, 0是普通睡眠
@property (nonatomic, strong) NSString *accurateType;
//失眠标志
@property (nonatomic, strong) NSString *insomniaTag;
//失眠得分
@property (nonatomic, strong) NSString *insomniaScore;
//失眠次数
@property (nonatomic, strong) NSString *insomniaTimes;
//beginTime开始时间,具体开始入睡多少分钟,endTime结束时间,具体开始入睡多少分钟
@property (nonatomic, strong) NSArray *insomniaRecord;
//睡眠曲线，16进制的字符串，客户端解析的时候在转换成数据流，每两个字节代表一个点, 高位在前,低位在后, 其中高3个比特代表睡眠的状态,深睡(0)、浅睡(1)、快速眼动(2)、失眠(3)、苏醒(4) 如0x1000这个数, 取高三位0x1000>>13, 得到的值看是0到5中的哪个。
@property (nonatomic, strong) NSString *sleepLine;

//根据曲线转换的失眠时长
@property (nonatomic, strong) NSString *insomniaDuration;

//这两个字段, 如果lastType == 1 就代表要和上一段睡眠拼接, 如果nextType==1就代表要和下一段睡眠也拼接, 拼接后除了入睡、起床要修改, 曲线要拼接, 其他都用最后一段的
@property (nonatomic, strong) NSString *lastType;
@property (nonatomic, strong) NSString *nextType;
@property (nonatomic, strong) NSString *mac;

//根据读取的数据创建模型，如果返回nil代表数据解析失败
+ (instancetype)modelWithAccurateSleepData:(NSData *)accurateSleepData dayNumber:(NSInteger)dayNumber sleepType:(NSInteger)sleepType;

- (int)getUpSleepPercent;
- (int)insomniaPercent;
- (int)eyeMovementPercent;
- (int)lightSleepPercent;
- (int)deepSleepPercent;


@end

NS_ASSUME_NONNULL_END
