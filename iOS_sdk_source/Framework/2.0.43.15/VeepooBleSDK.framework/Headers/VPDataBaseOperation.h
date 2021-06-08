//
//  VPDataBaseOperation.h
//  VeepooBleSDK
//
//  Created by 张冲 on 17/2/9.
//  Copyright © 2017年 zc.All rights reserved.
//

#import <Foundation/Foundation.h>
#import "VPAccurateSleepModel.h"

@interface VPDataBaseOperation : NSObject

/**
 获取某一天原始数据 一般是每隔5分钟或者10分钟的 如果间隔时间长就是在设备中没有读取到数据，原始数据主要作为数据分析，保存到自己的服务器，一般不给用户展示

 @param queryDate 要查询的日期 格式为2017-02-09
 @param tableID 查询数据的ID 传想要获取数据设备的MAC地址
 @return 返回的格式以时间为key 具体的dict为value 格式如下
 {
 "10:40" = {
 diastolic = 0;//高压值
 systolic = 0;//低压值
 heartValue = 0;//心率值
 sportValue = 17;//运动量
 stepValue = 0;//步数
 calValue = 0;//卡路里
 disValue = 0;//距离
 ppgs = [数组]; //使用的时, 如果有heartValue用heartValue,如果没有则优先使用ecgs,如果heartValue和ecgs都没有就用ppgs, ppgs和ecgs是这个时间段的心率数组
 ecgs = [数组];
 };
 "10:45" = {
 diastolic = 0;
 systolic = 0;
 heartValue = 0;
 sportValue = 25;
 stepValue = 0;
 calValue = 0;
 disValue = 0;
 ppgs = [数组]; //使用的时, 如果有heartValue用heartValue,如果没有则优先使用ppgs,如果heartValue和ppgs都没有就用ecgs, ppgs和ecgs是这个时间段的心率数组
 ecgs = [数组];
 };
 }
 */
+ (NSDictionary *)veepooSDKGetOriginalDataWithDate:(NSString *)queryDate andTableID:(NSString *)tableID;

/**
 获取原始数据转换为半小时的数据，如果有需求可以根据原始需求自定义，此方法主要是帮助开发者转变了原始数据为半小时数据 心率是通过求平均值得到的、运动量和步数是半小时内累加得到的，血压有专门的方法获取

 @param queryDate 要查询的日期 格式为2017-02-09
 @param tableID 查询数据的ID 传想要获取数据设备的MAC地址
 @return 返回的格式以时间为key 具体的dict为value 格式如下
 {
 "10:30" = {
 heartValue = 0;//半小时心率平均值
 sportValue = 108;//半小时运动量累加值
 stepValue = 0;//半小时计步数累加值
 calValue = 0;//半小时卡路里累加值
 disValue = 0;//半小时距离累加值
 };
 "11:00" = {
 heartValue = 0;
 sportValue = 33;
 stepValue = 0;
 calValue = 0;//半小时卡路里累加值
 disValue = 0;//半小时距离累加值
 };
 }
 特别说明心率平均值：10：30 就是10：30-11：00的平均值 11：00就是11：00-11：30的平均值，运动量和步数是半小时内所有值累加的
 */
+ (NSDictionary *)veepooSDKGetOriginalChangeHalfHourDataWithDate:(NSString *)queryDate andTableID:(NSString *)tableID;

/**
 获取一天的血压数据 血压测试在原始数据中每一个小时内正常情况下会有一组有效值，这个方法是把原始数据中存在有效的血压测试值提炼出来，没有做过其他的求平均之类的，原始数据中是什么，这里就提炼了什么

 @param queryDate 要查询的日期 格式为2017-02-09
 @param tableID 查询数据的ID 传想要获取数据设备的MAC地址
 @return 数组 格式如下
 (
 {
 Time = "07:05";
 diastolic = 106;
 isManual = N;
 systolic = 71;
 vein = 0;
 },
 {
 Time = "08:05";
 diastolic = 101;
 isManual = N;
 systolic = 65;
 vein = 0;
 }
 )
 */
