//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>

#import <Redbeard/RBImageSelectionViewItem.h>

@class RBPositioner;

/**
 *  Describes how to size `RBImageSelectionViewItem`s.
 */
typedef NS_ENUM(NSInteger, RBImageSelectionViewItemSizeMode)
{
    /**
     *  Indicates that the `itemSize` property should be used to allocate the size of items.
     */
    RBImageSelectionViewItemSizeModeSize,
    
    /**
     *  Indicates that the size of each item should match the `RBImageSelectionViewItem` itself. In this case the `itemSize` is ignored.
     */
    RBImageSelectionViewItemSizeModeFill,
    
    /**
     *  Indicates that the vertical size of each item should be obtained from the height applied to the `RBImageSelectionViewItem` itself. In this case the height `itemSize` component is ignored and only the width is used.
     */
    RBImageSelectionViewItemSizeModeFillVertical,
    
    /**
     *  Indicates that the horizontal size of each item should be obtained from the width applied to the `RBImageSelectionViewItem` itself. In this case the width `itemSize` component is ignored and only the height is used.
     */
    RBImageSelectionViewItemSizeModeFillHorizontal
};

@protocol RBImageSelectionViewDelegate;

/**
 *  An image selection field.
 */
@interface RBImageSelectionView : UIView

/**
 *  A delegate to receive image selection field events.
 */
@property (nonatomic, weak, nullable) id<RBImageSelectionViewDelegate> delegate;

/**
 *  The size of image item cells. Default = `150, 150`.
 */
@property (nonatomic) CGSize itemSize;

/**
 *  The sizing moode of items. Default = `RBImageSelectionViewItemSizeModeSize`.
 */
@property (nonatomic) RBImageSelectionViewItemSizeMode itemSizeMode;

/**
 *  Whether or not selection is allowed. Setting this to `NO` is useful if you just want to display a set of images.  Default = `YES`.
 */
@property (nonatomic) BOOL allowsSelection;

/**
 *  Whether or not multiple selection is allowed. Default = `NO`.
 */
@property (nonatomic) BOOL allowsMultipleSelection;

/**
 *  Whether or not zero selection is allowed.  Default = `YES`.
 */
@property (nonatomic) BOOL zeroSelectionAllowed;

/**
 *  An optional image that should be displayed if a failure occurs loading images.
 */
@property (nonatomic, nullable) UIImage *failureImage;

/**
 *  The content mode of the failure image.
 */
@property (nonatomic) UIViewContentMode failureImageContentMode;

/**
 *  The optional image overlay when selected.
 */
@property (nonatomic, nullable) UIImage *selectedOverlayImage;

/**
 *  The content mode of the selected overlay image.
 */
@property (nonatomic) UIViewContentMode selectedOverlayImageContentMode;

/**
 *  The default image to be used when an image is being downloaded.
 */
@property (nonatomic, nullable) UIImage *loadingImage;

/**
 *  The content mode of the loading image.
 */
@property (nonatomic) UIViewContentMode loadingImageContentMode;

/**
 *  Whether or not paging is enabled. When set this will reset the current scroll location. This means the underlying scroll view stops on multiples of the scroll view’s bounds.  Default = `NO`.
 */
@property (nonatomic) BOOL pagingEnabled;

/**
 *  The current page when `pagingEnabled` is set to YES. Value < 0 when paging is not enabled or there are no pages. Default = `-1` (no paging enabled or no pages).
 */
@property (nonatomic, readonly) NSInteger currentPageIndex;

/**
 *  Whether or not to show vertical scroll indicators.  Default = `YES`.
 */
@property (nonatomic) BOOL showsVerticalScrollIndicator;

/**
 *  Whether or not to show horizontal scroll indicators.  Default = `YES`.
 */
@property (nonatomic) BOOL showsHorizontalScrollIndicator;

/**
 *  An array of `RBImageSelectionViewItem` objects.
 */
@property (nonatomic, nullable) NSArray<RBImageSelectionViewItem *> *items;

/**
 *  The selected items by index.
 */
@property (nonatomic, readonly, nullable) NSArray<NSNumber *> *selectedIndexes;

/**
 *  The layout positioner used. You may theme this positioner. Default values =
 *  spacing = 10,
 *  dimensions = 1,
 *  margin = [0, 0, 0, 0],
 *  orientation = `RBOrientationHorizontal`,
 *  sizing = `RBGridPositionerSizeToSize`.
 */
@property (nonatomic, nonnull, readonly) RBGridPositioner *positioner;

/**
 *  Updates the selection state of the image at the given index.
 *
 *  @param selected  Whether or not the image item should be selected.
 *  @param index    The index of the image item to update the selection state of.
 */
- (void)setSelected:(BOOL)selected at:(NSInteger)index;

/**
 *  Unselects all image items.
 */
- (void)unselectAllItems;

/**
 *  The default layout positioner used. You may theme this positioner. Default = `RBGridPositioner` with values
 *  spacing = 0,
 *  dimensions = 1,
 *  margin = [0, 0, 0, 0],
 *  orientation = `RBOrientationVertical`,
 *  sizing = `RBGridPositionerSizeToSize`.
 *
 *  @return The default positioner.
 */
+ (nonnull RBPositioner *)defaultPositioner;

@end

/**
 *  A delegate to receive image selection field events for an `RBImageSelectionView` object.
 */
@protocol RBImageSelectionViewDelegate <NSObject>

@optional

/**
 *  Called when an image item was selected.
 *
 *  @param imageSelectionView   The `RBImageSelectionView` object.
 *  @param index                The index of the image item that was selected.
 */
- (void)imageSelectionView:(nonnull RBImageSelectionView *)imageSelectionView didSelectItemAt:(NSInteger)index;

/**
 *  Called when an image item was unselected.
 *
 *  @param imageSelectionView   The `RBImageSelectionView` object.
 *  @param index                The index of the image item that was unselected.
 */
- (void)imageSelectionView:(nonnull RBImageSelectionView *)imageSelectionView didDeselectItemAt:(NSInteger)index;

/**
 *  Called when `pagingEnabled` is set and a pagination occurs.
 *
 *  @param imageSelectionView   The `RBImageSelectionView` object.
 *  @param index                The index of the current page.
 */
- (void)imageSelectionView:(nonnull RBImageSelectionView *)imageSelectionView didPaginateTo:(NSInteger)index;

@end
