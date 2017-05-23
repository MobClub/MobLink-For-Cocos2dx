//
//  C2DXAndroidMobLink.m
//  Cocos2DXForMobLink
//
//  Created by 李同垒 on 2017/5/18.
//
//



#include "C2DXAndroidMobLink.h"
#include "JSON/CCJSONConverter.h"

USING_NS_CC;
using namespace mob::moblink;


#pragma mark - MobLink Interface

#ifdef __cplusplus
extern "C" {
#endif
    mob::moblink::C2DXRestoreSceneResultEvent restoreSceneCallBack = NULL;
#ifdef __cplusplus
}
#endif


void C2DXAndroidMobLink::registerApp(const char *appKey)
{
    JNIEnv* env = JniHelper::getEnv();
    jobject jContext = getAndroidContext(env);
    jobject jAppKey = env->NewStringUTF(appKey);

    JniMethodInfo mi;
    JniHelper::getStaticMethodInfo(mi, "com/mob/moblink/MobLink", "initSDK", "(Landroid/content/Context;Ljava/lang/String;)V");
    env->CallStaticVoidMethod(mi.classID, mi.methodID, jContext, jAppKey);
}


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
    C2DXAndroidActionListener* cxxListener = getCxxObjectFromJavaObject(env, jListener);
    cxxListener->setActionType(1);
    cxxListener->setGetModIdCallBack(callback);

    env->CallStaticVoidMethod(mi.classID, mi.methodID, jParam, jPath, jSource, jListener);
}

void C2DXAndroidMobLink::setRestoreCallBack(C2DXRestoreSceneResultEvent callback)
{
    restoreSceneCallBack = callback;
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

C2DXAndroidActionListener* C2DXAndroidMobLink::getCxxObjectFromJavaObject(JNIEnv* env, jobject jthiz)
{
    jclass jclazz = env->GetObjectClass(jthiz);
    jmethodID jmethod = env->GetMethodID(jclazz, "getCxxObject", "()I");
    jint result = env->CallIntMethod(jthiz, jmethod);
    return (C2DXAndroidActionListener*)result;

}

void C2DXAndroidMobLink::updateIntent()
{
    JNIEnv* env = JniHelper::getEnv();
    jobject jListener = newActionListener(env);

    jobject jactivity = getAndroidContext(env);
    jmethodID jmethod = env->GetMethodID(env->GetObjectClass(jactivity), "getIntent", "()Landroid/content/Intent;");
    jobject jIntent = env->CallObjectMethod(jactivity, jmethod);

    JniMethodInfo mi;
    JniHelper::getStaticMethodInfo(mi, "com/mob/moblink/MobLink", "setIntentHandler", "(Landroid/content/Intent;Lcom/mob/moblink/ActionListener;)V");
    env->CallStaticVoidMethod(mi.classID, mi.methodID, jIntent, jListener);

    jmethod = env->GetMethodID(env->GetObjectClass(jactivity), "setIntent", "(Landroid/content/Intent;)V");
    env->CallVoidMethod(jactivity, jmethod, nullptr);
}
