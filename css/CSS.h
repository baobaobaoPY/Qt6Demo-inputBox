#ifndef MAINCSS_H_
#define MAINCSS_H_

#include <QString>

namespace css {
const QString WhiteEdit {R"(
    QLineEdit {
        background: #f8f9fa;
        border: 1px solid #ced4da;
        border-radius: 5px;
        padding: 4px 8px;
    }
    )"  // end
};

const QString BlueBtn {R"(
    QPushButton {
        background: #40c0ff;
        color: white;
        border: none;
        border-radius: 5px;
        padding: 4px 8px;
    }

    QPushButton:hover {
        background: #30b4fa;
    }
    )"  // end
};

};  // namespace::css

#endif  // MAINCSS_H_