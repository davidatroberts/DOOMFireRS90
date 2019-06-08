#!/bin/sh

mkdir -p opk
cp build/fire opk/fire
mkdir opk/assets
cp assets/font.ttf opk/assets/font.ttf

print()
	case    ${IFS- } in
	(\ *)   printf  %b\\n "$*";;
	(*)     IFS=\ $IFS
	printf  %b\\n "$*"
	IFS=${IFS#?}
esac

print '[Desktop Entry]
Type=Application
Name=Fire
Comment=Doom Fire Demo
Exec=fire
Terminal=false
Type=Application
Categories=applications;
X-OD-NeedsDownscaling=false' > opk/default.rs90.desktop

mksquashfs ./opk fire.opk -all-root -noappend -no-exports -no-xattrs

rm -r opk
mv fire.opk build/fire.opk