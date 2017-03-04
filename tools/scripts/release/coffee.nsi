!ifdef HAVE_UPX
!packhdr tmp.dat "upx\upx -9 tmp.dat"
!endif

!ifdef NOCOMPRESS
SetCompress off
!endif

;--------------------------------

Name "Coffee"
Caption "Coffee"
Icon "coffee.ico"
OutFile "coffee.exe"

SetDateSave on
SetDatablockOptimize on
CRCCheck on
SilentInstall normal
XPStyle on

InstallDir "C:\Coffee"
InstallDirRegKey HKLM "Software\Coffee" "Install_Dir"

CheckBitmap "${NSISDIR}\Contrib\Graphics\Checks\classic-cross.bmp"

LicenseText "Please read the following License Agreement. You must accept the terms of this agreement before continuing with the installation."
LicenseData "coffee_license.txt"

RequestExecutionLevel user

;--------------------------------

Page license
Page components
Page directory
Page instfiles

UninstPage uninstConfirm
UninstPage instfiles

;--------------------------------

AutoCloseWindow false
ShowInstDetails show
ShowUninstDetails show

;--------------------------------

Function .onInit
    InitPluginsDir
    File /oname=$PLUGINSDIR\logo.bmp "logo.bmp"
    advsplash::show 1000 500 351 -1 $PLUGINSDIR\logo
    Pop $0
    Delete $PLUGINSDIR\logo.bmp
FunctionEnd

;--------------------------------

Section ""

  ; write reg info
  WriteRegStr HKLM SOFTWARE\Coffee "Install_Dir" "$INSTDIR"

  ; write uninstall strings
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Coffee" "DisplayName" "Coffee (remove only)"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Coffee" "UninstallString" '"$INSTDIR\coffee-uninst.exe"'

  SetOutPath $INSTDIR
  
  WriteUninstaller "coffee-uninstall.exe"

SectionEnd

Section "Install Source"

    SetOutPath $INSTDIR
    File /r /x "workspace" /x "tmp" /x "*.log" /x "*.ilk" /x "*.exp" /x "*.o" /x ".git" /x "*.ncb" /x "*.gitignore" /x "documentation" /x "projects" "..\..\..\"

SectionEnd

Section "Generate Binaries"
    
    ExecWait "$INSTDIR\tools\builder\builder.exe"

SectionEnd

Section "Create Shortcuts"

  SetOutPath $INSTDIR
  SetShellVarContext current
  
  CreateDirectory "$SMPROGRAMS\Coffee"
  
  CreateShortCut "$SMPROGRAMS\Coffee\Coffee Folder.lnk" "$INSTDIR\"
  CreateShortCut "$SMPROGRAMS\Coffee\Coffee Online.lnk" "http://www.coffee3d.net"
  CreateShortCut "$SMPROGRAMS\Coffee\Coffee Online API.lnk" "http://www.coffee3d.net/api/"
  
  CreateShortCut "$SMPROGRAMS\Coffee\Coffee Builder.lnk" "$INSTDIR\tools\builder\builder.exe"

  CreateDirectory "$SMPROGRAMS\Coffee\Solutions"  
  CreateShortCut "$SMPROGRAMS\Coffee\Solutions\Coffee Visual Studio 2005.lnk" "$INSTDIR\solutions\coffee_vs2005.sln"
  CreateShortCut "$SMPROGRAMS\Coffee\Solutions\Coffee Visual Studio 2008.lnk" "$INSTDIR\solutions\coffee_vs2008.sln"
  CreateShortCut "$SMPROGRAMS\Coffee\Solutions\Coffee Visual Studio 2010.lnk" "$INSTDIR\solutions\coffee_vs2010.sln"
  CreateShortCut "$SMPROGRAMS\Coffee\Solutions\Coffee Visual Studio 2012.lnk" "$INSTDIR\solutions\coffee_vs2012.sln"
  CreateShortCut "$SMPROGRAMS\Coffee\Solutions\Coffee MinGW-CodeBlocks.lnk" "$INSTDIR\solutions\coffee_mingw.workspace"

  CreateShortCut "$SMPROGRAMS\Coffee\Uninstall Coffee.lnk" "$INSTDIR\coffee-uninstall.exe"

SectionEnd

Section "Open binaries folder"
    
  ExecShell open "$INSTDIR\binaries\"

SectionEnd

;--------------------------------

; Uninstaller

UninstallText "This will uninstall Coffee. Project files will be removed as well. Hit next to continue."
UninstallIcon "${NSISDIR}\Contrib\Graphics\Icons\nsis1-uninstall.ico"

Section "Uninstall"

  SetShellVarContext current
  
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Coffee"
  Delete "$INSTDIR\coffee-uninstall.exe"
  RMDir /r "$SMPROGRAMS\Coffee"
  RMDir /r "$INSTDIR"

SectionEnd
