#!/usr/bin/bash

if ! [ -d sol ]; then
    mkdir sol
fi
if ! [ -d input ]; then
    mkdir input
fi

YEAR="${1}"
DAY="${2}"
DAY_NO_ZEROS="$(echo $DAY | sed 's/^0*//')"
DAY_FORMATTED="$(printf %02d $DAY)"
OUTPUT="input/Day_${DAY_FORMATTED}.txt"
PUZZLE_URL="https://adventofcode.com/${YEAR}/day/${DAY_NO_ZEROS}/input"

# Check if cookie is set
if [[ -z "$AOC_SESSION_COOKIE" ]]; then
    echo "No session cookie🍪 found! run aocd-token and then set AOC_SESSION_COOKIE"
    exit 1
fi

# Check if coding dir is already created
if [ -d "sol/Day_${DAY_FORMATTED}" ]; then
    echo "🎄 ERROR: Dir Day_${DAY_FORMATTED} has already been created!"
    exit 1
fi

# Download input
curl "${PUZZLE_URL}" -H "cookie: session=${AOC_SESSION_COOKIE}" -o "${OUTPUT}" 2>/dev/null

# Setup environment
mkdir -p "sol/Day_${DAY_FORMATTED}"
cp temp/temp.cc "sol/Day_${DAY_FORMATTED}/Day_${DAY_FORMATTED}.cc"
cp temp/temp.hh "sol/Day_${DAY_FORMATTED}/Day_${DAY_FORMATTED}.hh"
cp temp/Makefile "sol/Day_${DAY_FORMATTED}/Makefile"
# replace header file for day X
sed -i "s/temp/Day_${DAY_FORMATTED}/g" "sol/Day_${DAY_FORMATTED}/Day_${DAY_FORMATTED}.cc"

# Finished!
echo "🎅 You can now begin your coding!"