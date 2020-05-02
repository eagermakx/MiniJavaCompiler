// A Bison parser, made by GNU Bison 3.5.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2020 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// Undocumented macros, especially those whose name start with YY_,
// are private implementation details.  Do not rely on them.





#include "parser.hh"


// Unqualified %code blocks.
#line 23 "parser.y"


     #include "ast.h"

     #include "driver.hh"
     #include "location.hh"

     static yy::parser::symbol_type yylex(Scanner &scanner, Driver& driver) {
       return scanner.ScanToken();
     }

#line 57 "/Users/igor/Desktop/Compilers/fork/CompilersCourse/02-parsers/parser.cpp"


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

namespace yy {
#line 148 "/Users/igor/Desktop/Compilers/fork/CompilersCourse/02-parsers/parser.cpp"


  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              else
                goto append;

            append:
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
  parser::parser (Scanner &scanner_yyarg, Driver &driver_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      scanner (scanner_yyarg),
      driver (driver_yyarg)
  {}

  parser::~parser ()
  {}

  parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  parser::symbol_number_type
  parser::by_state::type_get () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[+state];
  }

  parser::stack_symbol_type::stack_symbol_type ()
  {}

  parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.type_get ())
    {
      case 44: // literal
        value.YY_MOVE_OR_COPY< Entity::Const* > (YY_MOVE (that.value));
        break;

      case 43: // id
        value.YY_MOVE_OR_COPY< Entity::Id* > (YY_MOVE (that.value));
        break;

      case 38: // expression
        value.YY_MOVE_OR_COPY< Expr::Base* > (YY_MOVE (that.value));
        break;

      case 46: // lvalue
        value.YY_MOVE_OR_COPY< Expr::lvalue* > (YY_MOVE (that.value));
        break;

      case 45: // rvalue
        value.YY_MOVE_OR_COPY< Expr::rvalue* > (YY_MOVE (that.value));
        break;

      case 41: // program
        value.YY_MOVE_OR_COPY< Program* > (YY_MOVE (that.value));
        break;

      case 39: // statement
        value.YY_MOVE_OR_COPY< Stmt::Base* > (YY_MOVE (that.value));
        break;

      case 47: // if_else_stmt
        value.YY_MOVE_OR_COPY< Stmt::Cond* > (YY_MOVE (that.value));
        break;

      case 40: // statements
        value.YY_MOVE_OR_COPY< Stmt::List* > (YY_MOVE (that.value));
        break;

      case 42: // var_decl
        value.YY_MOVE_OR_COPY< Stmt::VarDecl* > (YY_MOVE (that.value));
        break;

      case 36: // "number"
        value.YY_MOVE_OR_COPY< int > (YY_MOVE (that.value));
        break;

      case 35: // "identifier"
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.type_get ())
    {
      case 44: // literal
        value.move< Entity::Const* > (YY_MOVE (that.value));
        break;

      case 43: // id
        value.move< Entity::Id* > (YY_MOVE (that.value));
        break;

      case 38: // expression
        value.move< Expr::Base* > (YY_MOVE (that.value));
        break;

      case 46: // lvalue
        value.move< Expr::lvalue* > (YY_MOVE (that.value));
        break;

      case 45: // rvalue
        value.move< Expr::rvalue* > (YY_MOVE (that.value));
        break;

      case 41: // program
        value.move< Program* > (YY_MOVE (that.value));
        break;

      case 39: // statement
        value.move< Stmt::Base* > (YY_MOVE (that.value));
        break;

      case 47: // if_else_stmt
        value.move< Stmt::Cond* > (YY_MOVE (that.value));
        break;

      case 40: // statements
        value.move< Stmt::List* > (YY_MOVE (that.value));
        break;

      case 42: // var_decl
        value.move< Stmt::VarDecl* > (YY_MOVE (that.value));
        break;

      case 36: // "number"
        value.move< int > (YY_MOVE (that.value));
        break;

      case 35: // "identifier"
        value.move< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

#if YY_CPLUSPLUS < 201103L
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 44: // literal
        value.copy< Entity::Const* > (that.value);
        break;

      case 43: // id
        value.copy< Entity::Id* > (that.value);
        break;

      case 38: // expression
        value.copy< Expr::Base* > (that.value);
        break;

      case 46: // lvalue
        value.copy< Expr::lvalue* > (that.value);
        break;

      case 45: // rvalue
        value.copy< Expr::rvalue* > (that.value);
        break;

      case 41: // program
        value.copy< Program* > (that.value);
        break;

      case 39: // statement
        value.copy< Stmt::Base* > (that.value);
        break;

      case 47: // if_else_stmt
        value.copy< Stmt::Cond* > (that.value);
        break;

      case 40: // statements
        value.copy< Stmt::List* > (that.value);
        break;

      case 42: // var_decl
        value.copy< Stmt::VarDecl* > (that.value);
        break;

      case 36: // "number"
        value.copy< int > (that.value);
        break;

      case 35: // "identifier"
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 44: // literal
        value.move< Entity::Const* > (that.value);
        break;

      case 43: // id
        value.move< Entity::Id* > (that.value);
        break;

      case 38: // expression
        value.move< Expr::Base* > (that.value);
        break;

      case 46: // lvalue
        value.move< Expr::lvalue* > (that.value);
        break;

      case 45: // rvalue
        value.move< Expr::rvalue* > (that.value);
        break;

      case 41: // program
        value.move< Program* > (that.value);
        break;

      case 39: // statement
        value.move< Stmt::Base* > (that.value);
        break;

      case 47: // if_else_stmt
        value.move< Stmt::Cond* > (that.value);
        break;

      case 40: // statements
        value.move< Stmt::List* > (that.value);
        break;

      case 42: // var_decl
        value.move< Stmt::VarDecl* > (that.value);
        break;

      case 36: // "number"
        value.move< int > (that.value);
        break;

      case 35: // "identifier"
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
#if defined __GNUC__ && ! defined __clang__ && ! defined __ICC && __GNUC__ * 100 + __GNUC_MINOR__ <= 408
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
#endif
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    switch (yytype)
    {
      case 35: // "identifier"
#line 102 "parser.y"
                 { yyo << yysym.value.template as < std::string > (); }
#line 537 "/Users/igor/Desktop/Compilers/fork/CompilersCourse/02-parsers/parser.cpp"
        break;

      case 36: // "number"
#line 102 "parser.y"
                 { yyo << yysym.value.template as < int > (); }
#line 543 "/Users/igor/Desktop/Compilers/fork/CompilersCourse/02-parsers/parser.cpp"
        break;

      case 38: // expression
#line 102 "parser.y"
                 { yyo << yysym.value.template as < Expr::Base* > (); }
#line 549 "/Users/igor/Desktop/Compilers/fork/CompilersCourse/02-parsers/parser.cpp"
        break;

      case 39: // statement
#line 102 "parser.y"
                 { yyo << yysym.value.template as < Stmt::Base* > (); }
#line 555 "/Users/igor/Desktop/Compilers/fork/CompilersCourse/02-parsers/parser.cpp"
        break;

      case 40: // statements
#line 102 "parser.y"
                 { yyo << yysym.value.template as < Stmt::List* > (); }
#line 561 "/Users/igor/Desktop/Compilers/fork/CompilersCourse/02-parsers/parser.cpp"
        break;

      case 41: // program
#line 102 "parser.y"
                 { yyo << yysym.value.template as < Program* > (); }
#line 567 "/Users/igor/Desktop/Compilers/fork/CompilersCourse/02-parsers/parser.cpp"
        break;

      case 42: // var_decl
#line 102 "parser.y"
                 { yyo << yysym.value.template as < Stmt::VarDecl* > (); }
#line 573 "/Users/igor/Desktop/Compilers/fork/CompilersCourse/02-parsers/parser.cpp"
        break;

      case 43: // id
#line 102 "parser.y"
                 { yyo << yysym.value.template as < Entity::Id* > (); }
#line 579 "/Users/igor/Desktop/Compilers/fork/CompilersCourse/02-parsers/parser.cpp"
        break;

      case 44: // literal
#line 102 "parser.y"
                 { yyo << yysym.value.template as < Entity::Const* > (); }
#line 585 "/Users/igor/Desktop/Compilers/fork/CompilersCourse/02-parsers/parser.cpp"
        break;

      case 45: // rvalue
#line 102 "parser.y"
                 { yyo << yysym.value.template as < Expr::rvalue* > (); }
#line 591 "/Users/igor/Desktop/Compilers/fork/CompilersCourse/02-parsers/parser.cpp"
        break;

      case 46: // lvalue
#line 102 "parser.y"
                 { yyo << yysym.value.template as < Expr::lvalue* > (); }
#line 597 "/Users/igor/Desktop/Compilers/fork/CompilersCourse/02-parsers/parser.cpp"
        break;

      case 47: // if_else_stmt
#line 102 "parser.y"
                 { yyo << yysym.value.template as < Stmt::Cond* > (); }
#line 603 "/Users/igor/Desktop/Compilers/fork/CompilersCourse/02-parsers/parser.cpp"
        break;

      default:
        break;
    }
    yyo << ')';
  }
