#include "../head/main.h"
#include "../head/globalFonts.h"


int main (int argc, char* argv[]) {
    // 初始化QApplication
    QApplication app(argc, argv);

    // 设置全局字体样式
    globalFonts(&app);

    // 实例化myWidget类对象窗口
    myWidget win;
    // 显示myWidget窗口
    win.show();


    // 循环等待事件结束
    return app.exec();
}