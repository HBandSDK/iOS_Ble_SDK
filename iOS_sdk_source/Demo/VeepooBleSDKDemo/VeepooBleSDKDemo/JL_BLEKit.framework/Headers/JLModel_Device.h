//
//  JLModel_Device.h
//  JL_BLEKit
//
//  Created by 杰理科技 on 2021/10/15.
//  Copyright © 2021 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JL_TypeEnum.h"
#import "JLModel_Flash.h"
#import "JLModel_ANC.h"
#import "JLModel_RTC.h"
#import "JLModel_FM.h"
#import "JLModel_File.h"
#import "JLModel_EQ.h"


NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(UInt8, JL_DevicePlatform) {
    JL_DevicePlatformTuring         = 0,    //适用于【图灵】
    JL_DevicePlatformDeepbrain      = 1,    //适用于【Deepbrain】
    JL_DevicePlatformUnknown,
};
typedef NS_ENUM(UInt8, JL_SDKType) {
    JL_SDKTypeAI                    = 0,    //AI SDK  AC692x
    JL_SDKTypeST                    = 1,    //标准 SDK AC692x
    JL_SDKType693xTWS               = 2,    //
    JL_SDKType695xSDK               = 3,    //
    JL_SDKType697xTWS               = 4,    //
    JL_SDKType696xSB                = 5,    //696x_soundbox
    JL_SDKType696xTWS               = 6,    //
    JL_SDKType695xSC                = 7,    //695x_sound_card
    JL_SDKType695xWATCH             = 8,    //BR23 Watch
    JL_SDKType701xWATCH             = 9,    //BR28 Watch
    JL_SDKTypeUnknown,
};
typedef NS_ENUM(UInt8, JL_FunctionCode) {
    JL_FunctionCodeBT               = 0,    //BT
    JL_FunctionCodeMUSIC            = 1,    //音乐
    JL_FunctionCodeRTC              = 2,    //闹钟
    JL_FunctionCodeLINEIN           = 3,    //LineIn
    JL_FunctionCodeFM               = 4,    //FM
    JL_FunctionCodeLIGHT            = 5,    //LIGHT
    JL_FunctionCodeFMTX             = 6,    //发射频点
    JL_FunctionCodeCOMMON           = 0xff, //通用
};
typedef NS_ENUM(UInt8, JL_Partition) {
    JL_PartitionSingle              = 0,    //固件单备份
    JL_PartitionDouble              = 1,    //固件双备份
};
typedef NS_ENUM(UInt8, JL_OtaHeadset) {
    JL_OtaHeadsetNO                 = 0,    //耳机单备份 正常升级
    JL_OtaHeadsetYES                = 1,    //耳机单备份 强制升级
};
typedef NS_ENUM(UInt8, JL_OtaWatch) {
    JL_OtaWatchNO                   = 0,    //手表资源 正常升级
    JL_OtaWatchYES                  = 1,    //手表资源 强制升级
};
typedef NS_ENUM(UInt8, JL_OtaStatus) {
    JL_OtaStatusNormal              = 0,    //正常升级
    JL_OtaStatusForce               = 1,    //强制升级
};
typedef NS_ENUM(UInt8, JL_BootLoader) {
    JL_BootLoaderNO                 = 0,    //不需要下载Bootloader
    JL_BootLoaderYES                = 1,    //需要下载BootLoader
};
typedef NS_ENUM(UInt8, JL_OtaBleAllowConnect) {
    JL_OtaBleAllowConnectYES        = 0,    //OTA 允许BLE连接
    JL_OtaBleAllowConnectNO         = 1,    //OTA 禁止BLE连接
    JL_OtaBleAllowConnectUnknow     = 2,    //未定义
};
typedef NS_ENUM(UInt8, JL_BLEOnly) {        //是否仅仅支持BLE
    JL_BLEOnlyNO                    = 0,    //否
    JL_BLEOnlyYES                   = 1,    //是
};
typedef NS_ENUM(UInt8, JL_FasheEnable) {    //是否发射模式
    JL_FasheEnableNO                = 0,    //否
    JL_FasheEnableYES               = 1,    //是
};
typedef NS_ENUM(UInt8, JL_FasheType) {      //当前是否为发射模式
    JL_FasheTypeNO                  = 0,    //否
    JL_FasheTypeYES                 = 1,    //是
};
typedef NS_ENUM(UInt8, JL_MD5Type) {        //是否支持MD5校验
    JL_MD5TypeNO                    = 0,    //否
    JL_MD5TypeYES                   = 1,    //是
};
typedef NS_ENUM(UInt8, JL_GameType) {       //是否为游戏模式
    JL_GameTypeNO                   = 0,    //否
    JL_GameTypeYES                  = 1,    //是
};
typedef NS_ENUM(UInt8, JL_SearchType) {     //是否支持查找设备
    JL_SearchTypeNO                 = 0,    //否
    JL_SearchTypeYES                = 1,    //是
};
typedef NS_ENUM(UInt8, JL_KaraokeType) {    //是否支持卡拉OK
    JL_KaraokeTypeNO                = 0,    //否
    JL_KaraokeTypeYES               = 1,    //是
};
typedef NS_ENUM(UInt8,JL_KaraokeEQType){    //是否禁止app调节设备音效
    JL_KaraokeEQTypeNO              = 0,    //不禁止
    JL_KaraokeEQTypeYES             = 1,    //禁止
};
typedef NS_ENUM(UInt8,JL_FlashType){        //是否支持外挂Flash
    JL_FlashTypeNO                  = 0,    //不支持
    JL_FlashTypeYES                 = 1,    //支持
};
typedef NS_ENUM(UInt8,JL_AncType){          //是否支持ANC
    JL_AncTypeNO                    = 0,    //不支持
    JL_AncTypeYES                   = 1,    //支持
};
typedef NS_ENUM(UInt8, JL_AudioFileType) {  //是否支持音频文件传输
    JL_AudioFileTypeNO              = 0,    //否
    JL_AudioFileTypeYES             = 1,    //是
};
typedef NS_ENUM(UInt8, JL_FileSubcontractTransferCrc16Type){//文件分包传输是否支持crc16方式
    JL_FileSubcontractTransferCrc16TypeNO      = 0,    //不支持
    JL_FileSubcontractTransferCrc16TypeYES     = 1,    //支持
};
typedef NS_ENUM(UInt8, JL_ReadFileInNewWayType){       //是否以新的方式读取固件文件
    JL_ReadFileInNewWayTypeNO                  = 0,    //不支持
    JL_ReadFileInNewWayTypeYES                 = 1,    //支持
};

