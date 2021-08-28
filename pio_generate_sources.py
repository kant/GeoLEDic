#
# Note: this file is only used for the PlatformIO build. CMake has its own way of invoking these scripts,
# see src/programs/CMakeLists.txt
#

import os
from subprocess import Popen, PIPE

builddir = os.getcwd()+"/.pio/build"
gendir = builddir + "/generated"
os.makedirs(gendir,exist_ok=True)

p = Popen(["python3","conf/makeProgramBaseClasses.py",gendir,"--sources"], stdout=PIPE)
sources = p.communicate()

for gensrc in sources[0].decode('utf-8').split(';'):
    print(">> Generating " + gensrc)
    Popen(["python3","conf/makeProgramBaseClasses.py", gensrc])

print(">> Generating ProgramFactory.cpp")
Popen(["python3","conf/makeProgramFactory.py", gendir + "/ProgramFactory.cpp"])
