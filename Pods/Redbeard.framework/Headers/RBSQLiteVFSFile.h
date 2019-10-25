//
// Copyright (c) 2018 Redbeard Services Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef long long int sqlite3_int64;

@interface RBSQLiteVFSFile : NSObject

// Note: These are the public accessors, which are thread-safe.
//       Do not override these!

- (int)close;
- (int)readIntoBuffer:(void *)buffer amount:(NSUInteger)amount withOffset:(sqlite3_int64)offset;
- (int)writeFromBuffer:(const void *)buffer amount:(NSUInteger)amount withOffset:(sqlite3_int64)offset;
- (int)truncate:(sqlite3_int64)size;
- (int)syncWithFlags:(int)flags;
- (int)fileSizeWithOutSize:(sqlite3_int64 *)pSize;
- (int)lock:(int)eLock;
- (int)unlock:(int)eLock;
- (int)checkReservedLockWithResultOut:(int *)pResOut;
- (int)fileControlWithOperation:(int)op withArguments:(void *)pArg;
- (int)sectorSize;
- (int)deviceCharacteristics;

#pragma mark -
#pragma mark Subclassing

// Note: these functions return SQL error codes, or SQLITE_OK!

- (int)performClose;
- (int)performReadIntoBuffer:(void *)buffer amount:(NSUInteger)amount withOffset:(sqlite3_int64)offset;
- (int)performWriteFromBuffer:(const void *)buffer amount:(NSUInteger)amount withOffset:(sqlite3_int64)offset;
- (int)performTruncate:(sqlite3_int64)size;
- (int)performSyncWithFlags:(int)flags;
- (int)performFileSizeWithOutSize:(sqlite3_int64 *)pSize;
- (int)performLock:(int)eLock;
- (int)performUnlock:(int)eLock;
- (int)performCheckReservedLockWithResultOut:(int *)pResOut;
- (int)performFileControlWithOperation:(int)op withArguments:(void *)pArg;
- (int)performSectorSize;
- (int)performDeviceCharacteristics;

@end