#endif

  void
  parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  parser::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser::debug_level_type
  parser::debug_level () const
  {
    return yydebug_;
  }

  void
  parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  bool
  parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::operator() ()
  {
    return parse ();
  }

  int
  parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex (scanner, driver));
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case 44: // literal
        yylhs.value.emplace< Entity::Const* > ();
        break;

      case 43: // id
        yylhs.value.emplace< Entity::Id* > ();
        break;

      case 38: // expression
        yylhs.value.emplace< Expr::Base* > ();
        break;

      case 46: // lvalue
        yylhs.value.emplace< Expr::lvalue* > ();
        break;

      case 45: // rvalue
        yylhs.value.emplace< Expr::rvalue* > ();
        break;

      case 41: // program
        yylhs.value.emplace< Program* > ();
        break;

      case 39: // statement
        yylhs.value.emplace< Stmt::Base* > ();
        break;

      case 47: // if_else_stmt
        yylhs.value.emplace< Stmt::Cond* > ();
        break;

      case 40: // statements
        yylhs.value.emplace< Stmt::List* > ();
        break;

      case 42: // var_decl
        yylhs.value.emplace< Stmt::VarDecl* > ();
        break;

      case 36: // "number"
        yylhs.value.emplace< int > ();
        break;

      case 35: // "identifier"
        yylhs.value.emplace< std::string > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2:
