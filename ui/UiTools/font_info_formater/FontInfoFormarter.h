#ifndef FONTFORMATER_H
#define FONTFORMATER_H
#include <QString>
class QFont;

/**
 * @namespace UiTools supports the Ui sessions
 */
namespace UiTools {
/**
 * @namespace FontFormater supports the Font Info display sessions
 */
namespace FontFormater {
    /**
     * @brief get the string tells the fonts
     * 
     * @param font 
     * @return QString 
     */
    QString describeFont(const QFont& font);
}
}

#endif