typedef NS_ENUM(UInt8, JL_SmallFileWayType){           //是否支持小文件传输
    JL_SmallFileWayTypeNO                      = 0,    //不支持
    JL_SmallFileWayTypeYES                     = 1,    //支持
};

typedef NS_ENUM(UInt8,JL_CALLType) {
    JL_CALLType_OFF                 = 0,    //空闲
    JL_CALLType_ON                  = 1,    //通话中
};

typedef NS_ENUM(UInt8, JL_LightState) {
    JL_LightStateClose          = 0x00, //关闭
    JL_LightStateOpen           = 0x01, //开启
    JL_LightStateSetting        = 0x02, //设置模式
};
typedef NS_ENUM(UInt8, JL_LightMode) {
    JL_LightModeNormal          = 0x00, //彩色模式
    JL_LightModeFlash           = 0x01, //闪烁模式
    JL_LightModeScene           = 0x02, //情景模式
};
typedef NS_ENUM(UInt8, JL_LightFlashModeIndex) {
    JL_LightModeIndexColorfulFlash          = 0x00, //七彩闪烁
    JL_LightModeIndexRedFlash               = 0x01, //红色闪烁
    JL_LightModeIndexOrangeFlash            = 0x02, //橙色闪烁
    JL_LightModeIndexYeallowFlash           = 0x03, //黄色闪烁
    JL_LightModeIndexGreenFlash             = 0x04, //绿色闪烁
    JL_LightModeIndexCyanFlash              = 0x05, //青色闪烁
    JL_LightModeIndexBlueFlash              = 0x06, //蓝色闪烁
    JL_LightModeIndexPurpleFlash            = 0x07, //紫色闪烁
};

