//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

/**
 * A view that displays circle.
 */
@interface RBCircleView : UIView

/**
 * The radius (in points) of the circle.
 */
@property (nonatomic) CGFloat radius;

/**
 * The color of the circle.
 */
@property (nonatomic, nonnull) UIColor *circleColor;

/**
 * The line width to use when drawing the circle.
 */
@property (nonatomic) CGFloat lineWidth;

/**
 * Whether the circle is to be filled.
 */
@property (nonatomic) BOOL circleIsFilled;

@end
