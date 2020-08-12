#!/bin/bash

CURDIR=`pwd`
echo "Your current directory is $CURDIR. This is where the MVSDK software will be installed...\n"
A=`whoami`
B=`arch`

if [ $A != 'root' ]; then
   echo "You have to be root to run this script"
   echo "Fail !!!"
   exit 1;
fi

# 与管理员权限有关的rule文件
cp 88-mvusb.rules /etc/udev/rules.d/
echo "cp 88-mvusb.rules /etc/udev/rules.d/ \n"

# 运行库设置
echo "The processor architecture of this computer is $B \n"
if [ $B = "x86_64" ]; then
	cp x86_64/libMVSDK.so  /lib
	cp x86_64/libMVSDK.so  ../lib
	echo "Copy x86_64 64bit libMVSDK.so to /lib and ../lib \n"
elif [ $B = "i686" ]; then
	cp i386/libMVSDK.so  /lib
	cp i386/libMVSDK.so  ../lib
	echo "Copy i386 32bit libMVSDK.so to /lib and ../lib \n"
elif [ $B = "armv7l" ]; then
	cp armhf/libMVSDK.so  /lib
	cp armhf/libMVSDK.so  ../lib
	echo "Copy armhf 32bit libMVSDK.so to /lib and ../lib \n"
elif [ $B = "aarch64" ]; then
	cp armhf/libMVSDK.so  /lib
	cp armhf/libMVSDK.so  ../lib
	echo "Copy armhf 32bit libMVSDK.so to /lib and ../lib \n But I'm not sure if it's going to work on aarch64 architecture, if it works, remove this message."
else
	echo "Not support"
	exit 1;
fi

echo "Successful \n"
echo "Please  restart system  now!!!"