#line 109 "parser.y"
                                                                                            { yylhs.value.as < Program* > () = new Program(yystack_[2].value.as < Stmt::List* > ()); driver.program = yylhs.value.as < Program* > (); }
#line 892 "/Users/igor/Desktop/Compilers/fork/CompilersCourse/02-parsers/parser.cpp"
    break;

  case 3:
#line 112 "parser.y"
           { yylhs.value.as < Stmt::List* > () = new Stmt::List(); }
#line 898 "/Users/igor/Desktop/Compilers/fork/CompilersCourse/02-parsers/parser.cpp"
    break;

  case 4:
#line 113 "parser.y"
                           { yystack_[1].value.as < Stmt::List* > ()->AddStmt(yystack_[0].value.as < Stmt::Base* > ()); yylhs.value.as < Stmt::List* > () = yystack_[1].value.as < Stmt::List* > (); }
#line 904 "/Users/igor/Desktop/Compilers/fork/CompilersCourse/02-parsers/parser.cpp"
    break;

  case 5:
#line 120 "parser.y"
                                                            { yylhs.value.as < Stmt::Base* > () = new Stmt::Print(yystack_[2].value.as < Expr::Base* > ()); }
#line 910 "/Users/igor/Desktop/Compilers/fork/CompilersCourse/02-parsers/parser.cpp"
    break;

  case 6:
#line 121 "parser.y"
               { yylhs.value.as < Stmt::Base* > () = yystack_[0].value.as < Stmt::VarDecl* > (); }
#line 916 "/Users/igor/Desktop/Compilers/fork/CompilersCourse/02-parsers/parser.cpp"
    break;

  case 7:
#line 122 "parser.y"
                                { yylhs.value.as < Stmt::Base* > () = new Stmt::Assign(yystack_[3].value.as < Expr::lvalue* > (), yystack_[1].value.as < Expr::Base* > ()); }
#line 922 "/Users/igor/Desktop/Compilers/fork/CompilersCourse/02-parsers/parser.cpp"
    break;

  case 8:
#line 123 "parser.y"
                              { yylhs.value.as < Stmt::Base* > () = new Stmt::Ret(yystack_[1].value.as < Expr::Base* > ()); }
