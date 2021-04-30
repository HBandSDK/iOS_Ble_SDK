//
//  GRDFUTool.h
//  GRDFU
//
//  Created by Goodix_BLE on 2020/2/13.
//  Copyright © 2020 Goodix. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>
#import "GRDfuTask.h"
#import "GRDFULog.h"

NS_ASSUME_NONNULL_BEGIN

@interface GRDFUTool : NSObject

+ (NSString*)sdkVersion;

//default is NO
+ (void)enableLog:(BOOL)enable;

+ (void)upgradeWithCentralManager: (CBCentralManager*) centralManager
                      identifier : (NSString*) identifier
                    firmwareData : (NSData*) firmwareData
                           reset : (BOOL) reset
                       overwrite : (BOOL) overwrite
                        delegate : (id<GRDProgressDelegate>) delegate
                       extraInfo : (nullable NSDictionary*)info;

+ (void)copyModeUpgradeWithCentralManager: (CBCentralManager*) centralManager
                              identifier : (NSString*) identifier
                            firmwareData : (NSData*) firmwareData
                                copyAddr : (uint32_t) copyAddr
                               overwrite : (BOOL) overwrite
                                delegate : (id<GRDProgressDelegate>) delegate
                               extraInfo : (nullable NSDictionary*)info;

+ (void)abModeUpgradeWithCentralManager: (CBCentralManager*) centralManager
                            identifier : (NSString*) identifier
                         firmwareDatas : (NSArray<NSData*>*) firmwareDatas
                          handlerBlock : (BOOL(^)(GRDfuTask* task, GRDFirmware* selectedFw))handlerBlock
                              delegate : (id<GRDProgressDelegate>) delegate
                             extraInfo : (nullable NSDictionary*)info;


+(void)getImageInfoListWithCentralManager: (CBCentralManager*) centralManager
                              identifier : (NSString*) identifier
                              completion : (BOOL(^)(GRDfuTask* task, NSArray<GRDImgInfo*>* bootInfo))completion
                                delegate : (id<GRDProgressDelegate>) delegate
                               extraInfo : (nullable NSDictionary*)info;


+(void)resetDeviceWithCentralManager: (CBCentralManager*) centralManager
                         identifier : (NSString*) identifier
                     targetBootInfo : (GRDBootInfo*) bootInfo
                           delegate : (id<GRDProgressDelegate>) delegate
                          extraInfo : (nullable NSDictionary*)info;



+ (void)upgradeResourceWithCentralManager: (CBCentralManager*) centralManager
                              identifier : (NSString*) identifier
                                fileData : (NSData*) fileData
                              toExtFlash : (BOOL) toExtFlash
                                  toAddr : (uint32_t)toAddr
                                delegate : (id<GRDProgressDelegate>) delegate
                               extraInfo : (nullable NSDictionary*)info;


+ (void)initOuterFlashWithCentralManager: (CBCentralManager*) centralManager
                             identifier : (NSString*) identifier
                                 SpiCong:(GRDSpiCfg*)spiConfig
                            handleResult:(BOOL(^)(GRDfuTask* task, uint32_t flashId, uint32_t flashSize))resultBlock
                               delegate : (id<GRDProgressDelegate>) delegate
                              extraInfo : (nullable NSDictionary*)info;

+ (void)gusUpgradeWithCentralManager: (CBCentralManager*) centralManager
                         identifier : (NSString*) identifier
                       firmwareData : (NSData*) firmwareData
                           delegate : (id<GRDProgressDelegate>) delegate
                          extraInfo : (nullable NSDictionary*)info;

+ (void)changeDFUModeWithCentralManager: (CBCentralManager*) centralManager
                            identifier : (NSString*) identifier
                                  type : (NSInteger) type
                              delegate : (id<GRDProgressDelegate>) delegate
                             extraInfo : (nullable NSDictionary*)info;

+ (void)checkDeviceWithCentralManager: (CBCentralManager*) centralManager
                          identifier : (NSString*) identifier
                            delegate : (id<GRDProgressDelegate>) delegate
                           extraInfo : (nullable NSDictionary*)info;

+ (void)checkConnectTestWithCentralManager: (CBCentralManager*) centralManager
                        identifier : (NSString*) identifier
                              type : (NSInteger) type
                          delegate : (id<GRDProgressDelegate>) delegate
                         extraInfo : (nullable NSDictionary*)info;

@end



NS_ASSUME_NONNULL_END
