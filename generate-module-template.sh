#! /bin/bash

read -p "Enter directory name: " DirName;
read -p "Enter module name: " ModuleName
echo "Generating Module Template ${ModuleName}";
#Set up module directories
mkdir -p ./${DirName};
mkdir -p ./${DirName}/src;
mkdir -p ./${DirName}/include;

#Copy templates in created directories
cp ./.templates/TEMPLATE.* ${DirName};
cp ./.templates/CMakeLists.txt ${DirName};

#Rename the created templates
mv ${DirName}/TEMPLATE.cpp ${DirName}/src/${ModuleName}.cpp;
mv ${DirName}/TEMPLATE.h ${DirName}/include/${ModuleName}.h;

#Change the class names in the tamplates
sed -i 's/TEMPLATE/'${ModuleName}'/g' ${DirName}/src/${ModuleName}.cpp;
sed -i 's/TEMPLATE/'${ModuleName}'/g' ${DirName}/include/${ModuleName}.h;
sed -i 's/TEMPLATE/'${ModuleName}'/g' ${DirName}/CMakeLists.txt;

#Create Readme
touch ${DirName}/README.md

#Move created module directory to modules directory
mv ${DirName} ./modules

#Add sub directory to modules top level cmake lists
echo "add_subdirectory($DirName)" | tee -a ./modules/CMakeLists.txt

