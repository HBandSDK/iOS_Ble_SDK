//
//  DFUIAnimation.h
//  DFUIBox
//
//  Created by DFung on 16/5/18.
//  Copyright © 2016年 DFung. All rights reserved.
//

#import <Foundation/Foundation.h>


typedef enum : NSUInteger {
    DFUIAnimation_TYPE_SPRING,
} DFUIAnimation_TYPE;

@interface DFUIAnimation : NSObject

+ (void)showView:(UIView*)view Type:(DFUIAnimation_TYPE)type Completed:(void(^)(BOOL finished))block;
+ (void)hideView:(UIView*)view Type:(DFUIAnimation_TYPE)type Completed:(void(^)(BOOL finished))block;

@end
