; *** Inno Setup version 5.1.11+ 简体中文信息 by West King ***
;
; 若要下载用户提供的翻译文件，请访问:
;   http://www.jrsoftware.org/files/istrans/

[LangOptions]
LanguageName=<7B80><4F53><4E2D><6587>
LanguageID=$0804
LanguageCodePage=936
DialogFontName=宋体
DialogFontSize=9
WelcomeFontName=宋体
WelcomeFontSize=12
TitleFontName=宋体
TitleFontSize=29
CopyrightFontName=宋体
CopyrightFontSize=9

[Messages]

; *** 应用程序标题
SetupAppTitle=更新
SetupWindowTitle=更新 - %1
UninstallAppTitle=卸载
UninstallAppFullTitle=%1 卸载

; *** 其他公用信息
InformationTitle=信息
ConfirmTitle=确认
ErrorTitle=错误

; *** SetupLdr 信息
SetupLdrStartupMessage=现在将更新 %1。您想要继续吗？
LdrCannotCreateTemp=不能创建临时文件！更新中断。
LdrCannotExecTemp=不能执行临时目录中的文件！更新中断。

; *** 启动错误信息
LastErrorMessage=%1.%n%n错误 %2: %3
SetupFileMissing=更新目录中缺少文件 %1！请纠正该问题，或者获取一个新的程序副本。
SetupFileCorrupt=更新文件已损坏！请获取一个新的程序副本。
SetupFileCorruptOrWrongVer=更新文件已损坏，或者与此更新程序的版本不兼容！请纠正该问题，或者获取一个新的程序副本。
NotOnThisPlatform=此程序无法在 %1 上运行！
OnlyOnThisPlatform=此程序必须在 %1 上运行！
OnlyOnTheseArchitectures=此程序只能更新在下列处理器结构设计的 Windows 版本上:%n%n%1
MissingWOW64APIs=当前 Windows 版本不包含执行 64 位更新程序所需的功能！要纠正该问题，请更新 Service Pack %1。
WinVersionTooLowError=此程序需要 %1 v%2 或更高版本！
WinVersionTooHighError=此程序不能在 %1 v%2 或更高版本上更新！
AdminPrivilegesRequired=更新此程序时，你必须以管理员身份登录！
PowerUserPrivilegesRequired=更新此程序时，你必须以管理员或 Power Users 成员的身份登录！
SetupAppRunningError=更新程序检测到 %1 正在运行！%n%n请立即关闭其所有实例，然后点击“确定”继续，或者点击“取消”退出。
UninstallAppRunningError=卸载程序检测到 %1 正在运行！%n%n请立即关闭其所有实例，然后点击“确定”继续，或者点击“取消”退出。

; *** 其他错误信息
ErrorCreatingDir=更新程序无法创建目录“%1”
ErrorTooManyFilesInDir=无法在目录“%1”中创建文件！因为里面的文件太多

; *** 更新公用信息
ExitSetupTitle=退出更新
ExitSetupMessage=更新未完成！如果你现在退出，程序将无法更新！%n%n你可以以后再运行更新程序来完成更新。%n%n要退出更新吗？
AboutSetupMenuItem=关于更新程序(&A)...
AboutSetupTitle=关于更新程序
AboutSetupMessage=%1 v%2%n%3%n%n%1 主页:%n%4
AboutSetupNote=
TranslatorNote=

; *** 按钮
ButtonBack=< 上一步(&B)
ButtonNext=下一步(&N) >
ButtonInstall=更新(&I)
ButtonOK=确定
ButtonCancel=取消
ButtonYes=是(&Y)
ButtonYesToAll=全是(&A)
ButtonNo=否(&N)
ButtonNoToAll=全否(&O)
ButtonFinish=完成(&F)
ButtonBrowse=浏览(&B)...
ButtonWizardBrowse=浏览(&R)...
ButtonNewFolder=创建新文件夹(&M)

; *** "选择语言" 对话框信息
SelectLanguageTitle=选择更新语言
SelectLanguageLabel=请选择更新期间使用的语言:

