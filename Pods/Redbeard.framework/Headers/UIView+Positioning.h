//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>

@class UIInline;

/**
 *  `UIView` positioning methods.
 */
@interface UIView (Positioning)

/**
 * The bounds available for content after having taken into account safeAreaInsets.
 */
@property (nonatomic, readonly) CGRect contentBounds;


#pragma mark -
#pragma mark Anchor

/**
 *  Anchors the edges of the view to that of it's parents view safe area using layout constraints, i.e has the effect of matching and filling to the size of the parent view.
 *  Note it is safe to call this multiple times, the constraints are tracked automatically.
 */
- (void)anchorEdges;

/**
 *  Anchors the edges of the view to that of it's parents view using layout constraints, i.e has the effect of matching and filling to the size of the parent view.
 *  Note it is safe to call this multiple times, the constraints are tracked automatically.
 *
 *  @param usingSafeAreaEdges   The safe area edges that should also be used, pass [] to to ignore the safe area altogether and fill the complete bounds of the superview. Or set specific edges e.g. [ .left, .right, .bottom ].
 *  @param margin               The margin to maintain around the view within it's parent view's bounds.
 */
- (void)anchorEdges:(UIRectEdge)usingSafeAreaEdges margin:(UIEdgeInsets)margin;

/**
 *  Anchors, sizes and aligns the view within it's parent view's bounds using layout contraints.
 *  Note it is safe to call this multiple times, the constraints are tracked automatically.
 *
 *  @param vp       The vertical alignment to align to.
 *  @param hp       The horizontal alignment to align to.
 *  @param autosize Whether or not to autosize the view.
 *  @param margin   The margin to maintain around the view within it's parent view's bounds.
 *  @param useSafeArea  Whether to anchor taking into account the safe are or to ignore and use the complete bounds.
 */
- (void)anchorToVertical:(RBVerticalAlignment)vp
              horizontal:(RBHorizontalAlignment)hp
                autosize:(BOOL)autosize
                  margin:(UIEdgeInsets)margin
             useSafeArea:(BOOL)useSafeArea;

/**
 *  Anchors the view within it's parent view's bounds with the given size and a margin using layout constraints.
 *  Note it is safe to call this multiple times, the constraints are tracked automatically.
 *
 *  @param vp     The vertical alignment to align to.
 *  @param hp     The horizontal alignment to align to.
 *  @param size   The size of the view.
 *  @param margin The margin to maintain around the view within it's parent view's bounds.
 *  @param useSafeArea  Whether to anchor taking into account the safe are or to ignore and use the complete bounds.
 */
- (void)anchorToVertical:(RBVerticalAlignment)vp
              horizontal:(RBHorizontalAlignment)hp
                    size:(CGSize)size
                  margin:(UIEdgeInsets)margin
             useSafeArea:(BOOL)useSafeArea;

#pragma mark -
#pragma mark Move

/**
 *  Sizes and aligns the view within it's parent view's bounds.
 *
 *  @param vp       The vertical alignment to align to.
 *  @param hp       The horizontal alignment to align to.
 *  @param autosize Whether or not to autosize the view.
 */
- (void)moveToVertical:(RBVerticalAlignment)vp
            horizontal:(RBHorizontalAlignment)hp
              autosize:(BOOL)autosize;

/**
 *  Sizes and aligns the view within it's parent view's bounds with a margin.
 *
 *  @param vp       The vertical alignment to align to.
 *  @param hp       The horizontal alignment to align to.
 *  @param autosize Whether or not to autosize the view.
 *  @param margin   The margin to maintain around the view within it's parent view's bounds.
 */
- (void)moveToVertical:(RBVerticalAlignment)vp
            horizontal:(RBHorizontalAlignment)hp
              autosize:(BOOL)autosize
            withMargin:(UIEdgeInsets)margin;

/**
 *  Aligns the view within it's parent view's bounds with the given size.
 *
 *  @param vp   The vertical alignment to align to.
 *  @param hp   The horizontal alignment to align to.
 *  @param size The size of the view.
 */
- (void)moveToVertical:(RBVerticalAlignment)vp
            horizontal:(RBHorizontalAlignment)hp
              withSize:(CGSize)size;

/**
 *  Aligns the view within it's parent view's bounds with the given size and a margin.
 *
 *  @param vp     The vertical alignment to align to.
 *  @param hp     The horizontal alignment to align to.
 *  @param size   The size of the view.
 *  @param margin The margin to maintain around the view within it's parent view's bounds.
 */
- (void)moveToVertical:(RBVerticalAlignment)vp
            horizontal:(RBHorizontalAlignment)hp
              withSize:(CGSize)size
            withMargin:(UIEdgeInsets)margin;

/**
 *  Sizes and aligns the view within the given frame.
 *
 *  @param frame    The frame to position the view inside of.
 *  @param vp       The vertical alignment to align to.
 *  @param hp       The horizontal alignment to align to.
 *  @param autosize Whether or not to autosize the view.
 */
- (void)moveToFrame:(CGRect)frame
           vertical:(RBVerticalAlignment)vp
         horizontal:(RBHorizontalAlignment)hp
           autosize:(BOOL)autosize;

/**
 *  Sizes and aligns the view within the given frame.
 *
 *  @param frame    The frame to position the view inside of.
 *  @param vp       The vertical alignment to align to.
 *  @param hp       The horizontal alignment to align to.
 *  @param autosize Whether or not to autosize the view.
 *  @param margin   The margin to maintain around the view within the given frame.
 */
- (void)moveToFrame:(CGRect)frame
           vertical:(RBVerticalAlignment)vp
         horizontal:(RBHorizontalAlignment)hp
           autosize:(BOOL)autosize
         withMargin:(UIEdgeInsets)margin;

/**
 *  Sizes and aligns the view within the given frame with a size.
 *
 *  @param frame    The frame to position the view inside of.
 *  @param vp       The vertical alignment to align to.
 *  @param hp       The horizontal alignment to align to.
 *  @param size     The size of the view.
 */
- (void)moveToFrame:(CGRect)frame
           vertical:(RBVerticalAlignment)vp
         horizontal:(RBHorizontalAlignment)hp
           withSize:(CGSize)size;

/**
 *  Sizes and aligns the view within the given frame with a size and margin.
 *
 *  @param frame    The frame to position the view inside of.
 *  @param vp       The vertical alignment to align to.
 *  @param hp       The horizontal alignment to align to.
 *  @param size     The size of the view.
 *  @param margin   The margin to maintain around the view within the given frame.
 */
- (void)moveToFrame:(CGRect)frame
           vertical:(RBVerticalAlignment)vp
         horizontal:(RBHorizontalAlignment)hp
           withSize:(CGSize)size
         withMargin:(UIEdgeInsets)margin;

@end
