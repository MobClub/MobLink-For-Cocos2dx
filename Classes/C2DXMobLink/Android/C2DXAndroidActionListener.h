#ifndef __C2DXMobLinkSample__C2DXAndroidActionListener__
#define __C2DXMobLinkSample__C2DXAndroidActionListener__

#include "C2DXMobLinkCallBack.h"

using namespace mob::moblink;

class C2DXAndroidActionListener {
public:
    C2DXAndroidActionListener();
    virtual ~C2DXAndroidActionListener();
private:

    // 设置GetModId的回调函数
    C2DXGetMobIdResultEvent getModIdCallBack;

public:

    /**
     * Action操作成功时调用
     * @param result json字符串
     */
    void onResult(const char* result);

    /**
     * Action操作失败时调用
     * @param error json字符串
     */
    void onError(const char* error);

    /**
     * 设置GetModId的回调函数
     * @param cb
     */
    void setGetModIdCallBack(C2DXGetMobIdResultEvent cb);

    /**
     * 获取GetModId的回调函数
     */
    C2DXGetMobIdResultEvent getGetMoIdCallBack();

};

#endif
