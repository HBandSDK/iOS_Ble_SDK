//
//  VPOxygenAnalysisSectionOneView.h
//  WYPHealthyThird
//
//  Created by 张冲 on 17/7/21.
//  Copyright © 2017年 zc.All rights reserved.
//

#import <UIKit/UIKit.h>

@protocol VPOxygenAnalysisSectionOneViewDelegate <NSObject>

- (void)oxygenAnalysisSectionSectionOneViewBtnActionWithTag:(NSInteger)tag;

@end

@interface VPOxygenAnalysisSectionOneView : UIView

- (void)setOxygenAnalysisSectionOneViewUI;

@property (weak, nonatomic) IBOutlet UIView *sectionOneBackView;
@property (weak, nonatomic) IBOutlet UILabel *nameLabel;//名称
@property (weak, nonatomic) IBOutlet UIButton *apneaaBtn;//呼吸暂停
@property (weak, nonatomic) IBOutlet UILabel *appearTimeLabel;//频现时间
@property (weak, nonatomic) IBOutlet UILabel *appearDetailLabel;
@property (weak, nonatomic) IBOutlet UILabel *timesLabel;//次数
@property (weak, nonatomic) IBOutlet UILabel *timesDetailLabel;
@property (weak, nonatomic) IBOutlet UILabel *referenceValueLabel;//参考值
@property (weak, nonatomic) IBOutlet UILabel *referenceValueDetailLabel;

//把一天的血氧数据用VPOxygenAnalysisModel初始化得到的属性parseOneDayDict传入进来
@property (nonatomic, strong) NSDictionary *oneDayParseDict;

@property (nonatomic, weak) id<VPOxygenAnalysisSectionOneViewDelegate>delegate;

@end




