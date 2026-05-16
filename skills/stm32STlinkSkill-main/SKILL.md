---
name: stm32-stlink
description: Use this skill when the user asks to build, flash, program, probe, reset, read memory, or debug an STM32 microcontroller using ST-LINK in this Windows Keil/STM32CubeProgrammer project, or when they mention UV4.exe, STM32_Programmer_CLI.exe, OpenOCD, GDB, ST-LINK, SWD, or downloading firmware to the panel/control board.
allowed-tools: Bash, PowerShell
---

# STM32 ST-LINK Workflow

Use the local Windows toolchain first for this project:

- Keil uVision: `D:\Keil_v5\UV4\UV4.exe`
- ARMCC: `D:\Keil_v5\ARM\arm5_compiler\bin`
- STM32CubeProgrammer CLI: `C:\Users\ADMIN\.eide\tools\st_cube_programer\bin\STM32_Programmer_CLI.exe`

The original OpenOCD/GDB flow remains available as a fallback, but do not assume OpenOCD or `arm-none-eabi-gdb` is installed.

## Decision Rule

1. For normal build/download in this project, use the Windows scripts in `scripts/*.ps1`.
2. For ST-LINK connection, erase, reset, flash, verify, or memory reads, use `STM32_Programmer_CLI.exe`.
3. For Keil project build/download, use `UV4.exe`.
4. For source-level breakpoints/watch/step debugging, only use OpenOCD/GDB if those tools are confirmed present. `STM32_Programmer_CLI.exe` is not a GDB server and cannot provide full source-level debugging by itself.
5. For Keil GUI interactive debugging, use `uv4_debug.ps1` to launch uVision directly into a Debug Session when the project has ST-LINK debug settings configured.

## Windows Quick Commands

Run these from PowerShell. Paths may be overridden by parameters or environment variables.

Check tools:

```powershell
.\scripts\check_tools.ps1
```

Probe connected target:

```powershell
.\scripts\stlink_probe.ps1
```

Flash a `.hex`, `.bin`, or `.elf`:

```powershell
.\scripts\stlink_flash.ps1 -Firmware "path\to\output.hex"
```

For raw `.bin`, the default address is `0x08000000`:

```powershell
.\scripts\stlink_flash.ps1 -Firmware "path\to\output.bin" -Address 0x08000000
```

Reset the target:

```powershell
.\scripts\stlink_reset.ps1
```

Read 32-bit memory words:

```powershell
.\scripts\stlink_read32.ps1 -Address 0x20000000 -Count 16
```

Build a Keil project:

```powershell
.\scripts\uv4_build.ps1 -Project "path\to\project.uvprojx" -Target "Target 1" -Log "build.log"
```

Download through Keil project settings:

```powershell
.\scripts\uv4_download.ps1 -Project "path\to\project.uvprojx" -Target "Target 1" -Log "download.log"
```

List Keil targets:

```powershell
.\scripts\uv4_list_targets.ps1 -Project "path\to\project.uvprojx"
```

Launch Keil interactive debug:

```powershell
.\scripts\uv4_debug.ps1 -Project "path\to\project.uvprojx" -Target "Target 1"
```

Build first, then launch debug:

```powershell
.\scripts\uv4_debug.ps1 -Project "path\to\project.uvprojx" -Target "Target 1" -BuildFirst
```

Generate a Keil debug initialization file with scripted breakpoints, Watch variables, evaluations, and stepping:

```powershell
.\scripts\uv4_make_debug_ini.ps1 `
  -Output ".\debug_audio.ini" `
  -Breakpoint "main","f_Uart2_RX_Deal" `
  -Watch "MchInf.ModeRunState","MchInf.bflagbleset","AudioTaskStep" `
  -Evaluate "MchInf.ModeRunState" `
  -StepOver 1 `
  -Log ".\debug_audio.log"
```

Attach that initialization file to the Keil project:

```powershell
.\scripts\uv4_set_debug_ini.ps1 -Project "path\to\project.uvprojx" -InitFile ".\debug_audio.ini"
```

One-shot scripted debug launch:

```powershell
.\scripts\uv4_debug_scripted.ps1 `
  -Project "path\to\project.uvprojx" `
  -Target "Target 1" `
  -Breakpoint "main","f_Uart2_RX_Deal" `
  -Watch "MchInf.ModeRunState","AudioTaskStep" `
  -Evaluate "MchInf.ModeRunState" `
  -Log ".\debug_audio.log"
```

## Debugging Boundary

With only the confirmed project tools:

- Available: connect/probe, erase, program, verify, reset, read memory/register addresses, run after reset.
- Available through Keil GUI after `uv4_debug.ps1`: breakpoints, single-step, call stack, registers, memory window, Watch variables.
- Not available through `STM32_Programmer_CLI.exe` alone: breakpoints, single-step, call stack, local variables, watch expressions.

When using Keil GUI interactive debug for this project, useful Watch expressions include:

```c
MchInf.ModeRunState
MchInf.bflagbleset
MchInf.bflagTF
MchInf.Blekey
AudioTaskStep
AudioCurrentTrack
AudioPendingTrack
```

## Scripted Keil Debug

Keil debug initialization files can automate batch-style actions:

- `BS expr`: set execution/conditional/access breakpoints.
- `WS [winNr], expr, [base]`: add Watch expressions.
- `EVAL expr`: print evaluated values to the Command window and optional log file.
- `P n`: step over `n` source lines/instructions.
- `T n`: step into `n` source lines/instructions.
- `G`: run until a breakpoint or user stop.
- `G,stopAddr`: run until a temporary stop address.
- `LOG >path` / `LOG OFF`: capture Command window output.
- `EXIT`: leave debug mode after a scripted batch finishes.

Use scripted debug when the user wants repeatable setup or snapshots. Keep the GUI open when the user needs manual inspection after breakpoint hits. Do not use `EXIT` unless the user wants a batch run that closes debug mode automatically.

If true interactive debugging is required:

1. Prefer Keil GUI if the user is on Windows and has `UV4.exe`.
2. Use `uv4_list_targets.ps1` if the target name is unknown.
3. Use `uv4_debug.ps1` to enter the Debug Session.
4. If Keil project debug settings are not configured, tell the user to configure `Project -> Options for Target -> Debug -> Use: ST-Link Debugger` and `Utilities -> Use Debug Driver`.
5. Use OpenOCD/GDB only when those tools are confirmed present or when the user explicitly wants GDB.

## OpenOCD Fallback

Use the original Bash workflow only when OpenOCD/GDB are available:

```bash
./scripts/check_tools.sh
./scripts/detect_device.sh
./scripts/generate_config.sh f1
./scripts/flash.sh build/firmware.hex openocd.cfg
./scripts/debug.sh build/firmware.elf openocd.cfg
```

See `references/gdb-commands.md` only when running a real GDB session.
