//
//  JLSportDataModel.h
//  Test
//
//  Created by EzioChan on 2021/4/6.
//  Copyright © 2021 Zhuhai Jieli Technology Co.,Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface JLSportDataModel : NSObject

/// 设备的UUID
@property(nonatomic,strong)NSString *dev_uuid;

/// 请求内容数据
@property(nonatomic,strong)NSData *rqData;



@end

NS_ASSUME_NONNULL_END
