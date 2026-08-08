#!/usr/bin/env bash

set -euo pipefail

PAHO_VERSION="v1.3.14"

WORK_DIR="${GITHUB_WORKSPACE:-$(pwd)}"
PAHO_SOURCE_DIR="${WORK_DIR}/.ci/paho.mqtt.c"
PAHO_BUILD_DIR="${PAHO_SOURCE_DIR}/build"
INSTALL_PREFIX="${WORK_DIR}/.local"

echo "========================================"
echo "Installing Eclipse Paho MQTT C"
echo "Version: ${PAHO_VERSION}"
echo "Install prefix: ${INSTALL_PREFIX}"
echo "========================================"

rm -rf "${PAHO_SOURCE_DIR}"

mkdir -p "${WORK_DIR}/.ci"

git clone \
    --branch "${PAHO_VERSION}" \
    --depth 1 \
    https://github.com/eclipse-paho/paho.mqtt.c.git \
    "${PAHO_SOURCE_DIR}"

cmake \
    -S "${PAHO_SOURCE_DIR}" \
    -B "${PAHO_BUILD_DIR}" \
    -G Ninja \
    -DCMAKE_BUILD_TYPE=Debug \
    -DCMAKE_INSTALL_PREFIX="${INSTALL_PREFIX}" \
    -DPAHO_BUILD_SHARED=ON \
    -DPAHO_BUILD_STATIC=OFF \
    -DPAHO_BUILD_TESTS=OFF

cmake \
    --build "${PAHO_BUILD_DIR}" \
    --parallel

cmake \
    --install "${PAHO_BUILD_DIR}"

echo "========================================"
echo "Paho MQTT C installed successfully"
echo "========================================"