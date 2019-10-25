//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 *  An image item for an `RBImageSelectionView` object.
 */
@interface RBImageSelectionViewItem : NSObject

/**
 *  The url to the image.
 */
@property (nonatomic, readonly, nullable) NSURL *url;

/**
 *  The image object.
 */
@property (nonatomic, readonly, nullable) UIImage *image;

/**
 *  Initializes a new image item with an image url.
 *
 *  @param url The url to the image.
 *
 *  @return The initialized image item.
 */
- (nonnull instancetype)initWithUrl:(nonnull NSURL *)url;

/**
 *  Initializes a new image item with a `UIImage` object.
 *
 *  @param image The `UIImage` object.
 *
 *  @return The initialized image item.
 */
- (nonnull instancetype)initWithImage:(nonnull UIImage *)image;

@end
