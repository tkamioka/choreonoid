#include "MprStatement.h"
#include "MprProgram.h"
#include "MprBasicStatements.h"

using namespace std;
using namespace cnoid;

MprStatementClassRegistry& MprStatementClassRegistry::instance()
{
    static MprStatementClassRegistry registry;
    return registry;
}


MprStatementClassRegistry::MprStatementClassRegistry()
{

}


PolymorphicMprStatementFunctionSet::PolymorphicMprStatementFunctionSet()
    : PolymorphicFunctionSet<MprStatement>(MprStatementClassRegistry::instance())
{

}


MprStatement::MprStatement()
{
    classId_ = -1;
}


MprStatement::MprStatement(const MprStatement& org)
    : MprStatement()
{

}


MprStatement::~MprStatement()
{

}


void MprStatement::validateClassId() const
{
    classId_ = MprStatementClassRegistry::instance().classId(this);
}


MprProgram* MprStatement::holderProgram() const
{
    return holderProgram_.lock();
}


MprStructuredStatement* MprStatement::holderStatement() const
{
    if(auto program = holderProgram_.lock()){
        return program->holderStatement();
    }
    return nullptr;
}


MprProgram* MprStatement::topLevelProgram() const
{
    auto program = holderProgram();
    if(!program){
        return nullptr;
    }
    return program->topLevelProgram();
}


MprProgram* MprStatement::getLowerLevelProgram()
{
    return nullptr;
}


void MprStatement::notifyUpdate()
{
    if(auto holder = holderProgram()){
        holder->notifyStatementUpdate(this);
    }
}


