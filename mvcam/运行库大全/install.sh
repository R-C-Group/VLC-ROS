#!/bin/bash

CURDIR=`pwd`
echo "Your current directory is $CURDIR. This is where the MVSDK software will be installed..."
A=`whoami`
B=`arch`

if [ $A != 'root' ]; then
   echo "You have to be root to run this script"
   echo "Fail !!!"
   exit 1;
fi

# 与管理员权限有关的rule文件
cp 88-mvusb.rules /etc/udev/rules.d/

# 运行库设置
echo $B
if [ $B = "x86_64" ]; then
	cp x86_64/libMVSDK.so  /lib
	cp x86_64/libMVSDK.so  ../lib
	echo "Copy x86_64 64bit libMVSDK.so to /lib"
elif [ $B = "i386" ]; then
	cp i386/libMVSDK.so  /lib
	cp i386/libMVSDK.so  ../lib
	echo "Copy i386 libMVSDK.so to /lib"
elif [ $B = "armhf" ]; then
	cp armhf/libMVSDK.so  /lib
	cp armhf/libMVSDK.so  ../lib
	echo "Copy armhf 32bit libMVSDK.so to /lib"
else
	echo "Not support"
	exit 1;
fi

echo "Successful"
echo "Please  restart system  now!!!"
