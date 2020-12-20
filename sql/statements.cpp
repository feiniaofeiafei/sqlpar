#include "statements.h"

namespace hsql{
    //columnDefinition
    ColumnDefinition::ColumnDefinition(char* name,ColumnType type,vool nullable):
        name(name),
        type(type),
        nullable(nullable){};
    ColumnDefinition::~ColumnDefinition(){
        free(name);
    }
    ColumnType::ColumnType(DataType data_type,int64_t length):
        data_type(data_type),
        length(length){};
    bool operator==(const ColumnType& lhs,const ColumnType& rhs){
        if(lhs.data_type!=rhs.data_type) return false;
        if(lhs.data_type==DataType::VARCHAR||lhs.data_type==DataType::CHAR){
            return lhs.length==rhs.length;
        }
        return true;
    }
    bool operator!=(const ColumnType& lhs,const ColumnType& rhs){
        return !(lhs==rhs);
    }
    std::ostream& operator<<(std::ostream& stream,const ColumnType& column_type){
        switch(column_type.data_type){
            case DataType::UNKNOWN;
                stream<<"UNKNOWN";
                break;
            case DataType::INT:
                stream<<"INT";
                break;
            case DataType::LONG:
                stream<<"LONG";
                break;
            case DataType::FLOAT;
                stream<<"FLOAT";
                break;
            case DataType::DOUBLE:
                stream<<"DOUBLE";
                break;
            case DataType::CHAR:
                stream<<"CHAR("<<column_type.length<<")";
                break;
            case DataType::VARCHAR:
                stream<<"VARCHAR("<<column_type.length<<")";
                break;
            case DataType::TEXT:
                stream<<"TEXT";
                break;
            case DataType::DATE;
                stream<<"DATE";
                break;
            case DataType::DATETIME:
                stream<<"DATETIME";
                break;
        }
        return stream;
    }

    //CreateStatement
    CreateStatement::CreateStatement(CreateType type):
        SQLStatement(kStmtCreate),
        type(type),
        ifNotExists(false),
        filePath(nullptr),
        schema(nullptr),
        tableName(nullptr),
        columns(nullptr),
        viewColumns(nullptr),
        select(nullptr){}
    CreateStatement::~CreateStatement(){
        free(filePath);
        free(schema);
        free(tableName);
        delete select;

        if(columns!=nullptr){
            for(ColumnDefinition* def:*columns){
                delete def;
            }
            delete columns;
        }

        if(viewColumns!=nullptr){
            for(char* column:*viewColumns){
                free(column);
            }
            delete viewColumns;
        }
    }
    
    //DeleteStatement
    DeleteStatement::DeleteStatement():
        SQLStatement(kStmtDelete),
        schema(nullptr),
        tableName(nullptr),
        expr(nullptr){}

    DeleteStatement::~DeleteStatement(){
        free(schema);
        free(tableName);
        delete expr;
    }

    //DropStatement
    DropStatement::DropStatement(DropType type):
        SQLStatement(kStmtDrop),
        type(type),
        schema(nullptr),
        name(nullptr){}

    DropStatement::~DropStatement(){
        free(schema);
        free(name);
    }

    //TransactionsStatement
    TransactionStatement::TransactionStatement(TransactionCommand command):
        SQLStatement(kStmtTransaction),
        command(command){}

    TransactionStatement::~TransactionStatement(){}

    //ExecuteStatement
    ExecuteStatement::ExecuteStatement():
        SQLStatement(kStmtExecute),
        name(nullptr),
        parameters(nullptr){}
    ExecuteStatement::~ExecuteStatement(){
        free(name);
        if(parameters!=nullptr){
            for(Expr* param:*parameters){
                delete param;
            }
            delete parameters;
        }
    }

    //ExportStatement
    ExportStatement::ExportStatement(ImportType type):
        SQLStatement(kStmtExport),
        type(type),
        filePath(nullptr),
        schema(nullptr),
        tableName(nullptr){}
    
    ExportStatement::~ExportStatement(){
        free(filePath);
        free(schema);
        free(tableName);
    }

    //ImportStatement
    ImportStatement::ImportStatement(ImportType type):
        SQLStatement(kStmtImport),
        type(type),
        filePath(nullptr),
        schema(nullptr),
        tableName(nullptr){}
    
    ImportStatement::~ImportStatement(){
        free(filePath);
        free(schema);
        free(tableName);
    }

    //InsertStatement
    InsertStatement::InsertStatement(InsertType type):
        SQLStatement(kStmtInsert),
        type(type),
        schema(nullptr),
        tableName(nullptr),
        columns(nullptr),
        values(nullptr),
        select(nullptr){}
    