; *** 公用向导文本
ClickNext=点击“下一步”继续，或者点击“取消”退出更新。
BeveledLabel=
BrowseDialogTitle=浏览文件夹
BrowseDialogLabel=在以下列表中选择一个文件夹，然后点击“确定”。
NewFolderName=新建文件夹

; *** "欢迎" 向导页
WelcomeLabel1=欢迎使用 [name] 更新向导
WelcomeLabel2=现在将更新 [name/ver]。%n%n建议你在继续之前关闭其他应用程序。

; *** "密码" 向导页
WizardPassword=密码
PasswordLabel1=此更新程序受密码保护！
PasswordLabel3=请输入密码，然后点击“下一步”继续。密码区分大小写！
PasswordEditLabel=密码(&P):
IncorrectPassword=你输入的密码不正确！请重新输入。

; *** "许可协议" 向导页
WizardLicense=许可协议
LicenseLabel=请在继续之前阅读以下重要信息！
LicenseLabel3=请阅读以下许可协议。你必须接受此协议中的条款，才能继续更新。
LicenseAccepted=我接受(&A)
LicenseNotAccepted=我不接受(&D)

; *** "信息" 向导页
WizardInfoBefore=信息
InfoBeforeLabel=请在继续之前阅读以下重要信息！
InfoBeforeClickLabel=当你准备继续更新时，请点击“下一步”。
WizardInfoAfter=信息
InfoAfterLabel=请在继续之前阅读以下重要信息！
InfoAfterClickLabel=当你准备继续更新时，请点击“下一步”。

; *** "用户信息" 向导页
WizardUserInfo=用户信息
UserInfoDesc=请输入你的信息。
UserInfoName=用户名(&U):
UserInfoOrg=组织(&O):
UserInfoSerial=序列号(&S):
UserInfoNameRequired=你必须输入用户名！

; *** "选择目标位置" 向导页
WizardSelectDir=选择目标位置
SelectDirDesc=[name] 要更新到哪里？
SelectDirLabel3=更新程序将把 [name] 更新到以下文件夹。
SelectDirBrowseLabel=若要继续，请点击“下一步”。如果你要换一个文件夹，请点击“浏览”。
DiskSpaceMBLabel=至少需要 [mb] MB 可用磁盘空间。
ToUNCPathname=更新程序不能更新到 UNC 路径！如果你试图更新到网络中，就需要映射一个网络驱动器。
InvalidPath=你必须输入一个带盘符的完整路径！例如:%n%nC:\APP%n%n或者以下格式的 UNC 路径:%n%n\\server\share
InvalidDrive=你选择的驱动器或 UNC 路径不存在或者无法访问！请重新选择。
DiskSpaceWarningTitle=磁盘空间不足
DiskSpaceWarning=更新程序至少需要 %1 KB 的可用空间，但是所选驱动器上只剩 %2 KB！%n%n无论如何也要继续吗？
DirNameTooLong=文件夹名称或路径太长！
InvalidDirName=文件夹名称无效！
BadDirName32=文件夹名称不能包含以下字符:%n%n%1
DirExistsTitle=文件夹已存在
DirExists=文件夹:%n%n%1%n%n已存在！无论如何也要更新到此文件夹中吗？
DirDoesntExistTitle=文件夹不存在
DirDoesntExist=文件夹:%n%n%1%n%n不存在！你要创建此文件夹吗？

; *** "选择组件" 向导页
WizardSelectComponents=选择组件
SelectComponentsDesc=要更新那个组件？
SelectComponentsLabel2=请选择你要更新的组件，或者清除不想更新的组件。然后点击“下一步”继续。
FullInstallation=完全更新
CompactInstallation=简洁更新
CustomInstallation=自定义更新
NoUninstallWarningTitle=组件已存在
NoUninstallWarning=更新程序检测到你的电脑中已经更新了下列组件:%n%n%1%n%n取消选择这些组件将不会卸载他们。%n%n无论如何也要继续吗？
ComponentSize1=%1 KB
ComponentSize2=%1 MB
ComponentsDiskSpaceMBLabel=当前所选组件至少需要 [mb] MB 磁盘空间。

; *** "选择附加任务" 向导页
WizardSelectTasks=选择附加任务
SelectTasksDesc=要执行那些附加任务？
SelectTasksLabel2=请选择要在 [name] 更新期间执行的附加任务，然后点击“下一步”。

