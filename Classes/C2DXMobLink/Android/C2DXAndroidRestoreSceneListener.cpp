#include "C2DXAndroidRestoreSceneListener.h"

extern mob::moblink::C2DXRestoreSceneResultEvent restoreSceneCallBack;

C2DXAndroidRestoreSceneListener::C2DXAndroidRestoreSceneListener()
{
    restoreSceneCallBack = NULL;
}

void C2DXAndroidRestoreSceneListener::setRestoreSceneCallBack(C2DXRestoreSceneResultEvent cb)
{
    restoreSceneCallBack = cb;
}

void C2DXAndroidRestoreSceneListener::onReturnSceneData(JNIEnv* env, jobject jScene)
{
    C2DXMobLinkScene* scene = new C2DXMobLinkScene();
    jclass jclazz = env->GetObjectClass(jScene);

    jfieldID jField = env->GetFieldID(jclazz, "path", "Ljava/lang/String;");
    jobject jTemp = env->GetObjectField(jScene, jField);
    const char* cvalue = env->GetStringUTFChars((jstring)jTemp, NULL);
    if (NULL != cvalue) {
        scene->path = cvalue;
        env->ReleaseStringUTFChars((jstring )jTemp, cvalue);
    }

    // jField = env->GetFieldID(jclazz, "source", "Ljava/lang/String;");
    // jTemp = env->GetObjectField(jScene, jField);
    // cvalue = env->GetStringUTFChars((jstring)jTemp, NULL);
    // if (NULL != cvalue) {
    //     scene->source = cvalue;
    //     env->ReleaseStringUTFChars((jstring )jTemp, cvalue);
    // }

    // TODO
    jField = env->GetFieldID(jclazz, "params", "Ljava/util/HashMap;");
    jTemp = env->GetObjectField(jScene, jField);
    C2DXDictionary* dict = hashMap2Dict(env, jTemp);
    if (NULL != dict) {
        scene->setCustomParams(dict);
        dict->release();
    }

    C2DXRestoreSceneResultEvent prt = restoreSceneCallBack;
    if (prt) {
        prt(scene);
    }
}

C2DXDictionary* C2DXAndroidRestoreSceneListener::hashMap2Dict(JNIEnv* env, jobject jHashMap)
{
    C2DXDictionary* dict = C2DXDictionary::create();

    jclass jclazz = env->FindClass("com/mob/moblink/cocos2dx/MapUtil");
    jmethodID jMethod = env->GetStaticMethodID(jclazz, "keySet", "(Ljava/util/Map;)[Ljava/lang/Object;");
    jobject jKeys = env->CallStaticObjectMethod(jclazz, jMethod, jHashMap);
    jsize count = env->GetArrayLength((jarray)jKeys);


    jclazz = env->GetObjectClass(jHashMap);
    jMethod = env->GetMethodID(jclazz, "get", "(Ljava/lang/Object;)Ljava/lang/Object;");
    for (int i = 0; i < count; ++i) {
        jobject jKey = env->GetObjectArrayElement((jobjectArray)jKeys, i);
        jobject jValue = env->CallObjectMethod(jHashMap, jMethod, jKey);
        const char * cKey = env->GetStringUTFChars((jstring)jKey, NULL);
        const char * cValue = env->GetStringUTFChars((jstring)jValue, NULL);
        if (NULL != cKey && NULL != cValue) {
            dict->setObject(C2DXString::create(cValue), cKey);
        }
        if (NULL != cKey) {
            env->ReleaseStringUTFChars((jstring)jKey, cKey);
        }
        if (NULL != cValue) {
            env->ReleaseStringUTFChars((jstring)jValue, cValue);
        }
        env->DeleteLocalRef(jKey);
        env->DeleteLocalRef(jValue);
    }
    return dict;
}

C2DXRestoreSceneResultEvent C2DXAndroidRestoreSceneListener::getRestoreSceneCallBack()
{
    return restoreSceneCallBack;
}

C2DXAndroidRestoreSceneListener::~C2DXAndroidRestoreSceneListener()
{
    // do nothing
}

