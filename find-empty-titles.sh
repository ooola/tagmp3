#!/bin/bash
# This script looks for mp3 files with empty titles

check_file_for_empty_title() {
    TAGMP3=/usr/local/bin/tagmp3
    file="$1"
    title=$( $TAGMP3 -p "$file" | grep '^TITLE' )
    len=${#title} 
    
    if [ "$len" = "7" ]; then
        echo "Found file with no title: $file"
    fi
}

export -f check_file_for_empty_title

find . -type f -name '*.mp3' -exec bash -c 'check_file_for_empty_title "$0"' {} \;
