param
(
    [string] $sourceFilePath = $($PSScriptRoot + "\Arduino Libraries" )
)

$ArduinoPath = "C:\Program Files (x86)\Arduino\arduino.exe";

function FindAllExampleFiles()
{
	return Get-ChildItem $sourceFilePath -Recurse -Include *.ino -Exclude _*.ino | Foreach-Object { $_.FullName }
}

function BuildArduinoExample([string]$fileName)
{
    [string]$escapedFileName = "`"" + $fileName + "`"".Trim()
    [string[]]$cmdLineArgs = "--verify", $escapedFileName

    $procObj = Start-Process $ArduinoPath -ArgumentList $cmdLineArgs -Wait -PassThru
    return $procObj.ExitCode
    
}

function BuildAllArduinoExamples()
{
    [string[]]$exampleFiles = FindAllExampleFiles

    foreach($file in $exampleFiles)
    {
        $file

        [int]$exitCode = BuildArduinoExample $file

        $exitCode.ToString();

        if ($exitCode -ne 0)
        {
           "======> FAILED!"
        }
    }
}

#
# Entry Point
#

BuildAllArduinoExamples
#FindAllExampleFiles