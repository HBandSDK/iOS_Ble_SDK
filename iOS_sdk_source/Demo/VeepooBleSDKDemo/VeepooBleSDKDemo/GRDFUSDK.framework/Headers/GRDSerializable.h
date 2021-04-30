//
//  GRDSerializable.h
//  GRDFU
//
//  Created by dingjian on 2019/12/26.
//  Copyright © 2019 Goodix. All rights reserved.
//

#ifndef GRDSerializable_h
#define GRDSerializable_h

#import "GCXHexBuilder.h"
#import "GCXHexReader.h"

@protocol GRDSerializable <NSObject>

@required
-(uint32_t)getSerializationSize;
-(void)serializeTo:(GCXHexBuilder*)builder;
-(instancetype)deserializeFrom:(GCXHexReader*)reader;

@end

#endif /* GRDSerializable_h */
