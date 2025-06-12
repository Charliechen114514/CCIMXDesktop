#ifndef FUNCTORTREENODE_H
#define FUNCTORTREENODE_H
#include <QString>
#include "TreeNodeBase.h"

class FunctorTreeNode : public TreeNodeBase {
    QString name; ///< name of the function
    TreeNodeBase* argument; ///< nodes factors

public:
    /**
     * @brief Construct a new Functor Tree Node object
     * 
     * @param name  name of the function
     * @param arg nodes factors
     */
    FunctorTreeNode(QString name, TreeNodeBase* arg);
    ~FunctorTreeNode();
    /**
     * @brief evaluate the expressions
     * 
     * @return double 
     */
    double evaluate() const override;
};

#endif // FUNCTORTREENODE_H
