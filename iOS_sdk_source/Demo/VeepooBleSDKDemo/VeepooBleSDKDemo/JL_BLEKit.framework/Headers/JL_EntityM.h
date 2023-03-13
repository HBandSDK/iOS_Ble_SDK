//
//  JL_EntityM.h
//  JL_BLEKit
//
//  Created by 杰理科技 on 2020/9/1.
//  Copyright © 2020 www.zh-jieli.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import <CoreBluetooth/CoreBluetooth.h>
#import <UIKit/UIKit.h>
#import "JL_Tools.h"
#import "JL_ManagerM.h"

NS_ASSUME_NONNULL_BEGIN
//@class JL_EntityM;
typedef NS_ENUM(NSInteger, JL_EntityM_Status) {
    JL_EntityM_StatusBleOFF         = 0,    //BLE蓝牙未开启
    JL_EntityM_StatusConnectFail    = 1,    //BLE连接失败
    JL_EntityM_StatusConnecting     = 2,    //BLE正在连接
    JL_EntityM_StatusConnectRepeat  = 3,    //BLE重复连接
    JL_EntityM_StatusConnectTimeout = 4,    //BLE连接超时
    JL_EntityM_StatusConnectRefuse  = 5,    //BLE被拒绝
    JL_EntityM_StatusPairFail       = 6,    //配对失败
    JL_EntityM_StatusPairTimeout    = 7,    //配对超时
    JL_EntityM_StatusPaired         = 8,    //已配对
    JL_EntityM_StatusMasterChanging = 9,    //正在主从切换
    JL_EntityM_StatusDisconnectOk   = 10,   //已断开成功
    JL_EntityM_StatusNull           = 11,   //Entity为空
};
typedef void(^JL_EntityM_STATUS_BK)(JL_EntityM_Status status);

@interface JL_EntityM : NSObject<NSCopying>
@property(nonatomic,strong) JL_ManagerM   *mCmdManager;             //命令中心

@property(nonatomic,readonly,copy) CBPeripheral  *mPeripheral;      //BLE外设备
@property(nonatomic,strong) NSString        *mSERVICE;              //服务号AE00
@property(nonatomic,strong) NSString        *mRCSP_W;               //命令【写】通道AE01
@property(nonatomic,strong) NSString        *mRCSP_R;               //命令【读】通道AE02
@property(nonatomic,strong) NSData *__nullable mFilterKey;          //过滤码
@property(nonatomic,strong) NSData *__nullable mPairKey;            //配对码
@property(strong,nonatomic) NSData          *mAdvData;

@property(nonatomic,assign) int             mBLE_TIMEOUT;           //连接超时时间
@property(nonatomic,assign) BOOL            mBLE_FILTER_ENABLE;     //是否【开启过滤】
@property(nonatomic,assign) BOOL            mBLE_PAIR_ENABLE;       //是否【开启配对】
@property(nonatomic,assign) BOOL            mBLE_IS_PAIRED;         //是否完成配对
@property(nonatomic,assign) BOOL            mBLE_NEED_OTA;          //是否需要OTA
@property(nonatomic,assign) BOOL            isFrom_HISTROY;
@property(nonatomic,assign) BOOL            isBLE_CHANGE;
@property(nonatomic,assign) BOOL            isCMD_PREPARED;

@property(strong,nonatomic) NSString        *mUUID;
@property(strong,nonatomic) NSNumber        *mRSSI;
@property(readonly,copy,nonatomic)NSString  *mItem;
/**
 * mType值说明：
 *  -1：传统设备
 *  0：AI音箱
 *  1：TWS
 *  2：数码充电仓
 *  3：普通耳机
 *  4：声卡类型
 *  5：手表类型
 */
