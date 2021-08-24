import os
from subprocess import Popen, PIPE

builddir = os.getcwd()+"/.pio/build"
gendir = builddir + "/generated"
os.makedirs(gendir,exist_ok=True)

print (gendir)

p = Popen(["python3","conf/makeProgramBaseClasses.py",gendir,"--sources"], stdout=PIPE)
sources = p.communicate()

print(sources)

for gensrc in sources[0].decode('utf-8').split(';'):
    print(">> Generating " + gensrc)
    Popen(["python3","conf/makeProgramBaseClasses.py",gensrc])
