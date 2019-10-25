//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

/**
 * A `UIButton` with additional appearance options.
 */
@interface RBButton : UIButton

/**
 * The minimum size of the area from the center of the button that will accept touches.
 */
@property (nonatomic) CGSize minimumSelectionAreaSizeFromCenter;

/**
 * Whether or not the image and title should be vertically or horizontally arranged. 
 * Default = `RBOrientationHorizontal`.
 */
@property (nonatomic) RBOrientation orientation;

/**
 * Whether or not the title should be before the image. Default = `NO`.
 */
@property (nonatomic) BOOL titleFirst;

/**
 * The spacing to use between the label and the image. This has the effect of increasing 
 * the size of the button in the direction set via the `orientation` property. Default = `0`.
 */
@property (nonatomic) CGFloat spacing;

/**
 * Apply the title for `UIControlStateNormal`.
 *
 *  @param title    The title of the button.
 */
- (void)applyTitle:(NSString *)title;

/**
 * Apply the image for `UIControlStateNormal`.
 *
 *  @param image    The image of the button.
 */
- (void)applyImage:(UIImage *)image;

@end
