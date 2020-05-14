cmake_minimum_required(VERSION 3.0)
project(Compilers)

if (CMAKE_HOST_SYSTEM_NAME MATCHES "Darwin")
    execute_process(
            COMMAND brew --prefix bison
            RESULT_VARIABLE BREW_BISON
            OUTPUT_VARIABLE BREW_BISON_PREFIX
            OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    if (BREW_BISON EQUAL 0 AND EXISTS "${BREW_BISON_PREFIX}")
        message(STATUS "Found Bison keg installed by Homebrew at ${BREW_BISON_PREFIX}")
        set(BISON_EXECUTABLE "${BREW_BISON_PREFIX}/bin/bison")
    endif ()

    execute_process(
            COMMAND brew --prefix flex
            RESULT_VARIABLE BREW_FLEX
            OUTPUT_VARIABLE BREW_FLEX_PREFIX
            OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    if (BREW_FLEX EQUAL 0 AND EXISTS "${BREW_FLEX_PREFIX}")
        message(STATUS "Found Flex keg installed by Homebrew at ${BREW_FLEX_PREFIX}")
        set(FLEX_EXECUTABLE "${BREW_FLEX_PREFIX}/bin/flex")
        include_directories(${BREW_FLEX_PREFIX}/include)
    endif ()
endif ()

find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${Compilers_SOURCE_DIR}/bin)

project(jc)
set(
    HEADERS
    ${jc_SOURCE_DIR}/driver.hh
    ${jc_SOURCE_DIR}/parser.hh
    )

BISON_TARGET(
    MyParser
    parser.y
    ${jc_SOURCE_DIR}/parser.cpp
    DEFINES_FILE ${jc_SOURCE_DIR}/parser.hh
)

FLEX_TARGET(
    MyScanner
    scanner.l
    ${jc_SOURCE_DIR}/scanner.cpp
)

ADD_FLEX_BISON_DEPENDENCY(MyScanner MyParser)

add_executable(
    jc
    main.cpp
    driver.cpp
    ${BISON_MyParser_OUTPUTS}
    ${FLEX_MyScanner_OUTPUTS}
        Program.h Expr/Expr.h BaseNode.h Expr/BinaryOp.cpp Expr/BinaryOp.h Visitor/Visitor.h Expr/Id.h Expr/Id.cpp Stmt/Stmt.h Stmt/Assign.cpp Stmt/Assign.h Stmt/Print.cpp Stmt/Print.h Stmt/VarDecl.cpp Stmt/VarDecl.h Expr/UnaryOp.h Stmt/Ret.cpp Stmt/Ret.h Stmt/List.cpp Stmt/List.h Expr/UnaryOp.cpp ast.h Stmt/Cond.cpp Stmt/Cond.h ast_decl.h Visitor/PrintAST.cpp Visitor/PrintAST.h Visitor/Interpreter.h Visitor/Interpreter.cpp log.h SymbolTable/Symbol.cpp SymbolTable/Symbol.h Stmt/ScopedList.cpp Stmt/ScopedList.h Object/ClassObject.h Object/Integer.cpp Object/Integer.h Object/UninitObject.cpp Object/UninitObject.h SymbolTable/VariableScope.cpp SymbolTable/VariableScope.h SymbolTable/ScopeTree.cpp SymbolTable/ScopeTree.h SymbolTable/Table.cpp SymbolTable/Table.h error.h Visitor/SymbolTableBuilder.cpp Visitor/SymbolTableBuilder.h Decl/Base.h Decl/ClassBody.cpp Decl/ClassBody.h Decl/Class.cpp Decl/Class.h Decl/ClassMethod.cpp Decl/ClassMethod.h Decl/ClassField.cpp Decl/ClassField.h Functions/CallFrame.cpp Functions/CallFrame.h Decl/ClassMember.h Decl/ProgramBody.cpp Decl/ProgramBody.h Expr/Const.cpp Expr/Const.h Expr/This.cpp Expr/This.h Visitor/TypeChecker.cpp Visitor/TypeChecker.h Type/Type.h Type/Int.h Type/Bool.h Type/UserType.h Program.cpp Functions/FuncParamList.cpp Functions/FuncParamList.h Functions/FuncParameter.cpp Functions/FuncParameter.h Decl/MainClass.h Decl/MainClass.cpp Type/Void.h SymbolTable/Scope.cpp SymbolTable/Scope.h Type/Type.cpp Object/ClassObject.cpp Object/Object.h Object/Boolean.cpp Object/Boolean.h Type/Types.h Expr/New.cpp Expr/New.h Expr/Call.cpp Expr/Call.h Stmt/ExprStmt.cpp Stmt/ExprStmt.h Object/Object.cpp Functions/CallParamList.cpp Functions/CallParamList.h)
target_include_directories(jc PRIVATE ${jc_SOURCE_DIR})


