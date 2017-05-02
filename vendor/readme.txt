CMake 生产libjpeg-turbo的工程
1. 将libjpeg-turbo源码解压到一个目录:D:\libjpeg-turbo-1.4.0
2. 编译的工程：D:\libjpeg-turbo-1.4.0\build\libjpeg-turbo.sln
3. 依赖：CMake（版本最好是3.0以上的版本），nasm编译器(安装、设置环境变量)。
4. 编译工程的制作方法：
   1）从官方下载源码，使用CMake来制作VC工程
      A. 将源码解压到：D:\libjpeg-turbo-1.4.0
      B. 使用CMake制作VC工程，32位和64位需要放在不同的目录中(需要做两次配置)。
         注意需要勾选使用JPEG 8选项。
         x86工程目录：D:\libjpeg-turbo-1.4.0\build.x86，制作时选择Visual Studio 12 2013
         x64工程目录：D:\libjpeg-turbo-1.4.0\build.x64，制作时选择Visual Studio 12 2013 Win64
      C. 把不需要的工程从sln中删掉，只留下3个
      D. 根据生成的工程，调整选项，支持MD、MT；支持pdb输出等
   2）制作工程完成后，注意检查jconfig.h文件中的宏JPEG_LIB_VERSION定义值应为80
      一般生成是正确的。


项目工程的使用：
1,  libjpeg-turbo-1.5.1.zip 解压的D盘的根目录 D:\libjpeg-turbo-1.5.1
2,  把解压后的工程添加到要使用的目录中去，并设置好项目依赖
3， 注意把libjpeg-turbo 工程中的头文件替换freeImage 的libjpeg 中的头文件