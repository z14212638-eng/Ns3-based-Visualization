#!/bin/bash
set -e

# 打包目录
PACKAGE_NAME="Ns3Visualizer-user"
mkdir -p "$PACKAGE_NAME"

echo "Copying runtime files for user..."

# 可执行文件
cp Ns3Visualizer "$PACKAGE_NAME/"

# AppDir 里面的 Qt 动态库和插件
if [ -d AppDir ]; then
  cp -r AppDir/* "$PACKAGE_NAME/"

  # 1️⃣ 删除不必要的 Qt 模块（示例，根据你程序实际情况删）
  rm -rf "$PACKAGE_NAME/usr/plugins/mediaservice"        # 多媒体模块
  rm -rf "$PACKAGE_NAME/usr/plugins/platformthemes/qtvirtualkeyboard"
  rm -rf "$PACKAGE_NAME/usr/lib/*webkit*"               # WebKit
fi

# 配置文件和 JSON
cp *.json "$PACKAGE_NAME/" 2>/dev/null || true

# 图标和样式文件
cp -r icons "$PACKAGE_NAME/" 2>/dev/null || true
cp -r qss "$PACKAGE_NAME/" 2>/dev/null || true

# 桌面文件和启动脚本
if [ -f Ns3Visualizer.desktop ]; then
  # 确保桌面文件换行是 LF
  sed -i 's/\r$//' Ns3Visualizer.desktop
  cp Ns3Visualizer.desktop "$PACKAGE_NAME/"
fi

# 生成 run.sh 脚本
cat >"$PACKAGE_NAME/run.sh" <<'EOF'
#!/bin/bash
# 用户启动脚本
export LD_LIBRARY_PATH=$PWD/usr/lib:$LD_LIBRARY_PATH
export QT_PLUGIN_PATH=$PWD/usr/plugins
./Ns3Visualizer "$@"
EOF
chmod +x "$PACKAGE_NAME/run.sh"

# 2️⃣ 压缩成 xz，高效压缩
tar cJvf "${PACKAGE_NAME}.tar.xz" "$PACKAGE_NAME"

echo "✅ User package created: ${PACKAGE_NAME}.tar.xz"
echo "Size: $(du -h ${PACKAGE_NAME}.tar.xz | cut -f1)"
