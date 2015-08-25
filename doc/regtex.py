import os, sys, time, re
print time.localtime()[:6], sys.argv

REXES = [
         ['../plugin.xml', '../tmp/plugin1.xml', r'<\?.+\?>|<.?plugin>|<extension\s+point=".+">'],
         ['../plugin.xml', '../tmp/org.eclipse.ui.perspectives', r'<extension\s+point="org.eclipse.ui.perspectives".+?</extension>',re.M|re.S]
]

FILES = {}

for i in REXES:
     print i
     S = open(i[0], 'r') ; SRC = S.read() ; S.close()
     R = i[2]
     try:
         FND = re.findall(R, SRC, flags=i[3])
     except IndexError:
         FND = re.findall(R, SRC)
     for j in FND:
        try:
            FILES[i[1]] += [j]
        except KeyError:
            FILES[i[1]] = [j]

for k in FILES:
    T = open(k, 'w')
    for x in FILES[k]: print >> T, x
    T.close()
