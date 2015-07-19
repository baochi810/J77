#!/bin/bash

# get array of plugin names

# set IFS to newline so spaces aren't treated as delimiters in array
temp_ifs="$IFS"
IFS=$'\n'

script_path="$BASH_SOURCE"
script_path="/f/2015/projects/J77/cocos2d/plugin/tools"
echo "Path = ${script_path}"
ALL_PLUGINS=(`cd "${script_path}/../plugins" && find . -maxdepth 1 -type d`)
PLUGIN_NUM=${#ALL_PLUGINS[@]}
for ((i=0; i < ${PLUGIN_NUM}; i++))
do
    plugin_name="${ALL_PLUGINS[$i]}"
    ALL_PLUGINS[$i]="${plugin_name#./}"
done

export ALL_PLUGINS=("protocols" "facebook")
echo "ALL_PLUGINS = (${ALL_PLUGINS[@]})"

# restore IFS
IFS="$temp_ifs"
unset temp_ifs

# define the plugin root directory & publish target directory
export TARGET_DIR_NAME="publish"
if [ ! ${PLUGIN_ROOT} ]; then
    pushd ../
    export PLUGIN_ROOT="$(pwd)"
    popd
fi
export TARGET_ROOT="${PLUGIN_ROOT}/${TARGET_DIR_NAME}"
echo "PLUGIN_ROOT = ${PLUGIN_ROOT}"
echo "TARGET_ROOT = ${TARGET_ROOT}"

# get a string include all plugins name(separate with ':')
export PLUGINS_CAN_SELECT=""
for ((i=0; i < ${PLUGIN_NUM}; i++))
do
    plugin_name="${ALL_PLUGINS[$i]}"
    PLUGINS_CAN_SELECT="${PLUGINS_CAN_SELECT}${PLUGINS_CAN_SELECT:+:}${plugin_name}"
done
echo "PLUGINS_CAN_SELECT = ${PLUGINS_CAN_SELECT}"
