# -*- coding: UTF8 -*-

import os, sys, time
print sys.argv, time.localtime()[:6]

World = {}

class YFile:
    def __init__(self, FileName):
        self.FileName = FileName
        self.Handler = open(self.FileName)
    def __del__(self):
        self.Handler.close()

class YLexer:
    def __init__(self, Y):
        if type(Y) == type(''):
            self.YFile = YFile(Y)
        else:
            raise Y
    def go(self):
        pass

YLexer('Y.Y').go()
