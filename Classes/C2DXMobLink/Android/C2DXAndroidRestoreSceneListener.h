//
// Created by litl on 2017/5/18.
//

#ifndef __C2DXMobLinkSample__C2DXAndroidRestoreSceneListener__
#define __C2DXMobLinkSample__C2DXAndroidRestoreSceneListener__

#include "C2DXMobLinkCallBack.h"

using namespace mob::moblink;

class C2DXAndroidRestoreSceneListener {
public:
    C2DXAndroidRestoreSceneListener();
    virtual ~C2DXAndroidRestoreSceneListener();
private:

    // 场景还原的回调函数
    C2DXRestoreSceneResultEvent restoreSceneCallBack;

public:

    /**
     * 当时有场景还原时回调
     * @param result json字符串
     */
    void onReturnSceneData(JNIEnv* env, jobject scene);

    /**
     * 设置场景还原的回调函数
     * @param cb
     */
    void setRestoreSceneCallBack(C2DXRestoreSceneResultEvent cb);

    /**
     * 不加注释了, 我相信还得修改
     * @param cb
     */
    C2DXRestoreSceneResultEvent getRestoreSceneCallBack();

private:
    static C2DXDictionary* hashMap2Dict(JNIEnv* env, jobject jHashMap);

};

#endif
