#! /bin/bash

echo "Deleting old files"
rm *.pb.cc
rm *.pb.h
echo "Generating Proto Files"
protoc -I=./ --cpp_out=./ ProtoModuleInterface.proto
ls | grep "ProtoModuleInterface.*"