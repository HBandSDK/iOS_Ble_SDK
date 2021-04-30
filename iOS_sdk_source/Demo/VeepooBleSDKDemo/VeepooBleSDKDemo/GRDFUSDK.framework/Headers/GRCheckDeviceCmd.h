//
//  GRGusCmd.h
//  Charts
//
//  Created by Goodix_BLE on 2020/5/25.
//

#import "AbsCmd.h"
#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>

NS_ASSUME_NONNULL_BEGIN

@interface GRCheckDeviceCmd : AbsCmd

-(instancetype)setBleManager:(CBCentralManager*)mgr;

-(instancetype)setTargetIdentifier:(NSUUID*)identifier;

@end

NS_ASSUME_NONNULL_END