typedef NS_ENUM(UInt8, JL_LightFlashModeFrequency) {
    JL_LightFlashModeFrequencyFast          = 0x00, //快闪
    JL_LightFlashModeFrequencySlow          = 0x01, //慢闪
    JL_LightFlashModeFrequencyNormal        = 0x02, //缓闪
    JL_LightFlashModeFrequencyMusic         = 0x03, //音乐闪烁
};

typedef NS_ENUM(UInt8, JL_LightSceneMode) {
    JL_LightSceneModeRainbow                = 0x00, //彩虹
    JL_LightSceneModeHeartbeat              = 0x01, //心跳
    JL_LightSceneModeCandlelight            = 0x02, //烛火
    JL_LightSceneModeNightLight             = 0x03, //夜灯
    JL_LightSceneModeStage                  = 0x04, //舞台
    JL_LightSceneModeDiffuseColourBreathing = 0x05, //漫彩呼吸
    JL_LightSceneModeDiffuseRedBreathing    = 0x06, //漫红呼吸
    JL_LightSceneModeDiffuseGreenBreathing  = 0x07, //漫绿呼吸
    JL_LightSceneModeDiffuseBlueBreathing   = 0x08, //漫蓝呼吸
    JL_LightSceneModeGreenMood              = 0x09, //绿色心情
    JL_LightSceneModeSettingSunView         = 0x10, //夕阳美景
    JL_LightSceneModeMusicRhythm            = 0x11, //音乐律动
};

typedef NS_ENUM(UInt8, JL_FileHandleType) {     //文件句柄
    JL_FileHandleTypeSD_0                 = 0,    //SD_0
    JL_FileHandleTypeSD_1                 = 1,    //SD_1
    JL_FileHandleTypeFLASH                = 2,    //FLASH
    JL_FileHandleTypeUSB                  = 3,    //USB
    JL_FileHandleTypeLineIn               = 4,    //LineIn
    JL_FileHandleTypeFLASH2               = 5,    //FLASH2
};

typedef NS_ENUM(UInt8, JL_MusicMode) {
    JL_MusicModeLoopAll             = 0x01, //全部循环
    JL_MusicModeLoopDevice          = 0x02, //单设备循环
    JL_MusicModeLoopOne             = 0x03, //单曲循环
    JL_MusicModeRandomDevice        = 0x04, //单设备随机
    JL_MusicModeLoopFolder          = 0x05, //文件夹循环
};

typedef NS_ENUM(UInt8, JL_MusicStatus) {
    JL_MusicStatusPlay              = 0x01, //播放
    JL_MusicStatusPause             = 0x00, //暂停
};

typedef NS_ENUM(UInt8, JL_EQType) {         //EQ段数类型
    JL_EQType10                     = 0,    //固定10段式
    JL_EQTypeMutable                = 1,    //动态EQ段
};

//---------------------------------------------------------//
#pragma mark - RTC
typedef NS_ENUM(UInt8, JL_RTCAlarmType) {   //是否支持闹铃设置
    JL_RTCAlarmTypeNO               = 0,    //不支持
    JL_RTCAlarmTypeYES              = 1,    //支持
};
//---------------------------------------------------------//
#pragma mark - LINEIN
typedef NS_ENUM(UInt8, JL_LineInStatus) {
    JL_LineInStatusPause            = 0x00, //暂停
    JL_LineInStatusPlay             = 0x01, //播放
    JL_LineInStatusUnknown,
};
//---------------------------------------------------------//
#pragma mark - FM
typedef NS_ENUM(UInt8, JL_FMStatus) {
    JL_FMStatusPause                = 0x01, //播放
    JL_FMStatusPlay                 = 0x02, //暂停
    JL_FMStatusSearching            = 0x03, //搜索中
    JL_FMStatusUnknown,
};
typedef NS_ENUM(UInt8, JL_FMMode) {
    JL_FMMode875Mhz                 = 0x00, //87.5-108.0Mhz
    JL_FMMode760Mhz                 = 0x01, //76.5-108.0Mhz
    JL_FMModeUnknown,
};


