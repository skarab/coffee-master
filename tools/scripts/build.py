import sys
import os
import shutil
import datetime
from subprocess import *
import time

# Parse command line

def HasOption(option):
    for param in sys.argv:
        if param == option:
            return 1
    return 0
   
user_project = ""
user_config = "release"
user_mode = "build"
user_platform = "win32"
user_option = ""

if HasOption("workspace"):
    while not os.path.isfile("coffee.jam"):
        os.chdir("..")
    user_project = sys.argv[len(sys.argv)-1]
    if user_project.find("/externals/")>-1:
        user_project = "externals"

ENGINE_PATH = os.getcwd()

def DisplayUsage():
    print "Usage: build.py <project_name,debug,release,clean,full,compiler,platform>"
    print "Available projects :"
    print ". * (or all)"
    print ". externals"
    print ". coffee_engine"
    print ". coffee_player"
    print ". coffee_editor"
    print ". player"
    print ". coffee"
    print ". builder"
    print ". unittest"
    print ". plugins"
    print "Available compiler :"
    print ". mingw"
    print ". vs2005"
    print ". vs2008"
    print ". vs2010"
    print ". vs2012"
    print "Available platform :"
    print ". win32"
    print "Defaulting to simple build in release mode using vs2008"
    exit(0)

# Execute command depending of context

def Exec(cmd):
    if HasOption("jenkins"):
        process = Popen(cmd,shell=True, stdout=PIPE, stderr=PIPE)
        for line in process.stdout:
            print line.rstrip("\n")
        if process.wait()!=0:
            sys.stderr.write("Failed.")
            sys.exit(-1)
    else:
        os.system(cmd);
    
def deleteDir(path):
    cmd = "RMDIR "+ path +" /s /q"
    Exec(cmd)
    while os.path.isdir(path):
        Exec(cmd)
        time.sleep(1)

def createDir(path):
    cmd = "mkdir "+ path
    Exec(cmd)
    while not os.path.isdir(path):
        time.sleep(1)

if HasOption("*"):
    user_project = "*"
if HasOption("all"):
    user_project = "*"    
if HasOption("externals"):
    user_project = "externals"    
if HasOption("coffee_engine"):
    user_project = "engine"
if HasOption("coffee_player"):
    user_project = "player"
if HasOption("coffee_editor"):
    user_project = "editor"
if HasOption("player"):
    user_project = "applications\\player"  
if HasOption("coffee"):
    user_project = "applications\\editor"
if HasOption("builder"):
    user_project = "applications\\builder"      
if HasOption("unittest"):
    user_project = "unittest"

if HasOption("plugins"):
    user_project = "plugins"

if HasOption("debug"):
    user_config = "debug"
if HasOption("Debug"):
    user_config = "debug"
    
if HasOption("full"):
    user_mode = "full"
    if user_project == "":
        user_project = "*"
if HasOption("clean"):
    user_mode = "clean"
    if user_project == "":
        user_project = "*"

if HasOption("mingw"):
	user_compiler="mingw"     
elif HasOption("vs2005"):
	user_compiler="vs2005"
	os.putenv("JAM_VS_VERSION", "8.0")
elif HasOption("vs2010"):
	user_compiler="vs2010"
	os.putenv("JAM_VS_VERSION", "10.0")
elif HasOption("vs2012"):
	user_compiler="vs2012"
	os.putenv("JAM_VS_VERSION", "11.0")
else:
    user_compiler="vs2008"
    os.putenv("JAM_VS_VERSION", "9.0")
    
if user_project == "":        
    DisplayUsage()
    
# Process externals

def ProcessExternClean(path, folder, project_config, project_mode):
    print "Cleaning " + folder + " [" + user_platform + "][" + project_config + "][" + user_mode + "]..."
    os.chdir(path + folder + "\\")
    archive_time = os.path.getmtime('pack.7z') 
    folder_time = archive_time
    if os.path.isdir("pack"):
        folder_time = os.path.getmtime('pack')
    if time.ctime(archive_time)>time.ctime(folder_time):
        if os.path.isdir("pack"):
            deleteDir(path + folder + "\\pack\\")
    if project_mode == "clean" or project_mode == "full":
        libraries_path = "lib\\"+user_platform+"-"+user_compiler+"-"+project_config
        if os.path.isdir(libraries_path):
            deleteDir(path + folder + "\\" + libraries_path)
    if project_mode != "clean" and not os.path.isdir("pack"):
        Exec(ENGINE_PATH+"\\tools\\7z\\7z.exe -y x " + path + folder + "\\pack.7z")

