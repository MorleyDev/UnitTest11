param (
  [Parameter(Mandatory=$true)] [string] $projectName
)

$files = Get-ChildItem . * -rec | where {-not $_.psiscontainer}
foreach ($file in $files) {
  (Get-Content $file.PSPath) | Foreach-Object { $_.Replace("PROJNAME", $projectName) } | Set-Content $file.PSPath
}


foreach ($file in $files) { 
  Rename-Item $file.PSPath $file.Name.Replace("PROJNAME", "$projectName") 
}
Rename-Item "PROJNAME" $projectName
Rename-Item "PROJNAME_Tests" ($projectName + "_Tests")

Remove-Item .\Initialise.ps1
