//
//  JLEmergencyContactModel.h
//  JL_BLEKit
//
//  Created by EzioChan on 2022/2/17.
//  Copyright © 2022 www.zh-jieli.com. All rights reserved.
//

#import "JLwSettingModel.h"

NS_ASSUME_NONNULL_BEGIN

@interface JLEmergencyContactModel : JLwSettingModel

@property(nonatomic,strong)NSString *phoneNumber;

-(instancetype)initWithData:(NSData *)data;

-(instancetype)initWithPhoneNumber:(NSString *)phoneNumber;


@end

NS_ASSUME_NONNULL_END
