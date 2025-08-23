#ifndef CENTRE_XY_HPP_
#define CENTRE_XY_HPP_

#include <QGuiApplication>
#include <QScreen>
#include <QPoint>


// 通过算法自动计算屏幕中心坐标值并将其返回
static QPoint setMyWidget_axis(const unsigned short Width,
                                const unsigned short Height) {
    // 获取用户屏幕几何信息
    QScreen* screen = QGuiApplication::primaryScreen();

    // 将计算出的屏幕中心坐标返回
    return QPoint(
        (screen->geometry().width() - Width) / 2,
        (screen->geometry().height() - Height) / 2
    );
}

#endif  // CENTRE_XY_HPP_