#line 928 "/Users/igor/Desktop/Compilers/fork/CompilersCourse/02-parsers/parser.cpp"
    break;

  case 9:
#line 124 "parser.y"
                         { yylhs.value.as < Stmt::Base* > () = yystack_[1].value.as < Stmt::List* > (); }
#line 934 "/Users/igor/Desktop/Compilers/fork/CompilersCourse/02-parsers/parser.cpp"
    break;

  case 10:
#line 125 "parser.y"
                   { yylhs.value.as < Stmt::Base* > () = yystack_[0].value.as < Stmt::Cond* > (); }
#line 940 "/Users/igor/Desktop/Compilers/fork/CompilersCourse/02-parsers/parser.cpp"
    break;

  case 11:
#line 128 "parser.y"
                                      { yylhs.value.as < Stmt::Cond* > () = new Stmt::Cond(yystack_[2].value.as < Expr::Base* > (), yystack_[0].value.as < Stmt::Base* > (), nullptr); }
#line 946 "/Users/igor/Desktop/Compilers/fork/CompilersCourse/02-parsers/parser.cpp"
    break;

  case 12:
#line 129 "parser.y"
                                                         { yylhs.value.as < Stmt::Cond* > () = new Stmt::Cond(yystack_[4].value.as < Expr::Base* > (), yystack_[2].value.as < Stmt::Base* > (), yystack_[0].value.as < Stmt::Base* > ()); }
#line 952 "/Users/igor/Desktop/Compilers/fork/CompilersCourse/02-parsers/parser.cpp"
    break;

  case 13:
#line 137 "parser.y"
                              { yylhs.value.as < Expr::Base* > () = Expr::BinaryOp::Add(yystack_[2].value.as < Expr::Base* > (), yystack_[0].value.as < Expr::Base* > ()); }
#line 958 "/Users/igor/Desktop/Compilers/fork/CompilersCourse/02-parsers/parser.cpp"
    break;

  case 14:
#line 138 "parser.y"
                                { yylhs.value.as < Expr::Base* > () = Expr::BinaryOp::Sub(yystack_[2].value.as < Expr::Base* > (), yystack_[0].value.as < Expr::Base* > ()); }
#line 964 "/Users/igor/Desktop/Compilers/fork/CompilersCourse/02-parsers/parser.cpp"
    break;

  case 15:
#line 139 "parser.y"
                                { yylhs.value.as < Expr::Base* > () = Expr::BinaryOp::Mul(yystack_[2].value.as < Expr::Base* > (), yystack_[0].value.as < Expr::Base* > ()); }
#line 970 "/Users/igor/Desktop/Compilers/fork/CompilersCourse/02-parsers/parser.cpp"
    break;

  case 16:
#line 140 "parser.y"
                                { yylhs.value.as < Expr::Base* > () = Expr::BinaryOp::Div(yystack_[2].value.as < Expr::Base* > (), yystack_[0].value.as < Expr::Base* > ()); }
#line 976 "/Users/igor/Desktop/Compilers/fork/CompilersCourse/02-parsers/parser.cpp"
    break;

  case 17:
#line 142 "parser.y"
             { yylhs.value.as < Expr::Base* > () = yystack_[0].value.as < Expr::rvalue* > (); }
#line 982 "/Users/igor/Desktop/Compilers/fork/CompilersCourse/02-parsers/parser.cpp"
    break;

  case 18:
#line 144 "parser.y"
                     { yylhs.value.as < Expr::Base* > () = Expr::UnaryOp::Not(yystack_[0].value.as < Expr::Base* > ()); }
#line 988 "/Users/igor/Desktop/Compilers/fork/CompilersCourse/02-parsers/parser.cpp"
    break;

  case 19:
#line 146 "parser.y"
                         { yylhs.value.as < Expr::Base* > () = yystack_[1].value.as < Expr::Base* > (); }
#line 994 "/Users/igor/Desktop/Compilers/fork/CompilersCourse/02-parsers/parser.cpp"
    break;

  case 23:
#line 156 "parser.y"
                { yylhs.value.as < Stmt::VarDecl* > () = new Stmt::VarDecl(yystack_[1].value.as < Entity::Id* > ()); }
