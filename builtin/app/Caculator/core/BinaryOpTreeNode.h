#ifndef BINARYOPTREENODE_H
#define BINARYOPTREENODE_H
#include "ParseExceptions.h"
#include "core/TreeNodeBase.h"
#include <QChar>
/**
 * @brief   BinaryOpTreeNode is a derived node of
 *          TreeNodeBase, which handles the binary calc
 * 
 */
struct BinaryOpTreeNode : public TreeNodeBase {
public:
    /**
     * @brief Construct a new Binary Op Tree Node object
     * 
     * @param op operations char
     * @param left_hand left expression
     * @param right_hand right expression
     */
    BinaryOpTreeNode(QChar op,
                     TreeNodeBase* left_hand,
                     TreeNodeBase* right_hand);
    BinaryOpTreeNode() = delete;
    ~BinaryOpTreeNode() override;
    /**
     * @brief evaluate the expressions
     * 
     * @return double 
     */
    double evaluate() const override;

private:
    QChar op; ///< operations
    TreeNodeBase* left_hand; ///< left exp
    TreeNodeBase* right_hand; ///< right exp
};

#endif // BINARYOPTREENODE_H
