#ifndef SQLPARSER_SELECT_STATEMENT_H
#define SQLPARSER_SELECT_STATEMENT_H

#include "SQLStatement.h"
#include "Expr.h"
#include "Table.h"

namespace hsql{
    enum OrderType{
        kOrderAsc,
        kOrderDesc
    };

    enum SetType{
        kSetUnion,
        kSetIntersect,
        kSetExcept
    };
    
    //Description the limit clause within a select statement
    struct LimitDescription{
        LimitDescription(Expr* limit,Expr* offset);
        virtual ~LimitDescription();

        Expr* limit;
        Expr* offset;
    };

    //Description of the group-by clause within a select statement
    struct GroupByDescription{
        GroupByDescription();
        virtual ~GroupByDescription();

        std::vector<Expr*>* columns;
        Expr* having;
    };

    struct WithDescription{
        ~WithDescription();

        char* alias;
        SelectStatement* select;
    };

    struct SetOperation{
        SetOperation();
        virtual ~SetOperation();

        SetType setType;
        bool isAll;

        SelectStatement* nestedSelectStatement;
        std::vector<OrderDescription*>* resultOrder;
        LimitDescription* resultLimit;
    };

    //Representation of a full SQL select statement.
    struct SelectStatement: SQLStatement{
        SelectStatement();
        ~SelectStatement() override;

        TableRef* fromTable;
        bool selectDistinct;
        std::vector<Expr*>* selectList;
        Expr* whereClause;
        GroupByDescription* groupBy;

        std::vector<SetOperation*>* SetOperations;
        std::vector<OrderDescription*>* order;
        LimitDescription* limit;
    };
} //namespace hsql

#endif