#line 1000 "/Users/igor/Desktop/Compilers/fork/CompilersCourse/02-parsers/parser.cpp"
    break;

  case 24:
#line 159 "parser.y"
                 { yylhs.value.as < Entity::Id* > () = new Entity::Id(yystack_[0].value.as < std::string > ()); }
#line 1006 "/Users/igor/Desktop/Compilers/fork/CompilersCourse/02-parsers/parser.cpp"
    break;

  case 25:
#line 162 "parser.y"
             { yylhs.value.as < Entity::Const* > () = new Entity::Const(yystack_[0].value.as < int > ()); }
#line 1012 "/Users/igor/Desktop/Compilers/fork/CompilersCourse/02-parsers/parser.cpp"
    break;

  case 26:
#line 163 "parser.y"
             { yylhs.value.as < Entity::Const* > () = new Entity::Const(1); }
#line 1018 "/Users/igor/Desktop/Compilers/fork/CompilersCourse/02-parsers/parser.cpp"
    break;

  case 27:
#line 164 "parser.y"
              { yylhs.value.as < Entity::Const* > () = new Entity::Const(0); }
#line 1024 "/Users/igor/Desktop/Compilers/fork/CompilersCourse/02-parsers/parser.cpp"
    break;

  case 28:
#line 167 "parser.y"
       { yylhs.value.as < Expr::lvalue* > () = new Expr::lvalue(yystack_[0].value.as < Entity::Id* > ()); }
#line 1030 "/Users/igor/Desktop/Compilers/fork/CompilersCourse/02-parsers/parser.cpp"
    break;

  case 29:
#line 170 "parser.y"
            { yylhs.value.as < Expr::rvalue* > () = new Expr::rvalue(yystack_[0].value.as < Entity::Const* > ()); }
#line 1036 "/Users/igor/Desktop/Compilers/fork/CompilersCourse/02-parsers/parser.cpp"
    break;

  case 30:
#line 171 "parser.y"
         { yylhs.value.as < Expr::rvalue* > () = new Expr::rvalue(yystack_[0].value.as < Entity::Id* > ()); }
#line 1042 "/Users/igor/Desktop/Compilers/fork/CompilersCourse/02-parsers/parser.cpp"
    break;


