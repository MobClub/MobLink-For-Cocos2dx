//
// Created by litl on 2017/5/18.
//

#ifndef __C2DXMobLinkSample__C2DXAndroidActionListener__
#define __C2DXMobLinkSample__C2DXAndroidActionListener__

#include "C2DXMobLinkCallBack.h"

using namespace mob::moblink;

class C2DXAndroidActionListener {
public:
    C2DXAndroidActionListener();
    virtual ~C2DXAndroidActionListener();
private:
    // 0, 此对象是用于场景回调使用; 1, 此对象用于
    int actionType;

    // 设置GetModId的回调函数
    C2DXGetMobIdResultEvent getModIdCallBack;

public:
    /**
     * 设置类型, 0此对象用于场景还原回调; 1, 用于获取ModId回调
     * @param type
     */
    void setActionType(int type);

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
     * 设置GetModId的回调函数, 注意只有当1 == actionType才有意义
     * @param cb
     */
    void setGetModIdCallBack(C2DXGetMobIdResultEvent cb);

    /**
     * 不加注释了, 我相信还得修改
     * @param cb
     */
    C2DXGetMobIdResultEvent getGetMoIdCallBack();

};

#endif
