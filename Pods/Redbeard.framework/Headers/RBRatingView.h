//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>

@protocol RBRatingViewDelegate;

/**
 *  A view that provides granular rating stars (or another image).
 */
@interface RBRatingView : UIView

/**
 *  A delegate to receive selection events.
 */
@property (nonatomic, weak, nullable) id<RBRatingViewDelegate> delegate;

/**
 *  The orientation of the stars layout. Default = `RBOrientationHorizontal`.
 */
@property (nonatomic) RBOrientation orientation;

/**
 *  Gets or sets the current rating. Decimals allowed.
 */
@property (nonatomic) float rating;

/**
 *  Gets or sets the maximum rating. Default = 5. Must be > 0.
 */
@property (nonatomic) NSInteger maximumRating;

/**
 *  The image for the filled state.
 */
@property (nonatomic, nullable) UIImage *filledImage;

/**
 *  The image for the unfilled state.
 */
@property (nonatomic, nullable) UIImage *unfilledImage;

/**
 *  The spacing to use between each image. Default = 0.
 */
@property (nonatomic) CGFloat spaceBetweenImages;

/**
 *  Whether or not the rating field is currently enabled and will accept user interaction.  Default = `YES`.
 */
@property (nonatomic) BOOL enabled;

/**
 *  Whether or not zero selection is allowed.  Default = `NO`.
 */
@property (nonatomic) BOOL zeroSelection;

@end

/**
 *  The delegate to receive events from a `RBRatingView` object.
 */
@protocol RBRatingViewDelegate <NSObject>

@required

/**
 *  Called when the rating view did select a different value.
 *
 *  @param ratingView   The rating view object.
 *  @param rating       The new rating.
 */
- (void)ratingView:(nonnull RBRatingView *)ratingView ratingChangedTo:(float)rating;

@end
