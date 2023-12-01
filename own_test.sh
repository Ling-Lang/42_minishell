#!/bin/bash
MPATH="./minishell"
PROMPT=$(echo -e "\nexit\n" | $MPATH | head -n 1 | sed "s/\x1B\[[0-9;]\{1,\}[A-Za-z]//g" )
REMOVE_COLORS="sed s/\x1B\[[0-9;]\{1,\}[A-Za-z]//g"
REMOVE_EXIT="grep -v ^exit$"

mkdir ./mout
mkdir ./bout
mkdir ./out
function exec_test()
{
	TEST1=$(echo -e $@ | ./minishell 2>&- /dev/null | $REMOVE_COLORS | grep -vF "$PROMPT" | $REMOVE_EXIT )
    # TEST1=$(echo $@ "; exit" | ./minishell 2>&-)
    ES_1="$?"
    TEST2=$(echo -e $@ | bash 2>&-)
	ES_2=$?
    # printf "\n$MINI_OUTPUT\n"
    if [ "$TEST1" == "$TEST2" ] && [ "$ES_1" == "$ES_2" ]; then
		printf "✓ "
    else
        printf "$ES_1\t$ES_2\nMINISHELL:\n$TEST1\n\nBASH:\n$TEST2\n"
    fi
    echo
    sleep 0.1
}
function exec_diff_test()
{
    rm -rf ./out/*
    rm -rf ./mout/*
    TEST1=$(echo -e $@ | ./minishell 2>&- /dev/null | $REMOVE_COLORS | grep -vF "$PROMPT" | $REMOVE_EXIT )
    MOUT=$(cp ./out/* ./mout &>/dev/null)
    ES_1="$?"
    rm -rf ./out/*
    rm -rf ./bout/*
    TEST2=$(echo -e $@ | bash 2>&-)
    BOUT=$(cp ./out/* ./bout &>/dev/null)
	ES_2=$?
    ODIFF=$(diff --brief ./mout ./bout)
    if [ "$TEST1" == "$TEST2" ] && [ "$ES_1" == "$ES_2" ] && [ -z "$ODIFF" ]; then
		printf "✓ "
    else
        printf "$ES_1\t$ES_2\n$TEST1\t$TEST2\n"
    fi

}
TEST_FILE="file"
# exec_test 'echo test'
exec_test 'pwd'
exec_test 'ls -l | wc -l'
# exec_diff_test 'echo test > file'
exec_test 'echo $?'
# exec_test 'env'

rm -rf ./out
rm -rf ./bout
rm -rf ./mout