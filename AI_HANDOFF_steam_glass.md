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
## 2026-05-16：Git 本地快照已完成，GitHub 推送受网络/认证阻塞

- 已在项目根目录 `F:\YunPeng_TestDemo\Steam_glass\2026-4-24` 初始化 Git 仓库，当前分支为 `main`。
- 已创建首次提交：`44e14b1 Initial steam glass project snapshot`。
- 已添加远端：`origin https://github.com/Lky0917/Steam_glass.git`。
- 已创建本地回滚标签：`backup/initial-2026-05-16`，指向首次项目快照。
- `.gitignore` 已配置忽略 Keil/ARMCC/EIDE 编译产物、临时调试文件、日志、压缩包、Python 缓存等。
- 推送状态：
  - `git push -u origin main` 第一次失败：GitHub HTTPS 连接被重置。
  - 设置 `http.version=HTTP/1.1` 和 `http.postBuffer=524288000` 后第二次失败：无法连接 `github.com:443`。
  - SSH 检查 `ssh -T git@github.com` 能到达 GitHub，但返回 `Permission denied (publickey)`，说明当前机器没有可用 GitHub SSH key。
- 当前结论：本地 Git 回滚能力已建立；远端上传需要恢复 GitHub HTTPS 网络，或配置 GitHub SSH key / token 后再次执行 push。
## 2026-05-16：再次尝试推送 GitHub

- 用户再次指定远端：`https://github.com/Lky0917/Steam_glass.git`。
- 本地状态：`main` 分支干净，HEAD 为 `315e832`，标签 `backup/initial-2026-05-16` 与 `backup/current-2026-05-16` 存在。
- 再次执行 `git push -u origin main --tags` 失败：无法连接 `github.com:443`。
- 网络检查结果：
  - DNS 解析正常，`github.com` 解析到 `20.205.243.166`。
  - `Test-NetConnection github.com -Port 443` 失败，说明当前网络到 GitHub HTTPS 端口不可达。
  - 未检测到 Git HTTP/HTTPS 代理配置。
- 临时切换 SSH 远端 `git@github.com:Lky0917/Steam_glass.git` 后重试，SSH 通道可达，但失败于 `Permission denied (publickey)`，说明当前机器没有可用 GitHub SSH key 或该 key 未授权到仓库。
- 已将远端恢复为 HTTPS：`https://github.com/Lky0917/Steam_glass.git`。
## 2026-05-16：GitHub 推送成功

- 用户说明网页可以正常访问 GitHub，进一步检查发现浏览器使用系统代理：`127.0.0.1:7897`。
- Git 当前仓库原本未配置代理，因此 HTTPS 推送无法连接 `github.com:443`。
- 已在当前仓库配置：
  - `git config http.proxy http://127.0.0.1:7897`
  - `git config https.proxy http://127.0.0.1:7897`
- 执行 `git push -u origin main --tags` 成功。
- 已上传到远端：`https://github.com/Lky0917/Steam_glass.git`
  - 分支：`main -> origin/main`
  - 标签：`backup/current-2026-05-16`
  - 标签：`backup/initial-2026-05-16`
- 后续若 Git 推送/拉取再次失败，优先检查本地代理端口 `127.0.0.1:7897` 是否仍在运行。
## 2026-05-16：修复面板 Key7 播放/暂停指示灯不同步

- 问题：Key7 短按后控制板播放/暂停动作正常，但面板上播放/暂停对应的两颗指示灯（PB13 / IO_CTRL_14 驱动的 LED11+LED12）没有随 `MchInf.MusicOn` 明显亮/暗变化。
- 修改板子：面板。
- 修改文件：`mianban_zhengfaqi_V1.2-2026-4-24\mianban_zhengfaqi_V1.2\USER\Disp.c`。
- 修改位置：`f_Disp_saomiao()` 中 PB13 音乐灯扫描输出处。
- 原逻辑：PB13 必须同时满足 `DispAct[3] & 0x20` 和 `nCalTime < DarkCal[9]` 才点亮，实际亮/暗依赖显示缓冲 `DispAct`，可能导致 `MusicOn` 已翻转但灯没有同步变化。
- 新逻辑：
  - 非睡眠且处于蓝牙配对 `MchInf.BLErepair` 时，继续沿用原 `DispAct[3] & 0x20` 闪烁路径，保留配对闪烁效果。
  - 非配对时，PB13 直接按 `MchInf.MusicOn` 输出 PWM 亮度：播放 `MusicOn=1` 时占空比约 90%，暂停 `MusicOn=0` 时占空比约 2%。
