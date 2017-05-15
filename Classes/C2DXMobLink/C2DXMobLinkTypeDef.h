//
//  C2DXMobLinkTypeDef.h
//  Cocos2DXForMobLink
//
//  Created by 陈剑东 on 2017/5/9.
//
//

#ifndef __C2DXMobLinkSample__C2DXMobLinkTypeDef__
#define __C2DXMobLinkSample__C2DXMobLinkTypeDef__

USING_NS_CC;

#include "cocos2d.h"
#include <stdint.h>

#if COCOS2D_VERSION < 0x00030000

#define C2DXDictionary CCDictionary
#define C2DXArray CCArray
#define C2DXString CCString
#define C2DXPoint CCPoint
#define C2DXDouble CCDouble

#define C2DXInteger CCInteger
#define C2DXObject CCObject
#define C2DXPointMake(x,y) CCPointMake(x, y)
#define C2DXObjectAtIndex(i) objectAtIndex(i)

#else

#define C2DXDictionary __Dictionary
#define C2DXArray __Array
#define C2DXString __String
#define C2DXPoint cocos2d::Point
#define C2DXDouble __Double

#define C2DXInteger __Integer
#define C2DXObject Ref
#define C2DXPointMake(x,y) cocos2d::Point{static_cast<float>(x), static_cast<float>(y)}
#define C2DXObjectAtIndex(i) getObjectAtIndex(i)

#endif

#endif /* C2DXMobLinkTypeDef_h */
