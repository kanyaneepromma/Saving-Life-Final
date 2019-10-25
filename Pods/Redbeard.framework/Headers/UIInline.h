//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

/**
 *  Content alignment horizontally in a container.
 */
typedef NS_ENUM(NSInteger, RBHorizontalAlignment)
{
    /**
     *  Content alignment to the left of a container. 
     */
    RBHorizontalAlignmentLeft,
    
    /** 
     *  Content alignment to the center of a container. 
     */
    RBHorizontalAlignmentCenter,
    
    /** 
     *  Content alignment to the right of a container. 
     */
    RBHorizontalAlignmentRight
};

/**
 *  Content alignment vertically in a container.
 */
typedef NS_ENUM(NSInteger, RBVerticalAlignment)
{
    /** 
     *  Content alignment to the top of a container. 
     */
    RBVerticalAlignmentTop,
    
    /** 
     *  Content alignment to the middle of a container. 
     */
    RBVerticalAlignmentMiddle,

    /** 
     *  Content alignment to the bottom of a container. 
     */
    RBVerticalAlignmentBottom
};

/**
 *  The orientation of a canvas.
 */
typedef NS_ENUM(NSInteger, RBOrientation)
{
    /** 
     *  The vertical (portrait) orientation of a canvas. 
     */
    RBOrientationVertical,

    /** 
     *  The horizontal (landscape) orientation of a canvas. 
     */
    RBOrientationHorizontal
};

#pragma mark -
#pragma mark General

/**
 *  Converts an angle in degrees to radians.
 *
 *  @param degrees The angle in degrees.
 *
 *  @return The angle in radians.
 */
static inline float DegreesToRadians(float degrees)
{
    return degrees * (M_PI / 180.0);
}

/**
 *  Converts an angle in radians to degrees.
 *
 *  @param radians The angle in radians.
 *
 *  @return The angle in degrees.
 */
static inline float RadiansToDegrees(float radians)
{
    return radians / (M_PI / 180.0);
}

#pragma mark -
#pragma mark CGPoint & CGVector

/**
 * @name `CGPoint` and `CGVector`
 */

/**
 *  Calculates the `CGVector` from one `CGPoint` to another.
 *
 *  @param originPoint      The origin `CGPoint`.
 *  @param destinationPoint The destination `CGPoint`.
 *
 *  @return The `CGVector` from `start` to `end`.
 */
static inline CGVector CGVectorFromPointToPoint(CGPoint originPoint, CGPoint destinationPoint)
{
    return CGVectorMake(destinationPoint.x - originPoint.x,
                        destinationPoint.y - originPoint.y);
}

#pragma mark -
#pragma mark CGSize

/**
 * @name `CGSize`
 */

/**
 *  The maximum `CGSize`.
 */
static CGSize CGSizeMax = { CGFLOAT_MAX, CGFLOAT_MAX };

/**
 *  The empty `CGSize`.
 */
static CGSize CGSizeEmpty = { 0, 0 };

/**
 *  Determines whether a `sizeA` is larger than `sizeB` in either dimension.
 *
 *  @param sizeA The first `CGSize` value.
 *  @param sizeB The second `CGSize` value.
 *
 *  @return Whether or not `sizeA` is larger than `sizeB` in either dimension.
 */
static inline BOOL CGSizeIsLargerThanSize(CGSize sizeA, CGSize sizeB)
{
    return sizeA.width > sizeB.width || sizeA.height > sizeB.height;
}

/**
 *  Determines whether a `sizeA` is smaller than `sizeB` in either dimension.
 *
 *  @param sizeA The first `CGSize` value.
 *  @param sizeB The second `CGSize` value.
 *
 *  @return Whether or not `sizeA` is smaller than `sizeB` in either dimension.
 */
static inline BOOL CGSizeIsSmallerThanSize(CGSize sizeA, CGSize sizeB)
{
    return sizeA.width < sizeB.width || sizeA.height < sizeB.height;
}

/**
 *  Determines whether the given `CGSize` is empty.
 *
 *  @param size The size to check for being empty.
 *
 *  @return Whether or not the given `CGSize` is empty.
 */
