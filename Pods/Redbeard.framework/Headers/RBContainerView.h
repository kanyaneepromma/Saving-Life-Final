//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

/** The view mode to be used when sizing and positioning the child view. */
typedef NS_ENUM(NSInteger, RBContainerViewMode)
{
    /** The child view is scaled to fit the bounds of the container view. */
    RBContainerViewModeFit = 0,
    
    /** The child view maintains its desired size and is positioned in the middle of the container view. */
    RBContainerViewModeCenter
};

/**
 *  Contains a child view, providing margin and sizing functionality.
 */
@interface RBContainerView : UIView

/**
 *  The child view.
 */
@property (nonatomic, nonnull) UIView *child;

/**
 *  The margin to apply around the child view.
 */
@property (nonatomic) UIEdgeInsets margin;

/**
 *  The mode in which to layout the child view. Default = `RBContainerViewModeFit`.
 */
@property (nonatomic) RBContainerViewMode mode;

/**
 *  The minimum size that the container view will request.  Default = `CGSizeEmpty`.
 */
@property (nonatomic) CGSize minimumSize;

/**
 *  The maximum size that the container view will request.  Default = `CGSizeMax`.
 */
@property (nonatomic) CGSize maximumSize;

/**
 *  Whether or not the given aspect ratio should be enforced in sizing.
 */
@property (nonatomic) BOOL enforceAspectRatio;

/**
 *  The desired aspect ratio.
 */
@property (nonatomic) CGFloat aspectRatio;

/**
 *  Initializes a new container view object.
 *
 *  @param childView The child view.
 *
 *  @return The initialized object.
 */
- (nonnull instancetype)initWithChild:(nonnull UIView *)childView;

@end
