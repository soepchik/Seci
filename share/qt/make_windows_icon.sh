#!/bin/bash
# create multiresolution windows icon
ICON_SRC=../../src/qt/res/icons/seci.png
ICON_DST=../../src/qt/res/icons/seci.ico
convert ${ICON_SRC} -resize 16x16 seci-16.png
convert ${ICON_SRC} -resize 32x32 seci-32.png
convert ${ICON_SRC} -resize 48x48 seci-48.png
convert seci-16.png seci-32.png seci-48.png ${ICON_DST}

