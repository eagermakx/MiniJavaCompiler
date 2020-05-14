//
// Created by Igor Maximov on 04.04.2020.
//

#pragma once

// Basic

#include "Expr/Expr.h"
#include "Stmt/Stmt.h"
#include "Decl/Base.h"

// Extensions

#include "Expr/BinaryOp.h"
#include "Expr/UnaryOp.h"
#include "Expr/Id.h"
#include "Expr/Const.h"
#include "Expr/This.h"
#include "Expr/Call.h"
#include "Expr/New.h"

#include "Stmt/List.h"
#include "Stmt/ScopedList.h"
#include "Stmt/Print.h"
#include "Stmt/Assign.h"
#include "Stmt/Ret.h"
#include "Stmt/VarDecl.h"
#include "Stmt/Cond.h"
#include "Stmt/ExprStmt.h"

#include "Decl/Class.h"
#include "Decl/ClassBody.h"
#include "Decl/ClassField.h"
#include "Decl/ClassMethod.h"
#include "Decl/ProgramBody.h"
#include "Decl/MainClass.h"

#include "Functions/FuncParamList.h"
#include "Functions/CallParamList.h"

#include "Type/Type.h"
#include "Type/Int.h"
#include "Type/Bool.h"
#include "Type/Void.h"
#include "Type/UserType.h"


