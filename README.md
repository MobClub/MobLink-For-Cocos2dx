# Cocos2dx For MobLink 快速集成文档

## 下载并导入MobLink

下载[Cocos2dx-For-MobLink](https://github.com/MobClub/Cocos2dx-For-MobLink),下载完成后打开项目,将/Classes/C2DXMobLink文件夹复制到您的cocos2dx项目/Classes目录下

![](https://lh3.googleusercontent.com/-pHInEVOfEgU/WTUuDvQ4rpI/AAAAAAAABkg/atmlV1cdHZQe-M0Zv0NF-zv_2q8--hu9gCHM/I/m1.png)

## Android端接入

1. 复制/proj.android-studio/app/libs目录下的MobCommons.jar、MobLink-1.1.0.jar、MobLink-Cocos2dx.jar、MobTools.jar到您的coco2dx项目libs目录下

2. 添加编译需要的cpp源代码(Android.mk)

```
../../../Classes/C2DXMobLink/C2DXMobLink.cpp \
../../../Classes/C2DXMobLink/C2DXMobLinkScene.cpp \
../../../Classes/C2DXMobLink/C2DXMobLinkCallBack.cpp \
../../../Classes/C2DXMobLink/Android/C2DXAndroidMobLink.cpp \
../../../Classes/C2DXMobLink/Android/C2DXAndroidActionListener.cpp \
../../../Classes/C2DXMobLink/Android/com_mob_moblink_cocos2dx_ActionListener.cpp \
../../../Classes/C2DXMobLink/Android/C2DXAndroidRestoreSceneListener.cpp \
../../../Classes/C2DXMobLink/Android/com_mob_moblink_cocos2dx_RestoreSceneListener.cpp \
../../../Classes/C2DXMobLink/Android/JSON/CCJSONConverter.cpp \
../../../Classes/C2DXMobLink/Android/JSON/cJSON/cJSON.c
```

3. 添加编译需要的头文件路径(Android.mk)

```
$(LOCAL_PATH)/../../../Classes/C2DXMobLink \
$(LOCAL_PATH)/../../../Classes/C2DXMobLink/Android \
$(LOCAL_PATH)/../../../Classes/C2DXMobLink/Android/JSON \
$(LOCAL_PATH)/../../../Classes/C2DXMobLink/Android/JSON/cJSON
```

4. 配置AndroidManiFest.xml文件

请参考原生Android平台的配置文件中的， 配置AndroidManiFest.xml文件部分


[http://wiki.mob.com/sdk-moblink-android-2-0-0](http://wiki.mob.com/sdk-moblink-android-2-0-0)


## iOS端接入
对于iOS,还需要对Xcode项目进行一些配置
1.**(重要)** 配置***MobAppKey***以及***MobAppSecret***
在Xcode项目对应的info.plist文件中设置应MobLink官网获得的key和secret

![](https://lh3.googleusercontent.com/-Gfm9GqO7Tas/WTfRhQn2iHI/AAAAAAAABlA/osQn7gtmjsU9iUgieWMBETI52V6q60mLQCHM/I/m6.png)


2.添加MobLink库
在本demo项目的proj.ios_mac文件夹中找到SDK文件夹,将其添加到您的Xcode项目中(内含两个framework)

![](https://lh3.googleusercontent.com/-H5Sf_RFdee0/WTfS2sBz7SI/AAAAAAAABlM/jPyYYqWfG6s1JI3_YYVTDGVNgtbY5EOYACHM/I/m7.png)


3.添加系统依赖库

![](https://lh3.googleusercontent.com/-aUPKfyIVfII/WTUuELxg2ZI/AAAAAAAABko/BHhp1wkfR8AL0z5DTz0P1vhUfNKSxVhXACHM/I/m3.png)
选择项目Target-Build Phases-Link Binary With Libraries，然后选择“+”进行添加系统库：

libsqlite3
libz1.2.5
libstdc++
libicucore

4.配置Universal Link 以及 URL Scheme
i. URL Scheme
项目中需要配置URL Scheme以用于场景恢复时跳转到应用中（这里的scheme要唯一确定，不要与其他应用一致，建议使用项目名称作为scheme）。请参考下图配置您自己的URL Scheme：

![](https://lh3.googleusercontent.com/-FIt8LBPU1Ik/WTUuEtYtWKI/AAAAAAAABks/qAMg1gzfTnAMYBayoVJZgmARKFSw97WzACHM/I/m4.png)


ii.Universal Link
然后在项目中配置Universal Link，请务必填写后台生成的Universal Link地址 (建议直接从管理后台拷贝)参考下图：

![](https://lh3.googleusercontent.com/-iclHMVZl1cE/WTUuEusVTQI/AAAAAAAABkw/P6zMErfmthEhPDddv-Diaikga2pouZKoQCHM/I/m5.png)

上述步骤其实与原生iOS集成MobLink一致,具体可参考[iOS快速集成](http://wiki.mob.com/quick-import-ios/)中的第三点的第1、2小点。


## 添加代码

#### 1.设置场景回调
i.自行构建回调,自行处理得到的场景参数scene

```
void sceneHandler(C2DXMobLinkScene *scene)
{
    //自行处理取得的scene
    log("path = %s", scene->path.c_str());
    log("source = %s", scene->source.c_str());
    __Dictionary *custom = scene->getCustomParams();

    std::string content;
    content += "path:"; content += scene->path.c_str(); content += "\n";
    content += "source:"; content += scene->source.c_str(); content += "\n";
    content += "params:\n";

    DictElement *element;
    CCDICT_FOREACH(custom, element)
        {
            const char *key = element -> getStrKey();
            __String *obj = (__String*)element -> getObject();
            log("key = %s, value = %s",key,obj -> getCString());
            content += key; content += ":"; content += obj->getCString(); content += "\n";
        }

    MessageBox(content.c_str(), "得到场景恢复回调");
}
```

ii.将回调传入

```
//设置场景恢复之回调
    C2DXMobLink::setSceneRestoreCallBack(sceneHandler);
```

#### 2.获取Mobid
i.自行构建回调,自行处理得到的mobid

```
void getMobIdHandler(const char * mobid)
{
    log("result - mobid = %s", mobid);
    std::string content = "mobId:";
    content += mobid;
    MessageBox(content.c_str(), "获取MobId的回调");
}
```

ii.构建场景参数,并传入上述回调

```
C2DXMobLinkScene *scene = new C2DXMobLinkScene();
scene->path = "the path";
scene->source = "the source";

__Dictionary *customParams = __Dictionary::create();
customParams->setObject(__String::create("999"), "Price");
customParams->setObject(__String::create("1"), "Chapter");
customParams->setObject(__String::create("Dragon Fire"), "ChapterName");
scene->setCustomParams(customParams);

C2DXMobLink::getMobId(scene, getMobIdHandler);
```

**注意:获取到MobId后,应通过分享的方式将带有Mobid的链接分享出去**
**对于分享,我们更建议使用[Cocos2dx For ShareSDK](https://github.com/MobClub/New-C2DX-For-ShareSDK)**


    
# 如何Build Demo For Android 

1.使用git工具下载代码

```
https://github.com/MobClub/Cocos2dx-For-MobLink.git
```

2.复制cocos2d目录到项目/根目录下, 建议使用cocos版本为3.8.1 

3.使用AndroidStudio打开proj.android-studio项目

4.build 成功后，安装apk到手机上

5.在不同的平台(如微信/浏览器)分享以下链接，然后访问链接:

http://f.moblink.mob.com/demo/a?mobid=up 

http://f.moblink.mob.com/demo/b?mobid=up 

http://f.moblink.mob.com/demo/c?mobid=up 

http://f.moblink.mob.com/demo/d?mobid=up 