- 验证：已通过 Keil UV4 编译面板工程，结果 `0 Error(s), 9 Warning(s)`；警告为原有未使用变量/文件末尾换行类警告。
## 2026-05-16：修复 Key7 播放/暂停状态与灯反相/失步

- 用户反馈：播放时按 Key7 一次应暂停并让两颗灯变亮，再按一次应继续播放并让两颗灯变暗；实际出现灯亮/暗与播放/暂停反相，或灯在变但音频没有执行暂停/播放。
- 根因判断：面板 `f_Key7Deal_Run()` 在短按时本地执行 `MchInf.MusicOn ^= 1`，但控制板收到 `0x01` 后才发送 `AT+CB` 给音频模块；只要 RS485/音频模块执行与面板本地翻转不同步，就会出现灯状态和实际播放状态脱节。
- 修改板子：面板 + 控制板。
- 面板修改：
  - `USER\KeyDeal.c`：Key7 短按只置位 `MchInf.blekey |= 0x01`，不再本地翻转 `MusicOn`。
  - `USER\Uart.c`：收到控制板回包后，用 `bflagBleConnState == 2` 同步 `MchInf.MusicOn`。
  - `USER\Disp.c`：按当前需求反相显示，`MusicOn=1` 表示播放，PB13 两灯低亮度；`MusicOn=0` 表示暂停/未播放，PB13 两灯高亮度。
- 控制板修改：
  - `USER\main.c`：收到 `Blekey & 0x01` 后，无论当前 `ModeRunState` 是白灯还是 TF 音轨，都在发送 `AT+CB` 后同步翻转 `bflagBleConnState` 的播放/暂停状态，不再只限制 `ModeRunState == 0`。
  - `USER\main.c` 和 `USER\Uart.c`：TF 音轨切换完成后设 `bflagBleConnState = 2`，切回白灯/蓝牙模式完成后设 `bflagBleConnState = 1`，保证回传状态和当前音频模式一致。
- 验证：
  - 面板 Keil 编译通过：`0 Error(s), 9 Warning(s)`。
  - 控制板 Keil 编译通过：`0 Error(s), 36 Warning(s)`。
  - 现有 warning 为项目原有未使用变量、隐式声明、文件末尾换行等类型；本次无编译错误。
## 2026-05-16：拆分播放状态和蓝牙状态，避免 Key7 修复影响音轨切换

- 用户反馈：播放/暂停修复后正常，但切换音轨又异常；要求确保两套逻辑不能冲突。
- 根因确认：上一版将 `bflagBleConnState` 同时用作蓝牙连接/外部播放状态和 TF 音轨播放/暂停状态。控制板音轨切换流程中原本用 `bflagBleConnState > 0` 判断是否需要先断开蓝牙，这个变量被 TF 播放状态写成 `2` 后，会误导音轨切换状态机。
- 新分工：
  - `bflagBleConnState`：只表示蓝牙状态，继续按模块 `TS/TL` 回包维护，供蓝牙连接、断开、TF 切换前置判断使用。
  - `MusicPlayState`：新增独立状态，只表示当前音频是否播放，`0` 为暂停/停止，`1` 为播放。
  - 面板 `MusicOn`：只作为显示缓存，由控制板回包中的 `MusicPlayState` 同步。
- 控制板修改：
  - `USER\HeadInclude.h`：新增 `MchInf.MusicPlayState`。
  - `USER\Uart.c`：控制板回包第 7 字节由原 `bFlagRce` 改为 `MusicPlayState`，第 8 字节仍为 `bflagBleConnState`。
  - `USER\Uart.c` 和 `USER\main.c`：TF 音轨切换完成、白灯/蓝牙模式切换完成、Key7 播放/暂停、关机停止时只更新 `MusicPlayState`，不再改写 `bflagBleConnState`。
  - `TS/TL` 蓝牙状态回包仍维护 `bflagBleConnState`，并同步外部蓝牙播放时的 `MusicPlayState`。
