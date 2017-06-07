//
//  C2DXAndroidMobLink.m
//  Cocos2DXForMobLink
//
//  Created by 李同垒 on 2017/5/18.
//
//



#include "C2DXAndroidMobLink.h"
#include "JSON/CCJSONConverter.h"
#include "C2DXAndroidRestoreSceneListener.h"

USING_NS_CC;
using namespace mob::moblink;

void C2DXAndroidMobLink::getMobId(mob::moblink::C2DXMobLinkScene *scene, C2DXGetMobIdResultEvent callback)
{
    JNIEnv* env = JniHelper::getEnv();
    jstring jPath = env->NewStringUTF(scene->path.c_str());
    jstring jSource = env->NewStringUTF(scene->source.c_str());

    jobject jParam;
    {
        // 大括号, 隐藏不必要的变量
        C2DXDictionary* dict = scene->getCustomParams();
        CCJSONConverter* json = CCJSONConverter::sharedConverter();
        const char* ccContent = json->strFrom(dict);
        jParam = jsonString2HashMap(env, ccContent);
    }

    JniMethodInfo mi;
    JniHelper::getStaticMethodInfo(mi, "com/mob/moblink/MobLink"
            , "getMobID", "(Ljava/util/HashMap;Ljava/lang/String;Ljava/lang/String;Lcom/mob/moblink/ActionListener;)V");

    jobject jListener = newActionListener(env);
    C2DXAndroidActionListener* cxxListener = (C2DXAndroidActionListener*)getCxxObject(env, jListener);
    cxxListener->setGetModIdCallBack(callback);

    env->CallStaticVoidMethod(mi.classID, mi.methodID, jParam, jPath, jSource, jListener);
}

void C2DXAndroidMobLink::setRestoreCallBack(C2DXRestoreSceneResultEvent callback)
{
    JNIEnv* env = JniHelper::getEnv();
    JniMethodInfo mi;
    JniHelper::getStaticMethodInfo(mi, "com/mob/moblink/cocos2dx/RestoreSceneListener", "newInstance", "()Lcom/mob/moblink/cocos2dx/RestoreSceneListener;");
    jobject javaListener = env->CallStaticObjectMethod(mi.classID, mi.methodID);

    C2DXAndroidRestoreSceneListener* cxxListener = (C2DXAndroidRestoreSceneListener*) getCxxObject(env, javaListener);
    cxxListener->setRestoreSceneCallBack(callback);

    JniHelper::getStaticMethodInfo(mi, "com/mob/moblink/MobLink", "setRestoreSceneListener", "(Lcom/mob/moblink/RestoreSceneListener;)V");
    env->CallStaticVoidMethod(mi.classID, mi.methodID, javaListener);

    // 防止setRestoreCallBack调用过晚, 导致错过scene
    updateIntent();
}

jobject C2DXAndroidMobLink::getAndroidContext(JNIEnv* env)
{
    JniMethodInfo methodInfo;
    JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/lib/Cocos2dxActivity", "getContext", "()Landroid/content/Context;");
    return env->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID);
}

jobject C2DXAndroidMobLink::jsonString2HashMap(JNIEnv* env, const char* json)
{
    JniMethodInfo mi;
    JniHelper::getMethodInfo(mi, "com/mob/tools/utils/Hashon", "<init>", "()V");
    jobject jthiz = env->NewObject(mi.classID, mi.methodID);

    jmethodID jmethod = env->GetMethodID(mi.classID, "fromJson", "(Ljava/lang/String;)Ljava/util/HashMap;");
    jstring jJson = env->NewStringUTF(json);
    jobject result = env->CallObjectMethod(jthiz, jmethod, jJson);
    return result;
}

jobject C2DXAndroidMobLink::newActionListener(JNIEnv* env)
{
    JniMethodInfo mi;
    JniHelper::getStaticMethodInfo(mi, "com/mob/moblink/cocos2dx/ActionListener", "newInstance", "()Lcom/mob/moblink/cocos2dx/ActionListener;");
    return env->CallStaticObjectMethod(mi.classID, mi.methodID);
}

void C2DXAndroidMobLink::updateIntent()
{
    JNIEnv* env = JniHelper::getEnv();

    jobject jactivity = getAndroidContext(env);
    jmethodID jmethod = env->GetMethodID(env->GetObjectClass(jactivity), "getIntent", "()Landroid/content/Intent;");
    jobject jIntent = env->CallObjectMethod(jactivity, jmethod);

    JniMethodInfo mi;
    JniHelper::getStaticMethodInfo(mi, "com/mob/moblink/MobLink", "updateIntent", "(Landroid/app/Activity;Landroid/content/Intent;)V");
    env->CallStaticVoidMethod(mi.classID, mi.methodID, jactivity, jIntent);
}

jint mob::moblink::getCxxObject(JNIEnv *env, jobject jthiz) {
    jclass jthizclass = env->GetObjectClass(jthiz);
    jmethodID method = env->GetMethodID(jthizclass, "getCxxObject", "()I");
    jint result = env->CallIntMethod(jthiz, method);
    return result;
}