#!/bin/bash
#
# Helper script for i18n.
#

I18N_BASE=Base.lproj
LANG_LIST=i18n-supported.list

if [ "$1" == "extract" ] ; then
	# Extract string tables from the mother nibs:
	echo "Creating string tables for languages..."
	for lang in `tail -n 1 $LANG_LIST` ; do
		if [ "$lang.lproj" != "$I18N_BASE" ] ; then
			echo "  .. $lang"
			if [ ! -d "$lang.lproj" ] ; then
				mkdir "$lang.lproj"
			fi
		
			for nib in $I18N_BASE/*.nib ; do
				BASE_NIB=`basename $nib .nib`

				echo "  .... $BASE_NIB.nib"
			
				if [ -f "$lang.lproj/$BASE_NIB.strings" ] ; then
					DEST=$lang.lproj/$BASE_NIB-merge.strings
					echo "  ###### Already exists - writing to $DEST."
				else 
					DEST=$lang.lproj/$BASE_NIB.strings					
				fi
				ibtool --generate-stringsfile $DEST $nib
			done
		else
			echo "  .. Skipping BASE language: $lang"
		fi
	done
elif [ "$1" == "apply" ] ; then
	# Apply string tables to create nibs
	echo "Applying i18n to NIB files..."
	for lang in `tail -n 1 $LANG_LIST` ; do
		if [ "$lang.lproj" != "$I18N_BASE" ] ; then
			echo "  .. $lang"
		
			if [ ! -d "$lang.lproj" ] ; then
				mkdir "$lang.lproj"
			fi
		
			for nib in $I18N_BASE/*.nib ; do
				BASE_NIB=`basename $nib .nib`

				echo "  .... $BASE_NIB.nib"
			
				ibtool --strings-file $lang.lproj/$BASE_NIB.strings \
					--write $lang.lproj/$BASE_NIB.nib $nib
			done
		else
			echo "  .. Skipping BASE language: $lang"
		fi
	done
elif [ "$1" == "merge" ] ; then
	# Merge changes
	echo "Merging doesn't work yet."
	exit 1
	
	ibtool --previous-file ./old/Resources/en.lproj/MyNib.nib \
		--incremental-file ./old/Resources/fr.lproj/MyNib.nib \
		--strings-file ./new/Resources/fr.lproj/French_2.0.strings \
		--localize-incremental \
		--write ./new/Resources/fr.lproj/MyNib.nib \
		./new/Resources/en.lproj/MyNib.nib
else
	echo "Usage: $0 [extract|apply|merge]"
	exit 1
fi
