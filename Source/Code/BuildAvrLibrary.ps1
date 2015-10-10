param
(
    [string] $sourceFilePath = $($PSScriptRoot + "\ArduinoTemplateLibrary" ),
    [string] $targetFilePath = $($PSScriptRoot + "\Avr Library" )
)



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

function BuildLibrary()
{
    
}

#
# Entry point
#

BuildLibrary