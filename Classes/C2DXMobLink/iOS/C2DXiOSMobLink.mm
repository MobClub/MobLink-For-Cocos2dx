//
//  C2DXiOSMobLink.m
//  Cocos2DXForMobLink
//
//  Created by 陈剑东 on 2017/5/8.
//
//

#include "C2DXiOSMobLink.h"
#include "C2DXMobLinkScene.h"
#include "C2DXMobLinkTypeDef.h"

#import <MobLink/MobLink.h>
#import <MobLink/MLSDKScene.h>
#import <MOBFoundation/MOBFJson.h>
#import "C2DXiOSMobLinkDelegate.h"

using namespace mob::moblink;

/**
 *	@brief	转换NSDictionary为C2DXDictionary类型
 *
 *	@param 	dict 	字典
 *
 *	@return	字典类型
 */
C2DXDictionary* convertNSDictToCCDict(NSDictionary *dict);

/**
 *	@brief	转换C2DXDictionary为NSDictionary类型
 *
 *	@param 	dict 	字典
 *
 *	@return	字典类型
 */
NSMutableDictionary* convertC2DXDictionaryToNSDictionary(C2DXDictionary *Dictionary);

/**
 *	@brief	转换NSString为C2DXString类型
 *
 *	@param 	string 	字符串
 *
 *	@return	字符类型
 */
C2DXString* convertNSStringToC2DXString(NSString *string);

/**
 *	@brief	转换C2DXString为NSString类型
 *
 *	@param 	string 	字符串
 *
 *	@return	字符类型
 */
NSString* convertC2DXStringToNSString(C2DXString *String);

/**
 *	@brief	转换NSArray为C2DXArray类型
 *
 *	@param 	array 	数组
 *
 *	@return	数组类型
 */
C2DXArray* convertNSArrayToC2DXArray(NSArray *array);

/**
 *	@brief	转换C2DXArray为NSArray类型
 *
 *	@param 	array 	数组
 *
 *	@return	数组类型
 */
NSArray* convertC2DXArrayToNSArray(C2DXArray *Array);

C2DXDictionary* convertNSDictToCCDict(NSDictionary *dict)
{
    if (dict)
    {
        C2DXDictionary *ccDict = C2DXDictionary::create();
        NSArray *allKeys = [dict allKeys];
        for (int i = 0; i < [allKeys count]; i++)
        {
            NSString *key = [allKeys objectAtIndex:i];
            id value = [dict objectForKey:key];
            
            if ([value isKindOfClass:[NSString class]])
            {
                C2DXString *strValue = convertNSStringToC2DXString(value);
                if (strValue)
                {
                    ccDict -> setObject(strValue, [key UTF8String]);
                }
            }
            else if ([value isKindOfClass:[NSNumber class]])
            {
                C2DXString *strValue = convertNSStringToC2DXString([NSString stringWithFormat:@"%@", value]);
                if (strValue)
                {
                    ccDict -> setObject(strValue, [key UTF8String]);
                }
            }
            else if ([value isKindOfClass:[NSDate class]])
            {
                ccDict -> setObject(C2DXDouble::create([value timeIntervalSince1970] * 1000), [key UTF8String]);
            }
            else if ([value isKindOfClass:[NSDictionary class]])
            {
                C2DXDictionary *dictValue = convertNSDictToCCDict(value);
                if (dictValue)
                {
                    ccDict -> setObject(dictValue, [key UTF8String]);
                }
            }
            else if ([value isKindOfClass:[NSArray class]])
            {
                C2DXArray *arrValue = convertNSArrayToC2DXArray(value);
                if (arrValue)
                {
                    ccDict -> setObject(arrValue, [key UTF8String]);
                }
            }
        }
        return ccDict;
    }
    
    return NULL;
}

NSMutableDictionary * convertC2DXDictionaryToNSDictionary(C2DXDictionary * Dictionary)
{
    if (Dictionary)
    {
        NSMutableDictionary *dict = [NSMutableDictionary dictionary];
        C2DXArray *allkeys = Dictionary -> allKeys();
        
        if (allkeys != NULL)
        {
            for (int i = 0; i < allkeys -> count(); i ++)
            {
                C2DXString * key = dynamic_cast<C2DXString *> (allkeys -> C2DXObjectAtIndex(i));
                C2DXObject * value = Dictionary -> objectForKey(key -> getCString());
                
                if (dynamic_cast<C2DXString*>(value) != NULL)
                {
                    NSString *strValue = convertC2DXStringToNSString(dynamic_cast<C2DXString*>(value) );
                    if (strValue)
                    {
                        [dict setObject:strValue
                                 forKey:[NSString stringWithCString:key -> getCString()
                                                           encoding:NSUTF8StringEncoding]];
                    }
                }
                else if (dynamic_cast<C2DXDictionary*>(value) != NULL)
                {
                    NSMutableDictionary *dictValue = convertC2DXDictionaryToNSDictionary(dynamic_cast<C2DXDictionary*>(value));
                    if (dictValue)
                    {
                        [dict setObject:dictValue
                                 forKey:[NSString stringWithCString:key -> getCString()
                                                           encoding:NSUTF8StringEncoding]];
                    }
                }
                else if (dynamic_cast<C2DXArray*>(value) != NULL)
                {
                    NSArray *arrayValue = convertC2DXArrayToNSArray(dynamic_cast<C2DXArray*>(value));
                    if (arrayValue)
                    {
                        [dict setObject:arrayValue
                                 forKey:[NSString stringWithCString:key -> getCString()
                                                           encoding:NSUTF8StringEncoding]];
                    }
                }
            }
        }
        return  dict;
    }
    return NULL;
}

