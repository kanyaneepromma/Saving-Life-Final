//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 *  The result of comparing two objects for a binary search.
 */
typedef NS_ENUM(NSInteger, RBBinarySearchResult)
{
    /** The two objects are a match. */
    RBBinarySearchResultMatch,
    
    /** The first object is less than the second object. */
    RBBinarySearchResultLessThan,
    
    /** The first object is greater than the second object. */
    RBBinarySearchResultGreaterThan
};

/**
 * General purpose extensions to `NSArray`.
 */
@interface NSArray (Extensions)

/**
 * Adds the elements of self to a new `NSArray` performing `transformBlock` on each element.
 * Nil results from `transformBlock` results in the item not being added.
 *
 * @param transformBlock The block to run on each element before adding to the new `NSArray`.
 * @return The new `NSArray` containing the transformed elements.
 * @warning `transformBlock` must not be `nil`!
 */
- (nonnull NSArray *)arrayByTransformingElementsWithBlock:(nonnull __nullable id(^)(NSUInteger index, id __nonnull value))transformBlock;

/**
 * Adds the elements of self to a new `NSArray` up to a maximum of `maximumCount`.
 *
 * @param maximumCount The maximum number of elements to add to the new `NSArray`
 * @return The new `NSArray` containing a maximum of `maximumCount` elements.
 */
- (nonnull NSArray *)arrayWithMaxElementCount:(NSUInteger)maximumCount;

/**
 * Compares `arrayA` to `arrayB` adding to `addedItems` the items that were present in `arrayB` but not in `arrayA`
 * and adding to `removedItems` the items that were present in `arrayA` but not in `arrayB`.
 *
 * @param arrayA The first `NSArray`.
 * @param arrayB The `NSArray` to compare the first `NSArray` to.
 * @param addedItems The items that were present in `arrayB` but not in `arrayA`.
 * @param removedItems The items that were present in `arrayA` but not in `arrayB`.
 */
+ (void)compareArray:(nonnull NSArray *)arrayA withArray:(nonnull NSArray *)arrayB providingAddedItems:(NSArray * __nullable * __nullable)addedItems andRemovedItems:(NSArray * __nullable * __nullable)removedItems;

/**
 * Shuffles the elements of the `NSArray` randomly.
 *
 * @return A new `NSArray` with the shuffled elements.
 */
- (nonnull NSArray *)shuffledArray;

/**
 * Gets the first element of the `NSArray`, or `nil` if the `NSArray` is empty.
 *
 * @return The first element of the `NSArray` or nil.
 */
- (nullable id)firstObject;

/**
 * Gets the middle element of the `NSArray`, or `nil` if the `NSArray` is empty.
 *
 * @return The middle element of the `NSArray` or nil.
 */
- (nullable id)middleObject;

/**
 * Gets a random element of the `NSArray`, or `nil` if the `NSArray` is empty.
 *
 * @return A random element of the `NSArray` or nil.
 */
- (nullable id)randomObject;

/**
 * Whether the index `index` is in range for this `NSArray`.
 *
 * @param index The zero-based index of an element.
 * @return `true` if `index` is in range for the `NSArray`, and `false` if not.
 */
- (BOOL)indexInRange:(NSUInteger)index;

/**
 * Runs a binary search on the `NSArray` to find the range that matches according to `matchBlock`.
 * It assumes that the `NSArray` is sorted and the matching elements are contiguous.
 *
 * @param matchBlock The block used to determine the `RBBinarySearchResult` match for a given element.
 * @param startIndex The initial and resulting start index of the matching range.
 * @param finalIndex The initial and resulting end index of the matching range.
 * @return Whether or not the binary search was successful.
 * @warning `startIndex` and `finalIndex` must be initialized.  The default initialization should be 0 to `count` - 1.
 */
- (BOOL)binarySearchWithBlock:(nonnull RBBinarySearchResult(^)(id __nonnull obj))matchBlock withStartIndex:(nonnull NSUInteger *)startIndex withFinalIndex:(nonnull NSUInteger *)finalIndex;

/**
 * Check whether the `NSArray` contains at least one element of type `type`.
 *
 * @param type The `Class` type to check the existance of.
 * @return Whether or not at least one element of type `type` exists in the `NSArray`.
 */
- (BOOL)containsObjectOfType:(nonnull Class)type;

