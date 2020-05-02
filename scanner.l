%{
    #include <cerrno>
    #include <climits>
    #include <cstdlib>
    #include <cstring> // strerror
    #include <string>
    #include <iostream>
    #include "driver.hh"
    #include "parser.hh"
%}

%option noyywrap nounput noinput batch debug

%option c++
%option yyclass="Scanner"

%{
  // A number symbol corresponding to the value in S.
  yy::parser::symbol_type make_NUMBER(
    const std::string &s,
    const yy::parser::location_type& loc
  );
%}

id    [a-zA-Z][a-zA-Z_0-9]*
int   [0-9]+
blank [ \t\r]

%{
  // Code run each time a pattern is matched.
  # define YY_USER_ACTION  loc.columns (yyleng);
%}
%%

%{
  // A handy shortcut to the location held by the driver.
  yy::location& loc = driver.location;
  // Code run each time yylex is called.
  loc.step();
%}

{blank}+   loc.step ();
\n+        loc.lines (yyleng); loc.step ();

"class"    return yy::parser::make_kw_class     (loc);
"public"   return yy::parser::make_kw_public    (loc);
"static"   return yy::parser::make_kw_static    (loc);
"void"     return yy::parser::make_kw_void      (loc);
"main"     return yy::parser::make_kw_main      (loc);
"System"   return yy::parser::make_kw_System    (loc);
"out"      return yy::parser::make_kw_out       (loc);
"println"  return yy::parser::make_kw_println   (loc);
"new"      return yy::parser::make_kw_new       (loc);
"length"   return yy::parser::make_kw_length    (loc);
"true"     return yy::parser::make_kw_true      (loc);
"false"    return yy::parser::make_kw_false     (loc);
"return"   return yy::parser::make_kw_return    (loc);
"if"       return yy::parser::make_kw_if        (loc);
"else"     return yy::parser::make_kw_else      (loc);
"while"    return yy::parser::make_kw_while        (loc);

"."        return yy::parser::make_op_member    (loc);
"+"        return yy::parser::make_op_add       (loc);
"-"        return yy::parser::make_op_sub       (loc);
"*"        return yy::parser::make_op_mul       (loc);
"/"        return yy::parser::make_op_div       (loc);
"="        return yy::parser::make_op_assign    (loc);
"!"        return yy::parser::make_op_inv       (loc);

"("        return yy::parser::make_LPAREN       (loc);
")"        return yy::parser::make_RPAREN       (loc);
"{"        return yy::parser::make_LBRACE       (loc);
"}"        return yy::parser::make_RBRACE       (loc);
"["        return yy::parser::make_LBRACKET     (loc);
"]"        return yy::parser::make_RBRACKET     (loc);

"int"      return yy::parser::make_t_int        (loc);

";"        return yy::parser::make_SEMICOLON    (loc);

{int}      return make_NUMBER(yytext, loc);
{id}       return yy::parser::make_IDENTIFIER(yytext, loc);

.          {
                throw yy::parser::syntax_error(loc, "invalid character: " + std::string(yytext));
           }

<<EOF>>    return yy::parser::make_END (loc);
%%

yy::parser::symbol_type make_NUMBER(
  const std::string &s,
  const yy::parser::location_type& loc
) {
  errno = 0;
  long n = strtol(s.c_str(), NULL, 10);
  if (! (INT_MIN <= n && n <= INT_MAX && errno != ERANGE))
    throw yy::parser::syntax_error(loc, "integer is out of range: " + s);
  return yy::parser::make_NUMBER((int) n, loc);
}