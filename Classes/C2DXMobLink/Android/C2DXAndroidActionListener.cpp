//
// Created by litl on 2017/5/18.
//

#include "C2DXAndroidActionListener.h"
#include "JSON/CCJSONConverter.h"

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
    CCJSONConverter* json = CCJSONConverter::sharedConverter();
    C2DXDictionary* dic = json->dictionaryFrom(result);
    CCString* modId = (CCString*) dic->objectForKey("mobID");
    C2DXGetMobIdResultEvent prt = getModIdCallBack;
    if (prt) {
        prt(modId->getCString());
    }
    dic->release();
}

void C2DXAndroidActionListener::onError(const char* error)
{
    // do nothing
}

C2DXAndroidActionListener::~C2DXAndroidActionListener()
{
    // do nothing
}

