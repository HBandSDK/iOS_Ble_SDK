//
//  GRDResetCmd.h
//  GRDFU
//
//  Created by dingjian on 2019/12/25.
//  Copyright © 2019 Goodix. All rights reserved.
//

#import "GRDAbsDfuFrameCmd.h"
#import "GRDBootInfo.h"

NS_ASSUME_NONNULL_BEGIN

@interface GRDResetCmd : GRDAbsDfuFrameCmd
-(instancetype)setTargetBootInfo:(GRDBootInfo*)bootInfo;
@end

NS_ASSUME_NONNULL_END
