#!/usr/bin/env bash

# install the formatter by running `pip3 install c-formatter-42`
# or `pip3 install --user c-formatter-42` if you don't have root privileges

function norm {
	echo Formatting "$(basename "$1")"
	python3 -m c_formatter_42 <"$1" >temp
	mv temp "$1"
}

function format {
	clang-format -i "$1"
}

SRC_DIR='./src'

format "${SRC_DIR}/get_next_line.c"
format "${SRC_DIR}/get_next_line.h"
format "${SRC_DIR}/get_next_line_bonus.c"