static inline BOOL CGSizeIsEmpty(CGSize size)
{
    if(size.width > 0 && size.height > 0)
        return false;
    
    return true;
}

/**
 *  Scales both dimensions of the given `CGSize` by the given factor.
 *
 *  @param size   The `CGSize` to scale.
 *  @param factor The factor to scale the `CGSize` by.
 *
 *  @return The scaled `CGSize` value.
 */
static inline CGSize CGSizeWithFactor(CGSize size, CGFloat factor)
{
    return CGSizeMake(size.width * factor,
                      size.height * factor);
}

/**
 *  Reduces the given `CGSize` by the given `UIEdgeInsets`.
 *
 *  @param size   The `CGSize` value to reduce.
 *  @param insets The `UIEdgeInsets` to use to reduce the `CGSize`.
 *
 *  @return The reduced `CGSize` value.
 */
static inline CGSize CGSizeInner(CGSize size, UIEdgeInsets insets)
{
    return CGSizeMake(size.width - insets.left - insets.right,
                      size.height - insets.top - insets.bottom);
}

/**
 *  Expands the given `CGSize` by the given `UIEdgeInsets`.
 *
 *  @param size   The `CGSize` value to expand.
 *  @param insets The `UIEdgeInsets` to use to expand the `CGSize`.
 *
 *  @return The expanded `CGSize` value.
 */
static inline CGSize CGSizeOuter(CGSize size, UIEdgeInsets insets)
{
    return CGSizeMake(size.width + insets.left + insets.right,
                      size.height + insets.top + insets.bottom);
}

/**
 *  Constrains the given `CGSize` by a given minimum and maximum value.
 *
 *  Any zero values in `minimumSize` and `maximumSize` are ignored.  Thus `CGSizeZero` represents an ignored constraint.
 *
 *  @param size        The `CGSize` to constrain.
 *  @param minimumSize The minimum size to constrain to.
 *  @param maximumSize The maximum size to constrain to.
 *
 *  @return The constrained `CGSize` value.
 */
static inline CGSize CGSizeConstrain(CGSize size, CGSize minimumSize, CGSize maximumSize)
{
    CGSize sz = size;
    
    if(minimumSize.width > 0 && sz.width < minimumSize.width)
        sz.width = minimumSize.width;
    
    if(minimumSize.height > 0 && sz.height < minimumSize.height)
        sz.height = minimumSize.height;
    
    if(maximumSize.width > 0 && sz.width > maximumSize.width)
        sz.width = maximumSize.width;
    
    if(maximumSize.height > 0 && sz.height > maximumSize.height)
        sz.height = maximumSize.height;
    
    return sz;
}

/**
 *  Calculates the aspect ratio of the given `CGSize` value.
 *
 *  @param size The `CGSize` value to calculate the aspect ratio of.
 *
 *  @return The calculated aspect ratio.
 */
static inline CGFloat CGSizeAspectRatio(CGSize size)
{
    if(CGSizeIsEmpty(size))
        return 0;
    
    return size.width / size.height;
}

/**
 *  Adjusts a `CGSize` to fit inside of a containing `CGSize`,
 *  optionally maintaining the aspect ratio.
 *
 *  @param size                The `CGSize` to adjust.
 *  @param container           The container `CGSize` to adjust for.
 *  @param maintainAspectRatio Whether or not to maintain the aspect ratio of `size`.
 *
 *  @return The adjusted `CGSize` value.
 */
static inline CGSize CGSizeFit(CGSize size, CGSize container, BOOL maintainAspectRatio)
{
    CGFloat a = CGSizeAspectRatio(size);
    
    if(size.width > container.width)
    {
        size.width = container.width;
        
        if(maintainAspectRatio)
            size.height = container.width / a;
    }
    
    if(size.height > container.height)
    {
        size.height = container.height;
        
        if(maintainAspectRatio)
            size.width = container.height * a;
    }
    
    if(size.width < 0)
        size.width = 0;
    
    if(size.height < 0)
        size.height = 0;
    
    return size;
}

/**
 *  The type of container to use when calculating CGSizeContainer.
 */