@interface JLModel_Device : NSObject<NSCopying>
@property (copy,  nonatomic) NSString           *mBLE_UUID;       //设备UUID

@property (copy,  nonatomic) NSString           *versionProtocol;       //协议版本
@property (copy,  nonatomic) NSString           *versionFirmware;       //固件版本
@property (assign,nonatomic) JL_SDKType         sdkType;                //SDK类型
@property (assign,nonatomic) NSUInteger         battery;                //电量0~9
@property (assign,nonatomic) NSUInteger         currentVol;             //当前音量
@property (assign,nonatomic) NSUInteger         maxVol;                 //最大音量
@property (copy,  nonatomic) NSString           *btAddr;                //经典蓝牙地址
@property (copy,  nonatomic) NSString           *license;               //平台序列号
@property (assign,nonatomic) JL_DevicePlatform  platform;               //平台类型（图灵，Deepbrain）
@property (assign,nonatomic) JL_DeviceBTStatus  btStatus;               //经典蓝牙状态
@property (assign,nonatomic) uint32_t           function;               //BIT(0):BT BIT(1):MUSIC BIT(2):RTC
@property (assign,nonatomic) JL_FunctionCode    currentFunc;            //当前处于的模式
@property (assign,nonatomic) uint8_t            funcOnlineStatus;       //USb,SD,LineIn,网络电台是否在线
@property (copy,  nonatomic) NSString           *versionUBoot;          //uboot版本
@property (assign,nonatomic) JL_Partition       partitionType;          //设备单、双备份
@property (assign,nonatomic) JL_OtaStatus       otaStatus;              //OTA状态
@property (assign,nonatomic) JL_OtaHeadset      otaHeadset;             //耳机单备份 是否需要强制升级
@property (assign,nonatomic) JL_OtaWatch        otaWatch;               //手表资源 是否需要强制升级
@property (copy,  nonatomic) NSString           *pidvid;                //厂商ID
@property (copy,  nonatomic) NSString           *authKey;               //授权Key
@property (copy,  nonatomic) NSString           *proCode;               //授权Code
@property (assign,nonatomic) JL_BootLoader      bootLoaderType;         //是否下载BootLoader
@property (assign,nonatomic) JL_OtaBleAllowConnect otaBleAllowConnect;  //OTA是否允许BLE连接
@property (assign,nonatomic) JL_BLEOnly         bleOnly;                //是否仅仅支持BLE
@property (copy,  nonatomic) NSString           *bleAddr;                //ble蓝牙地址
@property (assign,nonatomic) JL_FasheEnable     fasheEnable;            //是否支持发射模式
@property (assign,nonatomic) JL_FasheType       fasheType;              //当前是否为发射模式
@property (assign,nonatomic) JL_MD5Type         md5Type;                //是否支持MD5固件校验
@property (assign,nonatomic) JL_GameType        gameType;               //是否为游戏模式
@property (assign,nonatomic) BOOL               isSupportGameModel;               //是否支持游戏模式
@property (assign,nonatomic) JL_SearchType      searchType;             //是否支持查找设备
@property (assign,nonatomic) JL_KaraokeType     karaokeType;            //是否支持卡拉OK
@property (assign,nonatomic) JL_KaraokeEQType   karaokeEQType;          //是否禁止app调节设备音效
@property (assign,nonatomic) JL_FlashType       flashType;              //是否外挂flash
@property (assign,nonatomic) JL_AncType         ancType;                //是否支持ANC
@property (assign,nonatomic) JL_AudioFileType   audioFileType;          //是否支持音频文件传输功能
/// 是否支持日志获取
@property (assign,nonatomic) BOOL               isSupportLog;
@property (assign,nonatomic) int                pitchLow;               //低音
@property (assign,nonatomic) int                pitchHigh;              //高音
@property (copy,  nonatomic) JLModel_Flash      *flashInfo;             //外挂flash信息

