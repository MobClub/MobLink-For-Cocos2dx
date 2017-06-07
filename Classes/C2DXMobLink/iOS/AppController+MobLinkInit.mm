//
//  AppController+MobLinkInit.m
//  Cocos2DXForMobLink
//
//  Created by 陈剑东 on 2017/6/7.
//
//

#import "AppController+MobLinkInit.h"
#import "C2DXiOSMobLinkDelegate.h"
#import <MobLink/MobLink.h>

@implementation AppController (MobLinkInit)

+ (void)initialize
{
    [MobLink setDelegate:[C2DXiOSMobLinkDelegate defaultDelegate]];
}


@end