+ (NSArray *)veepooSDKGetBloodDataWithDate:(NSString *)queryDate andTableID:(NSString *)tableID;


/**
 获取某一天睡眠的数据 一天可能有多段睡眠如 晚上睡一觉 白天睡一觉  而每一段睡眠又可能有多次的起夜
 
 @param queryDate 要查询的日期 格式为2017-02-09
 @param tableID 查询数据的ID 传想要获取数据设备的MAC地址
 @return 睡眠的数组 数组的长度代表一天有几段睡眠 下边的是具体的例子 仅供参考 数据有误
 (
 {
 "DEEP_HOUR" = "2.833";//深睡的时间，单位小时
 HeartBasic = 1;//暂时无用
 "LIGHT_HOUR" = "3.667";//浅睡的时间，单位小时
 "SLEEP_LEVEL" = 3;//睡眠等级区间1-5个等级为:差 一般 好 很好 完美,也可以自定义语言
 "SLEEP_TIME" = "2017/02/09 01:15";//睡眠开始时间
 "SLE_HOUR" = 6;//睡眠总的小时，单位小时
 "SLE_MINUTE" = 30;//睡眠总的分钟，单位分钟 SLE_HOUR + SLE_MINUTE 或者 DEEP_HOUR + LIGHT_HOUR 为总的睡眠时间  或者用WAKE_TIME - SLEEP_TIME 选择用哪个计算总的睡眠时间都可以
 "SLE_LINE" = 010000011111111011111111000001110020000001100200000000000001111111111100001100;//深浅睡眠曲线，0代表浅睡 1代表深睡 2代表苏醒起夜  每个值代表5分钟睡眠时间，如第一个0 就是睡眠的头5分钟 第二个1就是头5-10分钟的睡眠 第三个0就是10-15分钟的睡眠 以此类推 根据此字符串 自定义深浅睡眠曲线或者图形
 "WAKE_TIME" = "2017/02/09 03:45";//睡眠结束时间
 WakeUpTime = 0;//每段睡眠的苏醒次数
 }
 {
 "DEEP_HOUR" = "2.833";
 HeartBasic = 1;
 "LIGHT_HOUR" = "3.667";
 "SLEEP_LEVEL" = 3;
 "SLEEP_TIME" = "2017/02/09 04:15";
 "SLE_HOUR" = 6;
 "SLE_MINUTE" = 30;
 "SLE_LINE" = 000000011111111011111111000001110000000001100000000000000001111111111100001100;
 "WAKE_TIME" = "2017/02/09 07:45";
 WakeUpTime = 0;
 }
 )
 */
+ (NSArray *)veepooSDKGetSleepDataWithDate:(NSString *)queryDate andTableID:(NSString *)tableID;


/**
 获取精准睡眠的数据, 判断设备数据是精准睡眠还是普通睡眠VPPeripheralModel这个类中属性sleepType如果为0是普通睡眠使用上面的方法, 如果为1则是精准睡眠调用此接口
 数组的个数,代表一天有几段, 每个model是一段完整的睡眠
 @param queryDate 查询日期
 @param tableID 设备地址 mac
 @return 返回的是model数据
 */
+ (NSArray <VPAccurateSleepModel *>*)veepooSDKGetAccurateSleepDataWithDate:(NSString *)queryDate andTableID:(NSString *)tableID;

/**
 获取一天的步数 卡路里和距离
 
 @param queryDate 要查询的日期 格式为2017-02-09
 @param tableID 查询数据的ID 传想要获取数据设备的MAC地址
 @param userStature 用户的身高，通过此参数把步数转换为距离和卡路里，身高要和传给设备的个人信息一致，设备默认身高为175
 @param resultBlock 返回的格式以具体的名称为key 具体的数值为value 格式如下
 {
 Step = 5000;//一天总的步数
 Dis = 80.00;//转换后的距离单位为km
 Cal = 1600.0;//转换后的卡路里单位为kcal（千卡）
 }
 */
+ (void)veepooSDKGetStepDataWithDate:(NSString *)queryDate andTableID:(NSString *)tableID changeUserStature:(NSUInteger)userStature result:(void(^)(NSDictionary *stepDict))resultBlock;

