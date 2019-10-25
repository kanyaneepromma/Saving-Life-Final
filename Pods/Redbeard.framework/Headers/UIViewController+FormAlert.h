//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>

@class RBFormAlertSchema;
@class RBFormAlertViewController;

/**
 *  A delegate to receive form events such as submission and button taps for an `RBFormAlertViewController`.
 */
@protocol RBFormAlertViewControllerDelegate <NSObject>

@required

/**
 *  Called when the form is successfully submitted.
 *
 *  @param formAlertViewController The `RBFormAlertViewController` object.
 *  @param values                  The form values that were submitted.
 */
- (void)formAlertViewController:(nonnull RBFormAlertViewController *)formAlertViewController didSubmitWithValues:(nonnull NSDictionary<NSString *, id> *)values;

/**
 *  Called when the form alert was cancelled.
 *
 *  @param formAlertViewController The `RBFormAlertViewController` object.
 */
- (void)formAlertViewControllerDidCancel:(nonnull RBFormAlertViewController *)formAlertViewController;

/**
 *  Called when a form alert button was tapped.
 *
 *  @param formAlertViewController The `RBFormAlertViewController` object.
 *  @param identifier               The identifier of the button that was tapped.
 */
- (void)formAlertViewController:(nonnull RBFormAlertViewController *)formAlertViewController buttonWasSelectedWithIdentifier:(nonnull NSString *)identifier;

@optional

/**
 *  Called for each schema items corresponding `UIView` when the form is being setup.
 *
 *  @param formAlertViewController  The `RBFormAlertViewController` object.
 *  @param view                     The `UIView` object that the schema with the provided identifier has created.
 *  @param identifier               The identifier of the schema.
 */
- (void)formAlertViewController:(nonnull RBFormAlertViewController *)formAlertViewController
                      setupView:(nonnull UIView *)view
                  forIdentifier:(nonnull NSString *)identifier;

/**
 *  Called when a field will have it's value changed.
 *
 *  @param formAlertViewController  The `RBFormAlertViewController` object.
 *  @param identifier               The identifier of the field.
 *  @param value                    The current value of the field.
 *  @param newValue                 The new value that will be assigned to the field.
 */
- (void)formAlertViewController:(nonnull RBFormAlertViewController *)formAlertViewController
            fieldWithIdentifier:(nonnull NSString *)identifier
            willUpdateFromValue:(nullable id)value
                        toValue:(nullable id)newValue;

/**
 *  Called when a field value has changed.
 *
 *  @param formAlertViewController  The `RBFormAlertViewController` object.
 *  @param identifier               The identifier of the field.
 *  @param previousValue            The previous value of the field.
 *  @param value                    The new value of the field.
 */
- (void)formAlertViewController:(nonnull RBFormAlertViewController *)formAlertViewController
            fieldWithIdentifier:(nonnull NSString *)identifier
             didUpdateFromValue:(nullable id)previousValue
                        toValue:(nullable id)value;

/**
 *  Gets the view controller that should be used when presenting the photo library or camera.
 *
 *  @param formAlertViewController The `RBFormAlertViewController` object.
 *
 *  @return The `UIViewController` to present with.
 */
- (nonnull UIViewController *)presentingViewControllerForFormAlertViewController:(nonnull RBFormAlertViewController *)formAlertViewController;

@end

/**
 *  A block that is called when a managed form alert is submitted or cancelled by the user.
 *
 *  @param results      The form values that were submitted, or `nil` if the form was cancelled.
 *  @param wasCancelled Whether or not the form was cancelled by the user.
 */
typedef void (^FormAlertCompletionBlock)(NSDictionary<NSString *, id> * __nullable results, BOOL wasCancelled);

/**
 *  A block that is called when a custom button is tapped on a managed form alert.
 *
 *  @param buttonIdentifier     The identifier of the button that was tapped.
 *  @param shouldDismissAlert   Whether or not the form alert should be dismissed as a result of the button tap.
 */
typedef void (^FormAlertButtonSelectionBlock)(NSString * __nonnull buttonIdentifier, BOOL * __nonnull shouldDismissAlert);

/**
 *  Managed form alert functionality for any `UIViewController`.
 */
@interface UIViewController (FormAlert) <RBFormAlertViewControllerDelegate>

/**
 *  The default animator to use when presenting the form alert.
 */
@property (nonatomic, nonnull) RBPresentationAnimator *defaultFormAlertAnimator;

/**
 *  The default vertical alignment to use when positioning the form alert.
 */
@property (nonatomic) RBVerticalAlignment defaultFormAlertAlignment;

/**
 *  The default margin to use when positioning the form alert.
 */
@property (nonatomic) UIEdgeInsets defaultFormAlertMargin;

/**
 *  Presents a managed `RBFormAlertViewController` alert with the given schema. Note: You can also override the required delegate (RBFormAlertViewControllerDelegate) methods or implement the optional methods on the view controller for more control.
 *
 *  @param schema         The schema that describes the fields and functionality of the form to display.
 *  @param buttonSelected An optional block to be called when a custom button is tapped. Not not invoked for identifers `RBFormAlertSchema.submitButtonIdentifier`/`submitButton` and `RBFormAlertSchema.submitButtonIdentifier.cancelButtonIdentifier`/`cancelButton`.
 *  @param animated       Whether or not the presentation should be animated.
 *  @param completion     An optional block to be called when the form is dismissed or submitted successfully.
 */
- (void)formAlertWithSchema:(nonnull RBFormAlertSchema *)schema
             buttonSelected:(nullable FormAlertButtonSelectionBlock)buttonSelected
                   animated:(BOOL)animated
                 completion:(nullable FormAlertCompletionBlock)completion;
    
/**
 *  Presents the given managed `RBFormAlertViewController` alert. Note: You can also override the required delegate (RBFormAlertViewControllerDelegate) methods or implement the optional methods on the view controller for more control.
 *
 *  @param formAlertViewController  The alert.
 *  @param buttonSelected           An optional block to be called when a custom button is tapped. Not not invoked for identifers `RBFormAlertSchema.submitButtonIdentifier`/`submitButton` and `RBFormAlertSchema.submitButtonIdentifier.cancelButtonIdentifier`/`cancelButton`.
 *  @param animated                 Whether or not the presentation should be animated.
 *  @param completion       An optional block to be called when the form is dismissed or submitted successfully.
 */
- (void)formAlertWithFormAlertViewController:(nonnull RBFormAlertViewController *)formAlertViewController
                              buttonSelected:(nullable FormAlertButtonSelectionBlock)buttonSelected
                                    animated:(BOOL)animated
                                  completion:(nullable FormAlertCompletionBlock)completion;
/**
 *  Dismisses the top form alert that is open.
 *
 *  @param animated   Whether the dismissal should be animated.
 *  @param completion An optional block to be called when the form alert has been dismissed.
 *
 *  @return Whether or not there was an open form alert to close.
 */
- (BOOL)dismissFormAlertWithAnimation:(BOOL)animated
                           completion:(nullable dispatch_block_t)completion;

@end
