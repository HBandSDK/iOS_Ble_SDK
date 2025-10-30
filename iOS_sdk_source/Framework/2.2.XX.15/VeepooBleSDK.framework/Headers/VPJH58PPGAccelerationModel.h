//
//  VPJH58PPGAccelerationModel.h
//  VeepooBleSDK
//
//  Created by fengye on 2025/10/24.
//  Copyright © 2025 veepoo. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface VPJH58PPGAccelerationModel : NSObject

@property (nonatomic,assign) NSTimeInterval timestamp;

@property (nonatomic,strong) NSMutableArray *ppgValueArray;

@property (nonatomic,strong) NSMutableArray *accelerationXArray;

@property (nonatomic,strong) NSMutableArray *accelerationYArray;

@property (nonatomic,strong) NSMutableArray *accelerationZArray;

- (void)parsePPGAccelerationData:(NSData *)data;

@end

NS_ASSUME_NONNULL_END
