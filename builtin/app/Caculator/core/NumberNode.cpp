#include "NumberNode.h"


NumberNode::NumberNode(double val) : TreeNodeBase(){
    this->stored_value = val;
}

double NumberNode::evaluate() const {
    return stored_value;
}
