//
//  C2DXiOSMobLinkDelegate.h
//  Cocos2DXForMobLink
//
//  Created by 陈剑东 on 2017/5/8.
//
//
#include "C2DXiOSMobLink.h"

#import <Foundation/Foundation.h>
#import <MobLink/IMLSDKRestoreDelegate.h>

using namespace mob::moblink;

/**
 *  回调代理
 */
@interface C2DXiOSMobLinkDelegate : NSObject <IMLSDKRestoreDelegate>

/**
 *  获取代理对象
 *
 *  @return 代理对象
 */
+ (C2DXiOSMobLinkDelegate *)defaultDelegate;

@end