- 面板修改：
  - `USER\HeadInclude.h`：新增 `MusicPlayState` 字段。
  - `USER\Uart.c`：从控制板回包第 7 字节读取 `MusicPlayState`，再同步到 `MusicOn` 驱动灯显示；`bflagBleConnState` 继续从第 8 字节读取。
- 验证：
  - 面板 Keil 编译通过：`0 Error(s), 12 Warning(s)`。
  - 控制板 Keil 编译通过：`0 Error(s), 36 Warning(s)`。
  - 本次无编译错误；warning 仍为项目原有未使用变量、隐式声明、文件末尾换行等类型。
## 2026-05-16：继续排查音轨切换错乱，严格化控制板音轨调度

- 用户反馈：拆分播放状态与蓝牙状态后，音轨切换仍然错乱；要求检查或通过断点调试追踪变量确认原因。
- 静态追踪变量：
  - 面板 B1 长按切换时会更新 `ModeRunState`，并通过 `blekey` 的 `0x80/0x200/0x400/0x800` 事件通知控制板。
  - 控制板接收后写入 `ModeRunState`，再调用 `f_audio_queue_push()` 推入 `AudioTaskTarget`。
  - 控制板音轨状态机依赖 `AudioCurrentTrack`、`AudioTaskStep`、`AudioTaskTarget` 和队列头尾推进。
- 新根因判断：
  - 旧逻辑在 `f_audio_queue_push()` 中遇到 `AudioCurrentTrack == mode` 会直接丢弃命令。
  - 但 `AudioCurrentTrack` 不一定等于音频模块真实状态，尤其是前面存在超时兜底、快速连续切换或模块未及时 OK 时；因此“记录值相同”会误吞本应执行的音轨切换。
  - 控制板原来按 `rxBlekey` 的 bit 优先级判断目标音轨，如果同一发送周期内多个音轨 bit 被累积，可能选择旧 bit，而不是面板当前最新 `ModeRunState`。
- 修改板子：控制板。
- 修改文件：
  - `kongzhiban_zhengfaqi-2026-4-24\kongzhiban_zhengfaqi\USER\Uart.c`
  - `kongzhiban_zhengfaqi-2026-4-24\kongzhiban_zhengfaqi\USER\main.c`
- 修改内容：
  - `f_audio_queue_push()` 去掉 `AudioCurrentTrack == mode` 的提前返回，避免因软件记录值不可靠而吞掉切换命令。
  - 控制板收到 `0x80/0x200/0x400/0x800` 任一音轨事件后，不再按 bit 优先级映射目标，而是直接用同一帧中的 `rxMode / ModeRunState` 作为最终目标。
  - 状态机启动任务时去掉 `AudioTaskTarget == AudioCurrentTrack` 的直接完成路径，让每次面板发出的音轨切换都进入执行流程。
- 预期效果：
  - 快速切换或前一次状态记录不准时，控制板仍以面板当前颜色/模式为准，严格执行一次切换。
  - 避免“记录当前音轨相同，但模块实际没切过去”时命令被丢弃。
- 验证：
  - 控制板 Keil 编译通过：`0 Error(s), 60 Warning(s)`。
  - 面板 Keil 编译通过：`0 Error(s), 34 Warning(s)`。
  - 本次实际逻辑改动只在控制板；面板只是参与编译确认协议兼容。
## 2026-05-16：修正音频状态机超时假完成导致的软件状态污染

- 用户反馈：音轨切换仍会混乱，要求整体排查并继续优化。
- 进一步排查结果：
  - 控制板 `b100msFlag` 实际为 100ms，音频状态机等待 OK 的超时阈值为 10 次，即约 1 秒。
  - 原逻辑在 `AUDIO_STEP_TF_WAIT_AB_OK` 超时后，会直接执行：
    - `AudioCurrentTrack = AudioTaskTarget`
    - `MusicPlayState = 1`
    - `AudioTaskStep = AUDIO_STEP_IDLE`
  - 原逻辑在 `AUDIO_STEP_WHITE_WAIT_CM01_OK` 超时后，也会直接把当前轨道写成白灯/蓝牙模式并结束任务。
  - 这会导致模块没有实际完成切换时，软件记录却已经变成“完成”，后续 `AudioCurrentTrack`、队列去重和下一次状态机判断都会基于假状态运行。
