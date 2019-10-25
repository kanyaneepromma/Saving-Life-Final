//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>

@protocol RBNavigationControllerViewDelegate;

/**
 *  An internal view used by an `RBNavigationController` to bridge view and view controller events.
 */
@interface RBNavigationControllerView : UIView

/**
 *  A delegate to determine whether viewport updates should be propagated.
 */
@property (nonatomic, weak) id<RBNavigationControllerViewDelegate> delegate;

@end

/**
 *  A delegate to determine whether viewport updates should be propagated for an `RBNavigationControllerView`.
 */
@protocol RBNavigationControllerViewDelegate <NSObject>

@required

/**
 *  Called to determine whether a viewport update should be propagated to a subview or not.
 *
 *  @param navigationControllerView The `RBNavigationControllerView` object.
 *  @param viewport                 The new viewport that would be used.
 *  @param subview                  The subview that would be given the viewport update.
 *
 *  @return Whether or not the viewport update should be propagated to the subview.
 */
- (BOOL)navigationControllerView:(RBNavigationControllerView *)navigationControllerView shouldUseViewport:(CGRect *)viewport forSubview:(UIView *)subview;

@end
