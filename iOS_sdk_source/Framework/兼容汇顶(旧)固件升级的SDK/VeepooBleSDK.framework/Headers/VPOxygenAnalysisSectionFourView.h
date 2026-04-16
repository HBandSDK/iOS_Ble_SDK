//
//  VPOxygenAnalysisSectionFourView.h
//  WYPHealthyThird
//
//  Created by 张冲 on 17/9/13.
//  Copyright © 2017年 zc.All rights reserved.
//

#import <UIKit/UIKit.h>

@protocol VPOxygenAnalysisSectionFourViewDelegate <NSObject>

- (void)oxygenAnalysisSectionSectionFourViewBtnActionWithTag:(NSInteger)tag andShowType:(NSInteger)showType;

@end

@interface VPOxygenAnalysisSectionFourView : UIView

@property (weak, nonatomic) IBOutlet UIView *sectionFourBackView;
@property (weak, nonatomic) IBOutlet UIButton *lowOxygenBtn;

//开关这里自己增加target
@property (weak, nonatomic) IBOutlet UISwitch *lowOxygenSwitch;

@property (weak, nonatomic) IBOutlet UILabel *disconnectLabel;
@property (strong, nonatomic) IBOutlet UIImageView *arrowImageView;

//0就是只用开关，1是可设置开关、血氧值、振动时间等
@property (nonatomic, assign) NSInteger showType;

@property (nonatomic, weak) id<VPOxygenAnalysisSectionFourViewDelegate>delegate;

//0就是只用开关，1是可设置开关、血氧值、振动时间等
- (void)setOxygenAnalysisSectionFourViewUI:(BOOL)connect;

//连接状态改变
- (void)updateWithConnectState:(BOOL)connect;

@end
