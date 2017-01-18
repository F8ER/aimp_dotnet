set AimpVersion=%~1
set ConfigurationName=%~2
set SolutionDir=%~3
set TargetName=%~4
set ProjectName=%~5
set OutDir=%~6
set TargetPath=%~7

IF %ConfigurationName% == Debug (
    IF NOT EXIST "%SolutionDir%..\..\%AimpVersion%\Plugins\%TargetName%" mkdir "%SolutionDir%..\..\%AimpVersion%\Plugins\%TargetName%"
        copy "%TargetPath%" "%SolutionDir%..\..\%AimpVersion%\Plugins\%TargetName%\%ProjectName%_plugin.dll"
        copy "%SolutionDir%%ConfigurationName%\aimp_dotnet.dll" "%SolutionDir%..\..\%AimpVersion%\Plugins\%TargetName%\%ProjectName%.dll"
        copy "%SolutionDir%\AIMP.SDK\%OutDir%AIMP.SDK.dll" "%SolutionDir%..\..\%AimpVersion%\Plugins\%TargetName%\AIMP.SDK.dll"
)

IF %ConfigurationName% == Release (
    IF NOT EXIST "%SolutionDir%\%ConfigurationName%\AIMP.SDK\Demos" mkdir "%SolutionDir%\%ConfigurationName%\AIMP.SDK\Demos"
    IF NOT EXIST "%SolutionDir%\%ConfigurationName%\AIMP.SDK\Demos\%TargetName%" mkdir "%SolutionDir%\%ConfigurationName%\AIMP.SDK\Demos\%TargetName%"

    copy "%TargetPath%" "%SolutionDir%\%ConfigurationName%\AIMP.SDK\Demos\%TargetName%\%ProjectName%_plugin.dll"
    copy "%SolutionDir%\AIMP.SDK\%OutDir%AIMP.SDK.dll" "%SolutionDir%\%ConfigurationName%\AIMP.SDK\Demos\%TargetName%\AIMP.SDK.dll"
    copy "%SolutionDir%%ConfigurationName%\aimp_dotnet.dll" "%SolutionDir%\%ConfigurationName%\AIMP.SDK\Demos\%TargetName%\%ProjectName%.dll"
)