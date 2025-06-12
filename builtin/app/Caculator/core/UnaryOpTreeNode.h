#ifndef UNARYOPTREENODE_H
#define UNARYOPTREENODE_H
#include "ParseExceptions.h"
#include "TreeNodeBase.h"
#include <QChar>

/**
 * @brief   UnaryOpTreeNode is a derived node of
 *          TreeNodeBase, which handles the unary calc
 * 
 */
class UnaryOpTreeNode : public TreeNodeBase {
public:
    /**
     * @brief Construct a new Unary Op Tree Node object
     * 
     * @param oper 
     * @param child 
     */
    UnaryOpTreeNode(QChar oper, TreeNodeBase* child);
    ~UnaryOpTreeNode();
    /**
     * @brief evaluate the expressions
     * 
     * @return double 
     */
    double evaluate() const override;

private:
    QChar op; ///< op
    TreeNodeBase* operand; ///< hanlding exp
};

#endif // UNARYOPTREENODE_H
