 # Invokes a Cmd.exe shell script and updates the environment.
function Invoke-CmdScript {
  param(
    [String] $scriptName
  )
  $cmdLine = """$scriptName"" $args & set"
  & $Env:SystemRoot\system32\cmd.exe /c $cmdLine |
  select-string '^([^=]*)=(.*)$' | foreach-object {
    $varName = $_.Matches[0].Groups[1].Value
    $varValue = $_.Matches[0].Groups[2].Value
    set-item Env:$varName $varValue
  }
}

# Bootstraping VS cmdline tools
Invoke-CmdScript "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" amd64

$CXX="cl.exe"
$CXXFLAGS="/Zi /std:c++17 /EHs /EHsc /wd4005 "
$LDFLAGS=""

$WD=Get-Location
$INC="$WD\include"
$SRC="$WD\src"
$BUILD="$WD\bin\"
# $EXT="$WD\ext"

$CXXFLAGS+="-I $SRC "
$CXXFLAGS+="-I $WD/include "

# GLFW setup
$CXXFLAGS+="-I $Env:GLFW_DIR/include "
# $CXXFLAGS+="/fsanitize=address "
$LDFLAGS+="/LIBPATH:$Env:GLFW_DIR\lib-static-ucrt $Env:GLFW_DIR\lib-static-ucrt\glfw3dll.lib "

# GLAD
$CXXFLAGS+="-I $INC\glad "

$MAIN="$WD\src\main.cpp"

# Build phase
Write-Output "Using $CXX as the C++ compiler."

# if [ ! -d "$BUILD" ]
# then
#   mkdir "$BUILD";
# fi
# 
# cd "$BUILD" || exit # In case cd fails
# copy_shaders
# 
# if [[ $1 = "shaders" ]]
# then
#   exit 0
# fi

$OUT_NAME="trab2_cg.exe"

# Copy GLFW DLL to the build location
Copy-Item "$Env:GLFW_DIR\lib-static-ucrt\glfw3.dll" $BUILD

# Actually building now
$COMP_LINE = "$CXX  "
$COMP_LINE = "$CXX $MAIN $CXXFLAGS /Fe:$OUT_NAME /link $LDFLAGS"

Set-Location $BUILD

$operation = $args[0]

if ($operation -eq "tests")
{
$COMP_LINE = "$CXX -g $WD\src\tests.cpp /Fe:tests.exe -lm"
Invoke-Expression $COMP_LINE
Invoke-Expression "./tests.exe"
}
else
{
Write-Output $COMP_LINE
Invoke-Expression $COMP_LINE
}

Set-Location ..
Write-Output "Finished."

# echo | $CXX -dM -E -x c++ - # Dump defines
