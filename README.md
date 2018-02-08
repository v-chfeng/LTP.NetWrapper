# LTP.NetWrapper

# 哈工大 TLP
官方文档：
http://ltp.ai/docs/begin.html
http://ltp.readthedocs.io/zh_CN/latest/api.html

项目源码：
https://github.com/HIT-SCIR/ltp/releases


注意事项：
	1. 只支持utf-8字符串
	2. 处理句子长度为1024字
分词结果256

# 编译源码：
	1. 有x64 和 x86 区别， C#引用dll的时候也要注意
	2. TLP动态链接库封装
	 a.  首先编译TLP源码，生成需要的动态链接库和静态链接库
         b. 新建一个VC++ project, 
	 c.  添加TLP 源码的头文件
		项目-> 属性->C++ -> 常规->附加库目录->  加入头文件目录
	 d. 添加静态链接库的
		项目-> 属性->链接器 -> 常规->附加库目录->  加入库目录（静态库） 
	 e.  引用 include 同时编译成相应版本的库
		项目-> 属性->链接器 -> 常规->附加依赖项->  加入库名称
	3. C# 调用封装的API 
		a. String encode(utf-8) 转成byte[]传给C++ API
		b. C++结果也是utf-8，所以需要先encode(unicode) 再decode(utf-8) (因为内存中默认是Unicode编码，传给C#的string也是这个编码，需要转一下编码格式)
