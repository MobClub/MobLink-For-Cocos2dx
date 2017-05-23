//
//  C2DXMobLinkScene.cpp
//  Cocos2DXForMobLink
//
//  Created by 陈剑东 on 2017/5/4.
//
//

#include "C2DXMobLinkScene.h"

using namespace mob::moblink;

C2DXMobLinkScene::C2DXMobLinkScene()
{
    customParams = NULL;
}



void C2DXMobLinkScene::setCustomParams(C2DXDictionary* dic)
{
    if (customParams != dic) {
        if (NULL != customParams) {
            customParams->release();
        }
        customParams = dic;
        if (NULL != customParams) {
            customParams->retain();
        }
    }
}
C2DXDictionary* C2DXMobLinkScene::getCustomParams()
{
    return customParams;
}


C2DXMobLinkScene::~C2DXMobLinkScene()
{
    customParams->release();
}

