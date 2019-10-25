//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import <Redbeard/UIView+FormField.h>

@protocol RBSliderViewDelegate;

/**
 *  A slider field that can be used as a normal slider and a range slider.
 *  All components are internally `RBImageView`'s therefore you may 
 *  theme them. See theming documentation.
 */
@interface RBSliderView : UIControl

/**
 *  A delegate to receive slider value changes and extend string formatting.
 */
@property (nonatomic, weak, nullable) id<RBSliderViewDelegate> delegate;

/**
 *  The margin around the controls.
 */
@property (nonatomic) UIEdgeInsets margin;

/**
 *  The spacing between the slider and the slider labels.
 */
@property (nonatomic) CGFloat spacing;

/**
 *  Whether or not the range label is enabled. Default = `YES`.
 */
@property (nonatomic) BOOL labelsEnabled;

/**
 *  The minimum size of the selected range.
 */
@property (nonatomic, readonly) float minimumRange;

/**
 *  The maximum size of the selected range.
 */
@property (nonatomic, readonly) float maximumRange;

/**
 *  The minimum value of the available range.
 */
@property (nonatomic, readonly) float minimumValue;

/**
 *  The maximum value of the available range.
 */
@property (nonatomic, readonly) float maximumValue;

/**
 *  The start value of the selected range.
 */
@property (nonatomic) float startValue;

/**
 *  The end value of the selected range.
 */
@property (nonatomic) float endValue;

/**
 *  The start percentage of the selected range.
 */
@property (nonatomic, readonly) float startPercentage;

/**
 *  The end percentage of the selected range.
 */
@property (nonatomic, readonly) float endPercentage;

/**
 *  The size of the available range.
 */
@property (nonatomic, readonly) float range;

/**
 *  The size of the selected range.
 */
@property (nonatomic, readonly) float selectedRange;

/**
 *  Hide the start handle. Useful to make this function like a normal non-range slider. Default = `NO`.
 */
@property (nonatomic) BOOL hideStartHandle;

/**
 *  Disable the start handle. Stops the handle from being moved. Default = `NO`.
 */
@property (nonatomic) BOOL disableStartHandle;

/**
 *  Hide the end handle. Useful to make this function like a normal non-range slider in reverse. Default = `NO`.
 */
@property (nonatomic) BOOL hideEndHandle;

/**
 *  Disable the end handle. Stops the handle from being moved. Default = `NO`.
 */
@property (nonatomic) BOOL disableEndHandle;

/**
 *  Called to set the slider values. All values must be greater than zero.
 *  You may use `RBSliderViewDelegate` delegate to format and present values differently.
 *  The minimum and maximum range is set to equal minimum and maximum values.
 *
 *  @param minimumValue The smallest possible value that may be selected.
 *  @param maximumValue The largest possible value that may be selected.
 *  @param startValue   The inital starting value.
 *  @param endValue     The inital ending value.
 */
- (void)setMinimumValue:(float)minimumValue maximumValue:(float)maximumValue startValue:(float)startValue endValue:(float)endValue;

/**
 *  Called to set the slider values. All values must be greater than zero. 
 *  You may use `RBSliderViewDelegate` delegate to format and present values differently.
 *
 *  @param minimumValue The smallest possible value that may be selected.
 *  @param maximumValue The largest possible value that may be selected.
 *  @param startValue   The inital starting value.
 *  @param endValue     The inital ending value.
 *  @param minimumRange The smallest range (difference between endValue - startValue) that can be set.
 *  @param maximumRange The largest range (difference between endValue - startValue) that can be set.
 */
- (void)setMinimumValue:(float)minimumValue maximumValue:(float)maximumValue startValue:(float)startValue endValue:(float)endValue minimumRange:(float)minimumRange
           maximumRange:(float)maximumRange;

@end

/**
 *  A delegate to receive slider value changes and extend string formatting for an `RBSliderView` object.
 */
@protocol RBSliderViewDelegate <NSObject>

@required

/**
 *  Called to format the start value string for presentation in the label.
 *
 *  @param startValue  The start value.
 *  @param sliderField The slider field object.
 *
 *  @return The formatted `NSString` object.
 */
- (nonnull NSString *)formatSliderStartValue:(float)startValue sliderField:(nonnull RBSliderView *)sliderField;

/**
 *  Called to format the end value string for presentation in the label.
 *
 *  @param endValue    The end value.
 *  @param sliderField The slider field object.
 *
 *  @return The formatted `NSString` object.
 */
- (nonnull NSString *)formatSliderEndValue:(float)endValue sliderField:(nonnull RBSliderView *)sliderField;

@optional

/**
 *  Called when the numeric range selection changes.
 *
 *  @param sliderField The slider field object.
 */
- (void)valueDidChangeWithSliderField:(nonnull RBSliderView *)sliderField;

@end
