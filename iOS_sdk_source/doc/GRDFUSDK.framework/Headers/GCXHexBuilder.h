//
//  GCXHexBuilder.h
//  libcomx
//
//  Created by dingjian on 2019/12/22.
//  Copyright © 2019 Goodix. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface GCXHexBuilder : NSObject

+(instancetype)builderWithCapacity:(uint32_t)size;
+(instancetype)builderWithBytes:(void*)buf size:(uint32_t)size;
+(instancetype)builderWithData:(NSMutableData*)data;

-(instancetype)putValue:(uint32_t)value size:(uint32_t)size;
-(instancetype)putValue:(uint32_t)value size:(uint32_t)size isBigEndian:(BOOL)bigEndian;
-(instancetype)putBytes:(const void*)buf size:(uint32_t)size;
-(instancetype)putData:(NSData*)data;
-(instancetype)putData:(NSData*)data startPos:(uint32_t)pos size:(uint32_t)size;

-(const void*)getBuffer;
-(NSData*)getData;
-(int)getSize;
-(int)getBufferSize;
@end

NS_ASSUME_NONNULL_END
