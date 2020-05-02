%skeleton "lalr1.cc"
%require "3.5"

%defines
%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires {
    #include <string>
    class Scanner;
    class Driver;

    #include "ast_decl.h"

}

// %param { Driver &drv }

%define parse.trace
%define parse.error verbose

%code {

     #include "ast.h"

     #include "driver.hh"
     #include "location.hh"

     static yy::parser::symbol_type yylex(Scanner &scanner, Driver& driver) {
       return scanner.ScanToken();
     }
}

%lex-param { Scanner &scanner }
%lex-param { Driver &driver }
%parse-param { Scanner &scanner }
%parse-param { Driver &driver }

%locations

%define api.token.prefix {TOK_}

%token
// Unable to classify :)
    END 0 "end of file"
    SEMICOLON ";"

// Brackets
    LPAREN "("
    RPAREN ")"
    LBRACE "{"
    RBRACE "}"
    LBRACKET "["
    RBRACKET "]"

// Operators
    op_member 	"."
    op_assign 	"="
    op_sub	"-"
    op_add 	"+"
    op_mul	"*"
    op_div 	"/"
    op_inv	"!"

// Keywords
    kw_class 	"class"
    kw_public 	"public"
    kw_static 	"static"
    kw_void 	"void"
    kw_main 	"main"
    kw_System 	"System"
    kw_out 	"out"
    kw_println	"println"
    kw_new	"new"
    kw_length   "length"
    kw_true	"true"
    kw_false	"false"
    kw_return	"return"
    kw_if	"if"
    kw_else	"else"
    kw_while	"while"

// Types
    t_int	"int"
    t_boolean	"boolean"
;

%token <std::string> IDENTIFIER "identifier"
%token <int> NUMBER "number"
%nterm <Expr::Base*> expression
%nterm <Stmt::Base*> statement
%nterm <Stmt::List*> statements
%nterm <Program*> program
%nterm <Stmt::VarDecl*> var_decl
%nterm <Entity::Id*> id
%nterm <Entity::Const*> literal
%nterm <Expr::rvalue*> rvalue
%nterm <Expr::lvalue*> lvalue
%nterm <Stmt::Cond*> if_else_stmt

%printer { yyo << $$; } <*>;

%expect 1;

%%
%start program;
program:
    "class" "identifier" "{" "public" "static" "void" "main" "(" ")" "{" statements "}" "}" { $$ = new Program($11); driver.program = $$; }

statements:
    %empty { $$ = new Stmt::List(); }
    | statements statement { $1->AddStmt($2); $$ = $1; }

// Strictly speaking, the if else grammar is ambiguous, but precedence of shift over reduce
// solves the problem
// %expect 1 (Above) <- the parser expects to receive 1 shift/reduce conflict

statement:
    "System" "." "out" "." "println" "(" expression ")" ";" { $$ = new Stmt::Print($7); }
    | var_decl { $$ = $1; }
    | lvalue "=" expression ";" { $$ = new Stmt::Assign($1, $3); };
    | "return" expression ";" { $$ = new Stmt::Ret($2); }
    | "{" statements "}" { $$ = $2; };
    | if_else_stmt { $$ = $1; }

if_else_stmt:
    "if" "(" expression ")" statement { $$ = new Stmt::Cond($3, $5, nullptr); }
    | "if" "(" expression ")" statement "else" statement { $$ = new Stmt::Cond($3, $5, $7); };

// Set the precedence for binary ops
%left "+" "-";
%left "*" "/";
%left "!";

expression:
    expression "+" expression { $$ = Expr::BinaryOp::Add($1, $3); }
    | expression "-" expression { $$ = Expr::BinaryOp::Sub($1, $3); }
    | expression "*" expression { $$ = Expr::BinaryOp::Mul($1, $3); }
    | expression "/" expression { $$ = Expr::BinaryOp::Div($1, $3); }

    | rvalue { $$ = $1; }

    | "!" expression { $$ = Expr::UnaryOp::Not($2); }

    | "(" expression ")" { $$ = $2; };

type:
    simple_type;

simple_type:
    "int"
    | "boolean";

var_decl:
    type id ";" { $$ = new Stmt::VarDecl($2); };

id:
    "identifier" { $$ = new Entity::Id($1); };

literal:
    "number" { $$ = new Entity::Const($1); }
    | "true" { $$ = new Entity::Const(1); }
    | "false" { $$ = new Entity::Const(0); }

lvalue:
    id { $$ = new Expr::lvalue($1); };

rvalue:
    literal { $$ = new Expr::rvalue($1); }
    | id { $$ = new Expr::rvalue($1); };
%%

void
yy::parser::error(const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
}
