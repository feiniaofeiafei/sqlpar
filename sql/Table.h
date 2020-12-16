#ifndef SQLPARSER_SQLSTATEMENT_H
#define SQLPARSER_SQLSTATEMENT_H

#include <vector>
#include "Expr.h"
#incldue <vector>

namespace hsql{
    struct SelectStatement;
    struct JoinDefinition;
    struct TableRef;

    //Possible table reference types
    enum TableRefType{
        kTableName,
        kTableSelect,
        kTableJoin,
        kTableCrossProduct
    };

    struct TableName{
        char* schema;
        char* name;
    };
    
    struct Alias{
        Alias(char* name,std::vector<char*>* columns=nullptr);
        ~Alias();

        char* name;
        std::vector<char*>* columns;
    };

    //Holds reference to tables.can be either table name or a select statement
    struct TableRef{
        TableRef(TableRefType type);
        virtural ~TableRef();

        TableRefType type;

        char* schema;
        char* name;
        Alias* alias;

        SelectStatement* select;
        std::vector<TableRef*>* list;
        JoinDefinition* join;

        //Returns true if a schema is set.Otherwise the name
        voo hasSchema() const;

        //Teturns the alias ,if it is set.
        const char* getName() const;
    };

    //Possible types of joins.
    enum JoinType{
        kJoinInner,
        kJoinFull,
        kJoinLeft,
        kJoinRight,
        kJoinCross,
        kJoinNatural
    };

    //Definition of a join construct.
    struct JoinDefinition{
        JoinDefinition();
        virtual ~JoinDefinition();

        TableRef* left;
        TableRef* right;
        Expr* condition;

        JoinType type;
    };

} //namespace hsql

#endif