#!/bin/sh

PCV=pcv
REG_PATH=./regressions
REG_VER=""
TMP_DIR=""


function run_check()
{
        file_check=$1

        echo "Run check with $file_check..."
        $PCV $file_check.pcv > $TMP_DIR/$file_check.svg
        diff -Nudb $REG_PATH/$REG_VER/$file_check.svg $TMP_DIR/$file_check.svg > $TMP_DIR/$file_check.diff

        if [ -s $TMP_DIR/$file_check.diff ]
        then
                echo "*********************************"
                echo "*** WARNING: Regression found ***"
                echo "*********************************"
                cat $TMP_DIR/$file_check.diff
        else
                echo " |-> No regression"
        fi

}

function main()
{
        if [ $# -lt 2 ] || [ "$1" == "--help" ]
        then
                echo ""
                echo " Syntax: $0 --regression-with [version]"
                echo "         $0 --help"
                echo ""

                exit 1
        fi

        TMP_DIR=`mktemp -d -p $REG_PATH/`
        REG_VER=$2
        run_check test-var-all
        run_check test-var-char
        run_check test-var-gold
        run_check test-var-integer
        run_check test-var-ipv4
        run_check test-var-short
        run_check test-var-string1
        run_check test-var-string2

        rm -rf $TMP_DIR
}

main $@

