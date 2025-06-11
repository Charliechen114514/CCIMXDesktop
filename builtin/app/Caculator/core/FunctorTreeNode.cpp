#include "FunctorTreeNode.h"
#include "ParseExceptions.h"
#include <QMap>
static QMap<QString, std::function<double(double)>> functors = {
    { "sin", [](double x) { return std::sin(x); } },
    { "cos", [](double x) { return std::cos(x); } },
    { "tan", [](double x) { return std::tan(x); } },
    { "sqrt", [](double x) {
         if(x < 0){
            throw BadSqrtValue();
         }
        return std::sqrt(x); } },
    { "log", [](double x) { return std::log(x); } },
    { "exp", [](double x) { return std::exp(x); } }
};

FunctorTreeNode::FunctorTreeNode(QString name, TreeNodeBase* arg)
    : name(name)
    , argument(arg) { }

FunctorTreeNode::~FunctorTreeNode() {
    delete argument;
}

double FunctorTreeNode::evaluate() const {
    double val = argument->evaluate();
    auto it = functors.find(name);
    if (it != functors.end()) {
        return it.value()(val);
    }
    throw UnSupportiveFunction(name);
}
