#ifndef SQLPARSER_SQLSTATEMENT_H
#define SQLPARSER_SQLSTATEMENT_H

#include <stdlib.h>
#include <memory>
#include<vector>
#include "ColumnType.h"

namespace hsql{
    //???
    struct SelectStatement;

    //Helper function used by the lexer.
    //TODO: move to more appropriate place.
    char* substr(const char* source, int from, int to);

    enum ExprType{
        kExprLiteralFloat,
        kExprLiteralString,
        kExprLiteralInt,
        kExprLiteralNull,
        kExprStar,
        kExprParameter,
        kExprColumnRef,
        kExprFunctionRef,
        kExprOperator,
        kExprSelect,
        kExprHint,
        kExprArray,
        kExprArrayIndex,
        kExprExtract,
        kExprCast
    };

    //Operator types.These are importment for expressions of type kExprOperator.
    enum OperatorType{
        kOpNone,

        //Ternary operator
        kOpBetween,

        //n-nary special case
        kOpCase,
        kOpCaseListElement,

        //Binary operators.
        kOpPlus,
        kOpMinus,
        kOpAsterisk,
        kOpSlash,
        kOpPercentage,
        kOpCaret,

        kOpEquals,
        kOpNotEquals,
        kOpLess,
        kOpLessEq,
        kOpGreater,
        kOpGreaterEq,
        kOpLike,
        kOpNotLike,
        kOpILike,
        kOpAnd,
        kOpOr,
        kOpIn,
        kOpConcat,

        //Unary operators.
        kOpNot,
        kOpUnaryMinus,
        kOpIsNull,
        kOpExists
    };

    enum DatetimeField{
        kDatetimeNone,
        kDatetimeSecond,
        kDatetimeMinute,
        kDatetimeHour,
        kDatetimeDay,
        kDatetimeMonth,
        kDatetimeYear,
    };

}

#endif