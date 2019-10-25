//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>

/**
 *  `UIViewController` managed overlay image.
 *
 *  Displays an image in the view controller which is dismissed with a click.
 *  This should be used to show help overlay images.
 */
@interface UIViewController (ManagedOverlayImage)

/**
 *  Whether or not an overlay image is currently being presented.
 */
@property (nonatomic, readonly) BOOL isPresentingOverlay;

/**
 *  Presents an overlay image using a named image from the bundle.
 *
 *  @param imageName The name of the image in the bundle.
 *
 *  @return Whether or not the image was found and presented.
 */
- (BOOL)presentOverlayNoticeWithImageFromBundle:(nonnull NSString *)imageName;

/**
 *  Dismisses a currently presenting overlay image.
 *
 *  @return Whether or not there was a presenting overlay image to dismiss.
 */
- (BOOL)dismissOverlayNotice;

@end
