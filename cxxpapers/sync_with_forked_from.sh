#!/bin/sh
git remote -v
git fetch forked_from
git rebase forked_from/master
echo
echo
echo ===========================================================================================
echo "Now you need to type: git push -f"        !!!!! but only if rebase was uneventful !!!!!
echo ===========================================================================================
