import sys
import os
import shutil
import time

# FUNCTIONS ----------------------------------------------------------------------------------------

def HasOption(option):
    for param in sys.argv:
        if param == option:
            return 1
    return 0
    
# MAIN ---------------------------------------------------------------------------------------------

print "Initializing workspace directory..."

ENGINE_PATH = os.getcwd()

if HasOption("mingw"):
    project="codeblocks"
    compiler="mingw"
elif HasOption("vs2012"):
    project="vs2012"
    compiler="vs2012"
    os.putenv("JAM_VS_VERSION", "11.0")
elif HasOption("vs2010"):
    project="vs2010"
    compiler="vs2010"
    os.putenv("JAM_VS_VERSION", "10.0")
elif HasOption("vs2005"):
    project="vs2005"
    compiler="vs2005"
    os.putenv("JAM_VS_VERSION", "8.0")
else:
    project="vs2008"
    compiler="vs2008"
    os.putenv("JAM_VS_VERSION", "9.0")

print "Generate projects..."
def GenerateProject( base_path, project_name ):
    project_path = base_path + project_name + "\\build\\"
    workspace_path = base_path + project_name + "\\workspace\\"
    if not os.path.isdir(workspace_path):
        os.mkdir(workspace_path)
    os.chdir(project_path)
    os.system(ENGINE_PATH+"/tools/jamplus/bin/win32/jam.exe ROOT="+ENGINE_PATH+" COMPILER="+compiler+" --workspace --config=workspace.config --gen="+project+" --compiler="+compiler+" Jamfile.jam temp") 
    os.chdir(ENGINE_PATH)
    os.system("copy "+os.path.abspath(project_path+"temp\\source")+"\\*.cbp "+os.path.abspath(workspace_path))
    os.system("copy "+os.path.abspath(project_path+"temp\\source")+"\\*.vcproj "+os.path.abspath(workspace_path))
    os.system("copy "+os.path.abspath(project_path+"temp\\source")+"\\*.vcxproj "+os.path.abspath(workspace_path))
    os.system("copy "+os.path.abspath(project_path+"temp\\source")+"\\*.vcxproj.filters "+os.path.abspath(workspace_path))
    shutil.rmtree(project_path+"temp")

if not HasOption("plugins"):
    if not HasOption("plugin"):
        GenerateProject("", "externals")
        GenerateProject("", "engine")
        GenerateProject("", "player")
        GenerateProject("", "editor")
        GenerateProject("applications\\", "player")
        GenerateProject("applications\\", "editor")
        GenerateProject("applications\\", "builder")
        GenerateProject("", "unittest")

if HasOption("plugins"):
    for dirname, dirnames, filenames in os.walk("projects\\"):
        for subdirname in dirnames:
            if dirname.find("deploy\\Package")==-1:
                if subdirname.endswith(".plugin"):
                    GenerateProject(dirname+"\\", subdirname)
                elif subdirname.endswith(".editor"):
                    GenerateProject(dirname+"\\", subdirname)
                elif subdirname.endswith(".component"):
                    GenerateProject(dirname+"\\", subdirname)

if HasOption("plugin"):
    GenerateProject(sys.argv[len(sys.argv)-2]+"\\", sys.argv[len(sys.argv)-1])

print "... Done !"
