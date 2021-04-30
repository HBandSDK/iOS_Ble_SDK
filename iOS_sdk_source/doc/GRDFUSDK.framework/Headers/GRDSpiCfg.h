//
//  GRDSpiCfg.h
//  GRDFU
//
//  Created by dingjian on 2019/12/26.
//  Copyright © 2019 Goodix. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GRDSerializable.h"

typedef NS_ENUM(uint32_t, GRDSpiType) {
    GRDSpiTypeSpi = 1,
    GRDSpiTypeQspi
};

typedef NS_ENUM(uint32_t, GRDQSPIID) {
    GRDQSPIID_0 = 0,
    GRDQSPIID_1,
    GRDQSPIID_UnKnown
};

typedef NS_ENUM(uint32_t, GRDSpiIo) {
    GRDSpiCs = 0,
    GRDSpiClk,
    GRDSpiMosiOrIo0,
    GRDSpiMisoOrIo1,
    GRDSpiIo2, // 4
    GRDSpiIo3,
    GRDSpiIoMax
};

typedef struct _SPI_IO {
    uint32_t gpioType;
    uint32_t gpioNum;
    uint32_t gpioMux;
} SpiIo_t;

NS_ASSUME_NONNULL_BEGIN

@interface GRDSpiCfg : NSObject <GRDSerializable>
{
    @public
    GRDSpiType _spiType;
    SpiIo_t _io[GRDSpiIoMax];
    uint32_t _qspiModuleId;
}

-(void)setSpiType:(GRDSpiType)type;
-(void)setSpiIo:(GRDSpiIo)io gpioType:(uint32_t)type gpioNum:(uint32_t)num gpioMux:(uint32_t)mux;
-(void)setQspiModuleId:(uint32_t)moduleId;
//-(void)setCsWithType:(uint32_t)gpioType gpio:(uint32_t)pin mux:(uint32_t)mux;
//-(void)setClkWithType:(uint32_t)gpioType gpio:(uint32_t)pin mux:(uint32_t)mux;
//-(void)setMisoWithType:(uint32_t)gpioType gpio:(uint32_t)pin mux:(uint32_t)mux;
//-(void)setMosiWithType:(uint32_t)gpioType gpio:(uint32_t)pin mux:(uint32_t)mux;
//-(void)setIo0WithType:(uint32_t)gpioType gpio:(uint32_t)pin mux:(uint32_t)mux;
//-(void)setIo1WithType:(uint32_t)gpioType gpio:(uint32_t)pin mux:(uint32_t)mux;
//-(void)setIo2WithType:(uint32_t)gpioType gpio:(uint32_t)pin mux:(uint32_t)mux;
//-(void)setIo3WithType:(uint32_t)gpioType gpio:(uint32_t)pin mux:(uint32_t)mux;
@end

NS_ASSUME_NONNULL_END
