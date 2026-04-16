//
//  VPDashView.h
//  VeepooBleSDK
//
//  Created by 张冲 on 2018/12/22.
//  Copyright © 2018 zc.All rights reserved.
//

#import <UIKit/UIKit.h>

@interface VPDashView : UIView

//注意: 以下控件, 包括子类的控件, 如果修改frame, 要在addSubView之后修改, 否则无效

//视图左侧的图标
@property (nonatomic, strong) UIImageView *imageView;
//视图左侧的模块title
@property (nonatomic, strong) UILabel *titleLabel;
//视图无数据是展示的内容
@property (nonatomic, strong) UILabel *noDataLabel;

//曲线的颜色
@property (nonatomic, strong) UIColor *lineColor;
//设置下边时间点的颜色
@property (nonatomic, strong) UIColor *timeColor;

@end