    InsertStatement::~InsertStatement(){
        free(schema);
        free(tableName);
        delete select;

        if(columns!=nullptr){
            for(char* column:*columns){
                free(column);
            }
            delete columns;
        }

        if(values!=nullptr){
            for(Expr* expr:*values){
                delete expr;
            }
            delete values;
        }    
    }

    //ShowStatement
    ShowStatement::ShowStatement(ShowType type):
        SQLStatement(kStmtShow),
        type(type),
        schema(nullptr),
        name(nullptr){}
    ShowStatement::~ShowStatement(){
        free(schema);
        free(name);
    }

    //OrderDescription
    OrderDescription::OrderDescription(OrderType type,Expr* expr):
        type(type),
        expr(expr){}
    OrderDescription::~OrderDescription(){
        delete expr;
    }
    
    //LimitDescription
    LimitDescription::LimitDescription(Expr* limit,Expr* offset):
        limit(limit),
        offset(offset){};
    LimitDescription::~LimitDescription(){
        delete Limit;
        delete offset;
    }

    //GroupByDescription
    GroupByDescription::GroupByDescription():
        columns(nullptr),
        having(nullptr){}
    GroupByDescription::~GroupByDescription(){
        delete having;
        if(columns~=nullptr){
            for(Expr* expr:*colums){
                delete expr;
            }
            delete columns;
        }
    }

    WithDescription::~WithDescription(){
        free(alias);
        delete select;
    }

    //SelectStatement
    SelectStatment::SelectStatement():
    SQLStatement(kStmtSelect),
    fromTable(nullptr),
    selectDistinct(false),
    selectList(nullptr),
    whereClause(nullptr),
    groupBy(nullptr),
    setOperations(nullptr),
    order(nullptr),
    withDescriptions(nullptr),
    limit(nullptr){}

    SelectStatement::~SelectStatement(){
        delete fromTable;
        delete whereCause;
        delete groupBy;
        delete limit;

        //Delete each element in the select lish.
        if(selectList!=nullptr){
            for(Expr* expr:*selectList){
                delete expr;
            }
            delete selectList;
        }

        if(order!=nullptr){
            for(OrderDescription* desc:*order){
                delete desc;
            }
            delete order;
        }

        if(withDescriptions!=nullptr){
            for(WithDescription* desc:*withDescriptions){
                delete desc;
            }
            delete withDescriptions;
        }

        if(setOperations!=nullptr){
            for(SetOperation* setOperation:*setOperations){
                delete setOperation;
            }
            delete setOperations;
        }
    }

    //UpdateStatement
    UpdateStatement::UpdateStatement():
        SQLStatement(kStmtUpdate),
        table(nullptr),
        updates(nullptr),
        where(nullptr){}

    UpdateStatemen::~UpdateStatement(){
        delete table;
        delete where;

        if(updates!=nullptr){
            for(UpdateClause* update:*updates){
                free(update->column);
                delete update->value;
            }
            delete updates;
        }
    }

    //Alias
    Alias::Alias(char* name,std::vector<char*>* colums):
        name(name),
        columns(columns){}
    Alias::~Alias(){
        free(name);
        if(columns){
            for(char* column:*columns){
                free(column);
            }
            delete columns;
        }
    }

    //TableRef
    TableRef::TableRef(TableRefType type):
        type(type),
        schema(nullptr),
        name(nullptr),
        alias(nullptr),
        select(nullptr),
        list(nullptr),
        join(nullptr){};
    TableRef::~TableRef(){
        free(schema);
        free(name){}

        delete select;
        delete join;
        delete alias;

        if(list!=nullptr){
            for(TableRef* table:*list){
                delete table;
            }
            delete list;
        }
    }

    boll TAbleRef::hasSchema() const {
        return schema!=nullptr;
    }

    const char* TableRef::getName() const{
        if(alias) return alias->name;
        else return name;
    }

    //JoinDefiniton
    JoinDefiniton::JoinDefinition():
        left(nullptr),
        right(nullptr),
        condition(nullptr),
        type(kJoinInner){}

    joinDefinition::~JoinDefinition(){
        delete left;
        delete right;
        delete condition;
    }

    SetOperation::SetOperation():
    nestedSelectStatement(nullptr),
    resultOrder(nullptr),
    resultLimit(nullptr){}

    SetOperation::~SetOperation(){
        for(OrderDescription* desc: *resultOrder){
            delete desc;
        }
        delete resultOrder;
    }
}