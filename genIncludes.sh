#! /bin/bash

createGeneric() {
  echo "-- Creating generic include file: $1.all"
  #Make sure we run into subdirectories first:
  dirs=()
  for file in "$1"/*
  do
    if [ -d "$file" ]
    then
      # Recursion:
      dirs+=( "$file" )
    fi
  done
  for dir in ${dirs[@]}
  do
    createGeneric $dir
  done
  #Now list all files, including newly created .all files:
  if [ -f $1.all ]
  then
    rm $1.all
  fi
  dir=`basename $1`
  for file in "$1"/*
  do
    if [ -f "$file" ] && ( [ "${file##*.}" == "h" ] || [ "${file##*.}" == "all" ] )
    then
      file=`basename $file`
      echo "#include \"$dir/$file\"" >> $1.all
    fi
  done;
}

createGeneric $1