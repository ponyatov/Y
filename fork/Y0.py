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
tokens = ('COMMENT', 'ID', 'N', 'COLON', 'LCURL', 'RCURL')
t_ignore = '\r \t'
t_COMMENT = r'(//|\#).*'
t_ID = r'[A-Za-z]\w*\*{0,1}'
t_COLON = r';'
t_LCURL = r'\{'
t_RCURL = r'\}'
def t_N(t):
    r'\d+'
    t.value = int(t.value)
    return t
def t_newline(t):
    r'\n+'
    t.lexer.lineno += len(t.value)
def t_error(t):
    print >> sys.stderr, 'Y_error:', t
    t.lexer.skip(1)
lex.lex()

import ply.yacc as yacc
from Node import *
def p_main(p):
    '''main :
            | main expr'''
    if len(p)==1:
        p[0]=Node('main',[])
    else:
#         if p[1] is None:
#             p[0]=Node('main',[])
        p[0]=p[1].add_parts([p[2]])
def p_expr(p):
    '''expr : comment
            | COLON
            | id
            | N
            | LCURL
            | RCURL'''
    p[0]=Node('expr',[p[1]])
def p_cast(p):
    '''cast : id id'''
    p[0]=Node('CAST',[p[1],p[2]])
def p_comment(p):
    '''comment : COMMENT'''
    p[0]=Node('COMMENT',[p[1]],True)
def p_id(p):
    '''id : ID'''
    p[0]=Node('ID',[p[1]],True)
def p_error(p):
     print >> sys.stderr, p
     sys.stderr.flush()
     sys.stdout.flush()
Yparser=yacc.yacc()
print Yparser.parse(YFile('Y.Y').read())

# lex.input(self.YFile.read())
#     while True:
#         tok = lex.token()
#         if not tok: break
#         print tok
