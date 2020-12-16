#ifndef SQLPARSER_SQLSTATEMENT_H
#define SQLPARSER_SQLSTATEMENT_H

#include "SQLStatement.h"

// Note:hsqllementations of constructors and destructors can be found in statements.cpp.
namespace hsql
{
    enum DropType{
        kDropTable,
        kDropSchema,
        kDropIndex,
        kDropView,
        kDropPreparedStatement
    };

  // Represents SQL Delete statements.
  // Example "DROP TABLE students;"
  struct DropStatement:SQLStatement{

        DropStatement(DropType type);
        ~DropStatement() override;

        DropType type;
        bool ifExists;
        char* schema;
        char* name;
  }
} // namespace hsql
#endif
