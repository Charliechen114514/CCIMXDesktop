#include "UnaryOpTreeNode.h"


UnaryOpTreeNode::UnaryOpTreeNode(QChar oper, TreeNodeBase *child) : op(oper), operand(child) {}

UnaryOpTreeNode::~UnaryOpTreeNode() { delete operand; }

double UnaryOpTreeNode::evaluate() const {
    double val = operand->evaluate();
    if (op == '-') return -val;
    throw UnSupportedSymbol(op);
}
