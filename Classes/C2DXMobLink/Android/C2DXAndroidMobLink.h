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
            static void getMobId(C2DXMobLinkScene *scene, C2DXGetMobIdResultEvent callback);
            static void setRestoreCallBack(C2DXRestoreSceneResultEvent callback);

        private:
            static void updateIntent();

        private:
            static jobject getAndroidContext(JNIEnv* env);
            static jobject cxxScene2JavaScene(C2DXMobLinkScene* scene, JNIEnv* env);
            static jobject dict2HashMap(C2DXDictionary* dict, JNIEnv* env);
            static jobject newActionListener(JNIEnv* env);
        };

        jint getCxxObject(JNIEnv* env, jobject jthiz);
    }
}

#endif
