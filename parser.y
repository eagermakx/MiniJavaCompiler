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
     #include "CopyLocation.h"

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
    COMMA	  ","

// Brackets
    LPAREN 	 "("
    RPAREN 	 ")"
    LBRACE 	 "{"
    RBRACE   "}"
    LBRACKET "["
    RBRACKET "]"

// Operators
    op_member 	"."
    op_assign 	"="
    op_sub		"-"
    op_add 		"+"
    op_mul		"*"
    op_div 		"/"
    op_inv		"!"

	op_ge 		">="
    op_le 		"<="
    op_gt 		">"
    op_lt 		"<"
    op_e 		"=="
    op_ne 		"!="

// Keywords
    kw_class 	"class"
    kw_public 	"public"
    kw_static 	"static"
    kw_void 	"void"
    kw_main 	"main"
    kw_System 	"System"
    kw_out 		"out"
    kw_println	"println"
    kw_new		"new"
    kw_length   "length"
    kw_true		"true"
    kw_false	"false"
    kw_return	"return"
    kw_if		"if"
    kw_else		"else"
    kw_while	"while"
    kw_this		"this"

// Types
    t_int	"int"
    t_boolean	"boolean"
;

%token <std::string> IDENTIFIER "identifier"
%token <int> NUMBER "number"
%nterm <Expr::Base*> expression
%nterm <Expr::Id*> var_id
%nterm <Expr::Base*> uniform_expression
// %nterm <Expr::Const*> literal
// %nterm <Expr::rvalue*> rvalue
// %nterm <Expr::lvalue*> lvalue

%nterm <Stmt::Base*> statement
%nterm <Stmt::List*> statements
%nterm <Stmt::VarDecl*> local_var_decl
%nterm <Stmt::Cond*> if_else_stmt

%nterm <ClassField*> class_field
%nterm <ClassMethod*> class_method
%nterm <ClassBody*> decl_list
%nterm <Class*> class_decl
%nterm <MainClass*> main_class_decl

%nterm <Program*> program
%nterm <ProgramBody*> class_decl_list

%nterm <FuncParamList*> parameter_list
%nterm <FuncParameter*> func_parameter
%nterm <CallParamList*> call_param_list

%nterm <Type*> type

%printer { yyo << $$; } <*>;

%expect 1;

%%
%start program;
//program:
//    "class" "identifier" "{" "public" "static" "void" "main" "(" ")" "{" statements "}" "}" { $$ = new Program($11); driver.program = $$; }

program:
	main_class_decl class_decl_list { $$ = new Program($1, $2); driver.program = $$; @$ = @1; };

main_class_decl:
    "class" "identifier" "{" "public" "static" "void" "main" "(" ")" "{" statements "}" "}" { $$ = new MainClass($2, $11); @$ = @1; CopyLocation($$, @1); };

class_decl_list:
	%empty { $$ = new ProgramBody; }
    | class_decl_list class_decl { $1->AddClassDecl($2); $$ = $1; };

class_decl:
	"class" "identifier" "{" decl_list "}" { $$ = new Class($2, $4); @$ = @1; CopyLocation($$, @1); };

decl_list:
	%empty { $$ = new ClassBody; }
	| decl_list class_field { $1->AddField($2); $$ = $1;  }
	| decl_list class_method { $1->AddMethod($2); $$ = $1; };

class_field:
    type "identifier" ";" { $$ = new ClassField($1, $2); @$ = @1; CopyLocation($$, @1); };

class_method:
	"public" type "identifier" "(" parameter_list ")" "{" statements "}" { $$ = new ClassMethod($2, $3, $5, $8); @$ = @1; CopyLocation($$, @1); };

parameter_list:
	%empty { $$ = new FuncParamList; }
	| func_parameter { $$ = new FuncParamList; $$->AddParameter($1); }
	| parameter_list "," func_parameter { $1->AddParameter($3); $$ = $1; };

func_parameter:
	type "identifier" { $$ = new FuncParameter($1, $2); @$ = @1; };

statements:
    %empty { $$ = new Stmt::List(); }
    | statements statement { $1->AddStmt($2); $$ = $1; }

// Strictly speaking, the if else grammar is ambiguous, but precedence of shift over reduce
// solves the problem
// %expect 1 (Above) <- the parser expects to receive 1 shift/reduce conflict

