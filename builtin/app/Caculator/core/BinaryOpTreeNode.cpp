#include "BinaryOpTreeNode.h"
#include <QMap>

static const QMap<QString, std::function<double(double, double)>> mappings = {
    { "+", [](double a, double b) -> double { return a + b; } },
    { "-", [](double a, double b) -> double { return a - b; } },
    { "*", [](double a, double b) -> double { return a * b; } },
    { "/", [](double a, double b) -> double { return b != 0 ? a / b : throw DivideZeroException(); } },
    { "^", [](double a, double b) -> double { return std::pow(a, b); } }
};
BinaryOpTreeNode::BinaryOpTreeNode(QChar op, TreeNodeBase* left_hand, TreeNodeBase* right_hand)
    : TreeNodeBase() {
    this->op = op;
    this->left_hand = left_hand;
    this->right_hand = right_hand;
}

BinaryOpTreeNode::~BinaryOpTreeNode() {
    delete left_hand;
    delete right_hand;
}

double BinaryOpTreeNode::evaluate() const {
    double l = left_hand->evaluate();
    double r = right_hand->evaluate();
    auto it = mappings.find(op);
    if (it != mappings.end()) {
        return it.value()(l, r);
    }
    throw UnSupportedSymbol(op);
}
