//
//  GRDSetCtrlData.h
//  GRDFU
//
//  Created by dingjian on 2019/12/25.
//  Copyright © 2019 Goodix. All rights reserved.
//

#import "GRDAbsDfuFrameCmd.h"

NS_ASSUME_NONNULL_BEGIN

@interface GRDSetCtrlData : GRDAbsDfuFrameCmd
-(instancetype)setData:(NSData*)data;
@end

NS_ASSUME_NONNULL_END
