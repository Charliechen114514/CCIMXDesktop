#ifndef PARSER_H
#define PARSER_H

#include <QString>

class TreeNodeBase;

/**
 * @brief The Parser class is responsible for parsing a mathematical expression string
 *        and converting it into an abstract syntax tree (AST) of TreeNodeBase nodes.
 */
class Parser {
public:
    /**
     * @brief Default constructor.
     */
    Parser() = default;

    /**
     * @brief Default destructor.
     */
    ~Parser() = default;

    /**
     * @brief Sets the string to be parsed.
     * @param p The input expression string.
     */
    void setParserString(const QString& p);

    /**
     * @brief Returns the current parser string.
     * @return The expression string currently set.
     */
    QString parserString() const;

    /**
     * @brief Parses the input string and returns the root of the resulting AST.
     * @return A pointer to the root node of the parsed expression tree.
     */
    TreeNodeBase* parse();

private:
    /**
     * @brief The expression string to be parsed.
     */
    QString handle_expression;

    /**
     * @brief Current parsing position index in the expression.
     */
    int parse_pos { 0 };

    /**
     * @brief Returns the character at the current position without advancing.
     * @return The character at the current parse position.
     */
    QChar peekPos();

    /**
     * @brief Returns the character at the current position and advances the position.
     * @return The character at the current parse position before advancing.
     */
    QChar getChar();

    /**
     * @brief Skips whitespace and ignored characters in the expression.
     */
    void skipIgnored();

    /**
     * @brief Parses a complete expression.
     * @return A pointer to the root node of the parsed expression subtree.
     */
    TreeNodeBase* parseExpression();

    /**
     * @brief Parses a term within the expression.
     * @return A pointer to the root node of the parsed term subtree.
     */
    TreeNodeBase* parseTerm();

    /**
     * @brief Parses a factor within the expression.
     * @return A pointer to the root node of the parsed factor subtree.
     */
    TreeNodeBase* parseFactor();

    /**
     * @brief Parses a numeric value in the expression.
     * @return A pointer to the node representing the parsed number.
     */
    TreeNodeBase* parseNumber();

    /**
     * @brief Parses an identifier such as a function or variable name.
     * @return The parsed identifier as a QString.
     */
    QString parseIdentifier();
};

#endif // PARSER_H
