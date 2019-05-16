#!/bin/bash

sed -n '/<key>CFBundleVersion<\/key>/{n;p;}' < Info.plist | awk -F '>' '{print $2}' | awk -F '<' '{print $1}'
