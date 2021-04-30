//
//  GRDSetSpiCfg.h
//  GRDFU
//
//  Created by dingjian on 2019/12/26.
//  Copyright © 2019 Goodix. All rights reserved.
//

#import "GRDAbsDfuFrameCmd.h"
#import "GRDSpiCfg.h"

NS_ASSUME_NONNULL_BEGIN

/**
 This command will configure the IO of SPI and read the information of extern flash.
 */
@interface GRDInitExtFlashCmd : GRDAbsDfuFrameCmd
{
    @public
    GRDSpiCfg* _spiCfg;

    // the information read from extern flash
    uint32_t _flashId;
    uint32_t _flashSize;
}
/**
 If SPI Config is not specified, this command will only read the information of extern flash.
 */
-(instancetype)setSpiCfg:(GRDSpiCfg*)cfg;
@end

NS_ASSUME_NONNULL_END
