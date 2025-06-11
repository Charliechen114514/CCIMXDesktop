#ifndef NUMBERNODE_H
#define NUMBERNODE_H
#include "core/TreeNodeBase.h"
#include <QtClassHelperMacros>
struct NumberNode : public TreeNodeBase {
    Q_DISABLE_COPY_MOVE(NumberNode);
    NumberNode(double val);
    NumberNode() = delete;
    ~NumberNode() override = default;
    double evaluate() const override;

private:
    double stored_value{0.0};
};

#endif // NUMBERNODE_H
