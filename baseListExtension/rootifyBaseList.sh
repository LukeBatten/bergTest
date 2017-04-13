#!/bin/bash
source ~/.bashrc

# Remove all existing base list spreadsheets and .csvs
rm -rf base_list-A4-unrestricted.*
rm -rf base_list-A3-unrestricted.*

# Remove all relevant existing root files and other folders produced
rm -f baseList.root
rm -f baseListA3.root
rm -r baseData/
rm -r baseListCSVs/

# Get most recent from the elog. CHECK the string after anita_notes
echo "Pulling the newest spreadsheets from the elog"
wget -N "https://www.phys.hawaii.edu/elog/anita_notes/170412_152445/base_data_unrestricted-A4.tar.gz" # overwrite!
wget -N "https://www.phys.hawaii.edu/elog/anita_notes/170412_152426/base_data_unrestricted-A3.tar.gz" #overwrite!

echo "Extracting information..."
mkdir ./baseData
tar -zxf base_data_unrestricted-A4.tar.gz -C ./baseData
tar -zxf base_data_unrestricted-A3.tar.gz -C ./baseData

cp ./baseData/unrestricted-A4/base_list-A4-unrestricted.ods .
cp ./baseData/unrestricted-A3/base_list-A3-unrestricted.ods .

echo "Converting the individual spreadsheet 'sheets' into .csv files"
# converts spreadsheets into individual sheets
ssconvert -S base_list-A4-unrestricted.ods base_list-A4-unrestricted.csv
ssconvert -S base_list-A3-unrestricted.ods base_list-A3-unrestricted.csv

echo "Sorting out the files..."
# get rid of first 2 headers
sed -i '1,2 d' base_list-A4-unrestricted.csv.0
sed -i '1,2 d' base_list-A4-unrestricted.csv.1
sed -i '1,2 d' base_list-A4-unrestricted.csv.2
sed -i '1,2 d' base_list-A4-unrestricted.csv.3
sed -i '1,2 d' base_list-A3-unrestricted.csv.0
sed -i '1,2 d' base_list-A3-unrestricted.csv.1
sed -i '1,2 d' base_list-A3-unrestricted.csv.2
sed -i '1,2 d' base_list-A3-unrestricted.csv.3

# in case there are any empty fields, replace them with -999
sed -i 's/,\{2,\}/,-999,/g' base_list-A4-unrestricted.csv.0
sed -i 's/,\{2,\}/,-999,/g' base_list-A4-unrestricted.csv.1
sed -i 's/,\{2,\}/,-999,/g' base_list-A4-unrestricted.csv.2
sed -i 's/,\{2,\}/,-999,/g' base_list-A4-unrestricted.csv.3
sed -i 's/,\{2,\}/,-999,/g' base_list-A3-unrestricted.csv.0
sed -i 's/,\{2,\}/,-999,/g' base_list-A3-unrestricted.csv.1
sed -i 's/,\{2,\}/,-999,/g' base_list-A3-unrestricted.csv.2
sed -i 's/,\{2,\}/,-999,/g' base_list-A3-unrestricted.csv.3

# replaced exported quotes with nothing
sed -i 's/"//g' base_list-A4-unrestricted.csv.0
sed -i 's/"//g' base_list-A4-unrestricted.csv.1
sed -i 's/"//g' base_list-A4-unrestricted.csv.2
sed -i 's/"//g' base_list-A4-unrestricted.csv.3
sed -i 's/"//g' base_list-A3-unrestricted.csv.0
sed -i 's/"//g' base_list-A3-unrestricted.csv.1
sed -i 's/"//g' base_list-A3-unrestricted.csv.2
sed -i 's/"//g' base_list-A3-unrestricted.csv.3

# replaced 'comma space' with nothing to fix issues such as "Henderson, Mount"
sed -i 's/, //g' base_list-A4-unrestricted.csv.0
sed -i 's/, //g' base_list-A4-unrestricted.csv.1
sed -i 's/, //g' base_list-A4-unrestricted.csv.2
sed -i 's/, //g' base_list-A4-unrestricted.csv.3
sed -i 's/, //g' base_list-A3-unrestricted.csv.0
sed -i 's/, //g' base_list-A3-unrestricted.csv.1
sed -i 's/, //g' base_list-A3-unrestricted.csv.2
sed -i 's/, //g' base_list-A3-unrestricted.csv.3

# replace approximations (~) with nothing
sed -i 's/~//g' base_list-A4-unrestricted.csv.0
sed -i 's/~//g' base_list-A4-unrestricted.csv.1
sed -i 's/~//g' base_list-A4-unrestricted.csv.2
sed -i 's/~//g' base_list-A4-unrestricted.csv.3
sed -i 's/~//g' base_list-A3-unrestricted.csv.0
sed -i 's/~//g' base_list-A3-unrestricted.csv.1
sed -i 's/~//g' base_list-A3-unrestricted.csv.2
sed -i 's/~//g' base_list-A3-unrestricted.csv.3

# Move csvs to a folder and tar 'em up (made due to a request)
mkdir baseListCSVs
cp base_list-A3-unrestricted.csv.0 base_list-A3-unrestricted.csv.1 base_list-A3-unrestricted.csv.2 base_list-A3-unrestricted.csv.3  base_list-A4-unrestricted.csv.0 base_list-A4-unrestricted.csv.1 base_list-A4-unrestricted.csv.2 base_list-A4-unrestricted.csv.3 baseListCSVs
tar -zcvf baseListCSVs.tar.gz baseListCSVs

echo "--------"

echo "Running rootfication scripts"
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PWD
root -b -l <<EOF
     .! echo "Making ANITA-4 trees..."
   .X basesCampsRootifier.cxx
   .X antarcticTreatyRootifier.cxx
   .X fixedWingRootifier.cxx	
   .X awsRootifier.cxx
   .! echo "--------"
   .! echo "Making ANITA-3 trees..." 
   .X basesCampsRootifierA3.cxx
   .X antarcticTreatyRootifierA3.cxx	
   .X fixedWingRootifierA3.cxx	
   .X awsRootifierA3.cxx
   .! echo "--------"
EOF

echo "Tidying..."
rm -rf base_list-A*
rm -rf base_data_unrestricted-A*

echo "Done!"
