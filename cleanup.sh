#!/usr/bin/env sh
make clean
find . -iwholename '*cmake*' -not -name CMakeLists.txt -delete
find . -name 'Makefile' -delete
rm 'compile_commands.json'
