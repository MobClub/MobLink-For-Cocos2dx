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

#include "C2DXAndroidMobLink.h"

#endif

using namespace mob::moblink;

void C2DXMobLink::registerApp(const char *appKey)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    
    //Andorid
    C2DXAndroidMobLink::registerApp(appKey);
    
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    
    //iOS
    C2DXiOSMobLink::registerApp(appKey);
    
#endif
}

void C2DXMobLink::getMobId(mob::moblink::C2DXMobLinkScene *scene, C2DXGetMobIdResultEvent callback)
{
    
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    
    //Andorid
    C2DXAndroidMobLink::getMobId(scene, callback);

#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    
    //iOS
    C2DXiOSMobLink::getMobId(scene, callback);
    
#endif
}

void C2DXMobLink::setSceneRestoreCallBack(C2DXRestoreSceneResultEvent callback)
{

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    
    //Andorid
    C2DXAndroidMobLink::setRestoreCallBack(callback);

#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    
    //iOS
    C2DXiOSMobLink::setRestoreCallBack(callback);
    
#endif
    
}

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
void C2DXMobLink::updateIntent()
{
    C2DXAndroidMobLink::updateIntent();
}
#endif