#line 1046 "/Users/igor/Desktop/Compilers/fork/CompilersCourse/02-parsers/parser.cpp"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[+yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yy_error_token_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yy_error_token_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  // Generate an error message.
  std::string
  parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    std::ptrdiff_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */
    if (!yyla.empty ())
      {
        symbol_number_type yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];

        int yyn = yypact_[+yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yy_error_token_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char parser::yypact_ninf_ = -60;

  const signed char parser::yytable_ninf_ = -1;

  const signed char
  parser::yypact_[] =
  {
      -5,   -26,     4,     7,   -60,    -3,     3,     5,     6,    22,
      25,    28,   -60,    17,   -60,    24,    30,     1,    34,   -60,
     -60,   -60,   -60,   -60,   -60,    31,   -60,     8,   -60,    26,
     -60,    21,     1,     1,   -60,   -60,   -60,    59,   -60,   -60,
     -60,     1,     1,    42,   -60,    43,    74,   -60,   -60,     1,
       1,     1,     1,    78,    63,   -60,    39,   -60,    -8,    -8,
     -60,   -60,    35,   -60,    54,    36,     1,    35,    89,   -60,
      77,   -60
  };

  const signed char
  parser::yydefact_[] =
  {
       0,     0,     0,     0,     1,     0,     0,     0,     0,     0,
       0,     0,     3,     0,     3,     0,     0,     0,     0,    21,
      22,    24,     4,     6,    28,     0,    10,     0,    20,     0,
       2,     0,     0,     0,    26,    27,    25,     0,    30,    29,
      17,     0,     0,     0,     9,     0,     0,    18,     8,     0,
       0,     0,     0,     0,     0,    23,     0,    19,    14,    13,
      15,    16,     0,     7,     0,    11,     0,     0,     0,    12,
       0,     5
  };

  const signed char
  parser::yypgoto_[] =
  {
     -60,   -31,   -59,    67,   -60,   -60,   -13,   -60,   -60,   -60,
     -60,   -60,   -60
  };

  const signed char
  parser::yydefgoto_[] =
  {
      -1,    37,    22,    13,     2,    23,    38,    39,    40,    25,
      26,    27,    28
  };

  const signed char
  parser::yytable_[] =
  {
      24,    46,    47,    65,     4,    32,    51,    52,    69,     3,
      53,    54,     1,     5,    43,     6,    24,    33,    58,    59,
      60,    61,     7,    14,    15,     8,    10,     9,    34,    35,
      11,    30,    14,    44,    12,    68,    21,    36,    41,    16,
      31,    14,    42,    21,    45,    55,    17,    18,    16,    24,
      19,    20,    21,    56,    24,    17,    18,    16,    66,    19,
      20,    21,    48,    64,    17,    18,    63,    67,    19,    20,
      21,    49,    50,    51,    52,    49,    50,    51,    52,    57,
      71,    29,     0,    62,     0,     0,    49,    50,    51,    52,
      49,    50,    51,    52,    70,     0,     0,     0,     0,     0,
       0,    49,    50,    51,    52
  };

  const signed char
  parser::yycheck_[] =
  {
      13,    32,    33,    62,     0,     4,    14,    15,    67,    35,
      41,    42,    17,     6,    27,    18,    29,    16,    49,    50,
      51,    52,    19,     6,     7,    20,     4,    21,    27,    28,
       5,     7,     6,     7,     6,    66,    35,    36,     4,    22,
      10,     6,    11,    35,    23,     3,    29,    30,    22,    62,
      33,    34,    35,    10,    67,    29,    30,    22,     4,    33,
      34,    35,     3,    24,    29,    30,     3,    31,    33,    34,
      35,    12,    13,    14,    15,    12,    13,    14,    15,     5,
       3,    14,    -1,     5,    -1,    -1,    12,    13,    14,    15,
      12,    13,    14,    15,     5,    -1,    -1,    -1,    -1,    -1,
      -1,    12,    13,    14,    15
  };

  const signed char
  parser::yystos_[] =
  {
       0,    17,    41,    35,     0,     6,    18,    19,    20,    21,
       4,     5,     6,    40,     6,     7,    22,    29,    30,    33,
      34,    35,    39,    42,    43,    46,    47,    48,    49,    40,
       7,    10,     4,    16,    27,    28,    36,    38,    43,    44,
      45,     4,    11,    43,     7,    23,    38,    38,     3,    12,
      13,    14,    15,    38,    38,     3,    10,     5,    38,    38,
      38,    38,     5,     3,    24,    39,     4,    31,    38,    39,
       5,     3
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    37,    41,    40,    40,    39,    39,    39,    39,    39,
      39,    47,    47,    38,    38,    38,    38,    38,    38,    38,
      48,    49,    49,    42,    43,    44,    44,    44,    46,    45,
      45
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,    13,     0,     2,     9,     1,     4,     3,     3,
       1,     5,     7,     3,     3,     3,     3,     1,     2,     3,
       1,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\";\"", "\"(\"", "\")\"",
  "\"{\"", "\"}\"", "\"[\"", "\"]\"", "\".\"", "\"=\"", "\"-\"", "\"+\"",
  "\"*\"", "\"/\"", "\"!\"", "\"class\"", "\"public\"", "\"static\"",
  "\"void\"", "\"main\"", "\"System\"", "\"out\"", "\"println\"",
  "\"new\"", "\"length\"", "\"true\"", "\"false\"", "\"return\"", "\"if\"",
  "\"else\"", "\"while\"", "\"int\"", "\"boolean\"", "\"identifier\"",
  "\"number\"", "$accept", "expression", "statement", "statements",
  "program", "var_decl", "id", "literal", "rvalue", "lvalue",
  "if_else_stmt", "type", "simple_type", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned char
  parser::yyrline_[] =
  {
       0,   109,   109,   112,   113,   120,   121,   122,   123,   124,
     125,   128,   129,   137,   138,   139,   140,   142,   144,   146,
     149,   152,   153,   156,   159,   162,   163,   164,   167,   170,
     171
  };

  // Print the state stack on the debug stream.
  void
  parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  parser::yy_reduce_print_ (int yyrule)
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


} // yy
#line 1483 "/Users/igor/Desktop/Compilers/fork/CompilersCourse/02-parsers/parser.cpp"

#line 172 "parser.y"


void
yy::parser::error(const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
}
