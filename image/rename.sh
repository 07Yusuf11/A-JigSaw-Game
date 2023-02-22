#!/bin/bash

for file in *.png; do
	newfile=$(echo $file | sed -E 's/([0-9]+)-([0-9]+)\.png/Block\1-\2.png/')
	mv "$file" "$newfile"
done