/**
 获取某天的运动数据，如果qeryDate传入的值为nil则读取为全部数据

 @param queryDate 正常格式为2015-05-05 传入nil为读取所有天数的数据
 @param tableID 设备的mac地址，获取哪个设备的数据
 @return 获取设备运动数据
 备注：一天的运动数据可能是多条，所以结构为数据，全部的数据为每天数据的组成的数组，即数组下边的单条是每一天数据的数组，单条数据的结构为字典如下：
 [oneTimesRunnintDict setObject:totalTime forKey:VPDeviceRunningTotalTimeKey];//运动总的时间
 [oneTimesRunnintDict setObject:beginTime forKey:VPDeviceRunningBeginTimeKey];//运动的开始时间时间
 [oneTimesRunnintDict setObject:endTime forKey:VPDeviceRunningEndTimeKey];//运动的结束时间
 [oneTimesRunnintDict setObject:[NSString stringWithFormat:@"%d",paceTime] forKey:VPDeviceRunningPaceKey];//运动的平均配速
 [oneTimesRunnintDict setObject:[NSString stringWithFormat:@"%d",aerobicCount] forKey:VPDeviceRunningAerobicExerciseTimeKey];//运动总的有氧时间
 [oneTimesRunnintDict setObject:totalSportSp forKey:VPDeviceRunningTotalSportKey];//运动总的运动量
 [oneTimesRunnintDict setObject:totalStepSp forKey:VPDeviceRunningTotalStepKey];//运动总的步数
 [oneTimesRunnintDict setObject:totalCalSp forKey:VPDeviceRunningTotalCalKey];//运动总的卡路里单位cal
 [oneTimesRunnintDict setObject:totalDisSp forKey:VPDeviceRunningTotalDisKey];//运动总的路程单位m
 [oneTimesRunnintDict setObject:heartAverageValue forKey:VPDeviceRunningAverHeartKey];//运动平均心率
 [oneTimesRunnintDict setObject:pauseTotalTimeSp forKey:VPDeviceRunningPauseTotalTimeKey];//运动的暂停时间
 [oneTimesRunnintDict setObject:pauseTimesSp forKey:VPDeviceRunningPauseTimesKey];//运动的暂停次数
 [oneTimesRunnintDict setObject:crcSp forKey:VPDeviceRunningCrcKey];//运动的crc值
 [oneTimesRunnintDict setObject:recordCountSp forKey:VPDeviceRunningRecordCountKey];//运动的总的条数
 [oneTimesRunnintDict setObject:sportType forKey:VPDeviceRunningTypeKey];//运动模式类型
 [oneTimesRunnintDict setObject:@"0" forKey:VPDeviceRunningHideKey];//是否隐藏，只有用户删除了才隐藏，0代表不隐藏，1代表隐藏
 [oneTimesRunnintDict setObject:oneMinuteArray forKey:VPDeviceRunningArrayKey];//运动的详细数据
 
 oneMinuteArray为每一分钟的数据的数组，下边的结构是每一分钟的字典如下：
 NSDictionary *oneMinuteArrayDict = @{
 VPDeviceRunningPakageKey:packageSp,//第几包,从4开始
 VPDeviceRunningHeartKey:heartSp,//心率值
 VPDeviceRunningSportKey:sportValueSp,//运动量
 VPDeviceRunningStepKey:stepValueSp,//步数
 VPDeviceRunningDisKey:disValueSp,//距离单位m
 VPDeviceRunningCalKey:calValueSp,//卡路里单位cal
 VPDeviceRunningpauseKey:pauseSp//是否存在暂停，1代表存在暂停，其他的代表不存在暂停，运动过程中可能存在暂停在继续的操作
 };
 所有的key的字符串表示都在本文件最下边
 新增运动模式类型type字段, 0代表普通的单运动模式,1户外跑步, 2户外步行, 3室内跑步, 4.室内步行, 5.徒步, 6.踏步机, 7.户外骑行, 8.室内骑行, 9.椭圆机, 10.划船机
 6到10没有步数、距离和配速, 只有卡路里和心率, 0到5是全部都有
 */
