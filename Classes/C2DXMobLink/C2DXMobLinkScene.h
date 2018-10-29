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
#include "string"
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
            std::string path;
            
            /**
             *  来源参数
             */
            // std::string source;

            C2DXMobLinkScene();
            virtual ~C2DXMobLinkScene();

        public:
            void setCustomParams(C2DXDictionary* dic);
            C2DXDictionary* getCustomParams();
        private:
            /**
             *  自定义参数
             */
            C2DXDictionary *customParams;
        };
        
    }
}

#endif /* C2DXMobLinkScene_h */
