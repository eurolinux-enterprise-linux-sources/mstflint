#!/bin/sh

rev=`git parse-rev HEAD`
sed -e 's/#define TOOLS_SVN_VER "N\/A"/#define TOOLS_SVN_VER "$rev" $1
