//
// Created by litl on 2017/5/18.
//

#include "C2DXAndroidActionListener.h"
#include "JSON/CCJSONConverter.h"

extern mob::moblink::C2DXRestoreSceneResultEvent restoreSceneCallBack;

C2DXAndroidActionListener::C2DXAndroidActionListener()
{
    setActionType(0);
    getModIdCallBack = NULL;
}

void C2DXAndroidActionListener::setActionType(int type)
{
    actionType = type;
}

void C2DXAndroidActionListener::setGetModIdCallBack(C2DXGetMobIdResultEvent cb)
{
    getModIdCallBack = cb;
}

void C2DXAndroidActionListener::onResult(const char* result)
{
    CCJSONConverter* json = CCJSONConverter::sharedConverter();
    C2DXDictionary* dic = json->dictionaryFrom(result);
    if (0 == actionType) {
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
    } else if (1 == actionType) {
        CCString* modId = (CCString*) dic->objectForKey("mobID");
        C2DXGetMobIdResultEvent prt = getModIdCallBack;
        if (prt) {
            prt(modId->getCString());
        }
    }
    dic->release();
}

void C2DXAndroidActionListener::onError(const char* error)
{
    // do nothing, this is not good design
}

C2DXAndroidActionListener::~C2DXAndroidActionListener()
{
    // do nothing
}

