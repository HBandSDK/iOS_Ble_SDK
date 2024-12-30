//
//  VPHRVLorentAnalysisModel.h
//  VeepooBleSDK
//
//  Created by 张冲 on 2019/1/5.
//  Copyright © 2019 zc.All rights reserved.
//

#import <Foundation/Foundation.h>

@interface VPHRVLorentAnalysisModel : NSObject

//标题
@property (nonatomic, strong) NSString *title;
//评论
@property (nonatomic, strong) NSString *comment;
//几颗星
@property (nonatomic, assign) int startCount;

- (instancetype)initWithResult:(Byte *)result andIndex:(int)index;

@end
