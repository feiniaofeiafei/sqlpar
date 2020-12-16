#ifndef SQLPARSER_SELECT_STATEMENT_H
#define SQLPARSER_SELECT_STATEMENT_H

#include "SQLStatement.h"


namespace hsql{
    enum ImportType{
        kImportCSV,
        kImportTbl, //Hyrise file format
        kImportBinary,
        kImportAuto
    }
    //Represents SQL Import statements.
    struct ImportStatement:SQLStatement{
        ImportStatement(ImportType type);
        ~ImportStatement() override;

        ImportType type;
        char* filePath;
        char* schema;
        char* tableName;
    }
} //namespace hsql

#endif