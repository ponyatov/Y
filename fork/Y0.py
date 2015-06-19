# -*- coding: UTF8 -*-

import os, sys, time
print sys.argv, time.localtime()[:6]
sys.stdout = open(sys.argv[0]+'.log','w')

class YWorld:
    pass

class YFile:
    def __init__(self, FileName):
        self.FileName = FileName
        self.Handler = open(self.FileName)
    def __del__(self):
        self.Handler.close()
    def read(self):
        return self.Handler.read()

import ply.lex as lex
tokens = ('COMMENT', 'ID', 'N', 'SEMICOLON', 'LCURL', 'RCURL')
t_ignore = '\r \t'
t_COMMENT = r'(//|\#).*'
t_ID = r'[A-Za-z][A-Za-z0-9]*\*{0,1}'
t_SEMICOLON = r';'
t_LCURL = r'\{'
t_RCURL = r'\}'
def t_N(t):
    r'\d+'
    t.value = int(t.value)
    return t
def t_newline(t):
    r'\n+'
    t.lineno += len(t.value)
def t_error(t):
    print >> sys.stderr, 'Y_error:', t
    t.lexer.skip(1)
lex.lex()

import ply.yacc as yacc
def p_main(p):
    '''main : main expr
            | expr '''
def p_expr(p):
    '''expr : COMMENT 
            | ID
            | N
            | LCURL
            | RCURL
            | SEMICOLON '''
    print p
def p_error(p):
     print >> sys.stderr, p
     sys.stderr.flush()
     sys.stdout.flush()
yacc.yacc()

class YLexer:
    def __init__(self, Y):
        if type(Y) == type(''):
            self.YFile = YFile(Y)
        else:
            raise Y
    def go(self):
        yacc.parse(self.YFile.read())
#         lex.input(self.YFile.read())
#         while True:
#             tok = lex.token()
#             if not tok: break
#             print tok
#         yacc.parse()

YLexer('Y.Y').go()
