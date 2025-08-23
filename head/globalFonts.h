#ifndef GLOBALFONTS_H_
#define GLOBALFONTS_H_

#include <QFontDatabase>
#include <QApplication>
#include <QStringList>
#include "pathProcessing.h"


static void globalFonts(const QApplication* app) {
    // 加载`JetBrainsMonoNL-SemiBold`字体
    QString jetBrainsFontFamily;
    int jetBrainsFontId{QFontDatabase::addApplicationFont(
        mySource("JetBrainsMonoNL-SemiBold.ttf")
        )
    };
    if (jetBrainsFontId != -1) {
        QStringList jetBrainsFontFamilies{
            QFontDatabase::applicationFontFamilies(jetBrainsFontId)
        };

        if (!jetBrainsFontFamilies.isEmpty()) {
            jetBrainsFontFamily = jetBrainsFontFamilies.at(0);
        }
    }

    // 加载 LXGWWenKai-Medium 字体
    QString lxgwFontFamily;
    int lxgwFontId{QFontDatabase::addApplicationFont(
        mySource("LXGWWenKai-Medium.ttf")
        )
    };
    if (lxgwFontId != -1) {
        QStringList lxgwFontFamilies{
            QFontDatabase::applicationFontFamilies(lxgwFontId)
        };

        if (!lxgwFontFamilies.isEmpty()) {
            lxgwFontFamily = lxgwFontFamilies.at(0);
        }
    }

    // 加载成功后设置全局字体为`JetBrainsMonoNL-SemiBold`
    if (!jetBrainsFontFamily.isEmpty()) {
        QFont globalFont(jetBrainsFontFamily, 14);
        globalFont.setStyleStrategy(QFont::PreferAntialias);
        app->setFont(globalFont);

        // 如果`LXGW`字体也加载成功，则设置字体回退
        if (!lxgwFontFamily.isEmpty()) {
            QFont::insertSubstitution(
                jetBrainsFontFamily, 
                lxgwFontFamily
            );
        }
    } else if (!lxgwFontFamily.isEmpty()) {
        // 如果`JetBrains`字体加载失败但`LXGW`成功，则使用`LXGW`作为全局字体
        QFont globalFont(lxgwFontFamily, 14);
        globalFont.setStyleStrategy(QFont::PreferAntialias);
        app->setFont(globalFont);
    }
}

#endif // GLOBALFONTS_H_