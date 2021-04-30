//
//  GRDGetImgInfoList.h
//  GRDFU
//
//  Created by dingjian on 2019/12/23.
//  Copyright © 2019 Goodix. All rights reserved.
//

#import "GRDAbsDfuFrameCmd.h"
#import "GRDImgInfo.h"

NS_ASSUME_NONNULL_BEGIN

@interface GRDGetImgInfoList : GRDAbsDfuFrameCmd
{
    @public
    BOOL _isUpdateOp;
    BOOL _isEncrypted;
    NSMutableArray<GRDImgInfo*>* _imgInfoList;
}

@end

NS_ASSUME_NONNULL_END
