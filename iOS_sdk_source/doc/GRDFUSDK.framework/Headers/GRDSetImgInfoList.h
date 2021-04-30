//
//  GRDSetImgInfoList.h
//  GRDFU
//
//  Created by dingjian on 2019/12/23.
//  Copyright © 2019 Goodix. All rights reserved.
//

#import "GRDAbsDfuFrameCmd.h"
#import "GRDImgInfo.h"

NS_ASSUME_NONNULL_BEGIN

@interface GRDSetImgInfoList : GRDAbsDfuFrameCmd
-(instancetype)setImgInfoList:(NSMutableArray<GRDImgInfo*>*) list;
@end

NS_ASSUME_NONNULL_END
