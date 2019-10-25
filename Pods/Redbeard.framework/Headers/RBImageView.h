//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@class RBImageCenter;

@protocol RBImageViewDelegate;

/**
 *  An image view with asynchronous image loading.
 */
@interface RBImageView : UIImageView

/**
 *  A delegate that can implement image transformation.
 */
@property (nonatomic, weak, nullable) id<RBImageViewDelegate> delegate;

/**
 *  The aspect ratio of the image.
 */
@property (nonatomic, readonly) CGFloat aspectRatio;

/**
 *  Whether or not activity indication should be showed while an image is being loaded asynchronously. Default = NO.
 */
@property (nonatomic) BOOL shouldDisplayActivityDuringImageLoading;

/**
 *  Whether or not activity progress should be displayed where available when loading an image asynchronously. Default = NO.
 */
@property (nonatomic) BOOL shouldDisplayActivityProgressDuringImageLoading;

/**
 *  An optional image that should be displayed if a failure occurs loading images via the 'loadImageFrom...' methods.
 */
@property (nonatomic, nullable) UIImage *failureImage;

/**
 *  The content mode of the failure image.
 */
@property (nonatomic) UIViewContentMode failureImageContentMode;

/**
 *  An optional image that should be displayed whilst an image is being download via the 'loadImageFrom...' methods.
 */
@property (nonatomic, nullable) UIImage *loadingImage;

/**
 *  The content mode of the loading image.
 */
@property (nonatomic) UIViewContentMode loadingImageContentMode;

/**
 *  Loads an image asynchronously from disk.
 *
 *  @param path       The filesystem path to the image file.
 *  @param completion An optional block that is called on completion.
 */
- (void)imageFromDisk:(nonnull NSString *)path completion:(nullable void(^)(UIImage * __nullable image, NSError * __nullable error))completion;

/**
 *  Loads an image asynchronously from disk.
 *
 *  @param path       The filesystem path to the image file.
 *  @param client     The `RBImageCenter` to use to for operations.
 *  @param caching    Whether or not to cache the image or use a cached copy if possible.
 *  @param completion An optional block that is called on completion.
 */
- (void)imageFromDisk:(nonnull NSString *)path withClient:(nonnull RBImageCenter *)client caching:(BOOL)caching completion:(nullable void(^)(UIImage * __nullable image, NSError * __nullable error))completion;

/**
 *  Loads an image asynchronously from the network using the shared `RBImageCenter`.
 *
 *  @param request    The `NSURLRequest` request to the image.
 *  @param completion An optional block that is called on completion.
 */
- (void)imageFromRequest:(nonnull NSURLRequest *)request completion:(nullable void(^)(UIImage * __nullable image, NSError * __nullable error))completion;

/**
 *  Loads an image asynchronously from the network.
 *
 *  @param request    The `NSURLRequest` request to the image.
 *  @param client     The `RBImageCenter` to use to for operations.
 *  @param caching    Whether or not to cache the image or use a cached copy if possible.
 *  @param completion An optional block that is called on completion.
 */
- (void)imageFromRequest:(nonnull NSURLRequest *)request withClient:(nonnull RBImageCenter *)client caching:(BOOL)caching completion:(nullable void(^)(UIImage * __nullable image, NSError * __nullable error))completion;

/**
 *  Cancels the current asynchronous image load job.
 */
- (void)cancelLoad;

@end

/**
 *  A delegate that can implement image transformation for an `RBImageView` object.
 */
@protocol RBImageViewDelegate <NSObject>

@optional

/**
 *  Transform a `UIImage` before it is displayed by an `RBImageView`.
 *
 *  @param image     The `UIImage` to transform.
 *  @param imageView The `RBImageView` that is requesting an image transformation.
 *
 *  @return The transformed `UIImage` object.
 */
- (nullable UIImage *)transformedImageWithImage:(nullable UIImage *)image withImageView:(nonnull RBImageView *)imageView;

@end