+ (NSArray *)veepooSDKGetDeviceRunningDataWithDate:(NSString *)queryDate andTableID:(NSString *)tableID;


/**
 获取设备的某一天的血氧数据

 @param queryDate 要查询的日期格式为2015-02-05
 @param tableID 设备的mac地址，获取哪个设备的数据
 @return 获取一天血氧数据的数组，数组内是每一分钟的字典，格式如下
 NSDictionary *riginalDic = @{
 //时间
 VPOxygenTimeKey:currentPackageTime,
 //血氧值
 VPOxygenValueKey:oxygenValue,
 //没有下边的字段
 //呼吸暂停结果，0没有，1有
 VPApneaResultKey:apneaResult,
 VPIsHypoxiaKey:isHypoxia,
 //低氧时间
 VPHypoxiaTimeKey:hypoxiaTime,
 VPHypopneaKey:hypopnea,
 //心脏负荷
 VPCardiacLoadKey:cardiacLoad,
 VPHRVKey:HRV,
 //运动量
 VPSportValueKey:sportValue,
 VPHeartValueKey:heartValue,
 VPStepValueKey:stepValue,
 //呼吸率
 VPRespirationRateKey:respirationRate,
 VPTemp1Key:temp1};
 */
+ (NSArray *)veepooSDKGetDeviceOxygenDataWithDate:(NSString *)queryDate andTableID:(NSString *)tableID;

/**
 获取设备的某一天的hrv数据，没有此功能
 
 @param queryDate 要查询的日期格式为2015-02-05
 @param tableID 设备的mac地址，获取哪个设备的数据
 @return 获取一天hrv数据的数组，数组内是每一分钟的字典，格式如下
 NSDictionary *riginalDic = @{
 VPHRVTimeKey:hrvTime, 时间
 VPHRVValueKey:hrvValue, hrv值
 VPHRVTempKey:hrvTemp1, 预留参数
 VPHRVHeartsKey:@[这里是字符串数组，代表一分钟内所有的rr间期值，每一个数乘以10代表一个rr间期值，洛伦兹散点图就是根据这个画的，要把所有分钟的rr间期值组合到一起]
 };
 */
+ (NSArray *)veepooSDKGetDeviceHrvDataWithDate:(NSString *)queryDate andTableID:(NSString *)tableID;


/**
 获取设备某一天的体温自动测量数据
 @param queryDate 要查询的日期格式为2021-06-07
 @param tableID 设备的mac地址，获取哪个设备的数据
 @return 获取一天体温自动测量数据的数组，数组内是每5分钟的字典，格式如下
 NSDictionary *dataDic =  {
 VPDeviceTemperatrueDataMonthKey: month, 月份
 VPDeviceTemperatrueDataDayKey: day, 日
 VPDeviceTemperatrueDataHourKey: hour, 小时
 VPDeviceTemperatrueDataMinuteKey: minute, 分钟
 VPDeviceTemperatrueDataValueKey: value, 温度值（摄氏度）
 }
*/
+ (NSArray *)veepooSDKGetDeviceTemperatureDataWithDate:(NSString *)queryDate andTableID:(NSString *)tableID;

