//
//  VPOxygenAnalysisSectionThreeView.h
//  WYPHealthyThird
//
//  Created by 张冲 on 17/7/21.
//  Copyright © 2017年 zc.All rights reserved.
//

#import <UIKit/UIKit.h>

@protocol VPOxygenAnalysisSectionThreeViewDelegate <NSObject>

- (void)oxygenAnalysisSectionSectionThreeViewBtnActionWithTag:(NSInteger)tag;

@end

@interface VPOxygenAnalysisSectionThreeView : UIView

- (void)setOxygenAnalysisSectionThreeViewUI;

@property (weak, nonatomic) IBOutlet UIView *sectionThreeBackView;
@property (weak, nonatomic) IBOutlet UIButton *tipBtn;

@property (weak, nonatomic) IBOutlet UILabel *tipLabel;

//把一天的血氧数据用VPOxygenAnalysisModel初始化得到的属性parseOneDayDict传入进来
@property (nonatomic, strong) NSDictionary *oneDayParseDict;
@property (nonatomic, weak) id<VPOxygenAnalysisSectionThreeViewDelegate>delegate;

@end




