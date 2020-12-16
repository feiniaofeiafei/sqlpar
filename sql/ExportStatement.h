#ifndef SQLPARSER_SELECT_STATEMENT_H
#define SQLPARSER_SELECT_STATEMENT_H

#include "ImportStatement.h"
#include "SQLStatement.h"

namespace hsql{
    //Represens SQL Export statement.
    struct ExportStatement:SQLStatement{
        ExportStatement(ImportType type);
        ~ExportStatement() override;

    //ImportType is used for compatibility reason
    ImportType type;
    char* filePath;
    char* schema;
    char* tableName;
    };
}  //namespace hsql

#endif