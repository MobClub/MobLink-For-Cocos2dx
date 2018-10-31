#include "C2DXAndroidActionListener.h"

C2DXAndroidActionListener::C2DXAndroidActionListener()
{
    getModIdCallBack = NULL;
}

void C2DXAndroidActionListener::setGetModIdCallBack(C2DXGetMobIdResultEvent cb)
{
    getModIdCallBack = cb;
}

void C2DXAndroidActionListener::onResult(const char* result)
{
    C2DXGetMobIdResultEvent prt = getModIdCallBack;
    if (prt) {
        prt(result, "");
    }
}

void C2DXAndroidActionListener::onError(const char* error)
{
    // 临时解决mobid失败时, 传空字符串(与ios保持一致)
    C2DXGetMobIdResultEvent prt = getModIdCallBack;
    if (prt) {
        prt("", error);
    }
}

C2DXAndroidActionListener::~C2DXAndroidActionListener()
{
    // do nothing
}

