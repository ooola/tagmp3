#!/bin/sh

DATE=`date`
VERSION=`git describe --tags`
GITSHA=`git rev-parse HEAD`

cp version.template version.cpp
perl -p -i -e "s/DATE/$DATE/" version.cpp
perl -p -i -e "s/VERSION/$VERSION/" version.cpp
perl -p -i -e "s/GITSHA/$GITSHA/" version.cpp
