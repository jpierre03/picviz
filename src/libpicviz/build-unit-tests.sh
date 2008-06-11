#!/bin/sh

CC="gcc"
CFLAGS="-D_UNIT_TEST_ -I./include"


function compile()
{
        base=$1

        echo "Compiling $base..."
        $CC $base.c -o $base $CFLAGS
}

compile values-mapping

