//
//  GCXUtil.h
//  libcomx
//
//  Created by dingjian on 2019/12/23.
//  Copyright © 2019 Goodix. All rights reserved.
//

#import <Foundation/Foundation.h>

extern BOOL isMemoryOverlaid(uint32_t addr1, uint32_t size1, uint32_t addr2, uint32_t size2);

NS_ASSUME_NONNULL_BEGIN

@interface GCXUtil : NSObject
@end

NS_ASSUME_NONNULL_END
