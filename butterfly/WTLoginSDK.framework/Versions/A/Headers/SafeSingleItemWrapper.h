//
//  SafeSingleItemWrapper.h
//  WTLoginSDKForIOS
//
//  Created by  on 11-11-14.
//  Copyright (c) 2011年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SingleItemWrapper.h"

@interface SafeSingleItemWrapper : NSObject
{
    SingleItemWrapper *wapper;
    NSMutableDictionary *wapperDict;
    NSString *filePath;
}

// Designated initializer.
- (id)initSafeWithIdentifier: (NSString *)identifier accessGroup:(NSString *) accessGroup;

//- (BOOL)setSafeObject:(id)inObject forKey:(id)key;
//- (id)safeObjectForKey:(id)key;

- (BOOL)setFileStoreObject:(id)inObject forKey:(id)key;
- (id)fileStoreForKey:(id)key;

- (id)keyChainStoreForKey:(id)key;



// Initializes and resets the default generic keychain item data.
- (void)resetSafeKeychainItem;




@end
