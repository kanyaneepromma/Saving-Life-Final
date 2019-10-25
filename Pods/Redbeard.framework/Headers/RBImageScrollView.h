//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

/**
 *  A managed image view in a scroll area.  Supports zooming.
 */
@interface RBImageScrollView : UIView

/**
 *  Gets the underlying `RBImageView` object that is used to display an image.
 */
@property (nonatomic, readonly, nonnull) RBImageView *imageView;
    
/**
 *  Gets or sets the `UIImage` object being displayed.
 */
@property (nonatomic, nullable) UIImage *image;

/**
 *  An optional image that should be displayed if a failure occurs loading images.
 */
@property (nonatomic, nullable) UIImage *failureImage;

/**
 *  Whether or not zooming is enabled.
 */
@property (nonatomic) BOOL zoomEnabled;

/**
 *  Loads an image asynchronously from disk.
 *
 *  @param path       The filesystem path to the image file.
 *  @param completion An optional block that is called on completion.
 */
- (void)imageFromDisk:(nonnull NSString *)path completion:(nullable void(^)(UIImage * __nullable image, NSError * __nullable error, BOOL wasCancelled))completion;

/**
 *  Loads an image asynchronously from the network.
 *
 *  @param request    The `NSURLRequest` request to the image.
 *  @param completion An optional block that is called on completion.
 */
- (void)imageFromRequest:(nonnull NSURLRequest *)request completion:(nullable void(^)(UIImage * __nullable image, NSError * __nullable error))completion;

/**
 *  Cancels the current asynchronous image load job.
 */
- (void)cancelLoad;

#pragma mark -
#pragma mark Double Tap Zooming

/**
 *  Whether or not double tap zooming is enabled.
 */
@property (nonatomic) BOOL doubleTapZoomEnabled;

/**
 *  The double tap recognizer that triggers zooming.
 */
@property (nonatomic, readonly, nullable) UITapGestureRecognizer *doubleTapRecogniser;

@end