statement:
    "System" "." "out" "." "println" "(" expression ")" ";" { $$ = new Stmt::Print($7); @$ = @1; CopyLocation($$, @1); }
    | local_var_decl { $$ = $1; @$ = @1; CopyLocation($$, @1); }
    | var_id "=" expression ";" { $$ = new Stmt::Assign($1, $3); @$ = @1; CopyLocation($$, @1); };
    | "return" expression ";" { $$ = new Stmt::Ret($2); @$ = @1; CopyLocation($$, @1); }
    | "{" statements "}" { $$ = new Stmt::ScopedList($2); @$ = @1; CopyLocation($$, @1); };
    | if_else_stmt { $$ = $1; @$ = @1; CopyLocation($$, @1); }
    | expression ";" { $$ = new Stmt::ExprStmt($1); @$ = @1; CopyLocation($$, @1); }

if_else_stmt:
    "if" "(" expression ")" statement { $$ = new Stmt::Cond($3, $5, nullptr); @$ = @1; }
    | "if" "(" expression ")" statement "else" statement { $$ = new Stmt::Cond($3, $5, $7); @$ = @1; };

// Set the precedence for binary ops
%left "+" "-";
%left "*" "/";
%left "!";

%nonassoc "<=" ">=" "<" ">" "==" "!=";

expression:
    expression "+" expression { $$ = Expr::BinaryOp::Add($1, $3); @$ = @1; }
    | expression "-" expression { $$ = Expr::BinaryOp::Sub($1, $3); @$ = @1; }
    | expression "*" expression { $$ = Expr::BinaryOp::Mul($1, $3); @$ = @1; }
    | expression "/" expression { $$ = Expr::BinaryOp::Div($1, $3); @$ = @1; }

    | expression "<=" expression { $$ = Expr::BinaryOp::LE($1, $3); @$ = @1; }
    | expression ">=" expression { $$ = Expr::BinaryOp::GE($1, $3); @$ = @1; }
    | expression "<" expression { $$ = Expr::BinaryOp::LT($1, $3); @$ = @1; }
    | expression ">" expression { $$ = Expr::BinaryOp::GT($1, $3); @$ = @1; }
    | expression "==" expression { $$ = Expr::BinaryOp::E($1, $3); @$ = @1; }
    | expression "!=" expression { $$ = Expr::BinaryOp::NE($1, $3); @$ = @1; }

	| "!" expression { $$ = Expr::UnaryOp::Not($2); @$ = @1; }
    | "number" { $$ = new Expr::Const($1); $$->type = new Int(); @$ = @1; }
    | "true" { $$ = new Expr::Const(1); $$->type = new Bool(); @$ = @1; }
    | "false" { $$ = new Expr::Const(0); $$->type = new Bool(); @$ = @1; }
    | uniform_expression { $$ = $1; @$ = @1; };

uniform_expression:
    "(" expression ")" { $$ = $2; @$ = @1; }
    | var_id { $$ = $1; @$ = @1; CopyLocation($$, @1); }
    | "this" { $$ = new Expr::This(); @$ = @1; CopyLocation($$, @1); }
    | "new" "identifier" "(" ")" { $$ = new Expr::New($2); @$ = @1; CopyLocation($$, @1); }
    | uniform_expression "." "identifier" "(" call_param_list ")" { $$ = new Expr::Call($1, $3, $5); @$ = @1; CopyLocation($$, @1); };

call_param_list:
	%empty { $$ = new CallParamList(); }
	| expression { $$ = new CallParamList(); $$->AddParameter($1); }
	| call_param_list "," expression { $1->AddParameter($3); $$ = $1; }

/*method_invocation:
	expression "." "identifier" "(" ")" {};*/

type:
    "int" { $$ = new Int(); @$ = @1; }
    | "boolean" { $$ = new Bool(); @$ = @1; }
    | "identifier" { $$ = new UserType($1); @$ = @1; }
    | "void" { $$ = new Void(); @$ = @1; }

local_var_decl:
    type var_id ";" { $$ = new Stmt::VarDecl($1, $2); @$ = @1; };

var_id:
    "identifier" { $$ = new Expr::Id($1); @$ = @1; };

/*literal:
    "number" { $$ = new Entity::Const($1); }
    | "true" { $$ = new Entity::Const(1); }
    | "false" { $$ = new Entity::Const(0); }*/

/*
lvalue:
    id { $$ = new Expr::lvalue($1); }
    | id "[" expression "]" {};
*/

/*rvalue:
    literal { $$ = new Expr::rvalue($1); }
    | id { $$ = new Expr::rvalue($1); };*/
%%

void
yy::parser::error(const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
}
