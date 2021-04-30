//
//  GRDGetBootInfo.h
//  GRDFU
//
//  Created by dingjian on 2019/12/22.
//  Copyright © 2019 Goodix. All rights reserved.
//

#import "GRDAbsDfuFrameCmd.h"
#import "GRDBootInfo.h"

NS_ASSUME_NONNULL_BEGIN

@interface GRDGetBootInfo : GRDAbsDfuFrameCmd
{
    @public
    BOOL _isUpdateOp;
    BOOL _isEncrypted;
    GRDBootInfo* _bootInfo;
}
@end

NS_ASSUME_NONNULL_END
