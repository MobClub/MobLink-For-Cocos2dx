#include <jni.h>
#include "jni/JniHelper.h"
#include "com_mob_moblink_cocos2dx_RestoreSceneListener.h"
#include "C2DXAndroidRestoreSceneListener.h"
#include "C2DXAndroidMobLink.h"

USING_NS_CC;
/*
 * Class:     com_mob_moblink_cocos2dx_RestoreSceneListener
 * Method:    nativeOnCreateCxxObject
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_mob_moblink_cocos2dx_RestoreSceneListener_nativeOnCreateCxxObject
  (JNIEnv *env, jobject jthiz)
{
    C2DXAndroidRestoreSceneListener* listener = new C2DXAndroidRestoreSceneListener();
    return (jint)listener;
}

/*
 * Class:     com_mob_moblink_cocos2dx_RestoreSceneListener
 * Method:    nativeOnReturnSceneData
 * Signature: (Landroid/app/Activity;Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_com_mob_moblink_cocos2dx_RestoreSceneListener_nativeOnReturnSceneData
  (JNIEnv *env, jobject jthiz, jobject jactivity, jstring jvalue)
{
    C2DXAndroidRestoreSceneListener* listener = (C2DXAndroidRestoreSceneListener*)getCxxObject(env, jthiz);
    const char* cvalue = env->GetStringUTFChars(jvalue, JNI_FALSE);
    listener->onReturnSceneData(cvalue);
    env->ReleaseStringUTFChars(jvalue, cvalue);
}

/*
 * Class:     com_mob_moblink_cocos2dx_RestoreSceneListener
 * Method:    nativeOnDestoryCxxObject
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_mob_moblink_cocos2dx_RestoreSceneListener_nativeOnDestoryCxxObject
  (JNIEnv *env, jobject jthiz)
{
    C2DXAndroidRestoreSceneListener* listener = (C2DXAndroidRestoreSceneListener*)getCxxObject(env, jthiz);
    delete listener;
}
