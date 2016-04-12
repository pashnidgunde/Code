
//=========================================================================================
                        Folder structure
//========================================================================================
Build with clang using command:

./sh : contains script to execute the binary 

./bin : contains executable after running following build command

./config : includes configuration and input files for testing
           config.xml :: Weight configuration file
           input.xml :: includes input of marks

./source : includes source files


//=========================================================================================
                        Build Instructions:
//========================================================================================
Build with clang using command:

$ cd Assignment
$ mkdir bin
$ cd source
$ clang -std=c++11 main.cpp weightage_reader.cpp student_information.cpp student_info_reader.cpp 
../bin/find_grades ../config/config.xml ../config/input.xml

//========================================================================================
//                      Config and Input Setup
//========================================================================================

Config :: 
        1. Setup weight in % , use config.xml under config directory
Input: 
        1. Use file input.xml under config 
        2. Add multiple entries of students as required
        3. For extra credits, add a extra credit line in input 

//========================================================================================
//                      How to Execute using binary ( manually )
//========================================================================================

$ cd bin
$ ./find_grades ../config/config.xml ../config/input.xml

//========================================================================================
//                     How to execute using shell script with sample output
//========================================================================================

$ cd sh
/home/rupa/Code/assignment/assignment/sh:./find_grades.sh
Please provide config directory
usage: ./find_grades.sh config_dir
/home/rupa/Code/assignment/assignment/sh:./find_grades.sh ../config/
Setup :: Configuration file ==> ../config//config.xml and Input file ==> ../config//input.xml
Config values ::  Teacher Name ==> Prashant Assignment Weightage ==> 10.1 Exam Weightage ==> 89.9 Extra Credits/Per assignment ==> 2
----------------------------------------------------------------
Weightage calculation for Sally
After Assignment #1 is logged in the system: 85
After Assignment #2 is logged in the system: 86.5
After ExtraCredit #1 is logged in the system: 88.5
After Assignment #3 is logged in the system: 90.3333
After Exam #1 is logged in the system: 90.9327
----------------------------------------------------------------
Weightage calculation for Sony
After Assignment #1 is logged in the system: 85
After Assignment #2 is logged in the system: 81
After ExtraCredit #1 is logged in the system: 83
After ExtraCredit #2 is logged in the system: 85
After Assignment #3 is logged in the system: 88.6667
After Exam #1 is logged in the system: 90.7643
----------------------------------------------------------------
Weightage calculation for Dolly
After Assignment #1 is logged in the system: 85
After Assignment #2 is logged in the system: 83
After Assignment #3 is logged in the system: 87
After Exam #1 is logged in the system: 97.788
======================================== 
               Grade reports 
======================================== 
Final grade for Sally:: 90.9327
Final grade for Sony:: 90.7643
Final grade for Dolly:: 97.788

//========================================================================================
//                    Build Unit Tests
//========================================================================================
clang main.cpp -I/home/rupa/unittest-cpp /home/rupa/unittest-cpp/builds/libUnitTest++.a -o ../bin/unittests


//========================================================================================
//                   Execute UnitTests 
//========================================================================================
cd bin
./unittests

