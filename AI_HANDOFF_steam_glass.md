# 蒸汽机玻璃项目 AI 交接记录

日期：2026-05-16  
工作区：`F:\YunPeng_TestDemo\Steam_glass\2026-4-24`

## 项目结构

本项目有两块板：

- 面板：触摸板，负责触摸按键、RGB 灯、面板 LED 指示、通过 RS485 发命令给控制板。
- 控制板：执行控制板，负责继电器、传感器、SD/TF 音频模块、蓝牙/音频 AT 命令、通过 RS485 回传状态给面板。

主要源码路径：

- 面板工程：`F:\YunPeng_TestDemo\Steam_glass\2026-4-24\mianban_zhengfaqi_V1.2-2026-4-24\mianban_zhengfaqi_V1.2`
- 控制板工程：`F:\YunPeng_TestDemo\Steam_glass\2026-4-24\kongzhiban_zhengfaqi-2026-4-24\kongzhiban_zhengfaqi`

常用工具路径：

- Keil UV4：`D:\Keil_v5\UV4\UV4.exe`
- ARMCC 工具链：`D:\Keil_v5\ARM\arm5_compiler\bin`
- STM32 烧录工具：`C:\Users\ADMIN\.eide\tools\st_cube_programer\bin\STM32_Programmer_CLI.exe`

## 硬件和显示结论

用户确认：`TM1620/TM1628` 在控制板上，不在面板上。

面板上服务 Key7 音乐/蓝牙指示的两颗 LED，原理图为：

- `IO_CTRL_14 -> PB13`
- `PB13` 通过电阻驱动三极管 `Q27`
- `Q27` 低边开关控制 `LED11 + LED12`
- 这两颗灯硬件上共用一个 GPIO，只能同步亮灭/亮暗，不能独立控制

面板代码里实际落到 PB13 的路径：

- `MchInf.MusicOn`
- `bDarkMusic`
- `DarkCal[9]`
- `DispAct[3] & 0x20`
- `LED_BLE_ON_IO / LED_BLE_OFF_IO`
- PB13

相关代码：

- `USER\Disp.c`
- `USER\McuInit.h`

关键输出代码在面板 `Disp.c`：

```c
if ((DispAct[3] & 0x20) && (nCalTime < DarkCal[9])) // music
    LED_BLE_ON_IO;
else
    LED_BLE_OFF_IO;
```

## B1 音轨切换需求

B1 颜色和音轨绑定关系：

- 白灯：蓝牙/外部触发模式，无外部触发则静音
- 黄灯：音轨 1
- 蓝灯：音轨 2
- 紫灯：音轨 3
- 循环：白 -> 黄 -> 蓝 -> 紫 -> 白

面板侧 B1 长按逻辑位置：

- `mianban...\USER\KeyDeal.c`
- `ModeRunState` 循环 `0 -> 1 -> 2 -> 3 -> 0`

当前面板发给控制板的协议：

- `0x80`：切回白灯/蓝牙模式
- `0x200`：黄灯/音轨 1
- `0x400`：蓝灯/音轨 2
- `0x800`：紫灯/音轨 3

控制板侧接收协议位置：

- `kongzhiban...\USER\Uart.c`

现在控制板已经删除旧协议入口：

- 已去掉 `0x40 -> f_audio_queue_push(rxMode)`
- 现在只接受 `0x80 / 0x200 / 0x400 / 0x800` 进入音频任务

## 曾经的旧问题

旧问题：紫灯切白灯时，音轨 3 停不下来。

旧根因：

- 白灯分支只发 `AT+CM01`，没有先发 `AT+CB` 停当前 TF 播放
- 旧 `Uart.c` 的 `M` 回包分支会重新置位 `MchInf.Blekey |= 0x40`，可能把 TF 播放流程又拉起来

修复方向：

- 白灯切换使用 `CB -> CM01`
- 不再让旧 `M` 回包自动补 `0x40`

## 当前控制板音频状态机

控制板新增/使用的音频状态变量在：

- `kongzhiban...\USER\HeadInclude.h`

变量：

```c
unsigned char AudioQueue[8];
unsigned char AudioQueueHead;
unsigned char AudioQueueTail;
unsigned char AudioTaskTarget;
unsigned char AudioCurrentTrack;
unsigned char AudioTaskStep;
```

状态宏：

