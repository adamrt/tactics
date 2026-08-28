# ZODIAC.BIN

`BATTLE/ZODIAC.BIN` is a raw 65,536-byte image asset, not an executable
overlay. The startup routine `get_zodiac_frame` loads it from disc sector
`0xec61` with a byte size of `0x10000`, then uploads it directly with
`LoadImage` to the rectangle at `(640, 0)` with dimensions `128 x 256`.
That size is exactly `128 * 256 * 2`, so the file is a headerless 65,536-byte
VRAM payload uploaded as 128-by-256 16-bit transfer words. Downstream target
code renders it as 8-bit indexed texture data.

The extracted target digest is:

`a25787954679930e21a7d224f2ee2e6c0dfa27bb42aaccb9277df930f1f204cc`
