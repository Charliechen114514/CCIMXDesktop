#ifndef EXPRESSIONEVALUATOR_H
#define EXPRESSIONEVALUATOR_H
class QString;
/**
 * @namespace ExpressionEvaluator
 * @brief evaluator
 * 
 */
namespace ExpressionEvaluator {
/**
 * @brief evalute expression
 * 
 * @param expr expression
 * @return double result
 */
double evalute_expression(const QString& expr);
};

#endif // EXPRESSIONEVALUATOR_H
