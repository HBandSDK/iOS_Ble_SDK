//
//  JL_ManagerM.h
//  JL_BLEKit
//
//  Created by 杰理科技 on 2020/9/4.
//  Copyright © 2020 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <JL_BLEKit/JL_TypeEnum.h>
#import <JL_BLEKit/JL_RCSP.h>

#import <JL_BLEKit/JLModel_Device.h>
#import <JL_BLEKit/JLModel_RTC.h>
#import <JL_BLEKit/JLModel_Ring.h>
#import <JL_BLEKit/JLModel_File.h>
#import <JL_BLEKit/JLModel_FM.h>
#import <JL_BLEKit/JLModel_Headset.h>
#import <JL_BLEKit/JLModel_BT.h>
#import <JL_BLEKit/JLModel_EQ.h>
#import <JL_BLEKit/JLModel_SPEEX.h>
#import <JL_BLEKit/JLModel_Flash.h>
#import <JL_BLEKit/JLModel_ANC.h>
#import <JL_BLEKit/JLModel_AlarmSetting.h>
#import <JL_BLEKit/RTC_RingInfo.h>

#import <JL_BLEKit/JL_FunctionBaseManager.h>
#import <JL_BLEKit/JL_SmallFileManager.h>
#import <JL_BLEKit/JL_FileManager.h>
#import <JL_BLEKit/JL_OTAManager.h>
#import <JL_BLEKit/JL_FlashOperateManager.h>
#import <JL_BLEKit/JL_BinChargeManager.h>
#import <JL_BLEKit/JL_AlarmClockManager.h>
#import <JL_BLEKit/JL_CallManager.h>
#import <JL_BLEKit/JL_LightManager.h>
#import <JL_BLEKit/JL_TwsManager.h>
#import <JL_BLEKit/JL_SoundCardManager.h>
#import <JL_BLEKit/JL_LrcManager.h>
#import <JL_BLEKit/JL_SpeexManager.h>
#import <JL_BLEKit/JL_FindDeviceManager.h>
#import <JL_BLEKit/JL_MusicControlManager.h>
#import <JL_BLEKit/JL_FmManager.h>
#import <JL_BLEKit/JL_SystemEQ.h>
#import <JL_BLEKit/JL_SystemTime.h>
#import <JL_BLEKit/JL_SystemVolume.h>
#import <JL_BLEKit/JL_CustomManager.h>
#import <JL_BLEKit/JL_BatchManger.h>
#import <JL_BLEKit/JL_DeviceLogs.h>

NS_ASSUME_NONNULL_BEGIN

/*
 *  从JL_ManagerM发出去的通知都是字典，如下所示：
 *
 *  @{ kJL_MANAGER_KEY_UUID  :当前设备的UUID,
 *     kJL_MANAGER_KEY_OBJECT:外抛的对象 }
 */
extern NSString *kJL_MANAGER_KEY_UUID;      //KEY --> UUID
extern NSString *kJL_MANAGER_KEY_OBJECT;    //KEY --> 对象


@protocol JL_ManagerMDelegate <NSObject>
@optional
-(void)onManagerSendPackage:(JL_PKG*)pkg;

@end

@class JL_EntityM;
@interface JL_ManagerM : NSObject
@property(nonatomic,weak)id<JL_ManagerMDelegate>delegate;
@property(nonatomic,readonly,copy)NSString  *mBLE_UUID;
@property(nonatomic,readonly,copy)NSString  *mBLE_NAME;
@property(nonatomic,readonly,assign)uint8_t mCmdSN;
@property(nonatomic,weak)JL_EntityM         *mEntity;

@property(nonatomic,strong)JL_SmallFileManager      *mSmallFileManager;
@property(nonatomic,strong)JL_FileManager           *mFileManager;
@property(nonatomic,strong)JL_OTAManager            *mOTAManager;
@property(nonatomic,strong)JL_FlashOperateManager   *mFlashManager;
@property(nonatomic,strong)JL_BinChargeManager      *mChargingBinManager;
@property(nonatomic,strong)JL_CallManager           *mCallManager;
@property(nonatomic,strong)JL_AlarmClockManager     *mAlarmClockManager;
@property(nonatomic,strong)JL_LightManager          *mLightManager;
@property(nonatomic,strong)JL_TwsManager            *mTwsManager;
@property(nonatomic,strong)JL_SoundCardManager      *mSoundCardManager;
@property(nonatomic,strong)JL_SpeexManager          *mSpeexManager;
@property(nonatomic,strong)JL_LRCManager            *mLrcManager;
@property(nonatomic,strong)JL_FindDeviceManager     *mFindDeviceManager;
@property(nonatomic,strong)JL_MusicControlManager   *mMusicControlManager;
@property(nonatomic,strong)JL_FmManager             *mFmManager;
@property(nonatomic,strong)JL_SystemEQ              *mSystemEQ;
@property(nonatomic,strong)JL_SystemTime            *mSystemTime;
@property(nonatomic,strong)JL_SystemVolume          *mSystemVolume;
@property(nonatomic,strong)JL_CustomManager         *mCustomManager;
@property(nonatomic,strong)JL_BatchManger           *mBatchManger;
@property(nonatomic,strong)JL_DeviceLogs            *mDeviceLogs;


