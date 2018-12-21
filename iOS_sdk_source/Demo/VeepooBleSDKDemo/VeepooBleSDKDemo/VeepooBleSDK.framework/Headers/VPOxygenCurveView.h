//
//  VPOxygenCurveView.h
//  VeepooBleSDK
//
//  Created by 张冲 on 2018/12/20.
//  Copyright © 2018 veepoo. All rights reserved.
//

#import <UIKit/UIKit.h>

typedef enum : NSUInteger {
    VPOxygenCurveTypeOxygen,//血氧呼吸暂停曲线
    VPOxygenCurveTypeCardiacLoad,//心脏负荷
    VPOxygenCurveTypeSleepActivity,//睡眠活动
    VPOxygenCurveTypeRespirationRate,//呼吸率
    VPOxygenCurveTypeHypoxiaTime,//低氧时间
}VPOxygenCurveType;


@interface VPOxygenCurveView : UIView

- (instancetype)initWithVPOxygenCurveType:(VPOxygenCurveType)type;

//这里传入从数据库中取出的一天的数据即可
@property (nonatomic, strong) NSArray *oneDayOxygens;

@end
