//
//  GRGusCmd.h
//  Charts
//
//  Created by Goodix_BLE on 2020/5/25.
//

#import "AbsPeripheralCmd.h"
#import "GRDFirmware.h"
#import "GRDfuProfile.h"
#import "GCXHexReader.h"
#import "GCXHexBuilder.h"

NS_ASSUME_NONNULL_BEGIN

@interface GRDFUModeCmd : AbsPeripheralCmd
{
    @protected
    CBCharacteristic* _txChar; // 本机发送数据的端口
    CBCharacteristic* _rxChar; // 本机接收数据的端口
    CBCharacteristic* _ctrlChar; // 本机发送控制数据的端口
}

@property (nonatomic, assign) NSInteger type;

@end

NS_ASSUME_NONNULL_END
