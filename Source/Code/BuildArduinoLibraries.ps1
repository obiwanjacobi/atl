param
(
    [string] $sourceFilePath = $($PSScriptRoot + "\ArduinoTemplateLibrary" ),
    [string] $targetFilePath = $($PSScriptRoot + "\Arduino Libraries" )
)

"From: " + $sourceFilePath
"To: " + $targetFilePath


[string[]] $ATL_Files = "Array.h", "ArrayRef.h", "Bit.h", "BitArray.h", "BitFlag.h"

BuildLibrary "ATL" $ATL_Files

#
# Entry point
#

function BuildLibrary([string]$libraryName, [string[]]$files)
{
    CopySourceFiles $libraryName $files
    CreateHeaderFile $libraryName $files
    BuildKeywordsFile $libraryName $files
}

#
# Action functions
#

function CopySourceFiles([string]$libraryName, [string[]]$files)
{
    $fullTargetFilePath = $targetFilePath + "\" + $libraryName + "\utility"

    $fullTargetFilePath

    foreach ($file in $files)
    {
        $fullSourceFilePath = $sourceFilePath + "\" + $file

        $fullSourceFilePath

        Copy-Item  $fullSourceFilePath $fullTargetFilePath
    }
}

function CreateHeaderFile([string]$libraryName, [string[]]$files)
{
    $headerFilePath = $targetFilePath + "\" + $libraryName + "\" + $libraryName + ".h"

    CreateFile $headerFilePath $FileHeader

    WriteToFile ($headerFilePath) (BuildPreprocessorStart $libraryName)

    foreach ($file in $files)
    {
        WriteToFile ($headerFilePath) (BuildInclude $file)
    }

    WriteToFile ($headerFilePath) (BuildPreprocessorEnd $libraryName)
}

function BuildKeywordsFile([string]$libraryName, [string[]]$files)
{
    $keywordsFilePath = $targetFilePath + "\" + $libraryName + "\keywords.txt"

    CreateFile $keywordsFilePath $KeywordsHeader

    foreach ($file in $files)
    {
        $name = GetFileName $file
        WriteToFile ($keywordsFilePath) ($name + "`t`t`tKEYWORD1")
    }
}

#
# Support functions
#

function BuildInclude([string]$file)
{
    return "#include `"utility\" + $file + "`""
}

function BuildPreprocessorEnd([string]$libraryName)
{
    $var = BuildPreprocessorVar $libraryName
    return $NewLine + "#endif`t// " + $var
}

function BuildPreprocessorStart([string]$libraryName)
{
    $var = BuildPreprocessorVar $libraryName
    return "#ifndef " + $var + $NewLine + "#define " + $var + $NewLine
}

function BuildPreprocessorVar([string]$libraryName)
{
    return "__" + $libraryName + "_H__"
}

function CreateFile([string] $filePath, [string]$headerMessage)
{
    If (Test-Path $filePath) {Remove-Item $filePath}

    New-Item $filePath -ItemType File

    $headerMessage | Out-File $filePath -Encoding utf8
}

function WriteToFile([string]$filePath, [string]$content)
{
    $content | Out-File $filePath -Encoding utf8 -Append
}

function GetFileName([string]$file)
{
    return $file.Split(".h")[0]
}

$FileHeader = "// " + $HeaderMessage + $NewLine
$KeywordsHeader = "# " + $HeaderMessage + $NewLine
$HeaderMessage = "This file is generated. Do not change."
$NewLine = "`r`n"