#ifndef BINARYOPTREENODE_H
#define BINARYOPTREENODE_H
#include "ParseExceptions.h"
#include "core/TreeNodeBase.h"
#include <QChar>
struct BinaryOpTreeNode : public TreeNodeBase {
public:
    BinaryOpTreeNode(QChar op,
                     TreeNodeBase* left_hand,
                     TreeNodeBase* right_hand);
    BinaryOpTreeNode() = delete;
    ~BinaryOpTreeNode() override;
    double evaluate() const override;

private:
    QChar op;
    TreeNodeBase* left_hand;
    TreeNodeBase* right_hand;
};

#endif // BINARYOPTREENODE_H
