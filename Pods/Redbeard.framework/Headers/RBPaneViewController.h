//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>

/**
 *  A pane for a `RBPaneContainerViewController`.
 */
@interface RBPaneViewController : UIViewController

/**
 *  The desired width that the pane should occupy given the available container width.
 *
 *  @param containerWidth The available width in the container.
 *
 *  @return The width that will be used for the pane.
 */
- (CGFloat)widthThatFitsWidth:(CGFloat)containerWidth;

@end