def ProcessExternBuild(path, folder, project_config, project_mode):
    print "Building " + folder + " [" + user_platform + "][" + project_config + "][" + user_mode + "]..."
    os.chdir(path + folder + "\\")
    if os.path.isfile("Jamfile.jam"):
        EXTERN_PATH = os.getcwd();
        postfix = ""
        if project_mode == "clean":
            postfix = " clean"
        if project_mode == "full":
            postfix = " -a"
        if os.path.isdir("pack"):    
            Exec(ENGINE_PATH+"\\tools\\jamplus\\bin\\win32\\jam.exe "+user_option+ " -C" + path + folder + "\\"+" CONFIG=" + project_config + " COMPILER=" + user_compiler + postfix + " ROOT="+ENGINE_PATH)

def ProcessExternalsDirectories(path, project_config, project_mode):
    for folder in os.listdir(path):
        if os.path.isfile(path + folder + "\\pack.7z"):
            ProcessExternClean(path, folder, project_config, project_mode)
    for folder in os.listdir(path):
        if os.path.isfile(path + folder + "\\pack.7z"):
            ProcessExternBuild(path, folder, project_config, project_mode)
    if project_mode=="clean":
        for folder in os.listdir(path):
            if os.path.isdir(path + folder + "\\pack"):
                deleteDir(path + folder + "\\pack\\")      
            if os.path.isdir(path + folder + "\\lib"):
                deleteDir(path + folder + "\\lib\\")      
        if os.path.isdir(path + "..\\lib"):
            deleteDir(path + "..\\lib\\")      

def ProcessExternals(project_config, project_mode):
    print "Processing external libraries..."
    ProcessExternalsDirectories(ENGINE_PATH + "\\externals\\source\\", project_config, project_mode)
    os.chdir(ENGINE_PATH)

# Process project

def ProcessProject(project_name, project_config, project_mode):
    print "Processing " + project_name + " [" + user_platform + "][" + project_config + "][" + user_mode + "]..."
    binaries_path = "binaries\\"+user_platform+"-"+user_compiler+"-"+project_config
    if not os.path.isdir(binaries_path):
        createDir(binaries_path)
    postfix = ""
    if project_mode == "clean":
        postfix = " clean"
        Exec("del /s/q "+project_name+"\\"+binaries_path+"\\*.obj")
    if project_mode == "full":
        postfix = " -a"
    project_path = project_name+"\\build\\"
    os.chdir(project_path)
    Exec(ENGINE_PATH+"/tools/jamplus/bin/win32/jam.exe "+user_option+ " CONFIG="+project_config+" COMPILER="+user_compiler+postfix + " ROOT="+ENGINE_PATH)
    os.chdir(ENGINE_PATH)

# Process !

def ProcessUnitTest(the_config, the_mode):
    ProcessProject("unittest", the_config, the_mode)
    if user_mode!="clean":
        print "Running unittest..."
        binaries_path = ENGINE_PATH+"\\binaries\\"+user_platform+"-"+user_compiler+"-"+the_config
        if os.path.isdir(binaries_path):
            os.chdir(binaries_path);
            if os.path.isfile(binaries_path+"\\unittest.exe"):
                Exec(binaries_path+"\\unittest.exe")
            os.chdir(ENGINE_PATH)

def ProcessPlugins(the_config, the_mode):
    for dirname, dirnames, filenames in os.walk(ENGINE_PATH + "\\" + "projects\\"):
        for subdirname in dirnames:
            if dirname.find("deploy\\Package")==-1:
                path = os.path.join(dirname, subdirname)
                if subdirname.endswith(".plugin"):
                    ProcessProject(path, the_config, the_mode)
                elif subdirname.endswith(".editor"):
                    ProcessProject(path, the_config, the_mode)
                elif subdirname.endswith(".component"):
                    ProcessProject(path, the_config, the_mode)
            
def Process(the_project, the_config, the_mode):
    if the_project=="*":
        ProcessExternals(the_config, the_mode)
        Process("engine", the_config, the_mode)
        Process("player", the_config, the_mode)
        Process("editor", the_config, the_mode)
        Process("applications\\player", the_config, the_mode)
        Process("applications\\editor", the_config, the_mode)
        Process("applications\\builder", the_config, the_mode)
        ProcessUnitTest(user_config, user_mode)
        Process("plugins", the_config, the_mode)
    else:
        if the_project=="externals":
            ProcessExternals(the_config, the_mode)
        elif the_project=="unittest":
            ProcessUnitTest(user_config, user_mode)
        if the_project=="plugins":
            ProcessPlugins(the_config, the_mode)
        elif not (the_project=="externals"):
            ProcessProject(the_project, the_config, the_mode)

Process(user_project, user_config, user_mode)
            
print "...Done!"
