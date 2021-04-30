//
//  EstablishConnCmd.h
//  GRDFU
//
//  Created by dingjian on 2019/12/21.
//  Copyright © 2019 Goodix. All rights reserved.
//
//  用于根据设备的identifier来连接设备

#import "AbsCmd.h"
#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>

NS_ASSUME_NONNULL_BEGIN

@interface EstablishConnCmd : AbsCmd

-(instancetype)setBleManager:(CBCentralManager*)mgr;

-(instancetype)setTargetIdentifier:(NSUUID*)identifier;

-(CBPeripheral*)getConnectedPeripheral;
@end

NS_ASSUME_NONNULL_END
