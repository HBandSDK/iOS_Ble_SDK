//
//  GRDFUBuilder.h
//  GRDFU
//
//  Created by dingjian on 2019/12/21.
//  Copyright © 2019 Goodix. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>
#import "GRDFirmware.h"
#import "GRDSpiCfg.h"

NS_ASSUME_NONNULL_BEGIN

//此处定义几种任务类型

typedef NS_OPTIONS(NSUInteger, GRDTaskType) {
    GRDTaskTypeUpgrade      = 1 << 0,// 1,普通升级
    GRDTaskTypeCopyUpgrade  = 1 << 1,// 2,拷贝升级
    GRDTaskTypeGetImageList = 1 << 2,// 4,获取固件列表
    GRDTaskTypeResetDevice  = 1 << 3,// 8,重启设备
    GRDTaskTypeUpgradeResource  = 1 << 4,// 16,资源升级
    GRDTaskTypeInitOuterFlash  = 1 << 5,// 32,初始化外部存储器
    GRDTaskTypeABUpgrade  = 1 << 6,// 64,AB升级
    GRDTaskTypeDFUMode  = 1 << 7,// 128,切换为DFU模式
    GRDTaskTypeCheckDeviceExist  = 1 << 8,// 256,检查是否有升级后的设备
    GRDTaskTypeConnectTest  = 1 << 9,// 512,指令断联重联

};

@class GRDfuTask;
@protocol GRDProgressDelegate <NSObject>

-(void)dfuTaskDidStartWithType:(GRDTaskType)type extraInfo:(NSDictionary*)extraInfo;
-(void)dfuTaskDidUpdateProgress:(float)percent type:(GRDTaskType)type extraInfo:(NSDictionary*)extraInfo;
-(void)dfuTaskDidAbortForError:(int)errCode message:(NSString*)msg type:(GRDTaskType)type extraInfo:(NSDictionary*)extraInfo;
-(void)dfuTaskDidCompleteWithType:(GRDTaskType)type extraInfo:(NSDictionary*)extraInfo;

@end

@interface GRDfuTask : NSObject

-(instancetype)attachWithIdentifier:(NSUUID*)identifier centralManager:(CBCentralManager*)mgr;

-(instancetype)attachWithConnectedPeripheral:(CBPeripheral*)peripheral centralManager:(CBCentralManager* _Nullable)mgr;

/* Normal mode */
- (instancetype)setDfuMode:(GRDFirmware*)fw needReset:(BOOL)reset forceOverwrite:(BOOL)overwrite;

/* Copy mode */
- (instancetype)setDfuMode:(GRDFirmware*)fw
                  copyMode:(uint32_t)copyAddr
                overwrite : (BOOL) overwrite;

/* Resource mode */
- (instancetype)setDfuMode:(NSData*)fw toExtFlash:(BOOL)extFlash toAddr:(uint32_t)addr;

/* AB mode */
- (instancetype)setDfuMode:(NSArray<GRDFirmware*>*)fwList selectionHandler:(BOOL(^_Nullable)(GRDfuTask* task, GRDFirmware* selectedFw)) handlerBlock;

- (instancetype)attachWithIdentifier:(NSUUID *)identifier centralManager:(CBCentralManager *)mgr setGusMode:(GRDFirmware*)fw;

- (instancetype)attachWithIdentifier:(NSUUID *)identifier centralManager:(CBCentralManager *)mgr dfuType:(NSInteger) type;

- (instancetype)connectTestWithIdentifier:(NSUUID *)identifier centralManager:(CBCentralManager *)mgr type:(NSInteger)type;

- (instancetype)checkDeviceWithIdentifier:(NSUUID *)identifier centralManager:(CBCentralManager *)mgr;




- (instancetype)setCtrlData:(NSData*)data;
- (instancetype)setDelay:(float)second;
- (instancetype)resetDevice:(GRDBootInfo* _Nullable)toRunFw;
- (instancetype)getBootInfo:(BOOL(^)(GRDfuTask* task, GRDBootInfo* bootInfo))resultBlock;
- (instancetype)getImgInfoList:(BOOL(^)(GRDfuTask* task, NSArray<GRDImgInfo*>* bootInfo))resultBlock;
- (instancetype)prepareExtFlash:(GRDSpiCfg*)cfg handleResult:(BOOL(^)(GRDfuTask* task, uint32_t flashId, uint32_t flashSize))resultBlock;
- (instancetype)upgradeResourceWithFileData:(NSData*) fileData toExtFlash:(BOOL)toExtFlash toAddr:(uint32_t) toAddr;

- (instancetype)start:(id<GRDProgressDelegate>)callback;

/* For future usage */
-(CBCentralManager*)getCentralManager;
-(CBPeripheral*)getPeripheral;

- (void)setExtraInfo:(NSDictionary *)extraInfo;

@end

NS_ASSUME_NONNULL_END
