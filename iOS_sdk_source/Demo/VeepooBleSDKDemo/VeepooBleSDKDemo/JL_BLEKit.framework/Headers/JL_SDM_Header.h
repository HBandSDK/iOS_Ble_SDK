//
//  JL_SDM_Header.h
//  JL_BLEKit
//
//  Created by EzioChan on 2021/4/8.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#ifndef JL_SDM_Header_h
#define JL_SDM_Header_h

#import <Foundation/Foundation.h>
#import "JL_SDM_Stress.h"
#import "JL_SDM_Altitude.h"
#import "JL_SDM_MaxOxg.h"
#import "JL_SDM_RecTime.h"
#import "JL_SDM_HeartRate.h"
#import "JL_SDM_MoveSteps.h"
#import "JL_SDM_TrainLoad.h"
#import "JL_SDM_AirPressure.h"
#import "JL_SDM_OxSaturation.h"
#import "JL_SDM_SportMessage.h"
#import "JL_MSG_Weather.h"
#import "JL_MSG_Func.h"
#import "JLWatchEnum.h"
#import "NfcModel.h"
#import "JLwSettingModel.h"
#import "JLSensorFuncModel.h"
#import "JLSedentaryRmdModel.h"
#import "JLConsequentHeartRateModel.h"
#import "JLExerciseHeartRateRemindModel.h"
#import "JLAutoPressureModel.h"
#import "JLSleepMonitorModel.h"
#import "JLFallDetectionModel.h"
#import "JLEmergencyContactModel.h"
#import "JLOxygenSturationRemindModel.h"
#import "JLWristLiftDetectionModel.h"
#import "JLPersonInfoModel.h"
#import "JLDisconnectRemindModel.h"
#import "JLWearSyncInfoModel.h"
#import "JLWearSyncFinishModel.h"
#import "JLWearSyncRealTimeModel.h"
#import "JLWearSyncHealthChart.h"
#import "JLWearSyncHealthHeartRateChart.h"
#import "JLWearSyncHealthBloodOxyganChart.h"
#import "JLWearSyncHealthSleepChart.h"
#import "JLWearSyncHealthStepChart.h"
#import "JLWearSyncHealthWeightChart.h"


#include <syslog.h>
#ifndef JL_IOS
#define JL_IOS
#endif

#pragma - Please select your log mode and log level

// Note: Only debug mode will print log. You could also set mode for log level.
#define kJLDebugMode
// JLLogLevelFatal , JLLogLevelError , JLLogLevelWarn , JLLogLevelInfo , JLLogLevelDebug
#define JLLogLevelError
//Note: print method name
#define kModuleName __func__

#pragma ----------------------------------

#ifdef kJLDebugMode

static const int JL_IOS_FLAG_FATAL = 0x10;
static const int JL_IOS_FLAG_ERROR = 0x08;
static const int JL_IOS_FLAG_WARN  = 0x04;
static const int JL_IOS_FLAG_INFO  = 0x02;
static const int JL_IOS_FLAG_DEBUG = 0x01;

#ifdef JLLogLevelFatal
static const int JL_IOS_LOG_LEVEL = JL_IOS_FLAG_FATAL;
#elif defined(JLLogLevelError)
static const int JL_IOS_LOG_LEVEL = (JL_IOS_FLAG_FATAL | JL_IOS_FLAG_ERROR);
#elif defined(JLLogLevelWarn)
static const int JL_IOS_LOG_LEVEL = (JL_IOS_FLAG_FATAL | JL_IOS_FLAG_ERROR | JL_IOS_FLAG_WARN);
#elif defined(JLLogLevelInfo)
static const int JL_IOS_LOG_LEVEL = (JL_IOS_FLAG_FATAL | JL_IOS_FLAG_ERROR | JL_IOS_FLAG_WARN | JL_IOS_FLAG_INFO);
#elif defined(JLLogLevelDebug)
static const int JL_IOS_LOG_LEVEL = (JL_IOS_FLAG_FATAL | JL_IOS_FLAG_ERROR | JL_IOS_FLAG_WARN | JL_IOS_FLAG_INFO | JL_IOS_FLAG_DEBUG);
#endif



#define log4cplus_fatal(category, logFmt, ...) \
if(JL_IOS_LOG_LEVEL & JL_IOS_FLAG_FATAL) \
syslog(LOG_CRIT, "%s:" logFmt, category,##__VA_ARGS__); \

#define log4cplus_error(category, logFmt, ...) \
if(JL_IOS_LOG_LEVEL & JL_IOS_FLAG_ERROR) \
syslog(LOG_ERR, "%s:" logFmt, category,##__VA_ARGS__); \

#define log4cplus_warn(category, logFmt, ...) \
if(JL_IOS_LOG_LEVEL & JL_IOS_FLAG_WARN) \
syslog(LOG_WARNING, "%s:" logFmt, category,##__VA_ARGS__); \

#define log4cplus_info(category, logFmt, ...) \
if(JL_IOS_LOG_LEVEL & JL_IOS_FLAG_INFO) \
syslog(LOG_WARNING, "%s:" logFmt, category,##__VA_ARGS__); \

#define log4cplus_debug(category, logFmt, ...) \
if(JL_IOS_LOG_LEVEL & JL_IOS_FLAG_DEBUG) \
syslog(LOG_WARNING, "%s:" logFmt, category,##__VA_ARGS__); \


#else

#define log4cplus_fatal(category, logFmt, ...); \

#define log4cplus_error(category, logFmt, ...); \

#define log4cplus_warn(category, logFmt, ...); \

#define log4cplus_info(category, logFmt, ...); \

#define log4cplus_debug(category, logFmt, ...); \

#endif

///心率
typedef void(^JL_CB_HeartRate)(JL_SDM_HeartRate *heartRate);
///气压
typedef void(^JL_CB_AirPressure)(JL_SDM_AirPressure *ap);
///海拔
typedef void(^JL_CB_Altitude)(JL_SDM_Altitude *altitude);
///运动步数
typedef void(^JL_CB_MoveSteps)(JL_SDM_MoveSteps *ms);
///压力检测
typedef void(^JL_CB_Stress)(JL_SDM_Stress *stress);
///血氧饱和度
typedef void(^JL_CB_Oxsaturation)(JL_SDM_OxSaturation *oxs);
///训练负荷
typedef void(^JL_CB_TrainLoad)(JL_SDM_TrainLoad *tl);
///最大摄氧量
typedef void(^JL_CB_MaxOxg)(JL_SDM_MaxOxg *mo);
///运动恢复时间
typedef void(^JL_CB_RecTime)(JL_SDM_RecTime *rt);
///运动信息
typedef void(^JL_CB_SportMsg)(JL_SDM_SportMessage *sm);
///传感器log
typedef void(^JL_CB_WatchLog)(JL_WATCH_LOG_TYPE type,NSData *data);

//MARK:设置相关
///设置状态回复
typedef void(^JL_CB_Status)(BOOL succeed);

//MARK: - 同步相关
///读取同步运动状态
typedef void(^JL_CB_SyncSportInfo)(JLWearSyncInfoModel *infoModel);
/// 读取同步状态
typedef void(^JL_CB_SyncSportDataInfo)(JLWearSyncDataModel *infoModel);


#endif /* JL_SDM_Header_h */