```c
#define AUDIO_STEP_IDLE 0
#define AUDIO_STEP_TF_WAIT_DISCONNECT 1
#define AUDIO_STEP_TF_WAIT_CM04_OK 2
#define AUDIO_STEP_TF_SEND_AB 3
#define AUDIO_STEP_TF_WAIT_AB_OK 4
#define AUDIO_STEP_WHITE_WAIT_CB_OK 5
#define AUDIO_STEP_WHITE_SEND_CM01 6
#define AUDIO_STEP_WHITE_WAIT_CM01_OK 7
```

当前控制板音频任务流程在：

- `kongzhiban...\USER\main.c`

白灯目标 `0`：

- 如果当前在 TF：`AT+CB -> AT+CM01`
- 完成后 `AudioCurrentTrack = 0`

黄/蓝/紫目标 `1/2/3`：

- 从白灯/蓝牙进 TF：断蓝牙或切 TF，然后 `AT+CM04 -> AT+ABx`
- TF 内换轨：先 `AT+CB`，再 `AT+ABx`

控制板 `f_audio_queue_push()` 已改成“只保留最后目标”：

- 连续切换时不再无限堆 FIFO 历史命令
- 当前正在执行时，新目标会覆盖等待队列中的旧目标
- 已经是当前目标或正在执行目标时忽略

## 控制板新增超时兜底

用户测试出现：

- 前几轮正常
- 第 4 到第 7 轮开始出现延迟切换、白灯停不住、几轮不响应
- 第 8 轮后又恢复正常

判断：控制板偶尔卡在等待音频模块 `OK/TS/TL` 回包的中间状态。

已在控制板 `main.c` 增加音频状态机超时兜底：

- `AudioTaskStep` 非空闲后开始计时
- 约 1 秒没有回包则主动推进或收尾
- 覆盖：
  - 等蓝牙断开
  - 等 `CM04` OK
  - 等 `ABx` OK
  - 等白灯 `CB -> CM01` 的 OK

用户问：这样切到程序 1 后，会不会一段时间后自动切到程序 2？

答复：不会。超时只推进当前 `AudioTaskTarget`，不会生成新目标。只有面板再发 `0x400` 才会切到程序 2。

## Key7 播放/暂停和 LED 亮暗问题

Key7 是音乐/蓝牙复用键：

- 短按：播放/暂停，面板发 `0x01`
- 中按：下一曲，面板发 `0x02`
- 长按：蓝牙重配，面板发 `0x04`
- 超长按：空闲/释放资源，面板发 `0x08`

面板入口：

- `mianban...\USER\KeyDeal.c`
- 函数 `f_Key7Deal_Run()`

控制板收到 `0x01` 后：

- `kongzhiban...\USER\main.c`
- 发送 `AT+CB`
- `AT+CB` 在当前代码里被当作播放/暂停切换命令使用

曾经尝试：

1. 去掉面板本地 `MusicOn ^= 1`，改为根据控制板回传 `bflagBleConnState` 同步。
2. 实测：播放/暂停动作正常，但灯不变。
3. 判断：控制板回传状态没有可靠反映播放/暂停。
4. 恢复面板本地翻转灯状态。

当前面板 Key7 短按逻辑已改为：

```c
MchInf.blekey |= 0x01;
MchInf.MusicOn ^= 1;
```

注意：已经去掉 `ModeRunState == 0` 限制，非睡眠状态下 Key7 短按都会翻转这组灯。

当前面板显示逻辑：

- `MusicOn == 1` -> `bDarkMusic = 0` -> 亮
- `MusicOn == 0` -> `bDarkMusic = 1` -> 暗

当前 `DarkCal[9]` 已改为：

```c
if (bDarkMusic)
    DarkCal[9] = 2;
else
    DarkCal[9] = 90;
```

目的：让暂停时明显变暗。

但用户最后反馈：还是没有变化。

下一步应重点检查：

- `Key7` 短按分支是否真的被执行
- `MusicOn` 是否被其它显示分支改回去
- `bIconSound` 是否在当前模式下被置 1
- `DispAct[3] & 0x20` 是否始终有效
- PB13 是否实际就是这两颗灯的当前控制脚
- 当前烧录的到底是不是面板固件，而不是控制板固件

## 最近一次已烧录状态

控制板最近烧录：

- 文件：`kongzhiban...\EIDE\build\Target 1\kongzhiban_audio_fix.hex`
- 状态：编译成功并烧录成功
- 校验：`Download verified successfully`

面板最近烧录：

- 文件：`mianban...\EIDE\build\Target 1\zhengfaqi_mianban.hex`
- 状态：编译成功并烧录成功
- 校验：`Download verified successfully`

