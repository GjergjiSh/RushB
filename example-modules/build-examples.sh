cd Writer && make;
pwd;
cd ../Reader && make;
pwd;
cd ../;
pwd;
find . -name "*.so" -type f -exec cp {} ../bin/modules \;