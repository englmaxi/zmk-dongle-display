# Dongle Display

The ZMK shield in this module repository, when added, replaces the built-in status screen with a custom one designed for use with 128x64-pixel OLED displays.
As it shows only the peripheral battery levels, it is recommended to be used on dongles only.

## Usage

To use, first add this module to your `config/west.yml` by adding a new entry to `remotes` and `projects`:

```yaml west.yml
manifest:
  remotes:
    - name: zmkfirmware
      url-base: https://github.com/zmkfirmware
    - name: englmaxi
      url-base: https://github.com/englmaxi
  projects:
    - name: zmk
      remote: zmkfirmware
      revision: main
      import: app/west.yml
    - name: zmk-dongle-display
      remote: englmaxi
      revision: win # Windows modifier symbols
      # revision: mac # MacOS modifier symbols
  self:
    path: config
```

Than replace the build-in status screen by adding `dongle_display` to your `build.yaml`:

```yaml build.yaml
---
include:
  - board: seeeduino_xiao_ble
    shield: sweep_central_dongle dongle_display
```

The shield assumes that the dongle is already set up and working with the built-in status screen.
Have a look at the shields in my [`zmk-config`](https://github.com/englmaxi/zmk-config) to see how I did it.

## Widgets
- active hid indicators (CLCK, NLCK, SLCK)
- active modifiers
- bongo cat
- highest layer name
- output status
- peripheral battery levels

## Demo
![output](https://github.com/englmaxi/zmk-config/assets/43675074/8d268f23-1a4f-44c3-817e-c36dc96a1f8b)
![mods](https://github.com/englmaxi/zmk-config/assets/43675074/af9ec3f5-8f61-4629-abed-14ba0047f0bd)

## Dongle Designs
- [case1](/cases)
- [case2](/cases)
- [PCB with OLED and reset button breakouts](https://github.com/spe2/zmk_dongle_hardware)
- [Macintosh](https://makerworld.com/en/models/403660)
- [Redox](https://makerworld.com/en/models/242951)