//
//  GRDImgInfo.h
//  GRDFU
//
//  Created by dingjian on 2019/12/23.
//  Copyright © 2019 Goodix. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GRDBootInfo.h"

NS_ASSUME_NONNULL_BEGIN

#define VALID_IMG_INFO_PATTERN 0x4744

@interface GRDImgInfo : NSObject
{
    @public
    uint16_t _pattern;
    uint16_t _version;
    GRDBootInfo* _bootInfo;
    NSString* _comment;
}

-(void)serializeTo:(GCXHexBuilder*)builder;

-(uint32_t)getSerializationSize;

-(instancetype)deserializeFrom:(GCXHexReader*)reader;

-(instancetype)copyFrom:(GRDImgInfo*)other;
@end

NS_ASSUME_NONNULL_END
