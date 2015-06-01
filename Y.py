# -*- coding: UTF8 -*-

import os, sys, time, re

print time.localtime()[:6], sys.argv 

try:
    S = open(sys.argv[1])
except:
    S = open('system.Y')
print 'source file:', S

# однопроходный фортоподобный парсер/интерпретатор

def EndSource():
    'завершение обработки файлов исходника'
    print 'EOF'
    sys.exit(0)

# разделители
Delimiters = ' \t\r\n'

def NextWord():
    'получить следующее слово из входного потока'
    # слово
    w = ''
    while True:
        # чтение следующего символа 
        c = S.read(1)
        # проверка на конец файла
        if not c: EndSource()
        # проверка на разделитель
        if c in Delimiters: break
        # добавляем символ к слову
        w += c
    # рекурсия чтобы не возвращать пустых слов 
    if w:
        return w
    else:
        return NextWord()

# цикл парсера/интерпретатора
while True:
    print '[%s]' % NextWord() 

S.close()
