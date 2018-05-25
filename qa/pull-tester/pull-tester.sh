#!/bin/sh
# Copyright (c) 2013 The Straks Core developers
# Distributed under the MIT/X11 software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.
#
# Helper script for pull-tester.
#Param 1: path to seci srcroot
#Param ...: arguments for build-test.sh

if [ $# -lt 1 ]; then
  echo "usage: $0 [seci srcroot] build-test arguments..."
fi

killall -q seci-cli
killall -q secid

cd $1
shift

./autogen.sh
./configure
./qa/pull-tester/build-tests.sh "$@"
