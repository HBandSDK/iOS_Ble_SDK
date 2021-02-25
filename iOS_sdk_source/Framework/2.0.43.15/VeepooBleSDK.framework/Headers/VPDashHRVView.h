//
//  VPDashHRVView.h
//  VeepooBleSDK
//
//  Created by 张冲 on 2018/12/22.
//  Copyright © 2018 zc.All rights reserved.
//

#import "VPDashView.h"


@interface VPDashHRVView : VPDashView

//右上角健康指数title的Label
@property (nonatomic, strong) UILabel *hrvScoreTitleLabel;
//右上角健康指数分数的Label
@property (nonatomic, strong) UILabel *hrvScoreValueLabel;

@property (nonatomic, strong) NSArray *oneDayHrvs;

@end
