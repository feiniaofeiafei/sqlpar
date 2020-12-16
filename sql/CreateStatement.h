#ifndef SQLPARSER_SQLSTATEMENT_H
#define SQLPARSER_SQLSTATEMENT_H

#include "SQLStatement.h"
#include "ColumnType.h"

#include <iostream>

// Note: Implementations of constructors and destructors can be found in statements.cpp.
namespace hsql{
    struct SelectStatement;

    //Represents definition of a table column
    struct ColumnDefinition{
        ColumnDefinition(char*name,ColumnType,bool nullable);
        virtual ~ColumnDefinition();

        char* name;
        ColumnType type;
        bool nullable;
    };

    enum CreateType{
        kCreateTable,
        kCreateTableFromtbl, //Hyrise file format
        kCreateView
    };

    //Represents SQL Create statement.
    //Example:"CREATE TABLE students(name TEXT, student_number INTEGER, city TEXT, grade DOUBLE) "
    struct CreateStatement:SQLStatement{
        CreateStatement(CreateType type);
        ~CreateStatement() override;

        CreateType type;
        bool ifNotExists;
        char* filePath;
        char* schema;
        char* tableName;
        std::vector<ColumnDefinition*>* columns;
        std::vector<char*>* viewColumns;
        SelectStatement* select;
    }
}
#endif