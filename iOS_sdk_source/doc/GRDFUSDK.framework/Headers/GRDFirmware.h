//
//  GRDFirmware.h
//  GRDFU
//
//  Created by dingjian on 2019/12/23.
//  Copyright © 2019 Goodix. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GRDImgInfo.h"

NS_ASSUME_NONNULL_BEGIN

@interface GRDFirmware : NSObject

-(instancetype)initWithData:(NSData*)data;

-(BOOL)isValid;
-(BOOL)isEncrypted;

-(GRDImgInfo*)getInfo;
-(NSData*)getData;
-(uint32_t)getDataCheckSum;

@end

NS_ASSUME_NONNULL_END