/*--- File INFO ---*/
@property (assign,nonatomic) JL_FileHandleType        currentFileHandleType;                        //当前文件传输句柄
@property (assign,nonatomic) JL_FileSubcontractTransferCrc16Type fileSubcontractTransferCrc16Type;  //文件分包传输是否支持crc16方式
@property (assign,nonatomic) JL_ReadFileInNewWayType readFileInNewWayType;                          //是否以新的方式读取固件文件
@property (assign,nonatomic) JL_SmallFileWayType smallFileWayType;                                  //是否小文件方式传输

/*--- 公用INFO ---*/
@property (copy,  nonatomic) NSArray            *cardArray;             //卡的数组
@property (copy,  nonatomic) NSString           *handleUSB;             //USB   handle
@property (copy,  nonatomic) NSString           *handleSD_0;            //SD_0  handle
@property (copy,  nonatomic) NSString           *handleSD_1;            //SD_1  handle
@property (copy,  nonatomic) NSString           *handleFlash;           //Flash handle
@property (copy,  nonatomic) NSString           *handleFlash2;          //Flash handle2
@property (copy,  nonatomic) NSData             *handleUSBData;         //USB    handle Data
@property (copy,  nonatomic) NSData             *handleSD_0Data;        //SD_0   handle Data
@property (copy,  nonatomic) NSData             *handleSD_1Data;        //SD_1   handle Data
@property (copy,  nonatomic) NSData             *handleFlashData;       //Flash  handle Data
@property (copy,  nonatomic) NSData             *handleFlash2Data;      //Flash2 handle Data
@property (assign,nonatomic) JL_EQMode          eqMode;                 //EQ模式
@property (copy,  nonatomic) NSArray            *eqArray;               //EQ参数值（只适用于EQ Mode == CUSTOM情况）
@property (copy,  nonatomic) NSArray            *eqCustomArray;         //自定义EQ
@property (copy,  nonatomic) NSArray            *eqFrequencyArray;      //EQ频率
@property (assign,nonatomic) JL_EQType          eqType;                 //EQ段数类型F
@property (strong,nonatomic) NSArray            *eqDefaultArray;        //EQ的预设值数组 数组元素类型-->【JLEQModel】
@property (copy,  nonatomic) NSString           *errReason;             //错误原因
@property (assign,nonatomic) uint16_t           fmtxPoint;              //发射频点
@property (assign,nonatomic) uint8_t            mTWS_Mode;              //0x00:普通模式 0x01:发射模式
@property (assign,nonatomic) uint8_t            mTWS_Status;            //0x00:未连接   0x01:已连接
@property (copy  ,nonatomic) NSString           *mTWS_Addr;             //发射模式中，连接的外设地址
@property (copy  ,nonatomic) JLModel_ANC        *mAncModeCurrent;       //当前ANC的模式
@property (copy  ,nonatomic) NSMutableArray     *mAncModeArray;         //ANC模式数组

