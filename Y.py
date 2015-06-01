# -*- coding: UTF8 -*-

import os, sys, time, re
print time.localtime()[:6], sys.argv 

# открываем исходник на чтение
try:
    S = open(sys.argv[1])
except:
    S = open('system.Y')
print 'source file:', S

# набор языковых объектов

def comment():
    'отработка комментария'
    while S.read(1) != '\n': pass
    
def dump():
    'сброс распечатки пула и стека в файл'
    F = open(NextWord(), 'w')
    print >>F, time.localtime()[:6]
    print >>F, 'Stack:'
    for i in Stack: print >> F, '\t',i
    print >>F, 'World:'
    for i in World: print >> F, '\t',i,'\t',World[i]
    F.close()

# однопроходный фортоподобный парсер/интерпретатор

def SourceEOF():
    'завершение обработки файлов исходника'
    print 'EOF'
    sys.exit(0)
    
# рабочий стек

Stack = []

# пул объектов: World

World = {
    '#':comment,
    'dump':dump,
    'end':SourceEOF
   }

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
        if not c: SourceEOF()
        # проверка на разделитель
        if c in Delimiters: break
        # проверка на комментарий
        if c == '#': return '#'
        # добавляем символ к слову
        w += c
    # рекурсия чтобы не возвращать пустых слов 
    if w:
        return w
    else:
        return NextWord()

# цикл парсера/интерпретатора: выполнение объектов по имени из пула
while True: World[NextWord()]() 

S.close()
