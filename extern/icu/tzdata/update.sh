#!/bin/sh

# Change version.txt before run this script.

THIS_DIR=`readlink -f $0`
THIS_DIR=`dirname $THIS_DIR`

TMP_DIR=`mktemp -d`
VERSION=`cat $THIS_DIR/version.txt`
BASE_URL=https://github.com/unicode-org/icu-data/raw/master/tzdata/icunew/$VERSION/44

echo Downloading and updating little-endian files...
mkdir $TMP_DIR/le
cd $TMP_DIR/le
curl -OLs $BASE_URL/le/metaZones.res
curl -OLs $BASE_URL/le/timezoneTypes.res
curl -OLs $BASE_URL/le/windowsZones.res
curl -OLs $BASE_URL/le/zoneinfo64.res
rm $THIS_DIR/le.zip
zip $THIS_DIR/le.zip *.res

echo Downloading and updating big-endian files...
mkdir $TMP_DIR/be
cd $TMP_DIR/be
curl -OLs $BASE_URL/be/metaZones.res
curl -OLs $BASE_URL/be/timezoneTypes.res
curl -OLs $BASE_URL/be/windowsZones.res
curl -OLs $BASE_URL/be/zoneinfo64.res
rm $THIS_DIR/be.zip
zip $THIS_DIR/be.zip *.res

rm -r $TMP_DIR
