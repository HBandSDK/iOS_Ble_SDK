//
//  DFFadeLabel.h
//  DFUnits
//
//  Created by DFung on 2017/6/15.
//  Copyright © 2017年 DFung. All rights reserved.
//

#import <UIKit/UIKit.h>

/**
 DFFadeLabel is a UIView subclass adds a UILabel effect when the text of a label instance outgrows the available width. Instances of `DFLabel` can be configured
 for label fading or unFading toward Right、Left、Up、Down.
 */

typedef enum : NSUInteger {
    DFFadeLabel_TYPE_LEFT,
    DFFadeLabel_TYPE_RIGHT,
    DFFadeLabel_TYPE_UP,
    DFFadeLabel_TYPE_DOWN,
    DFFadeLabel_TYPE_CENTER,
    DFFadeLabel_TYPE_BOTHSIDE
} DFFadeLabel_TYPE;

@interface DFFadeLabel : UIView

@property(nonatomic,strong)UILabel*label;
@property(nonatomic,strong)NSString *text;

-(void)showFromDirection:(DFFadeLabel_TYPE)type;

@end
