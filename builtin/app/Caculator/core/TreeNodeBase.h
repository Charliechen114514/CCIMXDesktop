#ifndef TREENODEBASE_H
#define TREENODEBASE_H
/**
 * @brief Tree Node is expected to be like this!
 */
struct TreeNodeBase
{
    virtual ~TreeNodeBase() = default;
        /**
     * @brief evaluate the expressions
     * 
     * @return double 
     */
    virtual double evaluate() const = 0;
};

#endif // TREENODEBASE_H
