# iTunes Support

## 绪论
iTunes Support是一个以NERvSDK为基础开发的插件。目标是将iTunes和SAO Utils等使用NERvSDK的程序连接起来。实现互相交互。

目前iTunes Support实现的功能有从SAO Utils获取基本的信息，比如当前曲目，艺术家，专辑等。以及通过SAO Utils控制iTunes，比如播放/暂停，上一曲等。
## 安装
- iTunes版本需求：>= iTunes 5.0；（如果不符合要求SAO Utils会直接崩溃）
- NERvSDK版本需求：>= NERvSDK 0.2.1；
- SAO Utils版本需求：>= SAO Utils Beta 1；
- 操作系统版本需求：>= Windows 7；
- .net Framework版本需求：>= .net Framework 4.5

从GitHub存储库的Release获取最新版本的发布NVG包，在SAO Utils中打开首选项->插件，点击“安装”。选择下载的NVG包，勾选“启用”，并保存配置。即可安装成功。

##设置
iTunes Support会提供一系列的数据源，用于操作iTunes或获取iTunes信息。

### iTunes数据获取
该数据源负责从iTunes获取信息。

#### 播放进度
获取当前歌曲播放进度，以s为单位，建议更新间隔设置为100ms。并与GGO桌面挂件的条形图挂件连用。如图。![](http://p1.bqimg.com/4851/1611c808f64092a2.png)

#### 播放时间
获取当前歌曲播放进度，格式化为mm:ss的形式。建议更新间隔设置为100ms。

#### 标题、表演者、专辑
获取当前歌曲的标题、表演者、专辑。建议以1s为更新间隔。

> 注意，这三个字段可以通过设置更新参数为“roll”来开启滚动功能，还可以在roll后接数字来使字段在超过一段时间后滚动。同时可利用更新间隔来确定滚动速度。如图。![](http://p1.bpimg.com/4851/da7fe613f51acdf5.gif)

#### 音量
获取当前iTunes音量。以%为单位。

#### 第一行歌词、第二行歌词
获取当前歌曲中歌词标签通过LRC解析之后的歌词。
歌词标签一般这样设置：
![](http://p1.bqimg.com/4851/4487757d66f4f076.png)
对于多个时间标签相同的歌词条目，第一次遇到的作为第一行，最后一次作为第二行。如上图到01:35.16处：![](http://p1.bqimg.com/4851/268bd9d7ce6f3306.png)。

> __*警告：*__ 绝对不要在LRC标签中出现两个间隔时间极短的元素。由于插件时间计量不够精确，将会产生一些无法预料的输出。

#### 专辑封面
专辑封面桌面网页插件的作用在于将其位置设置为插件目录下的“widget\cover demo\index.html”，在插件启动的情况下就可以获取iTunes的专辑封面。如图：![](http://p1.bqimg.com/4851/b519d0084559c79d.png)

>注意，该字段会在第一次处理一首曲目的时候将其封面保存到插件目录下的artwork目录下。所以在专辑封面很多且磁盘空间较少的时候避免使用此字段。

### iTunes控制
该数据源用于控制iTunes。这些数据源目前只能配合GGO Widgets插件使用。
> 本数据源所有输出均来自各自的“更新参数”。

#### 播放/暂停、下一曲、上一曲
顾名思义，对播放进度进行控制。

#### 音量+
增加10%音量。在音量大于90%时将音量调至100%。

#### 音量-
降低10%音量。在音量小于10%时将音量调至0%。

## 综合实例
![](http://p1.bpimg.com/4851/89784b3dec349a22.gif)

## 断开连接的情况
若在插件运行时关闭iTunes，插件会表现为所有字段停止更新，标题字段变为“与iTunes断开连接”。重启iTunes后插件会自动连接iTunes。

## 参与开发
本程序采用C++与C#混合编程，C++与NERvSDK交互，C#与iTunes的iTunes COM SDK for Windows交互。C++与C#通过CLR交互，因此你需要一个Visual Studio 2015环境。

欢迎对本插件的改进提出建议，可以通过Issue的方式告诉我，或者利用SAO Utils开发/用户讨论群。如果能通过Push Request的方式贡献更是感谢。

### 项目结构
- iTunesSupport C++编写的与NERvSDK交互的部分。 NERvSDK:[详见这里](https://github.com/NERvGear/NERvSDK "NERvSDK")
- iTunesSupportImpl C#编写的与iTunes交互的部分。 iTunes COM SDK for Windows:[详见这里](http://www.joshkunz.com/iTunesControl/main.html "iTunes COM SDK for Windows")
- iTunesSupportImplDebug C#编写的用于调试iTunesSupportImplDebug的项目。内容目前无意义，但是可以自己编写代码来调试。
- Build NVG打包工具，请在Package目录下运行。
- Package 用于存放输出文件。
- Package/widget 用于专辑封面的文件，使用HTML、JavaScript和CSS编写，大部分引用了来自RangerCD的音乐播放器插件。（此部分代码采用Lolicon Public License协议）

## 已知问题
(经常发生) 插件断开连接后强行创建iTunesAppClass致使iTunes自动重启。解决方案：在需要退出iTunes时先退出SAO Utils或禁用插件。

## 鸣谢
- 本插件在开发中收到了来自SAO Utils开发讨论群大量dalao的帮助，在此对你们表示感谢。（还要感谢你们忍受我的自言自语【笑）
- 感谢GPBeta开发了SAO Utils和NERvSDK，为我们带来了这样一个平台。同时也在开发时给予了
- 感谢RangerCD开发了音乐播放器支持插件。这个插件就是iTunes Support的灵感来源。同时感谢CD用Lolicon Public License允许我使用他编写的专辑封面显示代码。
- 感谢ic#code的贡献者提供了用于构建NVG的SharpZipLib开源类库。

## 作者
目前本插件的作者有：

- Charlie Jiang <[cqjjjzr@126.com](mailto:cqjjjzr@126.com "cqjjjzr@126.com")>

## 授权
本插件除cover demo以外的部分使用Apache License 2.0协议公开源代码。协议详见LICENSE文档。

Package/widget下cover demo项目的开发者是RangerCD。使用Lolicon Public License公开源代码。协议详见LICENSE-LPL文档。