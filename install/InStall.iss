; 脚本由 Inno Setup 脚本向导 生成！
; 有关创建 Inno Setup 脚本文件的详细资料请查阅帮助文档！

[Setup]
; 注意: AppId 值用于唯一识别该应用程序。
; 禁止对其他应用程序的安装器使用相同的 AppId 值！
; (若要生成一个新的 GUID，请选择“工具 | 生成 GUID”。)
#define AppName "chilli"
#define AppVersion "1.0.0.3"
AppId={{5B303E75-D8B9-4A49-B064-EA2E3FB50ED7}}
AppName={#AppName}
AppVersion={#AppVersion}
AppCopyright=Copyright (C) Inc.
AppComments=""
VersionInfoVersion={#AppVersion}
VersionInfoDescription={#AppName}安装包
AppPublisher=""
DefaultDirName={pf32}\{#AppName}
DefaultGroupName={#AppName}
AllowNoIcons=yes
AlwaysShowDirOnReadyPage=yes
AlwaysShowGroupOnReadyPage=yes
DisableWelcomePage=no
OutputDir=.\
OutputBaseFilename={#AppName}.{#AppVersion}
Compression=lzma2/ultra
SolidCompression=yes
PrivilegesRequired=admin

ArchitecturesInstallIn64BitMode=x64 ia64

[Languages]
Name: "chinese"; MessagesFile: "ChineseSimplified.isl"

[Tasks]
;Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked
;Name: "quicklaunchicon"; Description: "{cm:CreateQuickLaunchIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
;Source: "..\bin\CloopenAgent.htm"; DestDir: "{app}"; Flags: ignoreversion 32bit
Source: "..\Win32\bin.Release\conf\*.xml"; DestDir: "{app}\conf\"; Flags: ignoreversion restartreplace uninsrestartdelete 32bit
Source: "..\Win32\bin.Release\conf\*.js"; DestDir: "{app}\conf\"; Flags: ignoreversion restartreplace uninsrestartdelete 32bit
Source: "..\Win32\bin.Release\*.dll"; DestDir: "{app}"; Flags: ignoreversion restartreplace uninsrestartdelete 32bit
Source: "..\Win32\bin.Release\chilli.exe"; DestDir: "{app}"; Flags: replacesameversion restartreplace uninsrestartdelete 32bit 
Source: "..\Win32\bin.Release\conf\log4cplus.properties"; DestDir: "{app}\conf\"; Flags: ignoreversion restartreplace uninsrestartdelete 32bit 

; 注意: 不要在任何共享系统文件上使用“Flags: ignoreversion”

[Icons]Name: "{group}\chilli"; Filename: "{app}\chilli.exe"
Name: "{group}\{cm:UninstallProgram,{#AppName}}"; Filename: "{uninstallexe}"
;Name: "{commondesktop}\CloopenClientPlugin"; Filename: "{app}\ClientPlugin.htm"; Tasks: desktopicon
;Name: "{userappdata}\Microsoft\Internet Explorer\Quick Launch\CloopenClientPlugin"; Filename: "{app}\ClientPlugin.htm"; Tasks: quicklaunchicon


[UninstallDelete]
Type:filesandordirs;Name:{app};
Type:dirifempty;Name:{pf32}\{#AppName};
Type:dirifempty;Name:{group};

[Registry]
;Root: HKLM; Subkey: "SOFTWARE\Samwoo\AA\TIP"; ValueType: string; ValueName: "ConnectionString"; ValueData:"Provider=SQLOLEDB.1;Password=sa;Persist Security Info=True;User ID=sa;Initial Catalog=TF_CMS;Data Source=10.1.86.129"; Flags:createvalueifdoesntexist    uninsdeletekey