-(void)setBleUuid:(NSString*)uuid;
-(void)setBleName:(NSString*)name;
-(void)inputPKG:(JL_PKG*)pkg;

-(void)noteEntityConnected;
-(void)noteEntityDisconnected;
-(void)noteEntityBleOff;

/**
 发送【命令包】
 @param cmdCode 具体要发送的命令
 @param needResponse 是否需要回复
 @param sendData 具体要发送的数据
 @discussion 只有isCommand是YES时needResponse才有意义，即只有命令才需要回复
 */
-(void)xmCommandCode:(uint8_t)cmdCode
             needRep:(BOOL)needResponse
                data:(NSData *)sendData;

/**
 发送【回复包】
 @param code  命令号
 @param sn      序号
 @param st      状态码
 @param data 回复的命令的内容
 */
-(void)cmdResponseCode:(uint8_t)code
                  OpSN:(UInt8)sn
                Status:(JL_CMDStatus)st
                  Data:(NSData* __nullable)data;

/**
 发送【通知命令】
 @param name    通知名字
 @param obj       携带对象
 */
-(void)managerPost:(NSString*)name Object:(id __nullable)obj;

/**
  获取当前命令序号
 */
-(uint8_t)xmCommandSN;

#pragma mark ---> 取出设备信息
-(JLModel_Device *)outputDeviceModel;

#pragma mark ---> 获取设备信息
extern NSString *kJL_MANAGER_TARGET_INFO;
-(void)cmdTargetFeatureResult:(JL_CMD_RESPOND __nullable)result;
-(void)cmdTargetFeature:(uint32_t)feature Result:(JL_CMD_RESPOND __nullable)result;

#pragma mark ---> 断开经典蓝牙
-(void)cmdDisconnectEdrResult:(JL_CMD_RESPOND __nullable)result;

#pragma mark ---> 重置配对流程标志（使适配连接ANCS设备）
-(void)cmdResetPairingResult:(JL_CMD_RESPOND __nullable)result;

#pragma mark ---> 获取系统信息（全获取）
/**
 @param function JL_FunctionCode
 @param result 回复
 */
-(void)cmdGetSystemInfo:(JL_FunctionCode)function
                 Result:(JL_CMD_RESPOND __nullable)result;
-(void)cmdGetSystemInfoResult;

#pragma mark ---> 获取系统信息（选择性获取）
/**
 @param function JL_FunctionCode
 @param result 回复
 */
-(void)cmdGetSystemInfo:(JL_FunctionCode)function
           SelectionBit:(uint32_t)bits
                 Result:(JL_CMD_RESPOND __nullable)result;
-(void)cmdGetSystemInfoResult_1;

#pragma mark ---> 设备主动返回的系统信息
extern NSString *kJL_MANAGER_SYSTEM_INFO;

#pragma mark ---> 通用、BT、Music、RTC、Aux
/**
 @param function 功能类型
 @param cmd 操作命令
 @param ext 扩展数据
 @param result 回复
 */
-(void)cmdFunction:(JL_FunctionCode)function
           Command:(UInt8)cmd
            Extend:(UInt8)ext
            Result:(JL_CMD_RESPOND __nullable)result;

typedef void(^JL_IMAGE_RT)(NSMutableDictionary* __nullable dict);
#pragma mark ---> 获取设备的图片
/**
 @param vid 设备vid
 @param pid 设备pid
 @param result 图片数据
 */
-(void)cmdRequestDeviceImageVid:(NSString*)vid
                            Pid:(NSString*)pid
                         Result:(JL_IMAGE_RT __nullable)result;

-(void)cmdRequestDeviceImageVid:(NSString*)vid
                            Pid:(NSString*)pid
                      ItemArray:(NSArray *__nullable)itemArray
                         Result:(JL_IMAGE_RT __nullable)result;

-(NSDictionary*)localDeviceImage:(NSString*)jsonFile;

#pragma mark ---> 通知固件开始播放TTS内容
-(void)cmdStartTTSNote;


/// 获取MD5信息
/// @param result 回调
-(void)cmdGetMD5_Result:(JL_CMD_RESPOND)result;

@end

NS_ASSUME_NONNULL_END