; *** "选择开始菜单文件夹" 向导页
WizardSelectProgramGroup=选择开始菜单文件夹
SelectStartMenuFolderDesc=程序的快捷方式要放到哪里？
SelectStartMenuFolderLabel3=更新程序将在以下开始菜单文件夹中创建程序的快捷方式。
SelectStartMenuFolderBrowseLabel=若要继续，请点击“下一步”。如果你要换一个文件夹，请点击“浏览”。
MustEnterGroupName=你必须输入一个文件夹名称！
GroupNameTooLong=文件夹名称或路径太长！
InvalidGroupName=文件夹名称无效！
BadGroupName=文件夹名称不能包含以下字符:%n%n%1
NoProgramGroupCheck2=禁止创建开始菜单文件夹(&D)

; *** "准备更新" 向导页
WizardReady=准备更新
ReadyLabel1=更新程序准备在你的电脑上更新 [name]。
ReadyLabel2a=点击“更新”继续，如果你想修改设置请点击“上一步”。
ReadyLabel2b=点击“更新”继续。
ReadyMemoUserInfo=用户信息:
ReadyMemoDir=目标位置:
ReadyMemoType=更新类型:
ReadyMemoComponents=所选组件:
ReadyMemoGroup=开始菜单文件夹:
ReadyMemoTasks=附加任务:

; *** "正在准备更新" 向导页
WizardPreparing=正在准备更新
PreparingDesc=更新程序正在准备在你的电脑上更新 [name]。
PreviousInstallNotCompleted=先前的程序还未更新或卸载完成，需要重启电脑来完成。%n%n电脑重启后，再运行更新程序来完成 [name] 的更新。
CannotContinue=更新程序不能继续！请点击“取消”退出。

; *** "正在更新" 向导页
WizardInstalling=正在更新
InstallingLabel=正在更新 [name]，请稍候...

; *** "更新完成" 向导页
FinishedHeadingLabel=[name] 更新完毕
FinishedLabelNoIcons=更新程序已将 [name] 更新到你的电脑上。
FinishedLabel=更新程序已将 [name] 更新到你的电脑上。现在可以通过程序图标来运行应用程序。
ClickFinish=请点击“完成”退出更新。
FinishedRestartLabel=若要完成 [name] 的更新，就必须重启电脑。你要立即重启吗？
FinishedRestartMessage=若要完成 [name] 的更新，就必须重启电脑。%n%n你要立即重启吗？
ShowReadmeCheck=是，我要查看自述文件
YesRadio=是(&Y)，立即重启电脑
NoRadio=否(&N)，稍后重启电脑
RunEntryExec=运行 %1
RunEntryShellExec=查看 %1

; *** "更新程序需要下一张磁盘" 信息
ChangeDiskTitle=更新程序需要下一张磁盘
SelectDiskLabel2=请插入磁盘 %1 后点击“确定”。%n%n如果磁盘上的文件不在以下所显示的文件夹中，就请输入正确的路径或点击“浏览”。
PathLabel=路径(&P):
FileNotInDir2=文件“%1”不在“%2”中！请插入正确的磁盘，或者选择其他文件夹。
SelectDirectoryLabel=请指定下一张磁盘的位置。

; *** 更新阶段信息
SetupAborted=更新程序未完成！%n%n请纠正该问题后重新运行更新程序。
EntryAbortRetryIgnore=请点击“重试”再次尝试，点击“忽略”继续，或“中止”取消更新。

; *** 更新状态信息
StatusCreateDirs=正在创建目录...
StatusExtractFiles=正在提取文件...
StatusCreateIcons=正在创建快捷方式...
StatusCreateIniEntries=正在创建 INI 条目...
StatusCreateRegistryEntries=正在创建注册表条目...
StatusRegisterFiles=正在注册文件...
StatusSavingUninstall=正在保存卸载信息...
StatusRunProgram=正在完成更新...
StatusRollback=正在撤销更改...

; *** 其他信息
ErrorInternal2=内部错误: %1
ErrorFunctionFailedNoCode=%1 失败
ErrorFunctionFailed=%1 失败！代码 %2
ErrorFunctionFailedWithMessage=%1 失败！代码 %2.%n%3
ErrorExecutingProgram=无法执行文件:%n%1

