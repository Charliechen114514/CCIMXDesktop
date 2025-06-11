#include "Parser.h"
#include "BinaryOpTreeNode.h"
#include "FunctorTreeNode.h"
#include "NumberNode.h"
#include "UnaryOpTreeNode.h"
void Parser::setParserString(const QString& p) {
    this->handle_expression = p;
    parse_pos = 0;
}

QString Parser::parserString() const {
    return handle_expression;
}

TreeNodeBase* Parser::parse() {
    TreeNodeBase* node = parseExpression();
    if (parse_pos < handle_expression.length())
        throw GeneralParseError();
    return node;
}

QChar Parser::peekPos() {
    return parse_pos < handle_expression.length() ? handle_expression[parse_pos] : QChar();
}

QChar Parser::getChar() {
    return parse_pos < handle_expression.length() ? handle_expression[parse_pos++] : QChar();
}

void Parser::skipIgnored() {
    while (peekPos().isSpace())
        ++parse_pos;
}

TreeNodeBase* Parser::parseExpression() {
    TreeNodeBase* node = parseTerm();
    while (true) {
        skipIgnored();
        QChar op = peekPos();
        if (op == '+' || op == '-') {
            getChar(); // consume operator
            TreeNodeBase* rhs = parseTerm();
            node = new BinaryOpTreeNode(op, node, rhs);
        } else
            break;
    }
    return node;
}

TreeNodeBase* Parser::parseTerm() {
    TreeNodeBase* node = parseFactor();
    while (true) {
        skipIgnored();
        QChar op = peekPos();
        if (op == '*' || op == '/' || op == "^") {
            getChar(); // consume operator
            TreeNodeBase* rhs = parseFactor();
            node = new BinaryOpTreeNode(op, node, rhs);
        } else {
            break;
        }
    }
    return node;
}

TreeNodeBase* Parser::parseFactor() {
    skipIgnored();
    QChar ch = peekPos();

    if (ch == '-') {
        getChar(); ///< consume '-'
        TreeNodeBase* node = parseFactor();
        return new UnaryOpTreeNode('-', node);
    }

    if (ch.isLetter()) {
        QString func = parseIdentifier();
        skipIgnored();
        if (getChar() != '(')
            throw UnSymmetryExpression();
        TreeNodeBase* arg = parseExpression();
        skipIgnored();
        if (getChar() != ')')
            throw UnSymmetryExpression();
        return new FunctorTreeNode(func, arg);
    }

    if (ch == '(') {
        getChar(); // consume '('
        TreeNodeBase* node = parseExpression();
        skipIgnored();
        if (getChar() != ')') {
            throw UnSymmetryExpression();
        }
        return node;
    }

    if (ch.isDigit() || ch == '.') {
        return parseNumber();
    }

    throw UnSupportedSymbol(ch);
}

TreeNodeBase* Parser::parseNumber() {
    skipIgnored();
    int start = parse_pos;
    while (peekPos().isDigit() || peekPos() == '.')
        ++parse_pos;
    bool ok;
    double val = handle_expression.mid(start, parse_pos - start).toDouble(&ok);
    if (!ok)
        throw InvalidNumber();
    return new NumberNode(val);
}

QString Parser::parseIdentifier() {
    skipIgnored();
    int start = parse_pos;
    while (peekPos().isLetter())
        ++parse_pos;
    return handle_expression.mid(start, parse_pos - start);
}
