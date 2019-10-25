//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

/**
 *  A header view for a menu segment.
 */
@interface RBMenuSegmentHeaderView : UIView

/**
 *  The title of the segment header.
 */
@property (nonatomic, nullable) NSString *title;

/**
 *  The image to display in the segment header view.
 */
@property (nonatomic, nullable) UIImage *image;

/**
 *  The height of the segment header.
 */
@property (nonatomic) CGFloat fixedHeight;

/**
 *  The margin to apply to the margin header.
 */
@property (nonatomic) UIEdgeInsets margin;

/**
 *  Creates a new menu segment header view.
 *
 *  @return The new header view.
 */
+ (nonnull RBMenuSegmentHeaderView *)newHeader;

/**
 *  Creates a new menu segment header view with a title.
 *
 *  @param title The title of the segment header.
 *
 *  @return The new header view.
 */
+ (nonnull RBMenuSegmentHeaderView *)newHeaderWithTitle:(nonnull NSString *)title;

/**
 *  Creates a new menu segment header view with an image.
 *
 *  @param image The image to display in the segment header view.
 *
 *  @return The new header view.
 */
+ (nonnull RBMenuSegmentHeaderView *)newHeaderWithImage:(nonnull UIImage *)image;

@end