@property (assign,nonatomic) JL_CALLType        mCallType;              //通话状态
@property (strong,nonatomic) NSArray            *reverberationTypes;    //混响所支持的类型
@property (assign,nonatomic) int                reverberationSwitchState;   //混响的开关
@property (assign,nonatomic) int                depthValue;                 //深度值
@property (assign,nonatomic) int                intensityValue;             //强度值
@property (assign,nonatomic) int                dynamicLimiterValue;        //限幅值
@property (assign,nonatomic) long               kalaokIndex;                //卡拉OK 组件索引
@property (assign,nonatomic) long               kalaokValue;                //卡拉OK 组件的值
@property (assign,nonatomic) uint64_t           kalaokMask;                 //卡拉OK 固件返回的掩码
@property (strong,nonatomic) NSArray            *mKaraokeMicFrequencyArray; //卡拉OK 频率数组
@property (strong,nonatomic) NSArray            *mKaraokeMicEQArray;        //卡拉OK EQ数组
@property (assign,nonatomic) JL_LightState      lightState;             // 0:关闭 1：打开 2：设置模式(彩色/闪烁/情景)
@property (assign,nonatomic) JL_LightMode       lightMode;              // 0：彩色 1:闪烁 2: 情景
@property (assign,nonatomic) uint8_t            lightRed;               // 灯光红色
@property (assign,nonatomic) uint8_t            lightGreen;             // 灯光绿色
@property (assign,nonatomic) uint8_t            lightBlue;              // 灯光蓝色
@property (assign,nonatomic) JL_LightFlashModeIndex lightFlashIndex;        // 闪烁模式Index
@property (assign,nonatomic) JL_LightFlashModeFrequency lightFrequencyIndex;    // 闪烁频率Index
@property (assign,nonatomic) JL_LightSceneMode  lightSceneIndex;        // 情景模式Index
@property (assign,nonatomic) uint16_t           lightHue;               // 色调，范围0-360
@property (assign,nonatomic) uint8_t            lightSat;               // 饱和度，0-100
@property (assign,nonatomic) uint8_t            lightLightness;         // 亮度，0-100

/*--- BT INFO ---*/
@property (strong,nonatomic) NSString           *ID3_Title;
@property (strong,nonatomic) NSString           *ID3_Artist;
@property (strong,nonatomic) NSString           *ID3_AlBum;
@property (assign,nonatomic) uint8_t            ID3_Number;
@property (assign,nonatomic) uint16_t           ID3_Total;
@property (strong,nonatomic) NSString           *ID3_Genre;
@property (assign,nonatomic) uint32_t           ID3_Time;
@property (assign,nonatomic) uint8_t            ID3_Status;             // 0x01:播放 0x00:暂停
@property (assign,nonatomic) uint32_t           ID3_CurrentTime;

/*--- Music INFO ---*/
@property (assign,nonatomic) JL_MusicStatus     playStatus;             //播放状态
@property (assign,nonatomic) JL_MusicMode       playMode;               //播放模式
@property (assign,nonatomic) uint32_t           currentClus;            //当前播放文件的簇号
@property (assign,nonatomic) uint32_t           currentTime;            //当前时间
@property (assign,nonatomic) uint32_t           tolalTime;              //总时长
@property (assign,nonatomic) JL_CardType        currentCard;            //当前卡
@property (copy,  nonatomic) NSString           *fileName;              //名字
@property (copy,  nonatomic) NSString           *typeSupport;           //解码音频格式
    
/*--- RTC INFO ---*/
@property (assign,nonatomic) uint8_t             rtcVersion;            //RTC 版本
@property (assign,nonatomic) JL_RTCAlarmType     rtcAlarmType;          //是否支持闹铃设置
@property (strong,nonatomic) JLModel_RTC         *rtcModel;             //设备当前时间
@property (strong,nonatomic) NSMutableArray      *rtcAlarms;            //设备闹钟数组
@property (strong,nonatomic) NSMutableArray      *rtcDfRings;           //默认铃声

/*--- LineIn INFO ---*/
@property (assign,nonatomic) JL_LineInStatus    lineInStatus;           //LineIn状态

/*--- FM INFO ---*/
@property (assign,nonatomic) JL_FMStatus        fmStatus;               //Fm状态
@property (assign,nonatomic) JL_FMMode          fmMode;                 //Fm 76.0或87.5
@property (strong,nonatomic) JLModel_FM          *currentFm;            //当前fm
@property (strong,nonatomic) NSArray            *fmArray;               //Fm列表

/*custom version info*/

/// 自定义版本信息
@property(strong,nonatomic) NSData              *customizeInfo;


-(void)cleanMe;
+(void)observeModelProperty:(NSString*)prty Action:(SEL)action Own:(id)own;
+(void)removeModelProperty:(NSString*)prty Own:(id)own;

#pragma mark ---> 设备信息
-(void)deviceInfoData:(NSData*)infoData;

#pragma mark ---> 各个模式信息
-(void)deviceModeInfoData:(NSData*)infoData;


@end

NS_ASSUME_NONNULL_END
