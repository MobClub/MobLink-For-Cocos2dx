//
// Created by litl on 2017/5/18.
//

#include "C2DXAndroidRestoreSceneListener.h"
#include "JSON/CCJSONConverter.h"

extern mob::moblink::C2DXRestoreSceneResultEvent restoreSceneCallBack;

C2DXAndroidRestoreSceneListener::C2DXAndroidRestoreSceneListener()
{
    restoreSceneCallBack = NULL;
}

void C2DXAndroidRestoreSceneListener::setRestoreSceneCallBack(C2DXRestoreSceneResultEvent cb)
{
    restoreSceneCallBack = cb;
}

void C2DXAndroidRestoreSceneListener::onReturnSceneData(const char* result)
{
    CCJSONConverter* json = CCJSONConverter::sharedConverter();
    C2DXDictionary* dic = json->dictionaryFrom(result);
    __String* path = (__String*) dic->objectForKey("path");
    __String* source = (__String*) dic->objectForKey("source");
    C2DXDictionary* params = (C2DXDictionary*) dic->objectForKey("params");

    C2DXMobLinkScene* scene = new C2DXMobLinkScene();
    scene->path = path->getCString();
    scene->source = source->getCString();
    scene->setCustomParams(params);

    C2DXRestoreSceneResultEvent prt = restoreSceneCallBack;
    if (prt) {
        prt(scene);
    }

    dic->release();
}

C2DXRestoreSceneResultEvent C2DXAndroidRestoreSceneListener::getRestoreSceneCallBack()
{
    return restoreSceneCallBack;
}

C2DXAndroidRestoreSceneListener::~C2DXAndroidRestoreSceneListener()
{
    // do nothing
}

