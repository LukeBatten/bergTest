#!/bin/bash
source ~/.bashrc

# Remove all existing base list spreadsheets and .csvs
rm -rf base_list-A4-unrestricted.*

# Remove all relevant existing root files
rm -f baseList.root

# Just do for ANITA-4 for now
echo "Pulling the newest spreadsheets from the elog"
wget -N "https://www.phys.hawaii.edu/elog/anita_notes/170409_223955/base_list-A4-unrestricted.ods" # overwrite!

echo "Converting the individual spreadsheet 'sheets' into .csv files"
# converts spreadsheets into individual sheets
ssconvert -S base_list-A4-unrestricted.ods base_list-A4-unrestricted.csv

echo "Sorting out the files..."
# get rid of first 2 headers
sed -i '1,2 d' base_list-A4-unrestricted.csv.0
sed -i '1,2 d' base_list-A4-unrestricted.csv.1
sed -i '1,2 d' base_list-A4-unrestricted.csv.2

# in case there are any empty fields, replace them with -999
sed -i 's/,\{2,\}/,-999,/g' base_list-A4-unrestricted.csv.0
sed -i 's/,\{2,\}/,-999,/g' base_list-A4-unrestricted.csv.1
sed -i 's/,\{2,\}/,-999,/g' base_list-A4-unrestricted.csv.2

# replaced exported quotes with nothing
sed -i 's/"//g' base_list-A4-unrestricted.csv.0
sed -i 's/"//g' base_list-A4-unrestricted.csv.1
sed -i 's/"//g' base_list-A4-unrestricted.csv.2

echo "Running rootfication scripts"
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PWD
root -b -l <<EOF
   .X basesCampsRootifier.cxx
   .X fixedWingRootifier.cxx	
   .X awsRootifier.cxx
EOF

echo "Done!"
