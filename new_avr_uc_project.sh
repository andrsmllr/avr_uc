#!/bin/sh
##############################################################################
# Script to create a new AVR uC project from template.
##############################################################################

# Check given command line arguments.
if ($# != 1)
    echo "Invalid number of arguments. Please provide a name for the new project."
    exit

# Create new AVR uC project folder.
parentDir=`dirname $1`
if ( parentDir!='.' ) then
    mkdir $1
    projectDir='./'$1
else
    mkdir `pwd`/$1
    projectDir=
fi

# Copy template to new AVR uC project folder.
cp -r ./template/* $1

mv $1/template.c $1/$1.c
mv $1/template.h $1/$1.h
sed -i "s/<PROJECT NAME>/$1/" < $1/Makefile

