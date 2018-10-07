#include "abstractsyntaxtree.h"

/**
 * Calculates the value from an AST (Abstract Syntax Tree). To parse numbers from strings, please use std::stod
 * @return A double representing the calculated value from the expression transformed into an AST
 */
double AbstractSyntaxTree::eval() const {
    // @TODO Your code goes here...
    return eval(root);
}

double AbstractSyntaxTree::eval(Node * root) const{
    if(!root){
      return -1;
    }
    if (!root->left && !root->right){
      return std::stod(root->elem);
    }
    double y = eval(root->right);
    double x = eval(root->left);
    string optr = root->elem;
    string result = std::to_string(x)+optr+std::to_string(y);
    return std::stod(result);
}
