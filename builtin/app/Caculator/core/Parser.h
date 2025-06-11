#ifndef PARSER_H
#define PARSER_H
#include <QString>
class TreeNodeBase;
class Parser {
public:
    Parser() = default;
    ~Parser() = default;
    void setParserString(const QString& p);
    QString parserString() const;
    TreeNodeBase* parse();

private:
    QString handle_expression;
    int parse_pos { 0 };
    QChar peekPos();
    QChar getChar();
    void skipIgnored();
    TreeNodeBase* parseExpression();
    TreeNodeBase* parseTerm();
    TreeNodeBase* parseFactor();
    TreeNodeBase* parseNumber();
    QString parseIdentifier();
};

#endif // PARSER_H
