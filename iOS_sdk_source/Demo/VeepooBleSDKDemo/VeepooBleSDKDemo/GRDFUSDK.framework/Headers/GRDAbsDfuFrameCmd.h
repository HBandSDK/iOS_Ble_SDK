//
//  AbsDfuCmd.h
//  GRDFU
//
//  Created by dingjian on 2019/12/22.
//  Copyright © 2019 Goodix. All rights reserved.
//
//  封装DFU通信协议的大包和解包

#import "AbsPeripheralCmd.h"

#define FIELD_SIZEOF_ACK  1
#define ACK_OK  0x01
#define ACK_ERR 0x02

NS_ASSUME_NONNULL_BEGIN

@interface GRDAbsDfuFrameCmd : AbsPeripheralCmd
{
    @protected
    CBCharacteristic* _txChar; // 本机发送数据的端口
    CBCharacteristic* _rxChar; // 本机接收数据的端口
    CBCharacteristic* _ctrlChar; // 本机发送控制数据的端口
}

-(BOOL)sendCmd:(int)code param:(NSData*)param;
-(void)onRcvCmd:(int)code param:(NSData*)param;

@end

NS_ASSUME_NONNULL_END
