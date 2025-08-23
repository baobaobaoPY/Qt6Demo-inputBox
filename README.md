# Qt6Demo-inputBox
一个基于`Qt6`的轻量练习项目，实现了`输入框 + 按钮`的简单交互Demo，用户在输入内容后，点击按钮或按下回车可将内容输出至控制台。  
项目采用模块化、低耦合设计(部分函数实现可复用)，支持跨平台(windows/linux)编译，非常适合参考学习。  
<img width="371" height="102" alt="PixPin_2025-08-23_15-05-311" src="https://github.com/user-attachments/assets/52238346-522e-4b0a-85a2-5494deeced4b" />
## 如何构建🤔？
1、首先确保已经安装：  
``` text
"vcpkg"、"cmake"、"ninja"、"clang"、"python3"、"Qt6"
```
然后在确认环境变量是否已经添加这些工具。  
2、在vcpkg安装完成`{fmt}`后导航至项目根目录下，打开`CMakelists.txt`文件，并将文件中配置的`Qt`安装路径修改为您自己的`Qt`安装路径，并执行`python build.py`即可完成所有构建。  
部分工具开源地址如下：
``` text
https://github.com/microsoft/vcpkg
https://github.com/Kitware/CMake
https://github.com/ninja-build/ninja
```
## 其他事项🤗
项目可跨平台(windows/linux)编译。  
整体准寻模块化搭建思维进行实现。  
cmake需确保满足3.20。  
clang需确保支持C++17。  
字体资源开源地址如下：
``` text
https://github.com/JetBrains/JetBrainsMono
https://github.com/lxgw/LxgwWenKai
```
