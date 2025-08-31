#ifndef PATHPROCESSING_H_
#define PATHPROCESSING_H_

#include <QCoreApplication>
#include <QFileInfo>
#include <QString>
#include <QHash>


// 资源类型映射表
static const QHash<QString, QString>ResourceSuffixMap {
    // 压缩文件
    {".zip", "/zip/"}, 
    {".7z", "/zip/"}, 
    {".rar", "/zip/"}, 
    {".tar", "/zip/"}, 
    {".gz", "/zip/"}, 
    {".bz2", "/zip/"}, 

    // 图标文件
    {".ico", "/ico/"}, 
    {".png", "/ico/"}, 
    {".jpg", "/ico/"}, 
    {".jpeg", "/ico/"}, 
    {".bmp", "/ico/"}, 
    {".svg", "/ico/"}, 
    {".webp", "/ico/"}, 

    // 字体文件
    {".ttf", "/font/"}, 
    {".otf", "/font/"}, 
    {".woff", "/font/"}, 
    {".woff2", "/font/"}, 

    // 音频文件
    {".mp3", "/audio/"}, 
    {".wav", "/audio/"}, 
    {".ogg", "/audio/"}, 
    {".flac", "/audio/"}, 
    {".m4a", "/audio/"}, 
    {".aac", "/audio/"}, 

    // 视频文件
    {".mp4", "/video/"}, 
    {".avi", "/video/"}, 
    {".mkv", "/video/"}, 
    {".mov", "/video/"}, 
    {".wmv", "/video/"}, 
    {".flv", "/video/"}
};

/**
 * @brief 根据文件名生成资源文件的完整路径
 *
 * 该函数根据传入的文件名，判断文件类型并生成相应的资源文件路径。
 * 如果文件类型在资源后缀映射表中存在，则使用映射表中的路径前缀；
 * 否则使用应用程序目录作为基础路径。
 *
 * @param fileName 文件名(可包含相对路径)
 * @return QString 返回完整的资源文件路径
**/
static QString resourcePath(const QString& fileName) {
    const QString myFilePath{QCoreApplication::applicationDirPath()};

    // 从文件名末尾开始向前查找点号位置
    int dotIndex {-1};
    for (int i = fileName.length() - 1; i >= 0; --i) {
        if (fileName[i] == '.') {
            dotIndex = i;
            break;
        }
        // 如果遇到路径分隔符则停止查找(可能为路径而非文件名)
        if (fileName[i] == '/' || fileName[i] == '\\') {
            break;
        }
    }

    // 如果找到点号，则提取后缀名
    if (dotIndex != -1 && dotIndex < fileName.length() - 1) {
        QString suffixWithDot{fileName.mid(dotIndex).toLower()};

        // 检查文件后缀是否在资源映射表中，如果存在则使用对应的路径前缀
        if (ResourceSuffixMap.contains(suffixWithDot)) {
            return myFilePath
                + ResourceSuffixMap.value(suffixWithDot)
                + fileName;
        }
    }

    // 默认情况下，将文件放在应用程序目录下
    return myFilePath + fileName;
}

// 将传入的资源文件名进行处理后返回实际资源存放路径
static QString mySource(const QString& fileName) {
    return resourcePath(fileName);
}

#endif  // PATHPROCESSING_H_