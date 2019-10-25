//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

#pragma mark -
#pragma mark General Numeric

#define MINMAX(number, minimumValue, maximumValue) \
MAX(MIN(number, maximumValue), minimumValue)

#pragma mark -
#pragma mark NSError

/**
 * Creates an `NSError`.
 *
 * @param domainName The domain in which the error occurred.
 * @param code The error code, or `0` if no code.
 * @param messageString The error description detailing what happened.
 * @return The `NSError` object.
 */
static inline NSError *NSErrorMakeWithDomain(NSString *domainName, NSInteger code, NSString *messageString)
{
    return [NSError errorWithDomain:domainName
                               code:code
                           userInfo:@{ NSLocalizedDescriptionKey: messageString }];
}

/**
 *  Creates an `NSError` object with the given code and message.
 *
 *  @param code          The error code.
 *  @param messageString The error message.
 *
 *  @return The `NSError` object.
 */
static inline NSError *NSErrorMake(NSInteger code, NSString *messageString)
{
    return NSErrorMakeWithDomain([[NSBundle mainBundle] infoDictionary][@"CFBundleIdentifier"],
                                 code,
                                 messageString);
}

#pragma mark -
#pragma mark Bitwise (unsigned int)

/**
 *  Sets the bit at the given index.
 *
 *  @param x      The `unsigned int` to set the bit in.
 *  @param bitNum The index of the bit to set.
 */
static inline void bitwise_set_bit(unsigned int *x, int bitNum)
{
    *x |= (1 << bitNum);
}

/**
 *  Unsets the bit at the given index.
 *
 *  @param x      The `unsigned int` to unset the bit in.
 *  @param bitNum The index of the bit to unset.
 */
static inline void bitwise_unset_bit(unsigned int *x, int bitNum)
{
    *x &= ~(1 << bitNum);
}

/**
 *  Copies the bit given to the value at the given bit index.
 *
 *  @param x      The `unsigned int` to copy the bit to.
 *  @param bitNum The index of the bit to copy to.
 *  @param v      The bit to copy.
 */
static inline void bitwise_copy_bit(unsigned int *x, int bitNum, BOOL v)
{
    *x = ( v ? (*x | (1 << bitNum)) : (*x & ~(1 << bitNum)) );
}

/**
 *  Retrieves the value of the bit at the given index.
 *
 *  @param x      The `unsigned int` value to check the bit in.
 *  @param bitNum The index of the bit to check.
 *
 *  @return The value of the bit.
 */
static inline BOOL bitwise_check_bit(unsigned int x, int bitNum)
{
    return x & (1 << bitNum);
}

/**
 *  Sets a bit mask in the given value.
 *
 *  @param x    The `unsigned int` value to set the bit mask to.
 *  @param mask The bit mask to set.
 */
static inline void bitwise_set(unsigned int *x, unsigned int mask)
{
    *x |= mask;
}

/**
 *  Unsets a bit mask in the given value.
 *
 *  @param x    The `unsigned int` value to unset the bit mask to.
 *  @param mask The bit mask to unset.
 */
static inline void bitwise_unset(unsigned int *x, unsigned int mask)
{
    *x &= ~mask;
}

/**
 *  Copies the bits in the bit mask from one value to another.
 *
 *  @param x    The `unsigned int` value to update.
 *  @param mask The bit mask to copy.
 *  @param v    The `unsigned int` to copy the bits in the mask from.
 */
static inline void bitwise_copy(unsigned int *x, unsigned int mask, unsigned int v)
{
    *x = ( v ? (*x | mask) : (*x & ~mask) );
}

/**
 *  Checks whether a bit mask is set.
 *
 *  @param x    The `unsigned int` value to check the bit mask in.
 *  @param mask The bit mask to check.
 *
 *  @return Whether or not the bit mask was set.
 */
static inline BOOL bitwise_check(unsigned int x, unsigned int mask)
{
    return x & mask;
}

#pragma mark -
#pragma mark NSRange

/**
 *  Creates a new `NSRange` value.
 *
 *  @param location The start location of the range.
 *  @param length   The length of the range.
 *
 *  @return The `NSRange` value.
 */
static inline NSRange NSRangeMake(NSUInteger location, NSUInteger length)
{
    NSRange r;
    r.location = location;
    r.length = length;
    return r;
}

/**
 *  Creates a new `NSRange` value with a first and last position.
 *
 *  @param first The position of the first element.
 *  @param last  The position of the last element.
 *
 *  @return The `NSRange` value.
 */
static inline NSRange NSRangeWithFirstAndLast(NSUInteger first, NSUInteger last)
{
    return NSRangeMake(first, last - first + 1);
}

/**
 *  The index of the first element in the `NSRange` value.
 *
 *  @param range The `NSRange` value.
 *
 *  @return The index of the first element.
 */
static inline NSUInteger NSRangeFirstIndex(NSRange range)
{
    if(range.length > 0)
        return range.location;
    
    return NSNotFound;
}

/**
 *  The index of the last element in the `NSRange` value.
 *
 *  @param range The `NSRange` value.
 *
 *  @return The index of the last element.
 */
static inline NSUInteger NSRangeLastIndex(NSRange range)
{
    if(range.length > 0)
        return range.location + range.length - 1;
    
    return NSNotFound;
}

/**
 *  An empty range.
 */
static NSRange NSRangeZero = { 0, 0 };

#pragma mark -
#pragma mark GCD

/**
 *  Performs the given block after the given delay in seconds.
 *
 *  @param delayInterval  The delay in seconds.
 *  @param actionBlock    The block to perform after the delay.
 */
static inline void dispatch_main_with_delay(NSTimeInterval delayInterval, void(^actionBlock)(void))
{
    dispatch_time_t popTime = dispatch_time(DISPATCH_TIME_NOW, (int64_t)(delayInterval * NSEC_PER_SEC));
    dispatch_after(popTime, dispatch_get_main_queue(), ^(void){
        
        actionBlock();
        
    });
}
