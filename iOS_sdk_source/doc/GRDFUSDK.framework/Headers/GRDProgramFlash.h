//
//  GRDProgramFlash.h
//  GRDFU
//
//  Created by dingjian on 2019/12/23.
//  Copyright © 2019 Goodix. All rights reserved.
//

#import "GRDAbsDfuFrameCmd.h"
#import "GRDFirmware.h"

NS_ASSUME_NONNULL_BEGIN

@interface GRDProgramFlash : GRDAbsDfuFrameCmd

-(instancetype)initAsNormalMode:(GRDFirmware*)fw needReset:(BOOL)reset;

-(instancetype)initAsResourceMode:(NSData*)data toExtFlash:(BOOL)extFlash toAddr:(uint32_t)addr;

-(instancetype)initAsCopyMode:(GRDFirmware*)fw copyAddr:(uint32_t)addr;

@end

NS_ASSUME_NONNULL_END
