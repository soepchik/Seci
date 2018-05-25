#!/bin/sh

TOPDIR=${TOPDIR:-$(git rev-parse --show-toplevel)}
SRCDIR=${SRCDIR:-$TOPDIR/src}
MANDIR=${MANDIR:-$TOPDIR/doc/man}

SECID=${SECID:-$SRCDIR/secid}
SECICLI=${SECICLI:-$SRCDIR/seci-cli}
SECITX=${SECITX:-$SRCDIR/seci-tx}
SECIQT=${SECIQT:-$SRCDIR/qt/seci-qt}

[ ! -x $SECID ] && echo "$SECID not found or not executable." && exit 1

# The autodetected version git tag can screw up manpage output a little bit
SECIVER=($($SECICLI --version | head -n1 | awk -F'[ -]' '{ print $6, $7 }'))

# Create a footer file with copyright content.
# This gets autodetected fine for secid if --version-string is not set,
# but has different outcomes for seci-qt and seci-cli.
echo "[COPYRIGHT]" > footer.h2m
$SECID --version | sed -n '1!p' >> footer.h2m

for cmd in $SECID $SECICLI $SECITX $SECIQT; do
  cmdname="${cmd##*/}"
  help2man -N --version-string=${SECIVER[0]} --include=footer.h2m -o ${MANDIR}/${cmdname}.1 ${cmd}
  sed -i "s/\\\-${SECIVER[1]}//g" ${MANDIR}/${cmdname}.1
done

rm -f footer.h2m
