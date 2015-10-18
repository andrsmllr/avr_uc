#!/bin/sh
##############################################################################
# Script to create a new AVR uC project from template.
##############################################################################

# Check given command line arguments.
if [ $# != 1 ]; then
    echo "Invalid number of arguments. Please provide a name for the new project."
    exit
fi

# Create new AVR uC project folder.
parentDir=`dirname $1`
if [ $parentDir!='.' ]; then
    mkdir $1
    projectDir='./'$1
else
    mkdir `pwd`/$1
    projectDir=''
fi

# Copy template to new AVR uC project folder.
cp -r ./template/* $1

# Rename files to match the new AVR uC project name.
mv $1/template.c $1/$1.c
mv $1/template.h $1/$1.h

# Replace template tokens by values.
TIMESTAMP=`date +%Y-%m-%d`
sed -e "s/<PROJECT NAME>/$1/" -i $1/Makefile
sed -e "s/YYYY-MM-DD/$TIMESTAMP/g" -i $1/$1.c $1/$1.h
sed -e "s/template/$1/g" -i $1/$1.c
sed -e "s/template/$1/g" -i $1/$1.h
sed -e "s/TEMPLATE/`echo $1 | tr [:lower:] [:upper:]`/g" -i $1/$1.h
