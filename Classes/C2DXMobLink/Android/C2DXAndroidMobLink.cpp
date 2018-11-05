#include "C2DXAndroidMobLink.h"
#include "C2DXAndroidRestoreSceneListener.h"
#include "string.h"

USING_NS_CC;
using namespace mob::moblink;

void C2DXAndroidMobLink::getMobId(mob::moblink::C2DXMobLinkScene *scene, C2DXGetMobIdResultEvent callback)
{
    JNIEnv* env = JniHelper::getEnv();
    jobject jScene = cxxScene2JavaScene(scene, env);

    JniMethodInfo mi;
    JniHelper::getStaticMethodInfo(mi, "com/mob/moblink/MobLink"
            , "getMobID", "(Lcom/mob/moblink/Scene;Lcom/mob/moblink/ActionListener;)V");

    // 创建jave层ActionListener对象
    jobject jListener = newActionListener(env);
    // 获取对应的c++层对象，以保证java层监听器回调被触发时，能找到c++层相应的回调
    C2DXAndroidActionListener* cxxListener = (C2DXAndroidActionListener*)getCxxObject(env, jListener);
    cxxListener->setGetModIdCallBack(callback);

    // 调用sdk相应方法
    env->CallStaticVoidMethod(mi.classID, mi.methodID, jScene, jListener);
}

void C2DXAndroidMobLink::setRestoreCallBack(C2DXRestoreSceneResultEvent callback)
{
    // 创建jave层RestoreSceneListener对象
    JNIEnv* env = JniHelper::getEnv();
    JniMethodInfo mi;
    JniHelper::getStaticMethodInfo(mi, "com/mob/moblink/cocos2dx/RestoreSceneListener", "newInstance", "()Lcom/mob/moblink/cocos2dx/RestoreSceneListener;");
    jobject javaListener = env->CallStaticObjectMethod(mi.classID, mi.methodID);

    // 获取对应的c++层对象，以保证java层监听器回调被触发时，能找到c++层相应的回调
    C2DXAndroidRestoreSceneListener* cxxListener = (C2DXAndroidRestoreSceneListener*) getCxxObject(env, javaListener);
    cxxListener->setRestoreSceneCallBack(callback);

    jobject jactivity = getAndroidContext(env);
    JniHelper::getStaticMethodInfo(mi, "com/mob/moblink/MobLink", "setActivityDelegate", "(Landroid/app/Activity;Lcom/mob/moblink/SceneRestorable;)V");
    env->CallStaticVoidMethod(mi.classID, mi.methodID, jactivity, javaListener);

    // 防止setRestoreCallBack调用过晚, 导致错过scene
    updateIntent();
}

jobject C2DXAndroidMobLink::getAndroidContext(JNIEnv* env)
{
    JniMethodInfo methodInfo;
    JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/lib/Cocos2dxActivity", "getContext", "()Landroid/content/Context;");
    return env->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID);
}

jobject C2DXAndroidMobLink::cxxScene2JavaScene(C2DXMobLinkScene* scene, JNIEnv* env)
{
    jclass jclazz = env->FindClass("com/mob/moblink/Scene");
    jmethodID jmethod = env->GetMethodID(jclazz, "<init>", "()V");
    jobject jScene = env->NewObject(jclazz, jmethod);

    jobject jTemp = env->NewStringUTF(scene->path.c_str());
    jfieldID jField = env->GetFieldID(jclazz, "path", "Ljava/lang/String;");
    env->SetObjectField(jScene, jField, jTemp);

    // jTemp = env->NewStringUTF(scene->source.c_str());
    // jField = env->GetFieldID(jclazz, "source", "Ljava/lang/String;");
    // env->SetObjectField(jScene, jField, jTemp);

    jTemp = NULL;
    C2DXDictionary* dict = scene->getCustomParams();
    if (NULL != dict) {
        jTemp = dict2HashMap(dict, env);
    }
    jField = env->GetFieldID(jclazz, "params", "Ljava/util/HashMap;");
    env->SetObjectField(jScene, jField, jTemp);

    // log("cxxScene2JavaScene. path: %s, source: %s", scene->path.c_str(), scene->source.c_str());
    // 打印日志
    log("[moblink-cocos]cxxScene2JavaScene. path: %s", scene->path.c_str());

    log("[moblink-cocos]cxxScene2JavaScene. customParams: ");
    __Dictionary *customParams = scene->getCustomParams();
    DictElement *element;
    CCDICT_FOREACH(customParams, element)
        {
            const char *key = element -> getStrKey();
            __String *obj = (__String*)element -> getObject();
            log("[moblink-cocos]cxxScene2JavaScene. key = %s, value = %s",key,obj -> getCString());
        }

    return jScene;
}

jobject C2DXAndroidMobLink::dict2HashMap(C2DXDictionary* dict, JNIEnv* env)
{
    jclass jclazz = env->FindClass("java/util/HashMap");
    jmethodID jMethod = env->GetMethodID(jclazz, "<init>", "()V");
    jobject jHashMap = env->NewObject(jclazz, jMethod);
    jMethod = env->GetMethodID(jclazz, "put", "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;");

    C2DXArray* keys = dict->allKeys();
    int size = NULL != keys ? keys->count() : 0;
    for (int i = 0; i < size; ++i) {
        CCString* key = dynamic_cast<CCString*>(keys->objectAtIndex(i));

        jobject jKey = env->NewStringUTF(key->getCString());
        jobject jValue = env->NewStringUTF(dict->valueForKey(key->getCString())->getCString());

        env->CallObjectMethod(jHashMap, jMethod, jKey, jValue);
    }
    return jHashMap;
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
    JniHelper::getStaticMethodInfo(mi, "com/mob/moblink/MobLink", "updateNewIntent", "(Landroid/content/Intent;Landroid/app/Activity;)V");
    env->CallStaticVoidMethod(mi.classID, mi.methodID, jIntent, jactivity);
}

jint mob::moblink::getCxxObject(JNIEnv *env, jobject jthiz) {
    jclass jthizclass = env->GetObjectClass(jthiz);
    jmethodID method = env->GetMethodID(jthizclass, "getCxxObject", "()I");
    jint result = env->CallIntMethod(jthiz, method);
    log("[moblink-cocos]getCxxObject. return: %ld", result);
    return result;
}