typedef NS_ENUM(NSInteger, RBSizeContainerType)
{
    /**
     *  Children can overlap, but all must individually fit.
     */
    RBSizeContainerTypeOverlap,

    /**
     *  Children are stacked vertically with no overlap.  All must individually fit horizontally.
     */
    RBSizeContainerTypeVertical,

    /**
     *  Children are stacked horizontally with no overlap.  All must individually fit vertically.
     */
    RBSizeContainerTypeHorizontal
};

/**
 *  Calculates the containing `CGSize` for a series of children `CGSize` values.
 *
 *  @param containerType The stacking mode for the children.
 *  @param n             The number of children.
 *  @param ...           The series of children `CGSize` values.
 *
 *  @return The calculated containing `CGSize` value.
 */
static inline CGSize CGSizeContainer(RBSizeContainerType containerType, NSUInteger n, ...)
{
    CGSize size = CGSizeEmpty;
    
    va_list arguments;
    va_start(arguments, n);
    
    for(NSUInteger i = 0; i < n; i++)
    {
        CGSize sz = va_arg(arguments, CGSize);
        
        if(containerType == RBSizeContainerTypeOverlap)
        {
            size.width = MAX(size.width, sz.width);
            size.height = MAX(size.height, sz.height);
        }
        else if(containerType == RBSizeContainerTypeVertical)
        {
            size.width = MAX(size.width, sz.width);
            size.height = size.height + sz.height;
        }
        else if(containerType == RBSizeContainerTypeHorizontal)
        {
            size.width = size.width + sz.width;
            size.height = MAX(size.height, sz.height);
        }
    }
    
    va_end(arguments);
    
    return size;
}

/**
 *  Calculates the containing `CGSize` for an array of `CGSize` values encapsulated via an NSValue.
 *
 *  @param containerType   The stacking mode for the children.
 *  @param sizes           The array of `NSValue` containing `CGSize` values.
 *
 *  @return The calculated containing `CGSize` value.
 */
static inline CGSize CGSizeContainerArray(RBSizeContainerType containerType, NSArray<NSValue *> *sizes)
{
    CGSize size = CGSizeEmpty;
    
    for(NSValue *value in sizes)
    {
        CGSize sz = [value CGSizeValue];
        
        if(containerType == RBSizeContainerTypeOverlap)
        {
            size.width = MAX(size.width, sz.width);
            size.height = MAX(size.height, sz.height);
        }
        else if(containerType == RBSizeContainerTypeVertical)
        {
            size.width = MAX(size.width, sz.width);
            size.height = size.height + sz.height;
        }
        else if(containerType == RBSizeContainerTypeHorizontal)
        {
            size.width = size.width + sz.width;
            size.height = MAX(size.height, sz.height);
        }
    }
        
    return size;
}

/**
 *  Subtracts `sizeB` from `sizeA`.
 *
 *  @param sizeA The `CGSize` to subtract from.
 *  @param sizeB The `CGSize` to subtract.
 *
 *  @return The resulting `CGSize` value.
 */
static inline CGSize CGSizeMinusSize(CGSize sizeA, CGSize sizeB)
{
    return CGSizeMake(sizeA.width - sizeB.width, sizeA.height - sizeB.height);
}

#pragma mark -
#pragma mark CGRect

/**
 * @name `CGRect`
 */

/**
 *  Scales and rounds off a `CGRect` value.
 *
 *  @param rect  The `CGRect` value to scale and round off.
 *  @param scale The scale factor to apply.
 *
 *  @return The resulting `CGRect` value.
 */
static inline CGRect CGRectIntegralScaledEx(CGRect rect, CGFloat scale)
{
    return CGRectMake(floorf(rect.origin.x * scale) / scale,
                      floorf(rect.origin.y * scale) / scale,
                      ceilf(rect.size.width * scale) / scale,
                      ceilf(rect.size.height * scale) / scale);
}

/**
 *  Rounds off a `CGRect` value, using the scale of the main `UIScreen`.
 *
 *  @param rect The `CGRect` value to round off.
 *
 *  @return The resulting `CGRect` value.
 */
static inline CGRect CGRectIntegralScaled(CGRect rect)
{
    return CGRectIntegralScaledEx(rect, [[UIScreen mainScreen] scale]);
}

