# QMK Keymap

Personal [QMK](https://qmk.fm) userspace for my [ZSA Voyager](https://www.zsa.io/voyager) inspired from [getreuer](https://github.com/getreuer/qmk-keymap)'s keymaps.

## Keyboard

- **Board:** ZSA Voyager (`zsa/voyager`)
- **Base layout:** [Magic Sturdy](https://github.com/Ikcelaks/keyboard_layouts/blob/main/magic_sturdy/magic_sturdy.md) with [getreuer's mods](https://getreuer.info/posts/keyboards/alt-layouts/index.html#magic-sturdy)

## Layout

[![Voyager keymap layout](keyboards/zsa/voyager/keymaps/omareloui/draw.svg)](keyboards/zsa/voyager/keymaps/omareloui/draw_keymap.yaml)

Layers, in order:

| Layer   | Purpose                                                                     |
| ------- | --------------------------------------------------------------------------- |
| `STRDY` | Base alpha layer (home row mods for Shift/Ctrl/Alt/GUI + layer taps)        |
| `GAME`  | Flat WASD-friendly layer for gaming                                         |
| `SYM`   | Symbols                                                                     |
| `NAV`   | Navigation, window/tab switching, text selection helpers                    |
| `NUM`   | Numpad-style numbers and math operators                                     |
| `WIN`   | Media keys, RGB matrix controls, window management (macOS-style GUI combos) |
| `FUN`   | Function keys, reboot                                                       |
| `EXT`   | Extra: clipboard ops, Unicode input, mouse jiggler, Orbital Mouse controls  |

Home row mods use **Chordal Hold** and **tapping term**.

### Magic keys

#### Magic Keys in Base Layer

|     |              |              |              |              |              |              |              |              |              |              |              |              |              |
| --- | ------------ | ------------ | ------------ | ------------ | ------------ | ------------ | ------------ | ------------ | ------------ | ------------ | ------------ | ------------ | ------------ |
| key | <kbd>A</kbd> | <kbd>O</kbd> | <kbd>U</kbd> | <kbd>E</kbd> | <kbd>C</kbd> | <kbd>D</kbd> | <kbd>G</kbd> | <kbd>P</kbd> | <kbd>Y</kbd> | <kbd>K</kbd> | <kbd>L</kbd> | <kbd>R</kbd> | <kbd>S</kbd> |
| ★   | <kbd>O</kbd> | <kbd>A</kbd> | <kbd>E</kbd> | <kbd>U</kbd> | <kbd>Y</kbd> | <kbd>Y</kbd> | <kbd>Y</kbd> | <kbd>Y</kbd> | <kbd>P</kbd> | <kbd>J</kbd> | <kbd>k</kbd> | <kbd>L</kbd> | <kbd>K</kbd> |
| ⟲   | <kbd>N</kbd> | <kbd>N</kbd> |              | <kbd>N</kbd> |              | <kbd>N</kbd> |              |              |              |              |              |              |              |

|     |               |                |                |                 |                |                           |
| --- | ------------- | -------------- | -------------- | --------------- | -------------- | ------------------------- |
| key | <kbd>I</kbd>  | <kbd>Q</kbd>   | <kbd>M</kbd>   | <kbd>T</kbd>    | <kbd>␣</kbd>   | <kbd>⇧</kbd>+<kbd>I</kbd> |
| ★   | <kbd>ON</kbd> | <kbd>UEN</kbd> | <kbd>ENT</kbd> | <kbd>MENT</kbd> | <kbd>THE</kbd> | <kbd>'</kbd>              |
| ⟲   | <kbd>S</kbd>  | <kbd>C</kbd>   | <kbd>S</kbd>   | <kbd>S</kbd>    | <kbd>N</kbd>   |                           |

#### Magic Keys in Symbols Layer

|     |              |              |              |                |               |               |                                                                                                                                               |
| --- | ------------ | ------------ | ------------ | -------------- | ------------- | ------------- | --------------------------------------------------------------------------------------------------------------------------------------------- |
| key | <kbd>(</kbd> | <kbd>[</kbd> | <kbd><</kbd> | <kbd>.</kbd>   | <kbd>=</kbd>  | <kbd>!</kbd>  | <kbd>+</kbd>, <kbd>-</kbd>, <kbd>\*</kbd>, <kbd>%</kbd>, <kbd>\|</kbd>, <kbd>^</kbd>, <kbd>~</kbd>, <kbd>$</kbd>, <kbd>\_</kbd>, <kbd>:</kbd> |
| ★   | <kbd>)</kbd> | <kbd>]</kbd> | <kbd>></kbd> | <kbd>./</kbd>  | <kbd>==</kbd> | <kbd>==</kbd> | <kbd>=</kbd>                                                                                                                                  |
| ⟲   |              |              |              | <kbd>../</kbd> |               |               |                                                                                                                                               |

|     |                           |                             |                    |                  |                    |
| --- | ------------------------- | --------------------------- | ------------------ | ---------------- | ------------------ |
| key | <kbd>"</kbd>              | <kbd>`</kbd>                | <kbd>#</kbd>       | <kbd>&</kbd>     | <kbd>@</kbd>       |
| ★   | <kbd>""\<cursor>"""</kbd> | <kbd>``↵\<cursor>↵```</kbd> | <kbd>include</kbd> | <kbd>nbsp;</kbd> | <kbd>USRNAME</kbd> |
| ⟲   |                           |                             |                    |                  |                    |

### Legend

The diagram uses glyphs instead of raw keycode names (mapped in `draw_config.yaml`'s `qmk_keycode_map`). Reference for reading it:

| Symbol       | Meaning                        |
| ------------ | ------------------------------ |
| <kbd>★</kbd> | Magic key                      |
| <kbd>⟲</kbd> | Repeat Key                     |
| <kbd>⎈</kbd> | Ctrl (left/right)              |
| <kbd>⇧</kbd> | Shift (left/right)             |
| <kbd>⎇</kbd> | Alt (left/right)               |
| <kbd>⌘</kbd> | GUI / Super / Cmd (left/right) |
| <kbd>⇪</kbd> | Caps Word                      |
| <kbd>⇞</kbd> | Page Up                        |
| <kbd>⇟</kbd> | Page Down                      |
| <kbd>↖</kbd> | Home                           |
| <kbd>↘</kbd> | End                            |
| <kbd>⧉</kbd> | Copy                           |
| <kbd>✂</kbd> | Cut                            |
| <kbd>🗎</kbd> | Paste                          |
| <kbd>⎁</kbd> | Select All                     |
| <kbd>⎀</kbd> | Select Line                    |
| <kbd>⟾</kbd> | Select Word Forwards           |
| <kbd>⟽</kbd> | Select Word Backwards          |
| <kbd>⎌</kbd> | Undo                           |
| <kbd>⎙</kbd> | Print screen                   |
| <kbd>⌕</kbd> | Search selected in new tab     |

## Modules

Community modules pulled in via `.gitmodules` and declared in `keymap.json`:

**From [getreuer/qmk-modules](https://github.com/getreuer/qmk-modules):**

- **Sentence Case** – auto-capitalizes the first letter after sentence-ending punctuation
- **Custom Shift Keys** – per-key alternate output when shifted, restricted here to layers 0, 1, and 5
- **Select Word** – smarter word/line selection helpers (`SELWORD` / `SELWBAK` / `SELLINE`)
- **Lumino** – opinionated RGB matrix lighting control scheme (`LUM_CYC`)
- **PaletteFx** – RGB matrix effects/palettes, all effects and palettes enabled
- **Orbital Mouse** – joystick-style cursor movement from a key cluster, with a custom speed curve
- **Mouse Turbo Click** – auto-repeating mouse clicks (`TURBO`, used on the `GAME` layer)
- **Cyclotab** – tab/window switching with a single key

**From [zsa/qmk_modules](https://github.com/zsa/qmk_modules):**

- **Navigator Trackball** – ZSA's official trackball driver; `NAV_TURBO`/`NAV_AIM`/`DRAG_SCROLL` (hold) and `NAV_VSCRL` (toggle) on the `EXT` layer top row

**Own module (`modules/omareloui/xcase`):**

- **XCase** – converts the following typed word into `camelCase`, `PascalCase`, `snake_case`, `kebab-case`, `Title Case`, or `path/case` on demand

## Other notable features

- **Combos** (`COMBO_ENABLE`) for punctuation and home-row-mod letter pairs
- **Autocorrect** with a custom dictionary (`autocorrection_dict.txt` / generated `autocorrect_data.h`)
- **Repeat Key** and **Layer Lock** for one-shot key repeats and stuck-on layers
- **Dynamic Macros** (nesting disabled)
- **Mouse keys** with a jigger keycode (`JIGGLE`, gated behind `ENABLE_MOUSE_JIGGLER`) to keep a session alive
- A handful of personal macros (email/username/ID snippets, symbol pairs, Magic-key expansions) implemented in `keymap.c`

## Configuring QMK

1. Install and set up the QMK CLI if you haven't already — see the [QMK docs](https://docs.qmk.fm/#/newbs).
2. Fork and clone this repository.
3. Point QMK at this userspace:

   ```sh
   qmk config user.overlay_dir="$(realpath qmk-keymap)"
   ```

4. (Optional) list or manage build targets:

   ```sh
   qmk userspace-list
   qmk userspace-add -kb zsa/voyager -km omareloui
   qmk userspace-remove -kb zsa/voyager -km omareloui
   ```

   The `zsa/voyager` + `omareloui` target is already declared in `qmk.json`, so this is only needed if you add more keymaps.

## Building

**Locally**, from inside the cloned repo:

```sh
qmk config user.overlay_dir="$(realpath .)"
qmk compile -kb zsa/voyager -km omareloui
# or
make zsa/voyager:omareloui
# or, to build every target listed in qmk.json:
qmk userspace-compile
```

This pulls in the `modules/getreuer` submodule automatically — run `git submodule update --init --recursive` first if you cloned without `--recurse-submodules`.

You can use `git submodule update --remote --recursive` to pull in updates from the upstream `getreuer/qmk-modules` repo.

There's also a `.devcontainer` (based on `ghcr.io/qmk/qmk_cli`) if you'd rather build inside VS Code / Codespaces without installing the toolchain locally.

**Via GitHub Actions:**

1. Enable Actions on your fork.
2. Push to `main` (or trigger the workflow manually).
3. `build_binaries.yaml` runs the reusable `qmk_userspace_build` / `qmk_userspace_publish` workflows against `qmk/qmk_firmware@develop`.
4. Grab the compiled `.bin`/`.uf2` from the fork's **Releases** tab once the run finishes.

## Flashing

1. Put the Voyager into bootloader mode (via [ZSA's Wally tool](https://www.zsa.io/flash) or the key combo for your layout).
2. Flash with QMK directly:

   ```sh
   qmk flash -kb zsa/voyager -km omareloui
   ```

3. Alternatively, drag-and-drop the built firmware file using Wally, or use the ZSA online flasher if you built via GitHub Actions.
4. Repeat for both halves if your firmware/EEPROM settings require it.

## License

GPL-2.0, consistent with QMK firmware itself. See `LICENSE`.
