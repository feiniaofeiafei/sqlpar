#ifndef SQLPARSER_SQLSTATEMENT_H
#define SQLPARSER_SQLSTATEMENT_H

#include <vector>
#include "Expr.h"

namespace hsql{
    enum StatementType{
        kStmtError, //unused
        kstmtSelect,
        kstmuImport,
        kStmtInsert,
        kStmtUpdate,
        kStmtDelete,
        kStmtCreate,
        kStmtDrop,
        kStmtPrepare,
        kStmtExport,
        kStmtRename,
        kStmtAlter,
        kStmtShow,
        kStmtTransaction
    };

    //Base struct for every SQL statement
    struct SQLStatement{
        SQLStatement(StatementType type);
        virtual ~SQLStatement();
        StatementType type() const;
        bool isType(StatementType type) const;

        //Shorthand for isType(type).
        bool is(StatementType type) const;

        //Length of the string in the SQL query string
        size_t stringLength;

        std::vector<Expr*>* hints;

        private:
            StatementType type_;    
    };
} //namespace hsql

#endif