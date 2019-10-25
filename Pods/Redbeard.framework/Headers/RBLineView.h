//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>

/**
 * A view that displays a line.
 */
@interface RBLineView : UIView

/**
 * The color of the line.
 */
@property (nonatomic, nonnull) UIColor *lineColor;

/**
 * The width of the line.
 */
@property (nonatomic) CGFloat lineWidth;

/**
 * Whether the line is to be drawn bottom-left to top-right (`true`)
 * or top-left to bottom-right (`false`).
 */
@property (nonatomic) BOOL bottomLeftToTopRight;

@end
