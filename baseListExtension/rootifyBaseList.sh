#!/bin/bash
source ~/.bashrc

# Remove all existing base list spreadsheets and .csvs
rm -rf base_list-A4-unrestricted.*
rm -rf base_list-A3-unrestricted.*

# Remove all relevant existing root files
rm -f baseList.root
rm -f baseListA3.root

# Get most recent from the elog. CHECK the string after anita_notes
echo "Pulling the newest spreadsheets from the elog"
wget -N "https://www.phys.hawaii.edu/elog/anita_notes/170409_223955/base_list-A4-unrestricted.ods" # overwrite!
wget -N "https://www.phys.hawaii.edu/elog/anita_notes/170410_214006/base_list-A3-unrestricted.ods" # overwrite!

echo "Converting the individual spreadsheet 'sheets' into .csv files"
# converts spreadsheets into individual sheets
ssconvert -S base_list-A4-unrestricted.ods base_list-A4-unrestricted.csv
ssconvert -S base_list-A3-unrestricted.ods base_list-A3-unrestricted.csv

echo "Sorting out the files..."
# get rid of first 2 headers
sed -i '1,2 d' base_list-A4-unrestricted.csv.0
sed -i '1,2 d' base_list-A4-unrestricted.csv.1
sed -i '1,2 d' base_list-A4-unrestricted.csv.2
sed -i '1,2 d' base_list-A3-unrestricted.csv.0
sed -i '1,2 d' base_list-A3-unrestricted.csv.1
sed -i '1,2 d' base_list-A3-unrestricted.csv.2

# in case there are any empty fields, replace them with -999
sed -i 's/,\{2,\}/,-999,/g' base_list-A4-unrestricted.csv.0
sed -i 's/,\{2,\}/,-999,/g' base_list-A4-unrestricted.csv.1
sed -i 's/,\{2,\}/,-999,/g' base_list-A4-unrestricted.csv.2
sed -i 's/,\{2,\}/,-999,/g' base_list-A3-unrestricted.csv.0
sed -i 's/,\{2,\}/,-999,/g' base_list-A3-unrestricted.csv.1
sed -i 's/,\{2,\}/,-999,/g' base_list-A3-unrestricted.csv.2

# replaced exported quotes with nothing
sed -i 's/"//g' base_list-A4-unrestricted.csv.0
sed -i 's/"//g' base_list-A4-unrestricted.csv.1
sed -i 's/"//g' base_list-A4-unrestricted.csv.2
sed -i 's/"//g' base_list-A3-unrestricted.csv.0
sed -i 's/"//g' base_list-A3-unrestricted.csv.1
sed -i 's/"//g' base_list-A3-unrestricted.csv.2

# replace approximations (~) with nothing
sed -i 's/~//g' base_list-A4-unrestricted.csv.0
sed -i 's/~//g' base_list-A4-unrestricted.csv.1
sed -i 's/~//g' base_list-A4-unrestricted.csv.2
sed -i 's/~//g' base_list-A3-unrestricted.csv.0
sed -i 's/~//g' base_list-A3-unrestricted.csv.1
sed -i 's/~//g' base_list-A3-unrestricted.csv.2

# Move csvs to a folder and tar 'em up
mkdir baseListCSVs
cp base_list-A3-unrestricted.csv.0 base_list-A3-unrestricted.csv.1 base_list-A3-unrestricted.csv.2 base_list-A4-unrestricted.csv.0 base_list-A4-unrestricted.csv.1 base_list-A4-unrestricted.csv.2 baseListCSVs
tar -zcvf baseListCSVs.tar.gz baseListCSVs

echo "Running rootfication scripts"
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PWD
root -b -l <<EOF
   .X basesCampsRootifier.cxx
   .X fixedWingRootifier.cxx	
   .X awsRootifier.cxx
   .X basesCampsRootifierA3.cxx
   .X fixedWingRootifierA3.cxx	
   .X awsRootifierA3.cxx
EOF

echo "Done!"
