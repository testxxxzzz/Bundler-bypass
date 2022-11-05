# Bundler-bypass

免杀捆绑器，过国内主流杀软。A Bundler bypass anti-virus

**请勿使用于任何非法用途，由此产生的后果自行承担。**

思路借鉴了[该文章](https://forum.butian.net/share/1778)，然后做了一些小改动，如取消了自删除功能，可以进行多次的上线，将文件写到了系统temp目录中并打开。

整体思路为在vs中打包静态资源文件，然后遍历打包的资源文件并将其写到主机的temp目录中，之后用ShellExecuteExA函数来打开。

使用方法为：

1、右键资源文件并添加资源，选择导入中的所有文件来选择我们想捆绑的文件和exe文件，并把资源类型赋值为文件的后缀，如pptx和exe

![image](https://user-images.githubusercontent.com/48757788/200118397-1a05cf8d-bb7e-4e63-94e0-5e11bf2f7df1.png)

2、将exe文件和捆绑的文件按照步骤一打包好了后，编译。

这里以geacon_pro捆绑一个pptx文件为例来上线：

![1667649118485](https://user-images.githubusercontent.com/48757788/200118502-94241fb7-526c-41c4-92b1-b6c9375223f7.jpg)




