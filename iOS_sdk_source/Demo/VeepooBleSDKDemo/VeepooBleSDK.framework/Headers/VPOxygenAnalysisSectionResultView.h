//
//  VPOxygenAnalysisSectionResultView.h
//  WYPHealthyThird
//
//  Created by 张冲 on 17/9/12.
//  Copyright © 2017年 zc.All rights reserved.
//

#import <UIKit/UIKit.h>

@protocol VPOxygenAnalysisSectionResultViewDelegate <NSObject>

- (void)oxygenAnalysisSectionResultViewBtnActionWithTag:(NSInteger)tag;

@end

@interface VPOxygenAnalysisSectionResultView : UIView

@property (weak, nonatomic) IBOutlet UIView *resultBackView;
@property (weak, nonatomic) IBOutlet UIButton *resultBtn;
@property (weak, nonatomic) IBOutlet UILabel *resultStateLabel;
//把一天的血氧数据用VPOxygenAnalysisModel初始化得到的属性parseOneDayDict传入进来
@property (nonatomic, strong) NSDictionary *oneDayParseDict;

@property (nonatomic, weak) id<VPOxygenAnalysisSectionResultViewDelegate>delegate;

- (void)setOxygenAnalysisSectionResultViewUI;

@end
