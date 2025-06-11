#include "ExpressionEvaluator.h"
#include "Parser.h"
#include "TreeNodeBase.h"
double ExpressionEvaluator::evalute_expression(const QString& expr) {
    Parser parser;
    parser.setParserString(expr);
    std::unique_ptr<TreeNodeBase> root(parser.parse());
    return root->evaluate();
}
