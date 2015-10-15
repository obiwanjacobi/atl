param
(
    [string] $sourceFilePath = $($PSScriptRoot + "\ArduinoTemplateLibrary" ),
    [string] $targetFilePath = $($PSScriptRoot + "\Avr Library" )
)

function FindFiles([string]$sourceFilePath)
{
    $path = $sourceFilePath + "\*"
    return Get-ChildItem $path -Include *.h;*.cpp | Foreach-Object { $_.FullName }
}

function CopyFile([string]$sourceFilePath, [string]$targetFilePath)
{
    $targetFolder = Split-Path $targetFilePath -Parent

    if (!(Test-Path $targetFolder -PathType Container))
    {
        New-Item $targetFolder -ItemType Directory
    } 

    Copy-Item $sourceFilePath $targetFilePath
}

function CopySourceFiles([string]$targetFilePath, [string[]]$files)
{
    foreach ($file in $files)
    {
        $fileName = Split-Path $file -Leaf

        $fulltargetFilePath = $targetFilePath + "\" + $fileName
        
        $fulltargetFilePath

        CopyFile $file $fulltargetFilePath
    }
}

function BuildLibrary()
{
    $avrSourceFilePath = $sourceFilePath + "\AVR"

    [string[]]$atlFiles = FindFiles $sourceFilePath
    [string[]]$avrFiles = FindFiles $avrSourceFilePath

    CopySourceFiles $targetFilePath $atlFiles
    CopySourceFiles ($targetFilePath + "\AVR") $avrFiles
}

#
# Entry point
#

BuildLibrary