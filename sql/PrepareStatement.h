#ifndef SQLPARSER_INSERT_STATEMENT_H
#define SQLPARSER_INSERT_STATEMENT_H

#include "SQLStatement.h"

namespace hsql{
    //Represents SQL Prepare statements.
    //Example:PREPARE test FROM 'SELECT * FROM test WHERE A = ?;'
    struct PrepareStatement:SQLStatement{
        PrepareStatement();
        ~PrepareStatement() override;

        char* name;

        //The query that is supposed to be prepared.
        char* query;
    };
}

#endif




