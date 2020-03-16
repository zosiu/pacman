#!/bin/sh

build_type=${1:-Release}
cmake -G "Unix Makefiles" -B build -DCMAKE_BUILD_TYPE=$build_type
make -C build
