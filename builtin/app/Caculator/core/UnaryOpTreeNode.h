#ifndef UNARYOPTREENODE_H
#define UNARYOPTREENODE_H
#include "ParseExceptions.h"
#include "TreeNodeBase.h"
#include <QChar>

class UnaryOpTreeNode : public TreeNodeBase {
public:
    UnaryOpTreeNode(QChar oper, TreeNodeBase* child);
    ~UnaryOpTreeNode();
    double evaluate() const override;

private:
    QChar op;
    TreeNodeBase* operand;
};

#endif // UNARYOPTREENODE_H
