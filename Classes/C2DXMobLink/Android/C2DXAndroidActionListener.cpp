//
// Created by litl on 2017/5/18.
//

#include "C2DXAndroidActionListener.h"
#include "JSON/CCJSONConverter.h"

C2DXAndroidActionListener::C2DXAndroidActionListener()
{
    setActionType(0);
}

void C2DXAndroidActionListener::setActionType(int type)
{
    actionType = type;
}

void C2DXAndroidActionListener::onResult(const char* result)
{
    CCJSONConverter* json = CCJSONConverter::sharedConverter();
    C2DXDictionary* dic = json->dictionaryFrom(result);
    CCString* path = (CCString*) dic->objectForKey("path");
    CCString* source = (CCString*) dic->objectForKey("source");
    C2DXDictionary* params = (C2DXDictionary*) dic->objectForKey("params");

    // TODO 这样复制是不行的，内存问题
    C2DXMobLinkScene* scene = new C2DXMobLinkScene();
    scene->path = path->_string.c_str();
    scene->source = source->_string.c_str();
    scene->customParams = params;

    C2DXRestoreSceneResultEvent prt = callBack.sceneResultEvent;
    if (prt) {
        prt(scene);
    }
}

void C2DXAndroidActionListener::onError(const char* error)
{
    // do nothing, this is not good design
}

void C2DXAndroidActionListener::setCallBack(C2DXMobLinkCallBack cb)
{
    callBack = cb;
}

C2DXMobLinkCallBack C2DXAndroidActionListener::getCallBack()
{
    return callBack;
}

C2DXAndroidActionListener::~C2DXAndroidActionListener()
{
    // do nothing
}

