; -- IconMasterXP Main Setup file --
;
; WARNING: If you create your own setup always generate a new AppId GUID
;
[Setup]
AppId={{977771A0-9843-4278-851E-73E530F903E3} 
AppName=IconMasterXP
VersionInfoVersion=4.9.0.0
AppVerName=IconMasterXP 4.9
AppPublisher=IconMasterXP.com
SourceDir="..\"
OutputBaseFilename=IconMasterXP
AppPublisherURL=http://www.iconmasterxp.com/
AppSupportURL=mailto:support@iconmasterxp.com
AppUpdatesURL=http://www.iconmasterxp.com/
DefaultDirName={pf}\IconMasterXP
DefaultGroupName=IconMasterXP
LicenseFile=Documentation\EULA.txt
OutputDir=Setup\Output
Compression=lzma
SolidCompression=yes
SetupIconFile="Source\IconMasterXP\res\IconMasterXP.ico"

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "Source\IconMasterXP\Release\IconMasterXP.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "Runtime\mfc100.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "Runtime\msvcr100.dll"; DestDir: "{app}"; Flags: ignoreversion

Source: "Source\IconMasterXP\psd2png.exe"; DestDir: "{app}"; Flags: ignoreversion

Source: "Documentation\IconMasterXP.chm"; DestDir: "{app}"; Flags: ignoreversion
Source: "Documentation\hh.exe.manifest"; DestDir: "{app}"; Flags: ignoreversion

[Icons]
Name: "{group}\IconMasterXP"; Filename: "{app}\IconMasterXP.exe"
Name: "{group}\{cm:ProgramOnTheWeb,IconMasterXP}"; Filename: "http://www.iconmasterxp.com/"
Name: "{group}\{cm:UninstallProgram,IconMasterXP}"; Filename: "{uninstallexe}"
Name: "{commondesktop}\IconMasterXP"; Filename: "{app}\IconMasterXP.exe"; Tasks: desktopicon

[Run]
Filename: "{app}\IconMasterXP.exe"; Description: "{cm:LaunchProgram,IconMasterXP}"; Flags: nowait postinstall skipifsilent