/**
 * Creates a new `NSArray` with elements excluding those between `fromIndex` and `toIndex`, adding to
 * `removedObjects` those elements within the exclusion range.
 *
 * @param fromIndex The starting index of the exclusion range.
 * @param toIndex The last index of the exclusion range.
 * @param removedObjects The excluded items.
 * @return The new `NSArray` with all elements outside of the exclusion range.
 */
- (nonnull NSArray *)arrayExcludingObjectsFrom:(NSUInteger)fromIndex to:(NSUInteger)toIndex removedObjects:(NSArray * __nullable * __nullable)removedObjects;

/**
 * Performs a merge on the property list by overriding all keys with their siblings
 * providing the given postfix.
 *
 * *An example: *
 * { "key": "value", "key_iPad": "value_iPad" } merged with the postfix "_iPad"
 * and `removeOverridesAfterApply` set to true would yield { "key": "value_iPad" }
 *
 * @param priorityPostfix The postfix denoting the overriding key.
 * @param removeOverridesAfterApply If this is `true`, the overriding keys (those with the postfix) will be removed after they have been applied.
 * @return The merged property list.
 */
- (nonnull instancetype)mergedArrayWithPriorityPostfix:(nonnull NSString *)priorityPostfix
                     removeOverridesAfterApply:(BOOL)removeOverridesAfterApply;

/**
 * Creates a new `NSArray` with all elements excluding those in `excludingObjects`.
 *
 * @param excludingObjects The objects to exclude.
 * @return A new `NSArray` containing all elements excluding those in `excludingObjects`.
 */
- (nonnull NSArray *)arrayExcludingObjects:(nonnull NSArray *)excludingObjects;

/**
 * Creates a new `NSArray` containing all of the elements that exist in both `self`
 * and in `array`.
 *
 * @param array The `NSArray` to intersect with `self`.
 * @return A new `NSArray` containing all of the elements that exist in both `self` and in `array`.
 */
- (nonnull NSArray *)arrayByIntersectingWithArray:(nonnull NSArray *)array;

/**
 * Removes all keys from the property list recursively except the keys specified in
 * `onlyLeafKeys`.
 *
 * @param onlyLeafKeys An `NSArray` of the keys to keep.
 * @return The pruned property list.
 */
- (nonnull NSArray *)prunedArrayWithOnlyLeafKeys:(nonnull NSArray *)onlyLeafKeys;

/**
 * Combines the `NSString` representations of the elements of the `NSArray`
 * to a single `NSString` using the separator given.
 *
 * @param separator The separator to join the elements with.
 * @return The joined `NSString`.
 */
- (nonnull NSString *)stringByCombiningComponentsWithSeparator:(nonnull NSString *)separator;

/**
 * Creates an `NSArray` containing all elements that match with the block given.
 *
 * @param matchBlock Used to determine whether a given element is a match or not.
 * @return The new `NSArray` containing only matching elements.
 */
- (nonnull NSArray *)arrayWithItemsMatching:(nonnull BOOL(^)(id __nonnull obj))matchBlock;

/**
 * Creates an `NSArray` containing all elements that are of the type given.
 *
 * @param itemType The type of object to match.
 * @return The new `NSArray` containing only matching elements.
 */
- (nonnull NSArray *)arrayWithItemsOfType:(nonnull Class)itemType;

@end


/** General purpose extensions to `NSMutableArray`.
 */
@interface NSMutableArray (Extensions)

/**
 * Performs the `transformBlock` on each element, removing the item when nil is returned.
 *
 * @param transformBlock The block to run on each element.
 * @warning `transformBlock` must not be `nil`!
 */
- (void)transformElementsWithBlock:(nonnull id __nullable (^)(NSUInteger index, id __nonnull value))transformBlock;

/**
 * Randomly shuffles the elements in the `NSArray`.
 */
- (void)shuffle;

/**
 * Removes the last element from the `NSArray` and returns it.
 *
 * @return The removed last element of the `NSArray`.
 */
- (nullable id)popLastObject;

/**
 * Adds an object to the `NSArray` unless it already exists in the `NSArray`.
 *
 * @param object The object to add to the `NSArray`.
 * @return Whether the item was added to the `NSArray` or not.
 */
- (BOOL)addObjectIfMissing:(nonnull id)object;

/**
 * Removes an object from the `NSArray` unless it doesn't already exist in the `NSArray`.
 *
 * @param object The object to remove from the `NSArray`.
 * @return Whether the item was removed from the `NSArray` or not.
 */
- (BOOL)removeObjectIfExists:(nonnull id)object;

@end
