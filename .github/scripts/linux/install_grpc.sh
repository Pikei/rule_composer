#!/usr/bin/env bash

set -euo pipefail

GRPC_VERSION="v1.82.0"

WORKSPACE="${GITHUB_WORKSPACE:-$(pwd)}"
SOURCE_DIR="${WORKSPACE}/.ci/grpc"
BUILD_DIR="${SOURCE_DIR}/cmake/build"
INSTALL_PREFIX="${WORKSPACE}/.local"

echo "========================================"
echo "Building gRPC"
echo "gRPC version: ${GRPC_VERSION}"
echo "Install prefix: ${INSTALL_PREFIX}"
echo "========================================"

mkdir -p "${WORKSPACE}/.ci"

rm -rf "${SOURCE_DIR}"

git clone \
    --branch "${GRPC_VERSION}" \
    --depth 1 \
    --recurse-submodules \
    https://github.com/grpc/grpc.git \
    "${SOURCE_DIR}"

echo "Configuring gRPC..."

cmake \
    -S "${SOURCE_DIR}" \
    -B "${BUILD_DIR}" \
    -G Ninja \
    -DCMAKE_BUILD_TYPE=Debug \
    -DCMAKE_INSTALL_PREFIX="${INSTALL_PREFIX}" \
    -DgRPC_INSTALL=ON \
    -DgRPC_BUILD_TESTS=OFF \
    -DgRPC_PROTOBUF_PROVIDER=module \
    -DgRPC_ZLIB_PROVIDER=module \
    -DgRPC_SSL_PROVIDER=package \
    -DgRPC_ABSL_PROVIDER=module \
    -DgRPC_CARES_PROVIDER=module \
    -DgRPC_RE2_PROVIDER=module \
    -DgRPC_PROTOBUF_PACKAGE_TYPE=CONFIG

echo "Building gRPC..."

cmake \
    --build "${BUILD_DIR}" \
    --parallel

echo "Installing gRPC..."

cmake \
    --install "${BUILD_DIR}"

echo "========================================"
echo "gRPC installation completed"
echo "========================================"

echo "Checking installation..."

test -f "${INSTALL_PREFIX}/lib/cmake/protobuf/protobuf-config.cmake"
test -f "${INSTALL_PREFIX}/lib/cmake/grpc/gRPCConfig.cmake"

echo "Protobuf CMake config:"
echo "  ${INSTALL_PREFIX}/lib/cmake/protobuf/protobuf-config.cmake"

echo "gRPC CMake config:"
echo "  ${INSTALL_PREFIX}/lib/cmake/grpc/gRPCConfig.cmake"
