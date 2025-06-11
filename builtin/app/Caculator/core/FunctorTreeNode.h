#ifndef FUNCTORTREENODE_H
#define FUNCTORTREENODE_H
#include <QString>
#include "TreeNodeBase.h"

class FunctorTreeNode : public TreeNodeBase {
    QString name;
    TreeNodeBase* argument;

public:
    FunctorTreeNode(QString name, TreeNodeBase* arg);
    ~FunctorTreeNode();
    double evaluate() const override;
};

#endif // FUNCTORTREENODE_H