/*
 NSString *const VPDeviceRunningTotalTimeKey = @"totalTime";
 NSString *const VPDeviceRunningBeginTimeKey = @"beginTime";
 NSString *const VPDeviceRunningEndTimeKey = @"endTime";
 NSString *const VPDeviceRunningPaceKey = @"averPace";
 NSString *const VPDeviceRunningAerobicExerciseTimeKey = @"aerobTime";
 NSString *const VPDeviceRunningTotalSportKey = @"totalSport";
 NSString *const VPDeviceRunningTotalStepKey = @"totalStep";
 NSString *const VPDeviceRunningTotalCalKey = @"totalCal";
 NSString *const VPDeviceRunningTotalDisKey = @"totalDis";
 NSString *const VPDeviceRunningAverHeartKey = @"averHeart";
 NSString *const VPDeviceRunningPauseTotalTimeKey = @"pauseTotalTime";
 NSString *const VPDeviceRunningPauseTimesKey = @"pauseCount";
 NSString *const VPDeviceRunningCrcKey = @"crcValue";
 NSString *const VPDeviceRunningArrayKey = @"oneMinuteData";
 NSString *const VPDeviceRunningRecordCountKey = @"recordCount";
 NSString *const VPDeviceRunningTypeKey = @"type";
 NSString *const VPDeviceRunningHideKey = @"isHide";
 
 NSString *const VPDeviceRunningPakageKey = @"packageCount";
 NSString *const VPDeviceRunningHeartKey = @"heartValue";
 NSString *const VPDeviceRunningSportKey = @"sportValue";
 NSString *const VPDeviceRunningStepKey = @"stepValue";
 NSString *const VPDeviceRunningCalKey = @"calValue";
 NSString *const VPDeviceRunningDisKey = @"disValue";
 NSString *const VPDeviceRunningpauseKey = @"isPause";
 
 NSString *const VPDeviceRunningMaxHeartKey = @"VPDeviceRunningMaxHeart";
 NSString *const VPDeviceRunningMinHeartKey = @"VPDeviceRunningMinHeartKey";
 NSString *const VPDeviceRunningMaxSportKey = @"VPDeviceRunningMaxSportKey";
 NSString *const VPDeviceRunningMinSportKey = @"VPDeviceRunningMinSportKey";
 NSString *const VPDeviceRunningMaxStepKey = @"VPDeviceRunningMaxStepKey";
 NSString *const VPDeviceRunningMinStepKey = @"VPDeviceRunningMinStepKey";
 NSString *const VPDeviceRunningMaxCalKey = @"VPDeviceRunningMaxCalKey";
 NSString *const VPDeviceRunningMinCalKey = @"VPDeviceRunningMinCalKey";
 NSString *const VPDeviceRunningMaxDisKey = @"VPDeviceRunningMaxDisKey";
 NSString *const VPDeviceRunningMinDisKey = @"VPDeviceRunningMinDisKey";
 
 NSString *const VPDeviceRunningPakageKey = @"packageCount";
 NSString *const VPDeviceRunningHeartKey = @"heartValue";
 NSString *const VPDeviceRunningSportKey = @"sportValue";
 NSString *const VPDeviceRunningStepKey = @"stepValue";
 NSString *const VPDeviceRunningCalKey = @"calValue";
 NSString *const VPDeviceRunningDisKey = @"disValue";
 NSString *const VPDeviceRunningpauseKey = @"isPause";
*/
/*
 NSString *const VPOxygenTimeKey = @"Time";
 NSString *const VPOxygenValueKey = @"OxygenValue";
 NSString *const VPApneaResultKey = @"ApneaResult";
 NSString *const VPIsHypoxiaKey = @"IsHypoxia";
 NSString *const VPHypoxiaTimeKey = @"HypoxiaTime";
 NSString *const VPHypopneaKey = @"Hypopnea";
 NSString *const VPCardiacLoadKey = @"CardiacLoad";
 NSString *const VPHRVKey = @"HRV";
 NSString *const VPSportValueKey = @"SportValue";
 NSString *const VPHeartValueKey = @"HeartValue";
 NSString *const VPStepValueKey = @"StepValue";
 NSString *const VPRespirationRateKey = @"RespirationRate";
 NSString *const VPTemp1Key = @"Temp1";
 NSString *const VPTemp2Key = @"Temp2";
*/
/*
NSString *const VPHRVTimeKey = @"time";
NSString *const VPHRVValueKey = @"hrvValue";
NSString *const VPHRVTempKey = @"temp1";
NSString *const VPHRVHeartsKey = @"hearts";
*/
/*
NSString *const VPDeviceTemperatrueDataMonthKey = @"month";
NSString *const VPDeviceTemperatrueDataDayKey = @"day";
NSString *const VPDeviceTemperatrueDataHourKey = @"hour";
NSString *const VPDeviceTemperatrueDataMinuteKey = @"minute";
NSString *const VPDeviceTemperatrueDataValueKey = @"value";
 */
@end




