//
//  GRDBootInfo.h
//  GRDFU
//
//  Created by dingjian on 2019/12/23.
//  Copyright © 2019 Goodix. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GCXHexBuilder.h"
#import "GCXHexReader.h"

NS_ASSUME_NONNULL_BEGIN

@interface GRDBootInfo : NSObject
{
    @public
    uint32_t _binSize;
    uint32_t _checkSum;
    uint32_t _loadAddr;
    uint32_t _runAddr;
    uint32_t _xqspiXipMode;
    // bitmap for Boot Config
    uint32_t _xqspiSpeed;
    uint32_t _codeCopyMode;
    uint32_t _systemClock;
    uint32_t _checkImage;
    uint32_t _bootDelay;
    uint32_t _isDapBoot;
}

-(void)serializeTo:(GCXHexBuilder*)builder;

-(uint32_t)getSerializationSize;

-(instancetype)deserializeFrom:(GCXHexReader*)reader;

- (instancetype)copyFrom:(GRDBootInfo *)other;

- (BOOL)isOverlaidTo:(GRDBootInfo *)other;

@end

NS_ASSUME_NONNULL_END
