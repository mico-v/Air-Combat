# Air Combat (SDL2)

一个用于学习 C++ 的最小飞机大战示例，使用 SDL2 实现跨平台窗口、输入与渲染。

## 功能
- 核心循环 + 输入 + 简单渲染
- WASD/方向键移动
- 空格发射子弹
- 敌人自动生成与碰撞

## 依赖
- C++17 编译器
- CMake 3.16+
- SDL2

## 构建与运行

### Arch Linux (含 WSL)
```bash
sudo pacman -Syu --needed base-devel cmake sdl2
cmake -S . -B build
cmake --build build
./build/AirCombat
```

### Ubuntu/Debian (参考)
```bash
sudo apt install libsdl2-dev
cmake -S . -B build
cmake --build build
./build/AirCombat
```

### WSL 图形说明
- Windows 11 + WSLg：无需额外配置，直接运行即可弹出窗口。
- 无 WSLg：需要自行安装 X Server，并设置 `DISPLAY` 环境变量。

### Windows
1. 下载 SDL2 开发包（含 CMake 配置文件）
2. 设置 `SDL2_DIR` 指向解压后的 `cmake/` 目录
3. 构建：
```bash
cmake -S . -B build -DSDL2_DIR=PATH_TO_SDL2/cmake
cmake --build build
```
4. 运行时确保 `SDL2.dll` 与 `AirCombat.exe` 同目录

## 操作
- 移动：WASD / 方向键
- 射击：空格
- 退出：ESC
