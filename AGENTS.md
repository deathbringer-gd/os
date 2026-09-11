# AGENTS.md

## Project overview
This workspace contains a small x86 kernel project with:
- `boot/boot.s` for the multiboot entry point
- `kernel/*.c` and `kernel/*.h` for low-level kernel code
- `linker.ld` for the linker layout
- `Makefile` for build orchestration when available

## Agent guidance
- In this repository, prefer syntax-aware completion only. Do not rely on AI auto-completion behavior for broad code generation or speculative edits.
- Keep changes minimal, explicit, and aligned with the existing low-level C and assembly style already used in this project.
- When editing files, preserve the current conventions in the boot code, interrupt handlers, terminals, and kernel entry flow.
- Favor small, reviewable patches over large refactors.
- If a build command is needed, check the repository’s existing `Makefile` and linker configuration before proposing commands.

## Useful files to inspect first
- `boot/boot.s`
- `kernel/kernel.c`
- `kernel/terminal.c`
- `kernel/terminal.h`
- `linker.ld`

## Notes
- This is a bare-metal/OS project, so correctness and exact low-level behavior matter more than convenience features.
- Do not introduce unrelated abstractions, frameworks, or tooling unless they are already part of the project.