注意：最近一次面板烧录时，STM32CubeProgrammer 识别到的芯片为：

- `STM32F101/F102/F103 Medium-density`
- `Flash size: 64 KBytes`

之前也曾识别到另一块面板/芯片为：

- `STM32F101/F103 High-density`
- `Flash size: 256 KBytes`

所以后续烧录前要确认 ST-LINK 当前接的是目标板。

## 编译方式

EIDE/Keil 命令行有时不稳定，可靠方式是用 ARMCC 手动编译单个改动文件再链接。

面板常用工作目录：

```powershell
F:\YunPeng_TestDemo\Steam_glass\2026-4-24\mianban_zhengfaqi_V1.2-2026-4-24\mianban_zhengfaqi_V1.2\EIDE
```

控制板常用工作目录：

```powershell
F:\YunPeng_TestDemo\Steam_glass\2026-4-24\kongzhiban_zhengfaqi-2026-4-24\kongzhiban_zhengfaqi\EIDE
```

烧录命令模板：

```powershell
& 'C:\Users\ADMIN\.eide\tools\st_cube_programer\bin\STM32_Programmer_CLI.exe' -c port=SWD mode=UR -d '<hex路径>' -v -rst
```

## 当前待解决问题

1. Key7 播放/暂停时，PB13 控制的两颗 LED 仍然没有明显亮暗变化。
2. B1 音轨连续切换已加队列覆盖和超时兜底，需要继续长时间实测确认是否彻底稳定。

## 建议下一步

优先解决 LED 亮暗：

1. 临时在 `Key7` 短按分支直接翻转一个测试标志，强制 PB13 全亮/全灭，而不是走 `DarkCal[9]` PWM。
2. 如果全亮/全灭有变化，说明硬件和 PB13 没问题，问题在显示亮度/图标位逻辑。
3. 如果全亮/全灭也没变化，说明 Key7 分支没有进、PB13 不是目标灯、或者当前固件没有烧到正确面板。
4. 再决定是否保留 PWM 亮暗，还是改成播放全亮、暂停全灭。

当前更推荐的最小验证改法：

- 在 `f_Disp_saomiao()` 中临时让 `MusicOn` 直接控制 PB13：

```c
if (MchInf.MusicOn)
    LED_BLE_ON_IO;
else
    LED_BLE_OFF_IO;
```

如果这样有效，再回头整理成正式逻辑。


## 2026-05-16 更新：项目 Skills 目录

已在项目根目录创建：

- `F:\YunPeng_TestDemo\Steam_glass\2026-4-24\skills`
- `F:\YunPeng_TestDemo\Steam_glass\2026-4-24\skills\README.md`

用途：后续存放本项目移植或定制的 Codex skills。

## 2026-05-16 更新：主频和串口波特率

两块板当前源码中的时钟和串口配置一致。

面板：

- 时钟配置文件：`mianban_zhengfaqi_V1.2-2026-4-24\mianban_zhengfaqi_V1.2\USER\McuInit.c`
- `RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9)`
- `HCLK = SYSCLK / 1`
- `PCLK2 = HCLK / 1`
- `PCLK1 = HCLK / 2`
- 若外部晶振 HSE 为 8MHz，则 SYSCLK/HCLK 为 72MHz，PCLK2 为 72MHz，PCLK1 为 36MHz。
- `ENABLE_UART1 / ENABLE_UART2 / ENABLE_UART3` 均开启。
- USART1 / USART2 / USART3 波特率均为 `115200`。

控制板：

- 时钟配置文件：`kongzhiban_zhengfaqi-2026-4-24\kongzhiban_zhengfaqi\USER\McuInit.c`
- `RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9)`
- `HCLK = SYSCLK / 1`
- `PCLK2 = HCLK / 1`
- `PCLK1 = HCLK / 2`
- 若外部晶振 HSE 为 8MHz，则 SYSCLK/HCLK 为 72MHz，PCLK2 为 72MHz，PCLK1 为 36MHz。
- `ENABLE_UART1 / ENABLE_UART2 / ENABLE_UART3` 均开启。
- USART1 / USART2 / USART3 波特率均为 `115200`。

注意：结论基于当前源码配置。实际主频还依赖硬件 HSE 晶振是否为 8MHz，以及 HSE 是否成功起振。

## 2026-05-16 更新：STM32 Debug Skill

用户已移植调试 skill 到项目目录：

- `F:\YunPeng_TestDemo\Steam_glass\2026-4-24\skills\stm32debug-skill-main`

