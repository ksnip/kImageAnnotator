#!/bin/bash

git clone --depth 1 git://github.com/ksnip/kColorPicker

cd kColorPicker || exit
mkdir build && cd build || exit
cmake .. -G"${CMAKE_GENERATOR}" -DBUILD_EXAMPLE=OFF -DCMAKE_INSTALL_PREFIX="${INSTALL_PREFIX}"
${MAKE_BINARY} && ${MAKE_BINARY} install