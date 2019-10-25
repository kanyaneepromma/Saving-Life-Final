//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Redbeard/RBSQLiteVFSFile.h>

@interface RBSQLiteVFS : NSObject

@property (nonatomic, readonly) NSString *name;

+ (instancetype)vfsWithName:(NSString *)name;
- (instancetype)initWithName:(NSString *)name;

- (int)openWithTarget:(NSString *)target flags:(int)flags outFlags:(int *)outFlags;
- (int)delete:(NSString *)name withSyncDir:(int)syncDir;
- (int)access:(NSString *)name withFlags:(int)flags withResultOut:(int *)pResOut;
- (int)fullPathname:(NSString *)name withOutCount:(int)nOut withOutChars:(char *)zOut;
- (int)randomness:(int)nByte withOutChars:(char *)zOut;
- (int)sleep:(int)microseconds;
- (int)currentTime:(double *)time;

#pragma mark -
#pragma mark Subclassing

- (RBSQLiteVFSFile *)file;

- (int)performOpenWithTarget:(NSString *)target flags:(int)flags outFlags:(int *)outFlags;
- (int)performDelete:(NSString *)name withSyncDir:(int)syncDir;
- (int)performAccess:(NSString *)name withFlags:(int)flags withResultOut:(int *)pResOut;
- (int)performFullPathname:(NSString *)name withOutCount:(int)nOut withOutChars:(char *)zOut;
- (int)performRandomness:(int)nByte withOutChars:(char *)zOut;
- (int)performSleep:(int)microseconds;
- (int)performCurrentTime:(double *)time;

@end