@property(assign,nonatomic) JL_DeviceType   mType;
@property(assign,nonatomic) BOOL            isExclusive;
@property(assign,nonatomic) BOOL            isBound;
@property(assign,nonatomic) BOOL            isEdrLinked;
@property(assign,nonatomic) BOOL            isCharging;
@property(assign,nonatomic) BOOL            isCharging_L;
@property(assign,nonatomic) BOOL            isCharging_R;
@property(assign,nonatomic) BOOL            isCharging_C;
@property(assign,nonatomic) uint8_t         mPower;
@property(assign,nonatomic) uint8_t         mPower_L;
@property(assign,nonatomic) uint8_t         mPower_R;
@property(assign,nonatomic) uint8_t         mPower_C;
@property(strong,nonatomic) NSString        *mVID;
@property(strong,nonatomic) NSString        *mPID;
@property(strong,nonatomic) NSString        *mEdr;
@property(strong,nonatomic) NSString        *mBleAddr;            //OTA设备需要
@property(assign,nonatomic) uint8_t         mChipType;            //0：690x 1：692x 2：693x
@property(assign,nonatomic) uint8_t         mProtocolType;        //默认0x00
/**
 0x00 - dismiss 不显示弹窗
 0x01 - unconnected 经典蓝牙未连接
    iOS : 不显示电量，请手动连接XXX
    Android：不显示电量，显示连接按钮
 0x02 - connected 经典蓝牙已连接
    iOS：判断已连接的经典蓝牙名是否一致，若未连接或蓝牙名不一致，
         显示“设备已被占用”。若一致，显示电量等信息。
    Android：判断已连接的经典蓝牙Mac是否一致，若未连接或蓝牙Mac不一致，
             显示“设备已被占用”。若一致，显示电量等信息。
 0x03 - connecting 设备正在自动回连
    Android 和 iOS 显示“设备正在自动回连 ”
 0x04 - connectionless 设备不可连接（需要按下配对按键）
    Android 和 iOS 显示配对操作方式
 */
@property(assign,nonatomic) int8_t          mScene;
@property(assign,nonatomic) uint8_t         mSeq;                   //Seq 每次开机会加 1，用于app区分是否同一次开机
@property(assign,nonatomic) uint8_t         mTWS_Paired;            //TWS配对标识，0:未配对 1:已配对
@property(assign,nonatomic) uint8_t         mTWS_Cap;               //0:关盖 1:开盖
@property(assign,nonatomic) uint8_t         mTWS_Mode;              //0:充电模式 1:发射模式
@property(assign,nonatomic) uint8_t         mHeadsetMaster;         //主从标识 (0:从机， 1:主机)
@property(assign,nonatomic) uint8_t         mHeadsetLinkEnable;     //连接标识 (0:可以连接 1:不可连接)
/**
 *  mWatchScene值说明:
 *  0x00:经典蓝牙未连接
 *  0x01:经典蓝牙已连接
 *  0x02:设备正在回连
 *  0x03:设备不可连接 (需要手动进入配对模式)
 */
@property(assign,nonatomic) uint8_t         mWatchScene;            //连接标识 (0:可以连接 1:不可连接)
@property(assign,nonatomic) uint8_t         mWatchWay;              //连接方式 0:ble 1:spp
/// 设备特殊类型
@property(assign,nonatomic) JLDevSpecialType  mSpecialType;

-(void)setBlePeripheral:(CBPeripheral *)mPeripheral;
-(void)setBleItem:(NSString *)mItem;

/**
 更新代理
*/
-(void)updateDelegate;

/**
 释放定时器
*/
-(void)releaseEntityTimer;

/**
 发送RCSP数据
 @param data 数据
 @return 是否已发送
 */
-(BOOL)writeRcspData:(NSData*)data;

/**
调整发数参数
@param isGame 是否为游戏模式
@param mtu 每包发数字节数
@param delay 延时时间
*/
-(void)setGameMode:(BOOL)isGame MTU:(NSUInteger)mtu Delay:(int)delay;

/**
开启GCD发数定时器
@param delay 发数时间间隔
*/
-(void)installTimingModeDelay:(NSTimeInterval)delay;

-(void)flashFinishedAction;


#pragma mark - 连接超时管理
-(void)startTimeout:(int)code;
-(void)stopTimeout;

#pragma mark - EntityM 模型转换
-(void)updateEntity:(NSDictionary*)dic;
+(JL_EntityM*)changeToEntity:(NSDictionary*)dic;
+(NSArray*)turnToEntityArray:(NSArray*)array;

@end

NS_ASSUME_NONNULL_END
