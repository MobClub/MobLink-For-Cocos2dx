#include <jni.h>
#include "jni/JniHelper.h"
#include "com_mob_moblink_cocos2dx_ActionListener.h"
#include "C2DXAndroidActionListener.h"
#include "C2DXAndroidMobLink.h"

USING_NS_CC;

/*
 * Class:     com_mob_moblink_cocos2dx_ActionListener
 * Method:    nativeOnCreateCxxObject
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_mob_moblink_cocos2dx_ActionListener_nativeOnCreateCxxObject
  (JNIEnv *env, jobject jthiz)
{
    C2DXAndroidActionListener* listener = new C2DXAndroidActionListener();
    return (jint)listener;
}

/*
 * Class:     com_mob_moblink_cocos2dx_ActionListener
 * Method:    nativeOnResult
 * Signature: (Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_com_mob_moblink_cocos2dx_ActionListener_nativeOnResult
  (JNIEnv *env, jobject jthiz, jstring jresult)
{
    C2DXAndroidActionListener* listener = (C2DXAndroidActionListener*)getCxxObject(env, jthiz);
    const char* cresult = env->GetStringUTFChars(jresult, JNI_FALSE);
    listener->onResult(cresult);
    env->ReleaseStringUTFChars(jresult, cresult);
    return 0;
}

/*
 * Class:     com_mob_moblink_cocos2dx_ActionListener
 * Method:    nativeOnError
 * Signature: (Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_com_mob_moblink_cocos2dx_ActionListener_nativeOnError
  (JNIEnv *env, jobject jthiz, jstring jerror)
{
    C2DXAndroidActionListener* listener = (C2DXAndroidActionListener*)getCxxObject(env, jthiz);
    const char* cresult = env->GetStringUTFChars(jerror, JNI_FALSE);
    listener->onError(cresult);
    env->ReleaseStringUTFChars(jerror, cresult);
    return 0;
}

/*
 * Class:     com_mob_moblink_cocos2dx_ActionListener
 * Method:    nativeOnDestoryCxxObject
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_mob_moblink_cocos2dx_ActionListener_nativeOnDestoryCxxObject
  (JNIEnv *env, jobject jthiz)
{
    C2DXAndroidActionListener* listener = (C2DXAndroidActionListener*)getCxxObject(env, jthiz);
    delete listener;
    return 0;
}
