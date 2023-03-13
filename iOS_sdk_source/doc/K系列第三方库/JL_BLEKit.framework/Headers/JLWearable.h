//
//  JLWearable.h
//  Test
//
//  Created by EzioChan on 2021/4/6.
//  Copyright © 2021 Zhuhai Jieli Technology Co.,Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JL_RCSP.h"
#import "JL_EntityM.h"
#import "JL_SDM_Header.h"
#import "JL_WatchProtocol.h"
#import "JLWearSync.h"
#import "JLWearSyncCustom.h"

NS_ASSUME_NONNULL_BEGIN

#define JL_RECIVED_DATA     @"JL_RECIVED_DATA"


/// 穿戴设备基础命令控制
@interface JLWearable : NSObject

@property(nonatomic,assign,readonly)uint8_t version;
@property(nonatomic,strong)JL_CB_HeartRate      heartRate;
@property(nonatomic,strong)JL_CB_AirPressure    airPressure;
@property(nonatomic,strong)JL_CB_Altitude       alititude;
@property(nonatomic,strong)JL_CB_MoveSteps      moveStep;
@property(nonatomic,strong)JL_CB_Stress         stress;
@property(nonatomic,strong)JL_CB_Oxsaturation   oxStaturation;
@property(nonatomic,strong)JL_CB_TrainLoad      trainLoad;
@property(nonatomic,strong)JL_CB_MaxOxg         maxOxg;
@property(nonatomic,strong)JL_CB_RecTime        rectime;
@property(nonatomic,strong)JL_CB_SportMsg       sportMsg;
@property(nonatomic,strong)JL_CB_WatchLog       logMsg;
@property(nonatomic,strong,readonly)JL_EntityM* responseEntity;

+(instancetype)sharedInstance;

/// 把对象加入协议
/// @param delegate 对象
-(void)w_addDelegate:(id<JL_WatchProtocol>)delegate;

/// 移除对象的协议
/// @param delegate 对象
-(void)w_removeDelegate:(id<JL_WatchProtocol>)delegate;

/// 移除所有对象的协议
-(void)w_removeAll;

/// 请求穿戴设备的数据
/// 使用例子：
/**
 JLWearable *w = [JLWearable sharedInstance];
 NSMutableArray *array = [NSMutableArray new];
 [array addObject:[JL_SDM_HeartRate requireRealTime:YES Resting:YES Max:YES]];
 [array addObject:[JL_SDM_Altitude requireRealTime:YES min:NO Max:NO]];
 [array addObject:[JL_SDM_MoveSteps require]];
 w.heartRate = ^(JL_SDM_HeartRate *heartRate) {
    //心率信息
 };
 w.alititude = ^(JL_SDM_Altitude *altitude) {
    //海拔信息
 };
 JL_EntityM *entity = [[JL_EntityM alloc] init];
 [w requestSportData:array withEntity:entity];
*/
/// @param reqModels 数据模型，可参考JL_SDM_相关的类型请求，这是个父类，这里是通过多态的方式来实现选择性的请求
/// @param entity 当前设备的entity
///
-(void)w_requestSportData:(NSMutableArray<JLSportDataModel *>*)reqModels withEntity:(JL_EntityM *)entity;

/// 私有测试接口
/// @param data 数据
/// @param entity 当前设备entity
/// @param opcode 操作
-(void)pr_requestSportDataMask:(NSData *)data withEntity:(JL_EntityM *)entity opCode:(uint16_t)opcode;


/// 收到数据解析
/// @param pkg 收到的数据包
/// @param entity 当前的entity
-(void)w_inputPKG:(JL_PKG*)pkg withEntity:(JL_EntityM *)entity;

/// 推送天气到手表
/// @param weather 天气内容
/// @param entity 服务对象
/// @param block 推送回调
-(void)w_syncWeather:(JL_MSG_Weather *)weather withEntity:(JL_EntityM *)entity result:(JL_CB_Status)block;


/**
 请求设备传感器的log
 使用示例
 [[JLWearable shareInstance] w_transportLog:Log_Acceleration | Log_HeartRate_BloodOxy withEntity:entity];
 */
/// 请求设备传感器的log
/// @param model 请求类型（Log_Acceleration | Log_HeartRate_BloodOxy）
/// @param entity 当前的entity
-(void)w_transportLog:(JL_WATCH_LOG_MASK)model withEntity:(JL_EntityM *)entity;


//MARK: - 设备设置命令

/// 查询读取设备信息
/// @param target JL_WATCH_SETTING枚举，支持|运算同时设置多个设备类型信息
/// @param entity 当前的entity
/// /// 本方法的返回结果，需要接收对应的协议：JL_WatchProtocol ，并把遵循协议的对象加入到本单例中
/// -(void)w_addDelegate:(id<JL_WatchProtocol>)delegate;
-(void)w_InquireDeviceFuncWith:(JL_WATCH_SETTING)target withEntity:(JL_EntityM *)entity;

/// 向设备写入设置信息
/// @param models 设置对应的功能模型
/// @param entity 当前的entity
/// @param block 回复设置的状态
/// 使用示例：
/// 如设置：传感器、久坐提醒、蓝牙断开提醒
///   NSMutableArray <JLwSettingModel *>* models = [NSMutableArray new];
/// /*计步相关传感器*/
/// JLSensorFuncModel *model = [[JLSensorFuncModel alloc] initWhthFuncByte:0x0073];//详情设置可参考相关接口
/// [models addObject:model];
/// /*久坐设置*/
/// JLSedentaryRmdModel *model1 = [[JLSedentaryRmdModel alloc] initWithModel:s_Shake Status:true];
/// [models addObject:model1];
/// /*蓝牙断开提醒*/
/// JLDisconnectRemindModel *model2 = [[JLDisconnectRemindModel alloc] initWithModel:s_BrightScreen Status:true];
/// [models addObject:model2];
/// [[JLWearable sharedInstance] w_SettingDeviceFuncWith:models withEntity:requestEntity]
/// 本方法的返回结果，需要接收对应的协议：JL_WatchProtocol ，并把遵循协议的对象加入到本单例中
/// -(void)w_addDelegate:(id<JL_WatchProtocol>)delegate;
-(void)w_SettingDeviceFuncWith:(NSArray <JLwSettingModel *> *)models withEntity:(JL_EntityM *)entity result:(JL_CB_Status)block;


@end

NS_ASSUME_NONNULL_END
