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

project(MiniJavaCompiler)
set(
    HEADERS
    ${MiniJavaCompiler_SOURCE_DIR}/driver.hh
    ${MiniJavaCompiler_SOURCE_DIR}/parser.hh
    )

BISON_TARGET(
    MyParser
    parser.y
    ${MiniJavaCompiler_SOURCE_DIR}/parser.cpp
    DEFINES_FILE ${MiniJavaCompiler_SOURCE_DIR}/parser.hh
)

FLEX_TARGET(
    MyScanner
    scanner.l
    ${MiniJavaCompiler_SOURCE_DIR}/scanner.cpp
)

ADD_FLEX_BISON_DEPENDENCY(MyScanner MyParser)

add_executable(
    MiniJavaCompiler
    main.cpp
    driver.cpp
    ${BISON_MyParser_OUTPUTS}
    ${FLEX_MyScanner_OUTPUTS}
        Program.h Expr/Expr.h BaseNode.h Expr/BinaryOp.cpp Expr/BinaryOp.h Visitor/Visitor.h Entity/Const.hpp Type/Type.h Entity/Entity.h Entity/Id.h Entity/Id.cpp Stmt/Stmt.h Stmt/Assign.cpp Stmt/Assign.h Stmt/Print.cpp Stmt/Print.h Stmt/VarDecl.cpp Stmt/VarDecl.h Expr/UnaryOp.h Stmt/Ret.cpp Stmt/Ret.h Stmt/List.cpp Stmt/List.h Expr/UnaryOp.cpp ast.h Expr/rvalue.cpp Expr/rvalue.h Expr/lvalue.cpp Expr/lvalue.h Stmt/Cond.cpp Stmt/Cond.h ast_decl.h Visitor/PrintAST.cpp Visitor/PrintAST.h)
target_include_directories(MiniJavaCompiler PRIVATE ${MiniJavaCompiler_SOURCE_DIR})