主要文件：

- `SKILL.md`：skill 使用说明
- `scripts\stm32-debug`：统一入口
- `scripts\stm32_debug.py`：统一 CLI 主实现
- `scripts\read_svd.py`：解析 SVD 外设/寄存器/位域
- `scripts\flash.sh`：OpenOCD 烧录脚本
- `scripts\monitor_swo.sh`：SWO 日志脚本
- `STM32F103.svd`：项目目标可用的 SVD 文件

该 skill 支持的能力：

- OpenOCD 会话管理
- GDB 读全局变量、地址、寄存器、SVD 位域
- 断点、条件断点、观察点、单步、调用栈、局部变量、CPU 寄存器
- SWO 日志捕获
- 历史采样记录

当前项目使用注意：

- skill 默认依赖 `arm-none-eabi-gcc / openocd / gdb-multiarch / python3`，而当前项目实际编译链路是 Keil ARMCC。
- 当前烧录主流程仍优先使用 `STM32_Programmer_CLI.exe`，路径：`C:\Users\ADMIN\.eide\tools\st_cube_programer\bin\STM32_Programmer_CLI.exe`。
- 若后续要使用在线变量/寄存器调试，需要确认本机是否有 OpenOCD 和可用的 GDB；否则需要把 skill 脚本适配到 Windows 当前工具链。
- `read_svd.py` 可独立用于解析 `STM32F103.svd`，不依赖目标板在线连接。

## 2026-05-16：学习新增 ST-LINK 烧录 skill

- 新增 skill 路径：`F:\YunPeng_TestDemo\Steam_glass\2026-4-24\skills\stm32STlinkSkill-main`。
- `SKILL.md` 名称：`stm32-stlink`，用途是通过 ST-LINK 对 STM32 进行检测、烧录和调试。
- 该 skill 的默认工作流依赖 Bash + OpenOCD + `arm-none-eabi-gdb` / `gdb-multiarch`：
  - `scripts\detect_device.sh`：用 OpenOCD 探测 ST-LINK/目标芯片并建议 STM32 family cfg。
  - `scripts\flash.sh`：支持 `.elf` / `.hex` / `.bin`，通过 OpenOCD 执行 `program ... verify reset exit`；`.bin` 默认写入 `0x08000000`。
  - `scripts\debug.sh`：启动 OpenOCD GDB server，并拉起 ARM GDB 调试。
- 当前项目已知可用的 Windows 烧录工具仍是：`C:\Users\ADMIN\.eide\tools\st_cube_programer\bin\STM32_Programmer_CLI.exe`。
- 后续如果用户要求“按新增 skill 烧录/调试”，优先参考该 skill 的检测、烧录、调试流程；但在当前 Windows 环境下，若未确认 OpenOCD/GDB 可用，实际烧录仍应优先使用已确认的 `STM32_Programmer_CLI.exe`，或先检查/适配 OpenOCD 工具链。
## 2026-05-16：适配 ST-LINK skill 到当前 Windows 工具链

- 已修改 skill：`F:\YunPeng_TestDemo\Steam_glass\2026-4-24\skills\stm32STlinkSkill-main\SKILL.md`。
- 新策略：当前项目优先使用 Windows 已确认工具链：
  - Keil UV4：`D:\Keil_v5\UV4\UV4.exe`
  - ARMCC：`D:\Keil_v5\ARM\arm5_compiler\bin`
  - STM32CubeProgrammer CLI：`C:\Users\ADMIN\.eide\tools\st_cube_programer\bin\STM32_Programmer_CLI.exe`
- 新增 PowerShell 脚本：
  - `scripts\check_tools.ps1`：检查 UV4、STM32_Programmer_CLI、ARMCC/armlink 路径。
  - `scripts\stlink_probe.ps1`：通过 CubeProgrammer CLI 连接/探测 SWD 目标。
  - `scripts\stlink_flash.ps1`：烧录 `.hex` / `.elf` / `.bin`，`.bin` 默认地址 `0x08000000`，烧录后校验并复位。
  - `scripts\stlink_reset.ps1`：复位目标板。
  - `scripts\stlink_read32.ps1`：读取 32 位内存字，用于轻量级状态/寄存器检查。
  - `scripts\uv4_build.ps1`：通过 Keil UV4 命令行构建工程。
  - `scripts\uv4_download.ps1`：通过 Keil UV4 命令行执行工程下载入口。
