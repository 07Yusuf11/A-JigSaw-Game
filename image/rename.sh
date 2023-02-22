#!/bin/bash

for file in *; do
	newfile=$(echo $file | sed -E 's/[0-9]+-([0-9]+)/Block\1.png/')
	mv "$file" "$newfile"
done
