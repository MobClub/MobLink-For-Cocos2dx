//
//  C2DXMobLinkCallBack.hpp
//  Cocos2DXForMobLink
//
//  Created by 陈剑东 on 2017/5/8.
//
//
#ifndef __C2DXMobLinkSample__C2DXMobLinkCallBack__
#define __C2DXMobLinkSample__C2DXMobLinkCallBack__

#include <stdio.h>
#include "C2DXMobLinkScene.h"
#include "C2DXMobLinkTypeDef.h"

namespace mob
{
    namespace moblink
    {
        /**
         *  获取mobid之回调
         *
         *  @param C2DXGetMobIdResultEvent 回调mobid
         */
        typedef void(*C2DXGetMobIdResultEvent) (const char * mobid);
        
        /**
         *  恢复场景之回调
         *
         *  @param C2DXRestoreSceneResultEvent 回调场景参数
         */
        typedef void(*C2DXRestoreSceneResultEvent) (C2DXMobLinkScene *scene);
    }
}

#endif /* C2DXMobLinkCallBack_h */
