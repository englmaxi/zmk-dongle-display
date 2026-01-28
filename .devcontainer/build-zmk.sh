#!/usr/bin/env bash
set -e # to exit the subshell as soon as an error happens
set -x

build_dir=$(mktemp -d -p "/tmp" zmk-build.XXXXXX)

board_name=$1
shield_name=$2
shield_file_name=$(echo $shield_name | tr ' ' '_')

export zmk_load_arg=" -DZMK_EXTRA_MODULES='${WORKSPACE_PATH}' "
new_tmp_dir=$(mktemp -d -p "/tmp" zmk-config.XXXXXX)
mkdir -p "${new_tmp_dir}"
base_dir=${new_tmp_dir}

config_dir="${CONFIG_DIR:-config}"

rm -rf $base_dir/.west

mkdir -p $base_dir/config/
cp -R $WORKSPACE_PATH/${config_dir}/* $base_dir/config/

cd $base_dir

west init -l "$base_dir/config/"
west update --fetch-opt=--filter=tree:0

west zephyr-export

west build \
    -s zmk/app \
    -d $build_dir \
    -b "$board_name" \
    -- -DZMK_CONFIG="$base_dir/config" \
    -DSHIELD="$shield_name" \
    $zmk_load_arg

FW_FILE="$WORKSPACE_PATH/$BUILD_SUBFOLDER/${shield_file_name}_${board_name}-zmk.uf2"
rm -rf "$FW_FILE" # remove the FW file from the target folder
mkdir -p "$WORKSPACE_PATH/$BUILD_SUBFOLDER"

cp "$build_dir/zephyr/zmk.uf2" "$FW_FILE" # copy FW to the target folder
echo -e "${Green}SUCCESSFULLY build $FW_FILE${Color_Off}"