/**
 *  Calculates the union of the given array of `CGRect` values.
 *
 *  @param rects An array of `NSValue` representations of `CGRect` values.
 *
 *  @return The resulting `CGRect` union.
 */
static inline CGRect CGRectUnionOfRects(NSArray<NSValue *> *rects)
{
    CGRect rect = CGRectNull;
    
    for(NSValue *rectValue in rects)
    {
        if(CGRectIsNull(rect))
            rect = [rectValue CGRectValue];
        else
            rect = CGRectUnion(rect, [rectValue CGRectValue]);
    }
    
    return rect;
}

/**
 *  Applies the given `UIEdgeInsets` to the given `CGRect` frame.
 *
 *  @param rect   The `CGRect` frame to apply insets to.
 *  @param insets The `UIEdgeInsets` to apply to the `CGRect` frame.
 *
 *  @return The resulting `CGRect` frame.
 */
static inline CGRect CGRectInner(CGRect rect, UIEdgeInsets insets)
{
    rect.origin.x += insets.left;
    rect.origin.y += insets.top;
    rect.size.width -= insets.left + insets.right;
    rect.size.height -= insets.top + insets.bottom;
    
    if(rect.size.width < 0)
        rect.size.width = 0;
    
    if(rect.size.height < 0)
        rect.size.height = 0;
    
    return rect;
}

/**
 *  Removes the given `UIEdgeInsets` from the given `CGRect` frame.
 *
 *  @param rect   The `CGRect` frame to remove the insets from.
 *  @param insets The `UIEdgeInsets` to remove from the `CGRect` frame.
 *
 *  @return The resulting `CGRect` frame.
 */
static inline CGRect CGRectOuter(CGRect rect, UIEdgeInsets insets)
{
    rect.origin.x -= insets.left;
    rect.origin.y -= insets.top;
    rect.size.width += insets.left + insets.right;
    rect.size.height += insets.top + insets.bottom;
    
    if(rect.size.width < 0)
        rect.size.width = 0;
    
    if(rect.size.height < 0)
        rect.size.height = 0;
    
    return rect;
}

/**
 *  Calculates the center `CGPoint` in the given `CGRect` frame.
 *
 *  @param rect The `CGRect` frame to find the center point of.
 *
 *  @return The resulting `CGPoint` value.
 */
static inline CGPoint CGRectCenterPoint(CGRect rect)
{
    return CGPointMake(rect.origin.x + (rect.size.width / 2.0),
                       rect.origin.y + (rect.size.height / 2.0));
}

/**
 *  Calculates the bottom right `CGPoint` in the given `CGRect` frame.
 *
 *  @param rect The `CGRect` frame to find the bottom right point of.
 *
 *  @return The resulting `CGPoint` value.
 */
static inline CGPoint CGRectBottomRight(CGRect rect)
{
    return CGPointMake(rect.origin.x + rect.size.width,
                       rect.origin.y + rect.size.height);
}

/**
 *  Creates a new `CGRect` with the given center point and size.
 *
 *  @param centerPoint The center `CGPoint`.
 *  @param size        The `CGSize` of the frame.
 *
 *  @return The resulting `CGRect` value.
 */
static inline CGRect CGRectWithCenterAndSize(CGPoint centerPoint, CGSize size)
{
    CGRect f;
    f.origin.x = centerPoint.x - (size.width / 2.0);
    f.origin.y = centerPoint.y - (size.height / 2.0);
    f.size = size;
    return f;
}

/**
 *  Creates a new `CGRect` with the given origin point and size.
 *
 *  @param origin The origin `CGPoint` value.
 *  @param size   The size value.
 *
 *  @return The resulting `CGRect` value.
 */
static inline CGRect CGRectWithOriginAndSize(CGPoint origin, CGSize size)
{
    CGRect f;
    f.origin = origin;
    f.size = size;
    return f;
}

/**
 *  Calculates the `CGRect` frame of a given size aligned within a container frame.
 *
 *  @param size      The size of the element to align.
 *  @param vp        The vertical alignment.
 *  @param hp        The horizontal alignment.
 *  @param container The container frame to position and align inside of.
 *
 *  @return The resulting aligned `CGRect` value.
 */
