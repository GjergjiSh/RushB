#! /bin/bash

echo "Deleting old files"
rm ../src/*.pb.cc
rm ../include/*.pb.h
echo "Generating Proto Files"
protoc -I=./ --cpp_out=./ ProtoModuleInterface.proto
ls | grep "ProtoModuleInterface.*"
mv ProtoModuleInterface.pb.cc ../src
mv ProtoModuleInterface.pb.h ../include
