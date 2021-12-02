//
//  VPHRVLorentView.h
//  VeepooBleSDK
//
//  Created by 张冲 on 2018/12/19.
//  Copyright © 2018 zc.All rights reserved.
//

#import <UIKit/UIKit.h>

@interface VPHRVLorentView : UIView

//三条线的颜色
@property (nonatomic, strong) UIColor *lineColor;
//散点图的颜色
@property (nonatomic, strong) UIColor *dotColor;
//数字文本的颜色
@property (nonatomic, strong) UIColor *numberColor;
//RRN文本的颜色
@property (nonatomic, strong) UIColor *textColor;
//数字文本的字体
@property (nonatomic, strong) UIFont *numberFont;
//RRN文本的字体
@property (nonatomic, strong) UIFont *textFont;

//传输从数据库获取某一天的hrv数据
@property (nonatomic, strong) NSArray *oneDayHrvs;

//scrollView的一些基本配置
@property (nonatomic, assign) BOOL showsVerticalScrollIndicator;
@property (nonatomic, assign) BOOL showsHorizontalScrollIndicator;
@property (nonatomic, assign) BOOL zoom;//是否可以缩放
@property (nonatomic, assign) BOOL canTap;//是否支持双击放大, 单击恢复功能

@end
