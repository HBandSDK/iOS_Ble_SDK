//
//  AbsPeripheralCmd.h
//  GRDFU
//
//  Created by dingjian on 2019/12/21.
//  Copyright © 2019 Goodix. All rights reserved.
//

#import "AbsCmd.h"
#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>

NS_ASSUME_NONNULL_BEGIN

@interface AbsPeripheralCmd : AbsCmd <CBPeripheralDelegate, CBCentralManagerDelegate>
{
    @protected
    CBPeripheral* _connectedPeripheral;
    id<CBPeripheralDelegate> _orgDelegateOfPeripheral;

    CBCentralManager* _centralManager;

    BOOL _abortOnDisconnection;
}

@property(nonatomic, weak) id<CBCentralManagerDelegate> orgDelegateOfCentralManager;

-(void)setConnectedPeripheral:(CBPeripheral*)peripheral;
-(void)setCentralManager:(CBCentralManager*)mgr;
-(void)setAbortOnDisconnection:(BOOL)enable;

@end

NS_ASSUME_NONNULL_END
