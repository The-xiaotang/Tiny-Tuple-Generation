# TinyExt - 扩展版TINY语言编译器

![License](https://img.shields.io/badge/license-MIT-blue.svg)
![Language](https://img.shields.io/badge/language-C%2B%2B17-orange.svg)
![Framework](https://img.shields.io/badge/framework-Qt%206.10-green.svg)
![Platform](https://img.shields.io/badge/platform-Windows-lightgrey.svg)

**TinyExt** 是一个基于经典 TINY 语言（源自 Kenneth C. Louden 的《Compiler Construction: Principles and Practice》）的增强版编译器。它不仅扩展了语言特性，还提供了一个基于 Qt 的现代化图形用户界面（GUI），支持源码编辑、语法高亮、语法树可视化以及中间代码生成。

## 📸 功能概览

### 核心特性
- **完整的编译前端**：包含词法分析（Scanner）、语法分析（Parser）、语义分析（Analyzer）。
- **扩展语言支持**：在标准 TINY 语言基础上增加了 `for` 循环、`while` 循环、位运算、正则表达式符号等。
- **图形化界面**：
  - **代码编辑器**：支持基本的文本编辑和文件操作。
  - **语法树可视化**：自动生成并绘制抽象语法树（AST），支持缩放和拖拽查看。
  - **错误报告**：实时显示编译错误信息，精确定位行号。
  - **中间代码展示**：生成并展示类 TM（Tiny Machine）中间代码。

## 🚀 扩展语法特性

TinyExt 对原生 TINY 语言进行了大幅扩展，支持更丰富的编程表达：

### 1. 扩展运算符
| 运算符 | 说明 | 示例 |
| :--- | :--- | :--- |
| `+=` | 加法赋值 | `x += 5` |
| `-=` | 减法赋值 | `x -= 2` |
| `++` | 自增 | `x++` (作为语句或表达式) |
| `--` | 自减 | `x--` |
| `%` | 取模 | `x % 10` |
| `^` | 幂运算 | `2 ^ 3` |

### 2. 比较与逻辑运算
| 运算符 | 说明 | 示例 |
| :--- | :--- | :--- |
| `<=` | 小于等于 | `if x <= 10 ...` |
| `>=` | 大于等于 | `if x >= 0 ...` |
| `<>` | **不等于** | `if x <> 0 ...` (注意不是 `!=`) |
| `and` | 逻辑与 | `if (x > 0) and (x < 10) ...` |
| `or` | 逻辑或 | `if (x < 0) or (x > 100) ...` |
| `not` | 逻辑非 | `not (x = 0)` |

### 3. 控制流结构
- **For 循环** (支持 `to` 和 `downto`)：
  ```tiny
  for i := 1 to 10 do
      write i
  enddo;
  
  for i := 10 downto 1 do
      write i
  enddo
  ```
- **While 循环**：
  ```tiny
  while x > 0 do
      x := x - 1
  enddo
  ```

### 4. 正则表达式操作符
编译器前端识别以下正则相关符号（主要用于扩展语法定义的实验性支持）：
- `|` : 并集 (Union)
- `&` : 连接 (Concatenation)
- `#` : 闭包 (Closure)
- `?` : 可选 (Option)
- `::=` : 定义符

## 🛠️ 构建与运行

### 环境要求
- **操作系统**: Windows (推荐), Linux, macOS
- **编译器**: 支持 C++17 的编译器 (如 MinGW 64-bit, GCC, MSVC)
- **Qt 版本**: Qt 6.10.0 或更高版本
- **构建工具**: qmake 或 CMake (本项目默认提供 `.pro` 文件)

### 编译步骤
1. **克隆仓库**
   ```bash
   git clone https://github.com/your-username/TinyExt.git
   cd TinyExt
   ```

2. **使用 Qt Creator 构建 (推荐)**
   - 打开 `TinyExt.pro` 文件。
   - 选择构建套件（Kit），例如 `Desktop Qt 6.10.0 MinGW 64-bit`。
   - 点击 **构建 (Build)** 按钮 (或 `Ctrl+B`)。
   - 点击 **运行 (Run)** 按钮 (或 `Ctrl+R`)。

3. **命令行构建**
   ```bash
   mkdir build && cd build
   qmake ../TinyExt.pro
   make  # 或者 mingw32-make
   ./release/TinyExt.exe
   ```

## 📂 项目结构

```text
TinyExt/
├── src/
│   ├── main.cpp        # 程序入口
│   ├── dialog.cpp/h    # 主窗口 UI 逻辑
│   ├── scan.cpp/h      # 词法分析器 (Scanner)
│   ├── parse.cpp/h     # 语法分析器 (Parser)
│   ├── analyze.cpp/h   # 语义分析器 (Analyzer)
│   ├── cgen.cpp/h      # 代码生成器 (Code Generator)
│   ├── vision.cpp/h    # 语法树可视化逻辑
│   ├── util.cpp/h      # 通用工具函数
│   └── globals.h       # 全局类型定义与配置
├── forms/
│   └── dialog.ui       # Qt Designer UI 文件
├── TinyExt.pro         # qmake 项目配置文件
└── README.md           # 项目说明文档
```

## 📝 示例代码

```tiny
/* 计算阶乘的示例程序 (C风格扩展) */
read x; /* 输入一个整数 */
if (x > 0) {
    fact := 1;
    repeat
        fact := fact * x;
        x--  /* 使用扩展的自减运算符 */
    until x = 0;
    write fact
}
```

## 🧪 测试指南

本项目目前主要通过图形界面进行交互式测试。

1.  启动程序 `TinyExt.exe`。
2.  在左侧代码编辑区输入测试代码，或点击“打开文件”加载 `.tny` 文件。
3.  点击工具栏上的 **"分析" (Analyze)** 按钮。
4.  观察右侧生成的 **语法树 (Syntax Tree)** 是否符合预期。
5.  检查底部 **消息窗口** 是否有错误提示。

### 测试用例 1: 基础阶乘 (Factorial - C-Style)
```tiny
read x;
if (0 < x) {
  fact := 1;
  repeat
    fact := fact * x;
    x := x - 1
  until x = 0;
  write fact
}
```

<img width="602" height="473" alt="屏幕截图 2026-01-01 122925" src="https://github.com/user-attachments/assets/03559125-c3e7-494e-beb5-046f5a546f94" />
<img width="602" height="473" alt="屏幕截图 2026-01-01 122939" src="https://github.com/user-attachments/assets/d8b07bb9-9a26-43e2-8ffe-30cd3ae6729e" />
<img width="602" height="473" alt="屏幕截图 2026-01-01 122946" src="https://github.com/user-attachments/assets/a516d35a-0b5c-47e8-b062-c98fd16dbb9e" />

### 测试用例 2: 扩展循环与运算 (Extended Features)
```tiny
/* 测试 for 循环和 += 运算符 */
x := 0;
for (i := 1; i <= 10; i++) do
  x += i
enddo;
write x
```

### 测试用例 3: 错误处理 (Error Handling)
```tiny
/* 缺少分号的错误示例 */
x := 10
y := 20  /* Error: expected ';' */
```

## 🔧 开发与调试
- **调试模式**: 在 `globals.h` 中可以开启调试开关（如 `TraceScan`, `TraceParse` 等），编译运行时会在控制台或日志中输出详细的分析过程。
- **添加新Token**: 修改 `globals.h` 中的 `TokenType` 枚举，并在 `scan.cpp` 的 `reservedWords` 或状态机中添加识别逻辑。

## 📄 许可证
本项目作为教育与学习用途开源。原始 TINY 编译器代码归 Kenneth C. Louden 所有。扩展部分遵循 MIT 许可证。
