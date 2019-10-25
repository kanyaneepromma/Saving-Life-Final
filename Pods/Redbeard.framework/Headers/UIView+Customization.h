//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>

/**
 *  `UIView` appearance customization properties.
 */
@interface UIView (Customization)

/**
 *  Whether or not the view should manage corners and corner radius so that a pill effect is obtained.
 *  Please note with this set to `YES` the 'cornerRadius' and 'corners' will no longer take affect until it is set back to `NO`.
 */
@property (nonatomic) BOOL pillCorners;

/**
 *  The radius of the view's corners. The higher, the more rounded the corners will be. Essentially sets self.layer.cornerRadius.
 */
@property (nonatomic) CGFloat cornerRadius;

/**
 *  Use this to affect the corner radius of specific corners. Default = UIRectCornerAllCorners.
 *  Please note if specific corners are set (i.e. not UIRectCornerAllCorners) the property self.layer.mask is co-opted 
 *  and used to manage the corners. The mask is added, removed and managed by Redbeard.
 *  Note this may therefore affect other layers you may have added. For example layer.shadow will not take affect
 *  as the layer.mask will prevent the shadow from being displayed.
 *  If specific rounded corners are set and a borderWidth > 0 is set please see note on borderEdges property.
 */
@property (nonatomic) UIRectCorner corners;

/**
 *  Use this to specify the edges that a border should be applied to. Default = UIRectEdgeAll.
 *  Please note if specific edges are set (i.e. not UIRectEdgeAll) the property self.layer will have a managed sublayer
 *  with zPosition = 999 that is used to manage the edges. The sublayer is added, removed and managed by Redbeard.
 *  The sublayer may be triggered if specific rounded corners (i.e. not UIRectCornerAllCorners) are set.
 *  Note this may therefore affect other layers you may have added.
 */
@property (nonatomic) UIRectEdge borderEdges;

/**
 *  The width of the border around the view's edge. Essentially sets self.layer.borderWidth.
 */
@property (nonatomic) CGFloat borderWidth;

/**
 *  The color of the border around the view's edge.  Essentially sets self.layer.borderColor.
 */
@property (nonatomic, nullable) UIColor *borderColor;

/**
 *  The shadow offset. This wraps self.layer.shadowOffset to allow ease of theming.
 */
@property (nonatomic) CGSize layerShadowOffset;

/**
 *  The shadow radius. This wraps self.layer.shadowRadius to allow ease of theming.
 */
@property (nonatomic) CGFloat layerShadowRadius;

/**
 *  The shadow opacity. This wraps self.layer.shadowOpacity to allow ease of theming.
 */
@property (nonatomic) CGFloat layerShadowOpacity;

/**
 *  The shadow color. This wraps self.layer.shadowColor to allow ease of theming.
 */
@property (nonatomic, nullable) UIColor *layerShadowColor;


/**
 *  Set this to `YES` if you would like to disable Redbeards view customizations, currently this means the following properties
 *  cornerRadius, corners, borderWidth, borderEdges, borderColor, pillCorners.
 *  This is useful if these properites which are managed by Redbeard intefere with your own customizations and layers.
 *  Default = `NO`.
 */
@property (nonatomic) BOOL disableManagedCustomizations;

/**
 *  Causes the forced application of any managed customizations if customizations have not been 
 *  disabled via `disableManagedCustomizations`. 
 *  Useful if you need to refresh managed customization properties such as 'corners', 'borderEdges' etc. 
 *  For performance reasons, managed customizations are applied when a change in the property occurs.
 *  e.g setting corners = UIRectCornerTopLeft twice, will not cause the view to be updated twice but only the once.
 */
- (void)applyManagedCustomizations;

@end
