//
//  C2DXiOSMobLink.h
//  Cocos2DXForMobLink
//
//  Created by 陈剑东 on 2017/5/8.
//
//

#ifndef __C2DXMobLinkSample__C2DXiOSMobLink__
#define __C2DXMobLinkSample__C2DXiOSMobLink__

#include <stdio.h>
#include "cocos2d.h"
#include "C2DXMobLinkScene.h"
#include "C2DXMobLinkCallBack.h"

/**
 *  MobLink iOS实现类
 */
namespace mob
{
    namespace moblink
    {
        class C2DXiOSMobLink
        {
        public:
 
            static void getMobId(C2DXMobLinkScene *scene, C2DXGetMobIdResultEvent callback);
            
            static void setRestoreCallBack(C2DXRestoreSceneResultEvent callback);

            static void resorteSceneCallBack(const char *path, const char *source, const char *paramsStr);

        };
        
    }
}

#endif /* C2DXiOSMobLink_h */
