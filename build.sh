#!/usr/bin/env bash

mkdir -p ./build
mkdir -p ./dependencies/include

CC="cc"
CXX="c++"

RAYLIB="./dependencies/raylib/build/raylib"

LDFLAGS="-L${RAYLIB} -l:libraylib.a -lm -lX11 -lGL -lpthread -ldl -lrt"
CFLAGS="-std=c++17 -pipe -Os"
WARNFLAGS="-W -Wall -Wpedantic -Wformat=2"

BUILDINCL="-I./dependencies/include"
CINCL="-I./include -I./source ${BUILDINCL}"
CFILES="source/*.cpp source/include/*.cpp"

EXEFILE="./build/units"
ASSETS="/home/$(whoami)/.local/share/units"

function print_help() {
    echo "USAGE:"
    echo "  ./build.sh [OPTIONS]"
    echo
    echo "OPTIONS:"
    echo "  -help, -h           Display this help message and exit."
    echo "  -compile, -c        Compile and generate the executable."
    echo "  -run, -r            Run the executable."
    echo "  -clean, -cl         Clean the directory."
    echo "  -install, -i        Install system-wide."
    echo "  -uninstall, -un     Uninstall."
    echo
    echo "EXAMPLES:"
    echo "  $ ./build.sh -help"
    echo "  $ ./build.sh -c -r"
    echo "  $ ./build.sh -c -i -cl"

    exit
}

function check_dependencies() {
    if [ ! -f "${EXEFILE}" ] ; then
        LSB_RELEASE=$(cat /etc/release 2>/dev/null)
        if [ ! "${LSB_RELEASE}" ] ; then
            LSB_RELEASE=$(cat /etc/os-release)
        fi

        case "${LSB_RELEASE}" in
        *ubuntu*) ;& *Ubuntu*) ;&
        *mint*) ;& *Mint*)
            echo "! Distribution detected: Ubuntu or Mint"
            sudo apt install -y libasound2-dev libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxinerama-dev libwayland-dev libxkbcommon-dev
            ;;
        *fedora*) ;& *Fedora*)
            echo "! Distribution detected: Fedora"
            sudo dnf install alsa-lib-devel mesa-libGL-devel libX11-devel libXrandr-devel libXi-devel libXcursor-devel libXinerama-devel libatomic
            ;;
        *arch*) ;& *Arch*)
            echo "! Distribution detected: Arch"
            sudo pacman -S --needed alsa-lib mesa libx11 libxrandr libxi libxcursor libxinerama
            ;;
        *gentoo*) ;& *Gentoo*)
            echo "! Distribution detected: Gentoo"
            echo "For Gentoo, you should handle the Raylib deps yourself."
            ;;
	    *nixos*) ;& *NixOS*)
            echo "! Distribution detected: NixOS"
            if [ "${IN_NIX_SHELL}" == "" ] ; then
                make_nix_shell
                echo "! shell.nix generated."
	            echo "For NixOS, please execute build.sh inside a nix-shell."
                exit
	        fi
	        ;;
        *)
            echo "Unsupported Linux distribution. Exiting."
            exit 1
            ;;
        esac
    fi
}

function make_nix_shell() {
    cat > shell.nix <<EOF
        { pkgs ? import <nixpkgs> {} }:
        pkgs.mkShell {
            nativeBuildInputs = with pkgs.buildPackages; [
                cmake gnumake pkg-config gcc unzip
            ];
            buildInputs = [
                pkgs.libGL
                pkgs.glfw
                pkgs.xwayland
                pkgs.xorg.libX11
                pkgs.xorg.libX11.dev
                pkgs.xorg.libXcursor
                pkgs.xorg.libXrandr
                pkgs.xorg.libXext
                pkgs.xorg.libXinerama
                pkgs.xorg.libXi
            ];
        }
EOF
}

function compile_dep() {
    if [ ! -d "./dependencies/${1}/" ] ; then 
        unzip ./dependencies/${1}.zip -d ./dependencies
        if [ $? -ne 0 ] ; then
            echo "- Failed to unzip ${1}."
            exit 1
        fi
    fi

    if [ -f "./dependencies/${1}/build/${1}/lib${1}.a" ] ; then
        return
    fi

    mkdir ./dependencies/${1}/build
    cmake ${2} -B ./dependencies/${1}/build -S ./dependencies/${1}/ ||
    { echo "Failed to compile ${1}. Cmake. Exiting." ; exit 1;}
    make ${3} -B -C ./dependencies/${1}/build/ ||
    { echo "Failed to compile ${1}. Make. Exiting." ; exit 1;}

    echo "+ Dependency: ${1} compiled successfully."

    if [ "${4}" ] ; then
        cp -v "./dependencies/${1}/${4}" ./dependencies/include
    fi
}

function compile() {
    rm -rf "${ASSETS}"
    mkdir -p "${ASSETS}"
    cp -r -v "./assets" "${ASSETS}"

    echo "  ${CXX} ${CFLAGS} ${CINCL} ${CFILES} ${WARNFLAGS} ${LDFLAGS} -DASSETS=\"${ASSETS}/assets\" -o \"${EXEFILE}\""

    ${CXX} ${CFLAGS} ${CINCL} ${CFILES} ${WARNFLAGS} ${LDFLAGS} \
        -DASSETS=\"${ASSETS}/assets\" \
        -o "${EXEFILE}" && echo "+ Units compiled successfully."
}

function clean() {
    rm -rf ./dependencies/{raylib,include}
    rm -rf ./build && mkdir ./build
    rm -rf "${ASSETS}"

    echo "+ Cleaned."
}

function install() {
    if [ -f "${EXEFILE}" ] ; then
        echo "- Please compile the source code first."
        exit 1
    fi

    sudo cp -v "${EXEFILE}" "/usr/local/lib"
}

function uninstall() {
    sudo rm "/usr/local/bin/units" 1>dev/null 2>&1
    echo "+ Uninstalled."
}

if [ $# -eq 0 ] ; then
    print_help
fi

while [ $# -ne 0 ] ; do
    case "${1}" in
    "-help") ;& "help") ;& "-h") ;& "h")
        print_help
        ;;
    "-compile") ;& "compile") ;& "-c") ;& "c")
        check_dependencies
        compile_dep "raylib" " " "PLATFORM=PLATFORM_DESKTOP" "src/raylib.h"
        compile
        ;;
   "-run") ;& "run") ;& "-r") ;& "r")
        "${EXEFILE}"
        ;;
   "-clean") ;& "clean") ;& "-cl") ;& "cl")
        clean
        ;;
   "-install") ;& "install") ;& "-i") ;& "i")
        install
        ;;
    "-uninstall") ;& "uninstall") ;& "-un") ;& "un")
        uninstall
        exit
        ;;
    *)
        echo "- Invalid option: ${0} ${1}."
        echo
        print_help
        ;;
    esac

    shift
done
