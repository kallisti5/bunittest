import os
env = Environment(ENV = os.environ)

# enable choosing other compilers
env["CC"] = os.getenv("CC") or env["CC"]
env["CXX"] = os.getenv("CXX") or env["CXX"]
env["ENV"].update(x for x in os.environ.items() if x[0].startswith("CCC_"))

env.Append(CPPPATH = ['#external/tpunitpp'])
env.Append(CXXFLAGS = ['-g'])
env.Append(LINKFLAGS = ['-g'])
env.Append(LIBS = ['be'])

env.StaticLibrary(['#/external/tpunitpp/tpunit++main.cpp'])

Export("env")
SConscript('kits/app/SConscript')
SConscript('kits/network/SConscript')
