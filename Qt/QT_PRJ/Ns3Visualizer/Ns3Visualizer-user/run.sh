#!/bin/bash
# 用户启动脚本
export LD_LIBRARY_PATH=$PWD/usr/lib:$LD_LIBRARY_PATH
export QT_PLUGIN_PATH=$PWD/usr/plugins
./Ns3Visualizer "$@"