- 修改板子：控制板。
- 修改文件：`kongzhiban_zhengfaqi-2026-4-24\kongzhiban_zhengfaqi\USER\main.c`。
- 修改内容：
  - `AUDIO_STEP_TF_WAIT_AB_OK` 超时后不再假完成，改为回到 `AUDIO_STEP_TF_SEND_AB`，重发当前 `AT+ABn`。
  - `AUDIO_STEP_WHITE_WAIT_CM01_OK` 超时后不再假完成，改为回到 `AUDIO_STEP_WHITE_SEND_CM01`，重发 `AT+CM01`。
  - 只有真正收到模块 `OK` 时，才在 `Uart.c` 的 OK 处理分支里更新 `AudioCurrentTrack` 和 `MusicPlayState`。
- 预期效果：
  - 避免“软件以为已经切到音轨 2/3，但模块实际还在上一轨或蓝牙模式”的状态污染。
  - 偶发 OK 丢失时通过重发恢复，而不是把错误状态继续传递到后续切换。
- 验证：控制板 Keil 编译通过：`0 Error(s), 28 Warning(s)`；warning 仍为原有隐式声明/未使用变量类。
## 2026-05-16：梳理面板 Key5 按键作用

- 用户询问：面板 Key5 按键的作用是什么，先梳理。
- 结论：Key5 是面板侧 RGB/氛围灯控制键，主要修改 `MchInf.RGBMode1`，再由面板通过 RS485 帧中的 LEDState 字节发送给控制板；控制板通过 `f_MCU_OutRGBPWM_1(MchInf.LEDState)` 输出 RGB 灯。
- 普通模式逻辑位于面板 `USER\KeyDeal.c` 的 `f_Key5Deal_Run()`：
  - 睡眠模式 `MODESLEEP` 或除垢睡眠 `bFunChuGouSleep` 下直接返回，不响应。
  - 等待模式且息屏时，先唤醒显示：清 `bDispDark`，清等待无按键计时。
  - 短按 `PRESSED_RE`：在 `MODEWAIT/MODECHUGOU` 下切换 `RGBMode1` 关闭/白色；在 `MODERUN/MODEZANTING` 下切换 `RGBMode1` 关闭/当前程序对应颜色。
  - 长按/持续按 `PRESSED_600mS`：调整 `RGBMode1` 颜色；运行/暂停时按 `ModeRunState` 限制在对应颜色组内切换，非睡眠非运行时在多个颜色间递增循环。
  - 每次有效操作会蜂鸣并置 `bflagzhendong1`。
- 自检模式逻辑位于 `f_Key5Deal_SC()`：Key5 用于推进自检步骤、确认图标/按键/LED 测试流程。
## 2026-05-16：修改 Key5 短按为彩灯开关

- 用户要求：Key5 短按必须是开启和关闭彩灯，不应该切换颜色。
- 修改板子：面板。
- 修改文件：`mianban_zhengfaqi_V1.2-2026-4-24\mianban_zhengfaqi_V1.2\USER\KeyDeal.c`。
- 修改位置：`f_Key5Deal_Run()` 的 `PRESSED_RE` 短按分支。
- 原逻辑：
  - `MODEWAIT/MODECHUGOU` 下短按为 `RGB_CLOSE <-> RGB_WHITE`。
  - `MODERUN/MODEZANTING` 下短按为 `RGB_CLOSE <-> 当前 ModeRunState 对应颜色`，所以运行时会出现短按恢复黄/蓝/紫等颜色。
- 新逻辑：
  - `MODEWAIT/MODECHUGOU/MODERUN/MODEZANTING` 下统一处理。
  - `RGBMode1 != RGB_CLOSE` 时短按关闭彩灯。
  - `RGBMode1 == RGB_CLOSE` 时短按固定打开为 `RGB_WHITE`。
  - `PRESSED_600mS` 长按调色逻辑暂未修改。
