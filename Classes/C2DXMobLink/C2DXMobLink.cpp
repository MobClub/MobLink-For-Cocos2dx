//
//  C2DXMobLink.cpp
//  Cocos2DXForMobLink
//
//  Created by 陈剑东 on 2017/5/4.
//
//

#include "C2DXMobLink.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS

#include "C2DXiOSMobLink.h"

#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#include ""

#endif

using namespace mob::moblink;

void C2DXMobLink::registerApp(const char *appKey)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    
    //Andorid
    
   
    
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    
    //iOS
    C2DXiOSMobLink::registerApp(appKey);
    
#endif
}

void C2DXMobLink::getMobId(mob::moblink::C2DXMobLinkScene *scene)
{
    
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    
    //Andorid
    
    
    
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    
    //iOS
    C2DXiOSMobLink::getMobId(scene);
    
#endif
}

void C2DXMobLink::setRestoreCallBack(mob::moblink::C2DXMobLinkCallBack callback)
{

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    
    //Andorid

    
    
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    
    //iOS
    C2DXiOSMobLink::setRestoreCallBack(callback);
    
#endif
    
}