static inline CGRect CGRectAlign(CGSize size, RBVerticalAlignment vp, RBHorizontalAlignment hp, CGRect container)
{
    CGRect nf = CGRectZero;
    
    nf.size = size;
    
    switch(hp)
    {
        case RBHorizontalAlignmentLeft:
            nf.origin.x = container.origin.x;
            break;
            
        case RBHorizontalAlignmentCenter:
            nf.origin.x = container.origin.x + ( (container.size.width / 2) - (nf.size.width / 2) );
            break;
            
        case RBHorizontalAlignmentRight:
            nf.origin.x = container.origin.x + ( container.size.width - nf.size.width );
            break;
    }
    
    switch(vp)
    {
        case RBVerticalAlignmentTop:
            nf.origin.y = container.origin.y;
            break;
            
        case RBVerticalAlignmentMiddle:
            nf.origin.y = container.origin.y + ( (container.size.height / 2) - (nf.size.height / 2) );
            break;
            
        case RBVerticalAlignmentBottom:
            nf.origin.y = container.origin.y + ( container.size.height - nf.size.height );
            break;
    }
    
    return nf;
}

#pragma mark -
#pragma mark UIEdgeInsets

/**
 * @name `UIEdgeInsets`
 */

/**
 *  Adds two `UIEdgeInsets` together.
 *
 *  @param edgeInsetsA The first `UIEdgeInsets` value.
 *  @param edgeInsetsB The second `UIEdgeInsets` value.
 *
 *  @return The resulting `UIEdgeInsets` value.
 */
static inline UIEdgeInsets UIEdgeInsetsAddToEdgeInsets(UIEdgeInsets edgeInsetsA, UIEdgeInsets edgeInsetsB)
{
    UIEdgeInsets ei;
    
    ei.top = edgeInsetsA.top + edgeInsetsB.top;
    ei.left = edgeInsetsA.left + edgeInsetsB.left;
    ei.bottom = edgeInsetsA.bottom + edgeInsetsB.bottom;
    ei.right = edgeInsetsA.right + edgeInsetsB.right;
    
    return ei;
}

/**
 *  Subtracts `edgeInsetsB` from `edgeInsetsA`.
 *
 *  @param edgeInsetsA The first `UIEdgeInsets` value.
 *  @param edgeInsetsB The second `UIEdgeInsets` value.
 *
 *  @return The resulting `UIEdgeInsets` value.
 */
static inline UIEdgeInsets UIEdgeInsetsMinusEdgeInsets(UIEdgeInsets edgeInsetsA, UIEdgeInsets edgeInsetsB)
{
    UIEdgeInsets ei;
    
    ei.top = edgeInsetsA.top - edgeInsetsB.top;
    ei.left = edgeInsetsA.left - edgeInsetsB.left;
    ei.bottom = edgeInsetsA.bottom - edgeInsetsB.bottom;
    ei.right = edgeInsetsA.right - edgeInsetsB.right;
    
    return ei;
}

#pragma mark -
#pragma mark Scaling (snapping to nearest point)

/**
 *  Rounds off the given `CGSize` value to the nearest point.
 *
 *  @param size The `CGSize` value to round.
 *
 *  @return The resulting `CGSize` value.
 */
static inline CGSize CGSizeScaled(CGSize size)
{
    return CGSizeMake(ceilf(size.width),
                      ceilf(size.height));
}

/**
 *  Rounds off the given `CGPoint` value to the nearest point.
 *
 *  @param point The `CGPoint` value to round.
 *
 *  @return The resulting `CGPoint` value.
 */
static inline CGPoint CGPointScaled(CGPoint point)
{
    return CGPointMake(floorf(point.x),
                       floorf(point.y));
}

/**
 *  Rounds off the given `CGRect` value to the nearest point.
 *
 *  @param rect The `CGRect` value to round.
 *
 *  @return The resulting `CGRect` value.
 */
static inline CGRect CGRectScaled(CGRect rect)
{
    return CGRectWithOriginAndSize(CGPointScaled(rect.origin),
                                   CGSizeScaled(rect.size));
}

