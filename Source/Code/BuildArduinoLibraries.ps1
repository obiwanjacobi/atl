param
(
    [string] $sourceFilePath = $($PSScriptRoot + "\ArduinoTemplateLibrary" ),
    [string] $targetFilePath = $($PSScriptRoot + "\Arduino Libraries" )
)


[string[]] $ATL_Files = "Array.h", "ArrayRef.h", "Bit.h", "BitArray.h", "BitFlag.h", "Collection.h", "CollectionRef.h", "Default.h", "Delays.h", "Delegate.h", "FixedString.h", "Func.h", "IdentifiableObject.h", "Iterator.h", "Range.h", "Ringbuffer.h", "StaticArray.h", "StaticString.h", "Time.h", "ValueContainer.h", "Arduino\Time_Arduino.h"
[string[]] $ATL_HD44780_Files = "BitArray.h", "HD44780_Controller.h", "HD44780_Driver.h", "HD44780_DriverSerial3Wire.h", "HD44780_Profile.h", "HD44780_View.h", "HD44780_ViewPort.h"
[string[]] $ATL_IO_Files = "BitArray.h", "BufferedInputStream.h", "DigitalInput.h", "Serial3WireOutput.h", "TextFormatInfo.h", "TextWriter.h", "Arduino\AnalogOutputPin.h", "Arduino\DigitalInputPin.h", "Arduino\DigitalOutputPin.h", "Arduino\StreamInputStream.h", "Arduino\StreamOutputStream.h"
[string[]] $ATL_MIDI_Files = "Midi.h", "MidiMessage.h", "MidiReader.h", "MidiWriter.h"
[string[]] $ATL_Process_Files = "Delays.h", "Time.h", "Arduino\Time_Arduino.h", "IdentifiableObject.h", "PID.h", "Task.h", "TimeoutTask.h"
[string[]] $ATL_TB6612FNG_Files = "TB6612FNG_Controller.h", "TB6612FNG_Driver.h", "TB6612FNG_DriverSerial3Wire.h"
[string[]] $ATL_UI_Files = "Array.h", "Collection.h", "Control.h", "ControlContainer.h", "Default.h", "DisplayWriter.h", "HD44780_DisplayWriter.h", "HorizontalPanel.h", "InputControl.h", "Iterator.h", "LabelControl.h", "Line.h", "NavigationController.h", "Page.h", "PageController.h", "Panel.h", "PanelControlContainer.h", "TextControl.h", "UpDownControl.h", "VerticalPanel.h"
[string[]] $ATL_URM37V32_Files = "URM37V32_Controller.h", "URM37V32_Driver.h"

$HeaderMessage = "This file is generated. Do not change."
$NewLine = "`r`n"
$FileHeader = "// " + $HeaderMessage + $NewLine
$KeywordsHeader = "# " + $HeaderMessage + $NewLine
$ArduinoInclude = "#include <Arduino.h>" + $NewLine

#
# Support functions
#

function BuildInclude([string]$file)
{
    return "#include `"utility\" + $file + "`""
}

function BuildPreprocessorVar([string]$libraryName)
{
    return "__" + $libraryName + "_H__"
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
    [array]$parts = $file.Split('.\/')

	if ($parts.Length -eq 3)
	{
	    return $parts[1]
	}

	return $parts[0]
}

function GetFileNameWithExtension([string]$file)
{
    [array]$parts = $file.Split('\/')

	return $parts[$parts.Length - 1]
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

#
# Action functions
#

function CopySourceFiles([string]$libraryName, [string[]]$files)
{
    $fullTargetFilePath = $targetFilePath + "\" + $libraryName + "\utility"

    foreach ($file in $files)
    {
        $fullSourceFilePath = $sourceFilePath + "\" + $file

        $fullSourceFilePath

        CopyFile $fullSourceFilePath ($fullTargetFilePath +  "\" + $file) 
    }
}

function CreateHeaderFile([string]$libraryName, [string[]]$files)
{
    $headerFilePath = $targetFilePath + "\" + $libraryName + "\" + $libraryName + ".h"

    CreateFile $headerFilePath $FileHeader

    WriteToFile ($headerFilePath) (BuildPreprocessorStart $libraryName)

	WriteToFile $headerFilePath $ArduinoInclude

    foreach ($file in $files)
    {
        #$onlyFile = GetFileNameWithExtension $file
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

function BuildLibrary([string]$libraryName, [string[]]$files)
{
    CopySourceFiles $libraryName $files
    CreateHeaderFile $libraryName $files
    BuildKeywordsFile $libraryName $files
}

#
# Entry point
#

BuildLibrary "ATL" $ATL_Files
BuildLibrary "ATL_HD44780" $ATL_HD44780_Files
BuildLibrary "ATL_IO" $ATL_IO_Files
BuildLibrary "ATL_MIDI" $ATL_MIDI_Files
BuildLibrary "ATL_Process" $ATL_Process_Files
BuildLibrary "ATL_TB6612FNG" $ATL_TB6612FNG_Files
BuildLibrary "ATL_UI" $ATL_UI_Files
BuildLibrary "ATL_URM37V32" $ATL_URM37V32_Files
