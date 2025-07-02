#ifndef AST_H
#define AST_H

#include <string>

struct AST
{
    AST* right, * left;
    std::string key;

    AST() : right(NULL), left(NULL), key(NULL) {}
};
#endif