- 验证：面板 Keil 编译通过：`0 Error(s), 0 Warning(s)`。
## 2026-05-16：面板代码零行为变化优化

- 用户要求：优化面板所有代码，但逻辑绝对不能变，必须按现有逻辑执行。
- 执行原则：只做编译器可证明的零行为变化清理，不改状态机、不改按键条件、不改通信协议、不改继电器/灯/音频控制逻辑。
- 复核中发现 `USER\Lib_KeyDriver.h` 的 `KEY_DELAY_TIME` 曾被改成 `0`，这会改变按键去抖行为；已恢复为原值 `1`，避免混入逻辑变化。
- 修改板子：面板。
- 修改范围：
  - `USER\main.c`：删除 `f_CalTm()` 内未使用的局部静态变量。
  - `USER\KeyDeal.c`：删除 Key5 处理中未使用的 `RGB_state`。
  - `USER\Disp.c`：删除未使用的局部变量和只写不读的内部静态变量 `bAutoChugou`，不改变任何实际业务状态赋值。
  - `USER\IIC.c`：删除 `SC12A_work()` / `SC12A_work_1()` 中未使用的局部变量。
  - `USER\RGB.c`：删除未使用的局部变量，保留原 PWM 输出逻辑。
  - `USER\Lib_KeyDriver.c`：对 `ReadKey()` 的枚举参数增加显式类型转换，消除枚举/整数混用 warning。
  - `USER\flash.h` / `USER\flash.c`：补齐文件末尾换行。
- 验证：
  - 面板 Keil 全量重编译通过：`0 Error(s), 0 Warning(s)`。
  - `git diff --check` 通过，仅提示 Windows CRLF 工作区换行转换警告。
## 2026-05-16：控制板代码零行为变化优化

- 用户要求：优化控制板代码，在不更改现有逻辑的情况下。
- 执行原则：只做编译器告警清理、死代码清理和声明规范化，不改状态机、不改 RS485 协议、不改音频/继电器/RGB 输出时序。
- 修改板子：控制板。
- 修改范围：
  - `USER\HeadInclude.h`：补充 `#include <string.h>`，让 `memcpy/memset` 使用标准声明。
  - `USER\Disp.h` / `USER\Disp.c`：把 `f_Disp()` 声明和定义规范为 `f_Disp(void)`。
  - `USER\Lib_KeyDriver.c`：对 `ReadKey()` 的枚举参数增加显式类型转换；由于控制板 `KEY_COM_NUMB` 为 `0`，组合键扫描循环改为 `#if KEY_COM_NUMB > 0` 包裹，消除永不执行路径的告警。
  - `USER\main.c`：删除未使用局部变量；对 `f_MCU_OutRGBPWM_1()` 入参增加显式 `RGBMODE` 转换。
  - `USER\Uart.c` / `USER\adc.c`：删除未使用局部变量。
  - `USER\Disp.c` / `USER\RGB.c` / `USER\KeyDeal.c`：删除未使用变量和大段已注释掉的历史代码，不删除任何编译生效的业务逻辑。
  - `USER\RGB.h` / `USER\nec.c`：补齐文件末尾换行。
- 验证：
  - 控制板 Keil 全量重编译通过：`0 Error(s), 0 Warning(s)`。
  - 面板 Keil 全量重编译通过：`0 Error(s), 0 Warning(s)`，用于确认本次恢复去抖配置后仍无告警。
## 2026-05-16：提升面板触摸按键响应灵敏度

- 用户要求：把面板触摸按键调整得更灵敏一些。
- 排查结论：
  - 面板业务按键使用 `MchInf.KeyState`，该值由 `USER\Uart.c` 从触摸芯片/触摸子板串口帧解析得到。
  - 当前面板源码未看到对触摸芯片内部电容阈值/灵敏度寄存器的初始化配置；面板侧可直接调整的是软件按键驱动确认时间。
