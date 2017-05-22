//
//  C2DXMobLinkScene.hpp
//  Cocos2DXForMobLink
//
//  Created by 陈剑东 on 2017/5/4.
//
//

#ifndef __C2DXMobLinkSample__C2DXMobLinkScene__
#define __C2DXMobLinkSample__C2DXMobLinkScene__

#include <stdio.h>
#include "C2DXMobLinkTypeDef.h"

namespace mob
{
    namespace moblink
    {
        class C2DXMobLinkScene
        {
        public:
            /**
             *  路径参数
             */
            const char *path;
            
            /**
             *  来源参数
             */
            const char *source;
            
            /**
             *  自定义参数
             */
            C2DXDictionary *customParams;

            C2DXMobLinkScene(){}
            ~C2DXMobLinkScene(){}
        };
        
    }
}

#endif /* C2DXMobLinkScene_h */
