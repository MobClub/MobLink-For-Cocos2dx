#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "C2DXMobLink.h"
#include "C2DXMobLinkScene.h"
#include "C2DXMobLinkCallBack.h"

USING_NS_CC;
using namespace std;
using namespace mob::moblink;

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
