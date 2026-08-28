# WLDCORE overlay

`WORLD/WLDCORE.BIN` is loaded at runtime address `0x80067000` and has no
executable header. Convert a runtime address to a file offset by subtracting
`0x80067000`. The entrypoint called by `open_world_and_wldcore` is
`0x800672f8`.

The target file is 448,808 bytes (`0x6d928`), stored at disc LBA 84,041. Its
extracted SHA-256 is
`e607cde27bee35117116d085ba72ce240f979eb307bf70a24440b4e965d705fb`.

Several local FFHacktics ranges omit the final MIPS `jr` delay slot. The
verified boundaries below include that instruction where it is part of the
routine:

- `world_bin_entrypoint`: `0x800672f8–0x80067484` (396 bytes)
- `world_process_frame_gate`: `0x80067484–0x800674e0` (92 bytes)
- `world_initialize_core`: `0x800674e0–0x800677a4` (708 bytes)
- `world_initialize_subsystems`: `0x80067c2c–0x80067cb4` (136 bytes)
- `world_finalize_loop`: `0x800682a0–0x80068308` (104 bytes)
- `world_initialize_runtime_state`: `0x80068308–0x800683fc` (244 bytes)
- `wldcore_clear_menu_result_800723f0`: `0x800723f0–0x80072404` (20 bytes)
- `wldcore_clear_menu_result_80072ee0`: `0x80072ee0–0x80072ef4` (20 bytes)
- `wldcore_clear_menu_result_8007addc`: `0x8007addc–0x8007adf0` (20 bytes)

Current reconstruction coverage is summarized in
[reconstruction.md](reconstruction.md); the authoritative per-function status
and ranges are in [`config/modules.yaml`](../config/modules.yaml).
