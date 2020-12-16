#ifndef SQLPARSER_SELECT_STATEMENT_H
#define SQLPARSER_SELECT_STATEMENT_H

#include "SQLStatement.h"

// Note:Implementations of constructors and destructor can be found in statements.cpp
namespace hsql{
    //Represents SQL Delete statements.
    //Example:"DELETE FROM students WHERE grade>3;"
    struct DeleteStatement:SQLStatement{
        DeleteStatement();
        ~DeleteStatement() override;

        char* schema;
        char* tableName;
        Expr* expr;
    };
} //namespace hsql

#endif