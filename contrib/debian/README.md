
Debian
====================
This directory contains files used to package secid/seci-qt
for Debian-based Linux systems. If you compile secid/seci-qt yourself, there are some useful files here.

## seci: URI support ##


seci-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install seci-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your seci-qt binary to `/usr/bin`
and the `../../share/pixmaps/seci128.png` to `/usr/share/pixmaps`

seci-qt.protocol (KDE)