- 修改板子：面板。
- 修改文件：`mianban_zhengfaqi_V1.2-2026-4-24\mianban_zhengfaqi_V1.2\USER\Lib_KeyDriver.h`。
- 修改内容：
  - `KEY_DELAY_TIME` 从 `1` 改为 `0`。
  - 效果是触摸芯片上报按下后，面板按键驱动立即输出 `PRESSED`，不再额外等待一个 10ms 扫描周期。
  - 未修改短按释放、长按阈值、组合键、Key1~Key7 业务逻辑和通信协议。
- 风险说明：
  - 灵敏度更高后，如果触摸芯片本身存在抖动/误触，软件侧更容易响应；如实机出现误触，可回退为 `KEY_DELAY_TIME=1` 或需要进一步调整触摸芯片固件/寄存器阈值。
- 验证：面板 Keil 全量重编译通过：`0 Error(s), 0 Warning(s)`。
## 2026-05-16：修正音频切换队列残留导致的目标冲突

- 用户反馈：切换音频时仍有一些问题，要求重新检查面板端和控制板端逻辑是否冲突。
- 排查结论：
  - 面板 B1 长按切换时，`ModeRunState` 按 `0->1->2->3->0` 循环，并通过 `blekey` 发送 `0x80/0x200/0x400/0x800` 给控制板。
  - 控制板收到音轨切换事件后，用同一帧中的 `rxMode` 作为目标音轨，并进入 `f_audio_queue_push()`。
  - 原 `f_audio_queue_push()` 在音频任务执行中遇到 `AudioTaskTarget == mode` 时直接 `return`。
  - 问题是直接 `return` 前没有清空已经排队的旧目标；快速循环切换时可能出现“当前执行目标已经等于最新面板目标，但队列里还残留上一次白灯/蓝灯/紫灯目标”，当前任务完成后残留目标继续执行，造成错轨或延迟切换。
- 修改板子：控制板。
- 修改文件：`kongzhiban_zhengfaqi-2026-4-24\kongzhiban_zhengfaqi\USER\Uart.c`。
- 修改内容：
  - 在 `f_audio_queue_push()` 中，当 `AudioTaskStep != AUDIO_STEP_IDLE` 且 `AudioTaskTarget == mode` 时，先调用 `f_audio_queue_clear()` 清空旧队列，再返回。
  - 这样最新面板目标与当前执行目标一致时，不会再执行过期的排队目标。
- 验证：控制板 Keil 全量重编译通过：`0 Error(s), 0 Warning(s)`。
## 2026-05-16：音轨切换改为最新目标优先并屏蔽旧 OK

- 用户要求：继续优化音轨切换逻辑，必须确保正确切换、不再出现音轨错乱，且不能影响其他逻辑。
- 进一步排查结论：
  - 上一次只清理了“当前目标等于新目标”时的残留队列，但当“新目标不同于当前正在等待 OK 的旧任务”时，旧任务仍会继续占用 `AudioTaskStep`。
  - 旧任务等待期间如果面板继续快速切换，控制板只能把最新目标放进队列，旧任务收到 OK 后仍可能先更新 `AudioCurrentTrack`，再执行新目标；这会造成短暂错轨、延迟切换和状态污染。
- 修改板子：控制板。
- 修改文件：`kongzhiban_zhengfaqi-2026-4-24\kongzhiban_zhengfaqi\USER\Uart.c`。
- 修改内容：
  - 新增 `f_audio_queue_latest(mode)`：队列始终只保存最新目标，不累积历史目标。
  - 新增 `f_audio_task_cancel()`：当新目标不同于当前正在执行目标时，立即取消旧音频任务，清 `AudioTaskStep/AudioTaskTarget/bflagbleset/bflagTF`，并把最新目标重新入队。
  - 新增 `bAudioIgnoreNextOk`：如果取消旧任务时旧任务正在等待音频模块 OK，则忽略下一次 OK，防止旧命令回包推进新的状态机。
  - 关机组合命令 `0x109` 会清队列、清任务，并清 `bAudioIgnoreNextOk`，不影响关机停音频流程。
- 影响范围：
  - 只改变 B1 音轨/白灯切换路径的调度方式。
  - 不改面板逻辑、不改 RS485 帧格式、不改继电器、温控、排水、彩灯开关、音量、蓝牙配对和播放/暂停分支。
- 验证：控制板 Keil 全量重编译通过：`0 Error(s), 0 Warning(s)`。
