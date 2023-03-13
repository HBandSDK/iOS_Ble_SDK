//
//  DFCircleTextView.h
//
//  Created by DFung on 2017/6/15.
//  Copyright © 2017年 DFung All rights reserved.
//

#import <UIKit/UIKit.h>

typedef enum {
    DFCircleTextAlignOutside,
    DFCircleTextAlignCenter,
    DFCircleTextAlignInside
} DFCircleTextAlignment;

@interface DFCircleTextView : UIView


/**
 *  Set the text to display in the DFCircleTextView
 */
@property (strong, nonatomic) NSString *text;

/**
 *  Set the Text Attributes for the text.
 *  Refer to the Text Attributes documentation for more info.
 */
@property (strong, nonatomic) NSDictionary *textAttributes;

/**
 *  Align the text left, right or center reletive to the baseAngle.
 */
@property (nonatomic) NSTextAlignment textAlignment;

/**
 *  Align the text inside, outside or centered on the circle.
 */
@property (nonatomic) DFCircleTextAlignment circleTextAlignment;

/**
 *  Set the radius of the circle.
 *  When no radius is set, the maximum radius is calculated and used.
 */
@property (nonatomic) float radius;

/**
 *  Set the base angle. See textAlignment property for more information.
 */
@property (nonatomic) float baseAngle;

/**
 *  Adjust the spacing of the characters.
 *  1 = default spacing, 0.5 = half spacing, 2 = double spacing, etc ...
 */
@property (nonatomic) float characterSpacing;


/**
 *  Disable the kerning cache.
 */
@property (nonatomic) BOOL disableKerningCache;

/**
 *  Clear the kerning cache.
 *  Note that this is automaticlly done when the app gives a memory warning.
 */
- (void)clearKerningCache;

/**
 *  Convenience function for quickly changing the textColor
 *  without the need of creating an NSDictionary *textAttributes
 */
- (void) setColor:(UIColor *)color;

/**
 *  text display from right side.
 */
-(void)showFromRight;

/**
 *  text display from left side.
 */
-(void)showFromLeft;

/**
 *  text display from outside.
 */
-(void)showFromOutside;

/**
 *  text display from inside.
 */
-(void)showFromInside;

/**
 *  text display from bothside.
 */
-(void)showFromBothSide;

/**
 *  text display from center.
 */
-(void)showFromCenter;

/**
 *  text will rotate.
 */
-(void)showRotateWise:(BOOL)wise;














@end
