//
//  GRDDelayCmd.h
//  GRDFU
//
//  Created by dingjian on 2019/12/25.
//  Copyright © 2019 Goodix. All rights reserved.
//

#import "AbsCmd.h"

NS_ASSUME_NONNULL_BEGIN

@interface GRDDelayCmd : AbsCmd
-(instancetype)setDelay:(float)second;
@end

NS_ASSUME_NONNULL_END
