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
      return 0;
    }
    if (!root->left && !root->right){
      return std::stod(root->elem);
    }
    if (root->elem == "+"){
      return eval(root->left) + eval(root->right);
    }
    else if (root->elem == "-"){
      return eval(root->left)-eval(root->right);
    }
    else if (root->elem == "*"){
      return eval(root->left) * eval(root->right);
    }
    else if (root->elem == "/"){
      return eval(root->left) / eval(root->right);
    }
    return 0;
  }
