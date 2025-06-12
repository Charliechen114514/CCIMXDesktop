#ifndef NUMBERNODE_H
#define NUMBERNODE_H
#include "core/TreeNodeBase.h"
#include <QtClassHelperMacros>
/**
 * @brief NumberNode holds number
 * 
 */
struct NumberNode : public TreeNodeBase {
    /**
     * @brief disable copy and move
     * 
     */
    Q_DISABLE_COPY_MOVE(NumberNode);
    /**
     * @brief Construct a new Number Node object
     * 
     * @param val 
     */
    NumberNode(double val);
    NumberNode() = delete;
    ~NumberNode() override = default;
    /**
     * @brief evaluate the expressions
     * 
     * @return double 
     */
    double evaluate() const override;

private:
    double stored_value{0.0}; ///< stored value
};

#endif // NUMBERNODE_H
