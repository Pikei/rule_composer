$ErrorActionPreference = "Stop"

$GrpcVersion = "v1.82.0"

$Workspace = $env:GITHUB_WORKSPACE

if ([string]::IsNullOrWhiteSpace($Workspace)) {
    $Workspace = (Get-Location).Path
}

$SourceDir = Join-Path $Workspace ".ci\grpc"
$BuildDir = Join-Path $SourceDir "cmake\build"
$InstallPrefix = Join-Path $Workspace ".local"

Write-Host "========================================"
Write-Host "Building gRPC"
Write-Host "gRPC version: $GrpcVersion"
Write-Host "Install prefix: $InstallPrefix"
Write-Host "========================================"

$CiDir = Join-Path $Workspace ".ci"

if (-not (Test-Path $CiDir)) {
    New-Item -ItemType Directory -Path $CiDir | Out-Null
}

if (Test-Path $SourceDir) {
    Remove-Item -Recurse -Force $SourceDir
}

Write-Host "Cloning gRPC..."

git clone `
    --branch $GrpcVersion `
    --depth 1 `
    --recurse-submodules `
    https://github.com/grpc/grpc.git `
    $SourceDir

Write-Host "Configuring gRPC..."

cmake `
    -S $SourceDir `
    -B $BuildDir `
    -DCMAKE_INSTALL_PREFIX="$InstallPrefix" `
    -DgRPC_INSTALL=ON `
    -DgRPC_BUILD_TESTS=OFF `
    -DgRPC_PROTOBUF_PROVIDER=module `
    -DgRPC_ZLIB_PROVIDER=module `
    -DgRPC_SSL_PROVIDER=module `
    -DgRPC_ABSL_PROVIDER=module `
    -DgRPC_CARES_PROVIDER=module `
    -DgRPC_RE2_PROVIDER=module `
    -DgRPC_PROTOBUF_PACKAGE_TYPE=CONFIG

Write-Host "Building gRPC..."

cmake `
    --build $BuildDir `
    --config Debug `
    --parallel

Write-Host "Installing gRPC..."

cmake `
    --install $BuildDir `
    --config Debug

Write-Host "========================================"
Write-Host "gRPC installation completed"
Write-Host "========================================"

$ProtobufConfig = Join-Path $InstallPrefix "lib\cmake\protobuf\protobuf-config.cmake"
$GrpcConfig = Join-Path $InstallPrefix "lib\cmake\grpc\gRPCConfig.cmake"

if (-not (Test-Path $ProtobufConfig)) {
    throw "Protobuf CMake configuration was not installed: $ProtobufConfig"
}

if (-not (Test-Path $GrpcConfig)) {
    throw "gRPC CMake configuration was not installed: $GrpcConfig"
}

Write-Host "Protobuf CMake config:"
Write-Host "  $ProtobufConfig"

Write-Host "gRPC CMake config:"
Write-Host "  $GrpcConfig"
