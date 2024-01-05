#!/usr/bin/bash

if ! [ -d sol ]; then
    mkdir sol
fi
if ! [ -d input ]; then
    mkdir input
fi

usage() {
    echo "Usage: $0 [-h] [-s Date] [-d Date]"
    echo
    echo "s          Run the setup for day <Date>"
    echo "h          Print this help function"
    echo "d          Download the input of <Date> (download input only)"
}

DAY=""
download() {
    YEAR="2023"
    DAY_NO_ZEROS="$(echo $DAY | sed 's/^0*//')"
    DAY_FORMATTED="$(printf %02d $DAY)"
    OUTPUT="input/Day_${DAY_FORMATTED}.txt"
    PUZZLE_URL="https://adventofcode.com/${YEAR}/day/${DAY_NO_ZEROS}/input"

    if [ -z "$DAY" ]; then
        echo "[🎄 ERROR] You must set the date to download!"
        exit 1
    fi
    # Check if input is already created
    if [ -f "input/Day_${DAY_FORMATTED}.txt" ]; then
        echo "[🎄 ERROR] Input Day_${DAY_FORMATTED} has already been created!"
        exit 1
    fi
    # Check if cookie is set
    if [[ -z "$AOC_SESSION" ]]; then
        echo "[🎄 ERROR] No 🍪 found! run aocd-token and then set AOC_SESSION"
        exit 1
    fi
    # Download input
    curl "${PUZZLE_URL}" -H "cookie: session=${AOC_SESSION}" -o "${OUTPUT}" 2>/dev/null
}

setup() {
    if [ -z "$DAY" ]; then
        echo "[🎄 ERROR] You must set the date to download!"
        exit 1
    fi
    # Check if coding dir is already created
    if [ -d "sol/Day_${DAY_FORMATTED}" ]; then
        echo "[🎄 ERROR] Directory Day_${DAY_FORMATTED} has already been created!"
        exit 1
    fi
    FILE="sol/Day_${DAY_FORMATTED}/Day_${DAY_FORMATTED}"
    # Setup environment
    mkdir -p "sol/Day_${DAY_FORMATTED}"
    cp temp/temp.cc "${FILE}.cc"
    cp temp/temp.hh "${FILE}.hh"
    # replace day number
    sed -i "s/temp/Day_${DAY_FORMATTED}/g" "${FILE}.cc"
    sed -i "s/dayXX/day${DAY_FORMATTED}/g" "${FILE}.cc"
    sed -i "s/dayXX/day${DAY_FORMATTED}/g" "${FILE}.hh"
    sed -i "s/DAY_XX/DAY_${DAY_FORMATTED}/g" "${FILE}.hh"

    # insert solver to header
    sed -i "s:// TMP_H:#include \"${FILE}.hh\"\n// TMP_H:g" "sol.hh"
    # insert entry
    sed -i "s:// TMP_ENTRY:   \{${DAY}, \&day${DAY}\},\n // TMP_ENTRY:g" "sol.hh"

    # Finished!
    echo "[🎅 SUCCESS] You can now begin your coding!"

}

if [[ ! $@ =~ ^\-.+ ]]; then
    usage
    exit 0
fi

while getopts ":d:hs:" arg; do
    case $arg in
    s)
        DAY=${OPTARG}
        download
        setup
        exit 0
        ;;
    d)
        DAY=${OPTARG}
        download
        exit 0
        ;;
    h | *)
        usage
        ;;
    esac
done
