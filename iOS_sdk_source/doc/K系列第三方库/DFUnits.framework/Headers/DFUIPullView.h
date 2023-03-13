//
//  DFUIPullView.h
//  RetainTest
//
//  Created by DFung on 2016/12/7.
//  Copyright © 2016年 DFung. All rights reserved.
//

#import <UIKit/UIKit.h>


#define kPULLVIEW_IMAGE_SIZE    40.0
#define kPULLVIEW_TIME          1.5

typedef enum : NSUInteger {
    PullView_TYPE_TABLEVIEW,
    PullView_TYPE_COLLECTIONVIEW
} PullView_TYPE;




@protocol DFUIPullViewDelegate <NSObject>
@optional

-(void)onDFUIPullViewIsLoading;
-(void)onDFUIPullViewLoadFinished;

@end



@interface DFUIPullView : UIView

@property(nonatomic,weak)   id<DFUIPullViewDelegate>delegate;
@property(nonatomic,strong) NSString                *subText;
@property(nonatomic,weak)   UIScrollView            *outScrollView;
@property(nonatomic,weak)   id                      outView;

- (instancetype)initWithScrollView:(UIScrollView*)scrollView
                              Type:(PullView_TYPE)type
                            OnView:(id)view;

- (void)setSubImage:(UIImage*)sImage;

@end
