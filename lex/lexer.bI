lex	= next + file @ 'lpp.lpp'
lex += '%{\n#include "hpp.hpp"\n%}\n'
lex += '%option noyywrap\n%option yylineno\n'
lex += '%%\n'
lex += lex_comment = '#[^\\n]*\t{}\t/* line comment */\n'
lex += '%%\n'