- 验证结果：`check_tools.ps1` 已通过，确认本机 UV4、STM32_Programmer_CLI、ARMCC/armlink 均存在；所有新增 `.ps1` 脚本通过 PowerShell 语法解析检查。
- 重要边界：`STM32_Programmer_CLI.exe` 可以连接、擦写、校验、复位、读内存，但不是 GDB server，不能单独提供源码级断点、单步、调用栈、局部变量 watch。若需要完整交互式 debug，仍需确认 OpenOCD/GDB 可用，或使用 Keil uVision 交互式调试能力。
## 2026-05-16：将 Keil uVision 交互式调试入口并入 ST-LINK skill

- 已更新 `skills\stm32STlinkSkill-main\SKILL.md`，新增 Keil GUI 交互式调试流程。
- 新增脚本：
  - `scripts\uv4_list_targets.ps1`：读取 `.uvprojx` 中的 Keil Target 名称。
  - `scripts\uv4_debug.ps1`：通过 `UV4.exe -d` 启动 Keil Debug Session；支持 `-BuildFirst` 先构建再进入调试。
- 已验证所有 PowerShell 脚本语法通过。
- 已读取两个工程的 target 名称：
  - 控制板：`Target 1`
  - 面板：`Target 1`
- 后续可自动执行的调试入口：
  - 控制板：`uv4_debug.ps1 -Project "F:\YunPeng_TestDemo\Steam_glass\2026-4-24\kongzhiban_zhengfaqi-2026-4-24\kongzhiban_zhengfaqi\MDK\muban_STM32.uvprojx" -Target "Target 1"`
  - 面板：`uv4_debug.ps1 -Project "F:\YunPeng_TestDemo\Steam_glass\2026-4-24\mianban_zhengfaqi_V1.2-2026-4-24\mianban_zhengfaqi_V1.2\MDK\muban_STM32.uvprojx" -Target "Target 1"`
- 边界：脚本可以自动打开 Keil 并进入 Debug Session，但断点、单步、Watch 变量等仍是 Keil GUI 内交互操作；若要完全脚本化断点/Watch，需要后续单独研究 Keil debug initialization file / uVision automation 能力。
## 2026-05-16：将 Keil 断点、单步、Watch 脚本化能力并入 ST-LINK skill

- 已更新 `skills\stm32STlinkSkill-main\SKILL.md`，新增 Scripted Keil Debug 说明。
- 新增脚本：
  - `scripts\uv4_make_debug_ini.ps1`：生成 Keil Debug Initialization File，可写入 `BS` 断点、`WS` Watch、`EVAL` 表达式输出、`P/T/O` 单步、`G` 运行、`LOG` 日志、`EXIT` 退出等命令。
  - `scripts\uv4_set_debug_ini.ps1`：将生成的 `.ini` 写入 Keil `.uvoptx` 的 `<tIfile>` 字段；默认会备份 `.uvoptx`。
  - `scripts\uv4_debug_scripted.ps1`：一键生成 `.ini`、写入 `.uvoptx`、启动 `UV4.exe -d` 进入调试。
- 验证结果：
  - 所有 `.ps1` 脚本通过 PowerShell 语法解析。
  - `uv4_make_debug_ini.ps1` 已测试可正确生成多条 `BS` / `WS` / `EVAL` 命令。
  - `uv4_set_debug_ini.ps1` 已在临时拷贝的 Keil 工程上验证可正确写入 `<tIfile>`，未修改真实控制板/面板工程配置。
- 能自动化的范围：批处理式设置断点、Watch、表达式求值、若干单步、运行到断点/地址、输出日志。
- 不能完全替代的范围：Keil GUI 中实时观察断点命中后的人工判断、动态点选变量、手动继续/单步等交互动作；这些仍需要 GUI 或后续更复杂的 uVision 自动化方案。
## 2026-05-16：准备上传项目到 GitHub 仓库

- 用户要求将当前项目代码上传到 GitHub 仓库：`https://github.com/Lky0917/Steam_glass.git`，用于保证代码可随时回滚。
- 当前项目根目录原本不是 Git 仓库，准备在 `F:\YunPeng_TestDemo\Steam_glass\2026-4-24` 初始化 Git。
- 已新增 `.gitignore`：保留源码、Keil 工程文件、文档、skill 和交接记录；忽略 Keil/ARMCC 编译产物、日志、临时调试文件、压缩包、缓存文件。
- 远端连通性初次检查 `git ls-remote` 被网络重置，后续仍会继续尝试添加远端并 push；若推送因网络或 GitHub 认证失败，本地提交仍可用于本机回滚。