C2DXString* convertNSStringToC2DXString(NSString *string)
{
    if (string)
    {
        return C2DXString::create([string cStringUsingEncoding:NSUTF8StringEncoding]);
    }
    
    return NULL;
}

NSString* convertC2DXStringToNSString(C2DXString *string)
{
    if (string)
    {
        return [NSString stringWithCString:string -> getCString() encoding:NSUTF8StringEncoding];
    }
    return NULL;
}

C2DXArray* convertNSArrayToC2DXArray(NSArray *array)
{
    if (array)
    {
        C2DXArray *ccArray = C2DXArray::create();
        
        for (int i = 0; i < [array count]; i++)
        {
            id value = [array objectAtIndex:i];
            if ([value isKindOfClass:[NSString class]])
            {
                C2DXString *strValue = convertNSStringToC2DXString(value);
                if (strValue)
                {
                    ccArray -> addObject(strValue);
                }
            }
            else if ([value isKindOfClass:[NSNumber class]])
            {
                C2DXString *strValue = convertNSStringToC2DXString([NSString stringWithFormat:@"%@", value]);
                if (strValue)
                {
                    ccArray -> addObject(strValue);
                }
            }
            else if ([value isKindOfClass:[NSDate class]])
            {
                ccArray -> addObject(C2DXDouble::create([value timeIntervalSince1970] * 1000));
            }
            else if ([value isKindOfClass:[NSDictionary class]])
            {
                C2DXDictionary *dictValue = convertNSDictToCCDict(value);
                if (dictValue)
                {
                    ccArray -> addObject(dictValue);
                }
            }
            else if ([value isKindOfClass:[NSArray class]])
            {
                C2DXArray *arrayValue = convertNSArrayToC2DXArray(value);
                if (arrayValue)
                {
                    ccArray -> addObject(arrayValue);
                }
            }
        }
        
        return ccArray;
    }
    
    return NULL;
}

NSArray* convertC2DXArrayToNSArray(C2DXArray *array)
{
    if (array)
    {
        NSMutableArray *nsArray = [NSMutableArray array];
        for (int i = 0; i < array -> count(); i++)
        {
            C2DXObject * value = array -> C2DXObjectAtIndex(i);
            if (dynamic_cast<C2DXString*>(value) != NULL)
            {
                NSString *strValue = convertC2DXStringToNSString(dynamic_cast<C2DXString*>(value) );
                if (strValue)
                {
                    [nsArray addObject:strValue];
                }
            }
            else if (dynamic_cast<C2DXDictionary*>(value) != NULL)
            {
                NSMutableDictionary *dictValue = convertC2DXDictionaryToNSDictionary(dynamic_cast<C2DXDictionary*>(value));
                if (dictValue)
                {
                    [nsArray addObject:dictValue];
                }
            }
            else if (dynamic_cast<C2DXArray*>(value) != NULL)
            {
                NSArray *arrayValue = convertC2DXArrayToNSArray(dynamic_cast<C2DXArray*>(value));
                if (arrayValue)
                {
                    [nsArray addObject:arrayValue];
                }
            }
        }
        return nsArray;
    }
    return NULL;
}

#pragma mark - MobLink Interface
static mob::moblink::C2DXRestoreSceneResultEvent restoreSceneCallBack;

void C2DXiOSMobLink::getMobId(C2DXMobLinkScene *scene, C2DXGetMobIdResultEvent callback)
{
    const char *pathChar = scene->path.c_str();
    const char *sourceChar = scene->source.c_str();
    NSString *path = [NSString stringWithCString:pathChar encoding:NSUTF8StringEncoding];
    NSString *source = [NSString stringWithCString:sourceChar encoding:NSUTF8StringEncoding];
    NSMutableDictionary *dict = convertC2DXDictionaryToNSDictionary(scene -> getCustomParams());
    
    MLSDKScene *theScene = [[MLSDKScene alloc] initWithMLSDKPath:path source:source params:dict]; 
    
    [MobLink getMobId:theScene result:^(NSString *mobid) {
       
        if (mobid)
        {
            callback([mobid UTF8String]);
        }
    }];
}

void C2DXiOSMobLink::setRestoreCallBack(mob::moblink::C2DXRestoreSceneResultEvent callback)
{
    restoreSceneCallBack = callback;
}

void C2DXiOSMobLink::resorteSceneCallBack(const char *path, const char *source, const char *paramsStr)
{
    C2DXMobLinkScene *scene = new C2DXMobLinkScene();
    scene -> path = path;
    scene -> source = source;
    
    NSString *params = [NSString stringWithCString:paramsStr encoding:NSUTF8StringEncoding];
    NSDictionary *dict = [MOBFJson objectFromJSONString:params];
    scene -> setCustomParams(convertNSDictToCCDict(dict));
    restoreSceneCallBack(scene);
    
}
