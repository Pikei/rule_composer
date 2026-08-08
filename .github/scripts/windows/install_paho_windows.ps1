$ErrorActionPreference = "Stop"

$PahoVersion = "v1.3.14"

$WorkDir = $env:GITHUB_WORKSPACE

if ([string]::IsNullOrWhiteSpace($WorkDir)) {
    $WorkDir = Get-Location
}

$PahoSourceDir = Join-Path $WorkDir ".ci\paho.mqtt.c"
$PahoBuildDir = Join-Path $PahoSourceDir "build"
$InstallPrefix = Join-Path $WorkDir ".local"

Write-Host "========================================"
Write-Host "Installing Eclipse Paho MQTT C"
Write-Host "Version: $PahoVersion"
Write-Host "Install prefix: $InstallPrefix"
Write-Host "========================================"

if (Test-Path $PahoSourceDir) {
    Remove-Item -Recurse -Force $PahoSourceDir
}

$CiDir = Join-Path $WorkDir ".ci"

if (-not (Test-Path $CiDir)) {
    New-Item -ItemType Directory -Path $CiDir | Out-Null
}

git clone `
    --branch $PahoVersion `
    --depth 1 `
    https://github.com/eclipse-paho/paho.mqtt.c.git `
    $PahoSourceDir

cmake `
    -S $PahoSourceDir `
    -B $PahoBuildDir `
    -DCMAKE_INSTALL_PREFIX="$InstallPrefix" `
    -DPAHO_BUILD_SHARED=ON `
    -DPAHO_BUILD_STATIC=OFF `
    -DPAHO_BUILD_TESTS=OFF

cmake `
    --build $PahoBuildDir `
    --config Debug `
    --parallel

cmake `
    --install $PahoBuildDir `
    --config Debug

Write-Host "========================================"
Write-Host "Paho MQTT C installed successfully"
Write-Host "========================================"
