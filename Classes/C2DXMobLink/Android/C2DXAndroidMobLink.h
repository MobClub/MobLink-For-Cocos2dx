//
//  C2DXAndroidMobLink.h
//  Cocos2DXForMobLink
//
//  Created by 李同垒 on 2017/5/18.
//
//

#ifndef __C2DXMobLinkSample__C2DXAndroidMobLink__
#define __C2DXMobLinkSample__C2DXAndroidMobLink__

#include <stdio.h>
#include "cocos2d.h"
#include "jni.h"
#include "C2DXMobLinkScene.h"
#include "C2DXMobLinkCallBack.h"
#include "C2DXAndroidActionListener.h"

/**
 *  MobLink Android实现类
 */
namespace mob
{
    namespace moblink
    {
        class C2DXAndroidMobLink
        {
        public:
            static void registerApp(const char *appKey);
            static void getMobId(C2DXMobLinkScene *scene);
            static void setRestoreCallBack(C2DXMobLinkCallBack callback);
            static void resorteSceneCallBack(const char *path, const char *source, const char *paramsStr);
            static void updateIntent();

        private:
            static jobject getAndroidContext(JNIEnv* env);
            static jobject jsonString2HashMap(JNIEnv* env, const char* json);
            static jobject newActionListener(JNIEnv* env);
            static C2DXAndroidActionListener* getCxxObjectFromJavaObject(JNIEnv* env, jobject jthiz);
        };
        
    }
}

#endif
