#!/bin/bash

if [[ "${BUILD_TYPE}" == "AppImage" ]]; then
    sudo add-apt-repository ppa:beineri/opt-qt562-trusty -y
    sudo apt-get update -qq
elif [[ "${BUILD_TYPE}" == "deb" ]]; then
    docker pull ubuntu:17.10
    docker run --name build-container -v `pwd`:`pwd` -w `pwd` -dit ubuntu:17.10 bash
elif [[ "${BUILD_TYPE}" == "rpm" ]]; then
    docker pull opensuse:42.2
    docker run --name build-container -v `pwd`:`pwd` -w `pwd` -dit opensuse:42.2 bash
elif [[ "${BUILD_TYPE}" == "exe" ]]; then
    export PATH=$QT_BIN:$PATH
    export PATH=$QT_PLUGIN:$PATH
    export PATH=$CL_BIN:$PATH
    export PATH=$RC_BIN:$PATH
    export LIB=$UM_LIB:$LIB
    export LIB=$UCRT_LIB:$LIB
    export LIB=$MSVCRTD_LIB:$LIB
    export LIB=$KCOLORPICKER_LIB:$LIB
    export LIB=$KIMAGEANNOTATOR_LIB:$LIB
    export INCLUDE=$UM_INCLUDE:$INCLUDE
    export INCLUDE=$UCRT_INCLUDE:$INCLUDE
    export INCLUDE=$SHARED_INCLUDE:$INCLUDE
    export INCLUDE=$MSVCRTD_INCLUDE:$INCLUDE
    export INCLUDE=$KCOLORPICKER_INCLUDE:$INCLUDE
    export INCLUDE=$KIMAGEANNOTATOR_INCLUDE:$INCLUDE

    wget --quiet -O qtbase.7z https://download.qt.io/online/qtsdkrepository/windows_x86/desktop/qt5_563/qt.563.win32_msvc2015/5.6.3-0-201709190903qtbase-Windows-Windows_10-MSVC2015-Windows-Windows_10-X86.7z
    wget --quiet -O qtwinextras.7z https://download.qt.io/online/qtsdkrepository/windows_x86/desktop/qt5_563/qt.563.win32_msvc2015/5.6.3-0-201709171315qtwinextras-Windows-Windows_10-MSVC2015-Windows-Windows_10-X86.7z
    wget --quiet -O qttools.7z https://download.qt.io/online/qtsdkrepository/windows_x86/desktop/qt5_563/qt.563.win32_msvc2015/5.6.3-0-201708150657qttools-Windows-Windows_10-MSVC2015-Windows-Windows_10-X86.7z

    7z x qtbase.7z -o/c/qt
    7z x qtwinextras.7z -o/c/qt
    7z x qttools.7z -o/c/qt
fi
