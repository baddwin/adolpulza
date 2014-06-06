#Copy this file into release build folder, then run NSIS and open this file

#Hide All NSIS Windows
WindowIcon Off
#Enable silent mode
SilentInstall Silent
#AutoClose after exit
AutoCloseWindow True
#package icon
Icon "icon-hi.ico"
#package exe name
OutFile AdolPulza_beta.exe

RequestExecutionLevel user

Section
	#create a directory for the app in TEMP
	StrCpy $INSTDIR $TEMP\AdPulza
	
	#Use that directory created in TEMP as the working directory
	SetOutPath $INSTDIR
	
	#Files to be included in the package
	File "AdolPulza.exe"
	File "Qt5Core.dll"
	File "Qt5Gui.dll"
	File "Qt5Widgets.dll"
	File "adolpulza.sqlite"
	File /r "plugins"
	
	#change some attributes
	#SetFileAttributes "$INSTDIR\libEGL.dll" SYSTEM|HIDDEN  
	#SetFileAttributes "$INSTDIR\libGLESv2.dll" SYSTEM|HIDDEN
	
	System::Call 'Kernel32::SetEnvironmentVariable(t, t) i("QT_PLUGIN_PATH", "$INSTDIR\plugins").r0'
	StrCmp $0 0 error
	#launch the main EXE inside the package
	ExecWait "$INSTDIR\AdolPulza.exe"
	Goto done
error:
  MessageBox MB_OK "Can't set environment variable"
done:
	#change working directory
	SetOutPath $TEMP
	
	#remove working directory
	RMDir /r $INSTDIR
SectionEnd 