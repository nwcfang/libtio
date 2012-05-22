#!/bin/bash

state=""

LD_OLD=${LD_LIBRARY_PATH}
export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:$(pwd)/lib/


case "$TERM" in
    xterm-color|linux|xterm*) 
        color_prompt="yes";
	echo "I have color";;
    *)
        color_prompt='no';
	echo "No colors :(";;
esac

if [ "${color_prompt}" = "yes" ] ; then
    TS="(\033[0;36mTS\033[0m)";
    TSPASS="\033[0;32mPASS\033[0m";
    TSFAIL="\033[0;31mFAIL\033[0m";
    TSFINFAIL="\033[0;31mTESTING FAIL\033[0m";
    TSFINPASS="\033[0;32mAll tests PASS\033[0m";
    RUNMSG="\033[1;34mRun test:\033[0m";
    TEST="\033[1;34mTest \033[0m";
else
    TS="(TS) ";
    TSPASS="PASS";
    TSFAIL="FAIL";
    TSFINFAIL="TESTING FAIL"
    TSFINPASS="All tests PASS"
    RUNMSG="Run test:";
    TEST="Test ";
fi;
    

if test -z $1 ; then 
    echo "ERROR YOU SHULD SHOW WHERE I NEED SEARCH TEST FILES";
fi;

for i in `ls $1/test_*`; do
    echo -e "$TS: $RUNMSG $i"
    if ! ./$i ; then
        echo -e "$TS: $TEST $i [$TSFAIL]";
        state="fail";        
    else
        echo -e "$TS: $TEST $i [$TSPASS]";
    fi;
done;

if ls $1/fail_* &> /dev/null; then
    for i in `ls $1/fail_* | egrep -v "\.result$"`; do
        echo -e "$TS: $RUNMSG $i"
        result="";
        if test -f "${i}.result"; then
            result=`cat ${i}.result`;
        fi
        ./$i;
        pres=$?;
        if test -n "${result}"; then
            if test ! "${result}" = "${pres}"; then
                echo -e "$TS: $TEST $i [$TSFAIL]";
                state="fail";
            else
                echo -e "$TS: $TEST $i [$TSPASS]";
            fi;
        else
            if test ${pres} -ne 0; then
                echo -e "$TS: $TEST $i [$TSPASS]";
            else
                echo -e "$TS: $TEST $i [$TSFAIL]";
                state="fail";
            fi;
        fi;
    done;
fi;

export LD_LIBRARY_PATH=${LD_OLD}        

if [ -z ${state} ]; then    
    echo -e "$TS: $TSFINPASS";
else
    echo -e "\a$TS: $TSFINFAIL";
    exit -1;    
fi;

