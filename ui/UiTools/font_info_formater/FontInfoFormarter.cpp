#include "FontInfoFormarter.h"
#include <QFont>
QString UiTools::FontFormater::describeFont(const QFont& font) {
    QString info;
    info += QString("Family: %1\n").arg(font.family());
    info += QString("Point size: %1\n").arg(font.pointSizeF());

    if (font.weight() > QFont::Normal)
        info += "Bold\n";
    if (font.italic())
        info += "Italic\n";
    if (font.underline())
        info += "Underline\n";
    if (font.strikeOut())
        info += "Strikeout\n";
    if (font.fixedPitch())
        info += "Monospaced\n";

    if (font.letterSpacing() != 0.0)
        info += QString("Letter spacing: %1\n").arg(font.letterSpacing());
    if (font.wordSpacing() != 0.0)
        info += QString("Word spacing: %1\n").arg(font.wordSpacing());

    return info;
}