; *** 注册表错误
ErrorRegOpenKey=打开注册表键出错:%n%1\%2
ErrorRegCreateKey=创建注册表键出错:%n%1\%2
ErrorRegWriteKey=写入注册表键出错:%n%1\%2

; *** INI 错误
ErrorIniEntry=在文件“%1”中创建 INI 条目时出错！

; *** 文件复制错误
FileAbortRetryIgnore=点击“重试”再次尝试，点击“忽略”跳过此文件 (不推荐)，或点击“中止”取消更新。
FileAbortRetryIgnore2=点击“重试”再次尝试，点击“忽略”继续 (不推荐)，或点击“中止”取消更新。
SourceIsCorrupted=源文件已损坏
SourceDoesntExist=源文件“%1”不存在
ExistingFileReadOnly=现有文件已标记为只读。%n%n点击“重试”除去只读属性并再次尝试，点击“忽略”跳过此文件，或点击“中止”取消更新。
ErrorReadingExistingDest=尝试读取现有文件时出错:
FileExists=文件已存在！%n%n要覆盖它吗？
ExistingFileNewer=现有文件比要更新的更新！建议保留现有文件。%n%n要保留现有文件吗？
ErrorChangingAttr=试图更改现有文件的属性时出错:
ErrorCreatingTemp=试图在目标目录中创建文件时出错:
ErrorReadingSource=试图读取源文件时出错:
ErrorCopying=试图复制文件时出错:
ErrorReplacingExistingFile=试图替换现有文件时出错:
ErrorRestartReplace=重启后替换失败:
ErrorRenamingTemp=试图重命名目标目录中的文件时出错:
ErrorRegisterServer=无法注册 DLL/OCX: %1
ErrorRegSvr32Failed=RegSvr32 失败！退出代码 %1
ErrorRegisterTypeLib=无法注册类型库: %1

; *** 递交更新错误
ErrorOpeningReadme=试图打开自述文件时出错！
ErrorRestartingComputer=更新程序无法重启电脑！请手动操作。

; *** 卸载程序信息
UninstallNotFound=文件“%1”不存在！无法卸载
UninstallOpenError=文件“%1”打不开！无法卸载
UninstallUnsupportedVer=卸载日志“%1”的格式无法被此版本的卸载程序识别！无法卸载
UninstallUnknownEntry=卸载日志中遇到未知条目 (%1)
ConfirmUninstall=是否确定要彻底卸载 %1 及其所有组件？
UninstallOnlyOnWin64=此更新只能在 64 位 Windows 上卸载！
OnlyAdminCanUninstall=此更新只能由管理员卸载！
UninstallStatusLabel=正在写作 %1，请稍候...
UninstalledAll=%1 已成功卸载。
UninstalledMost=%1 卸载完成。%n%n某些元素无法清除，请手动操作。
UninstalledAndNeedsRestart=若要完成 %1 的卸载，就必须重启电脑。%n%n要立即重启吗？
UninstallDataCorrupted=文件“%1”已损坏！无法卸载

; *** 卸载阶段信息
ConfirmDeleteSharedFileTitle=清楚共享文件吗？
ConfirmDeleteSharedFile2=下列共享文件不再被其他程序使用，要清除吗？%n%n如果其他程序仍然使用此文件，却被删除的话，那些程序可能无法正常运行。如果你不确定，请选择“否”。留下此文件对你的系统也不会有什么损害。
SharedFileNameLabel=文件名:
SharedFileLocationLabel=位置:
WizardUninstalling=卸载状态
StatusUninstalling=正在卸载 %1...

[CustomMessages]

NameAndVersion=%1 v%2
AdditionalIcons=附加图标:
CreateDesktopIcon=创建桌面图标(&D)
CreateQuickLaunchIcon=创建快速启动图标(&Q)
ProgramOnTheWeb=%1 网站
UninstallProgram=卸载 %1
LaunchProgram=运行 %1
AssocFileExtension=将 %2 文件与 %1 关联(&A)
AssocingFileExtension=正在将 %2 文件与 %1 关联...
