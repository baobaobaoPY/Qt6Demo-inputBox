#ifndef MAIN_H_
#define MAIN_H_

#include <QPushButton>
#include <QLineEdit>
#include <QWidget>
#include <QObject>
#include <QIcon>
#include <fmt/core.h>
#include <memory>
#include "pathProcessing.h"
#include "../css/CSS.h"
#include "centre_XY.h"

using namespace fmt;


namespace {
    // 设置myWidget类的窗体大小参数
    constexpr unsigned short myWidget_W {295};  // 设置`宽`值
    constexpr unsigned short myWidget_H {50};  // 设置`高`值

    // 设置myWidget类中`edit`输入框的XY与宽高参数
    constexpr unsigned short edit_X {5};  // 设置`X`值
    constexpr unsigned short edit_Y {5};  // 设置`Y`值
    constexpr unsigned short edit_W {220};  // 设置`宽`值
    constexpr unsigned short edit_H {40};  // 设置`高`值

    // 设置myWidget类中`btn`按钮的XY与宽高参数
    constexpr unsigned short btn_X {230};  // 设置`X`值
    constexpr unsigned short btn_Y {6};  // 设置`Y`值
    constexpr unsigned short btn_W {60};  // 设置`宽`值
    constexpr unsigned short btn_H {38};  // 设置`高`值

    // 设置myWiget窗口标题文本占位符
    const QString myWigetName {"初见Qt6"};
    // 设置myWidget类中`edit`背景文本占位符
    const QString editText {"请输入任意字符："};
    // 设置myWidget类中的`btn`按钮文本占位符
    const QString btnName {"输出"};

};  // namespace


class myWidget : public QWidget {
public:
    explicit myWidget(QWidget* parent = nullptr) : QWidget(parent) {
        // 获取屏幕中心XY坐标值
        QPoint setX_Y{
            setMyWidget_axis(myWidget_W, myWidget_H)
        };
        // 配置myWidget窗口显示坐标和固定大小
        move(setX_Y.x(), setX_Y.y() - 100);
        setFixedSize(myWidget_W, myWidget_H);
        // 配置窗口不可最大化
        setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
        // 配置myWidget窗口标题
        setWindowTitle(myWigetName);
        // 配置窗口标题栏图标
        setWindowIcon(QIcon(
            mySource("IDI_ICON1.ico")
            )
        );

        // 创建QLineEdit类对象，并设置基类为myWidget
        edit = std::make_unique<QLineEdit>(this);
        // 配置输入框背景文本占位符
        edit->setPlaceholderText(editText);
        // 配置edit的坐标与大小
        edit->setGeometry(edit_X, edit_Y, edit_W, edit_H);
        // 配置edit样式
        edit->setStyleSheet(css::WhiteEdit);

        // 创建QPushButton对象，并设置基类为myWidget
        btn = std::make_unique<QPushButton>(btnName, this);
        // 配置btn的坐标与大小
        btn->setGeometry(btn_X, btn_Y, btn_W, btn_H);
        // 配置btn样式
        btn->setStyleSheet(css::BlueBtn);

        // 绑定信号(点击按钮时将输入框内内容进行输出)
        QObject::connect(btn.get(), &QPushButton::clicked,
            [this] (void) -> void {
                // 将输入内容转换为QString
                QString input {edit->text()};

                // 判断输入内容是否为空？
                // 如果不为空则清空输入框并输出输入框内内容。
                if (!input.isEmpty()) {
                    edit->clear();  // 清空输入框
                    // 输出input内容
                    println("{}", input.toStdString());
                }
            }
        );

        // 绑定信号(在输入框内输入内容时按下回车时代替点击按钮)
        QObject::connect(
            edit.get(), &QLineEdit::returnPressed,
            btn.get(), &QPushButton::click
        );
    }

private:
    std::unique_ptr<QPushButton> btn;  // 实例化QPushButton类对象
    std::unique_ptr<QLineEdit> edit;  // 实例化QLineEdit类对象
};

#endif  // MAIN_H_