//
//  VPDashOxygenView.h
//  VeepooBleSDK
//
//  Created by 张冲 on 2018/12/22.
//  Copyright © 2018 zc.All rights reserved.
//

#import "VPDashView.h"


@interface VPDashOxygenView : VPDashView

//右上角血氧平均title
@property (nonatomic, strong) UILabel *oxygenAveTitleLabel;
//右上角血氧平均值
@property (nonatomic, strong) UILabel *oxygenAveValueLabel;

@property (nonatomic, strong) NSArray *oneDayOxygens;

@end
