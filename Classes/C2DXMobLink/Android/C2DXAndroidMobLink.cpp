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
static mob::moblink::C2DXMobLinkCallBack theCallBack;

void C2DXAndroidMobLink::registerApp(const char *appKey)
{
    JNIEnv* env = JniHelper::getEnv();
    jobject jContext = getAndroidContext(env);
    jobject jAppKey = env->NewStringUTF(appKey);

    jclass jMobLinkClass = env->FindClass("com/mob/moblink/MobLink");
    jmethodID jmethod = env->GetStaticMethodID(jMobLinkClass, "initSDK", "");

    env->CallStaticVoidMethod(jMobLinkClass, jmethod, jContext, jAppKey);
}


void C2DXAndroidMobLink::getMobId(mob::moblink::C2DXMobLinkScene *scene)
{
    JNIEnv* env = JniHelper::getEnv();
    jstring jPath = env->NewStringUTF(scene->path);
    jstring jSource = env->NewStringUTF(scene->source);

    jobject jParam;
    {
        // 大括号, 隐藏不必要的变量
        C2DXDictionary* dict = scene->customParams;
        CCJSONConverter* json = CCJSONConverter::sharedConverter();
        const char* ccContent = json->strFrom(dict);
        jParam = jsonString2HashMap(env, ccContent);
    }

    jclass jMobLinkClass = env->FindClass("com/mob/moblink/MobLink");
    jmethodID jmethod = env->GetStaticMethodID(jMobLinkClass, "getMobID"
            , "(Ljava/util/HashMap;Ljava/lang/String;Ljava/lang/String;Lcom/mob/moblink/ActionListener;)V");

    jobject jListener = newActionListener(env);
    C2DXAndroidActionListener* cxxListener = getCxxObjectFromJavaObject(env, jListener);
    cxxListener->setActionType(1);
    cxxListener->setCallBack(theCallBack);

    env->CallStaticVoidMethod(jMobLinkClass, jmethod, jParam, jPath, jSource, jListener);
}

void C2DXAndroidMobLink::setRestoreCallBack(mob::moblink::C2DXMobLinkCallBack callback)
{
    theCallBack = callback;
}

void C2DXAndroidMobLink::resorteSceneCallBack(const char *path, const char *source, const char *paramsStr)
{
    // TODO for what
}

jobject C2DXAndroidMobLink::getAndroidContext(JNIEnv* env)
{
    jclass jclazz = env->FindClass("org/cocos2dx/lib/Cocos2dxActivity");
    jmethodID jmethod = env->GetMethodID(jclazz, "getContext", "()Landroid/content/Context;");
    return env->CallStaticObjectMethod(jclazz, jmethod);
}

jobject C2DXAndroidMobLink::jsonString2HashMap(JNIEnv* env, const char* json)
{
    jclass jclazz = env->FindClass("com/mob/tools/utils/Hashon");
    jmethodID jmethod = env->GetMethodID(jclazz, "<init>", "void(V)");
    jobject jthiz = env->NewObject(jclazz, jmethod);

    jmethod = env->GetMethodID(jclazz, "fromJson", "(Ljava/lang/String;)Ljava/util/HashMap;");
    jstring jJson = env->NewStringUTF(json);
    jobject result = env->CallObjectMethod(jthiz, jmethod, jJson);
    return result;
}

jobject C2DXAndroidMobLink::newActionListener(JNIEnv* env)
{
    jclass jclazz = env->FindClass("com/mob/moblink/cocos2dx/ActionListener");
    jmethodID jmethod = env->GetMethodID(jclazz, "newInstance", "()Lcom/mob/moblink/cocos2dx/ActionListener;");
    return env->CallStaticObjectMethod(jclazz, jmethod);
}

C2DXAndroidActionListener* C2DXAndroidMobLink::getCxxObjectFromJavaObject(JNIEnv* env, jobject jthiz)
{
    jclass jclazz = env->GetObjectClass(jthiz);
    jmethodID jmethod = env->GetMethodID(jclazz, "getCxxObject", "()I");
    jint result = env->CallIntMethod(jthiz, jmethod);
    return (C2DXAndroidActionListener*)result;

}
