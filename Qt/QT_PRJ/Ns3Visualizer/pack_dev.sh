#!/bin/bash
set -e

# 打包目录
PACKAGE_NAME="Ns3Visualizer-dev"
mkdir -p "$PACKAGE_NAME"

echo "Copying all runtime files..."
cp Ns3Visualizer "$PACKAGE_NAME/"

if [ -d AppDir ]; then
  cp -r AppDir/* "$PACKAGE_NAME/"
fi

# 配置文件、JSON、图标、样式
cp *.json "$PACKAGE_NAME/" 2>/dev/null || true
cp -r icons "$PACKAGE_NAME/" 2>/dev/null || true
cp -r qss "$PACKAGE_NAME/" 2>/dev/null || true

# 桌面文件
if [ -f Ns3Visualizer.desktop ]; then
  sed -i 's/\r$//' Ns3Visualizer.desktop
  cp Ns3Visualizer.desktop "$PACKAGE_NAME/"
fi

# 复制源码
echo "Copying source code..."
# 所有 cpp, h, ui, pro, user 文件, CMakeLists.txt, build 脚本, utils 目录
cp -r *.cpp *.h *.ui *.pro *.user CMakeLists.txt "$PACKAGE_NAME/" 2>/dev/null || true
cp -r build-cmake build.sh clean.sh "$PACKAGE_NAME/" 2>/dev/null || true
cp -r utils "$PACKAGE_NAME/" 2>/dev/null || true

# 生成 run.sh
cat >"$PACKAGE_NAME/run.sh" <<'EOF'
#!/bin/bash
# 开发者启动脚本
export LD_LIBRARY_PATH=$PWD/usr/lib:$LD_LIBRARY_PATH
export QT_PLUGIN_PATH=$PWD/usr/plugins
./Ns3Visualizer "$@"
EOF
chmod +x "$PACKAGE_NAME/run.sh"

# 压缩成 tar.xz 高压缩
tar cJvf "${PACKAGE_NAME}.tar.xz" "$PACKAGE_NAME"

echo "✅ Developer package created: ${PACKAGE_NAME}.tar.xz"
echo "Size: $(du -h ${PACKAGE_NAME}.tar.xz | cut -f1)"
