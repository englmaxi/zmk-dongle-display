# Dongle Display

This module repository provides a ZMK shield that replaces the built-in status screen with a custom screen designed for 128x64-pixel OLED displays, or 128x32 with some limitations.

## Usage

To use this module, first add it to your `config/west.yml` by adding a new entry to `remotes` and `projects`:

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
      revision: main
  self:
    path: config
```

Next, replace the built-in status screen by adding `dongle_display` to your `build.yaml`:

```yaml build.yaml
---
include:
  - board: seeeduino_xiao_ble
    shield: sweep_central_dongle dongle_display
```

This shield assumes that the [dongle](https://zmk.dev/docs/development/hardware-integration/dongle) is already set up and functioning with the built-in status screen.
For setup examples, refer to the shields in my [`zmk-config`](https://github.com/englmaxi/zmk-config/tree/master/boards/shields).
- If you are using the larger 1.3" OLED, replace `solomon,ssd1306fb` with `sinowealth,sh1106` and set `segment-offset = <2>`.
- If you are using a nice!nano, replace `xiao_i2c` with `pro_micro_i2c`.
- If you are using the smaller 0.91" OLED, replace `height = <64>;` by `height = <32>;`

## Widgets
- active hid indicators (CLCK, NLCK, SLCK)
- active modifiers
- bongo cat
- highest layer name
- output status
- peripheral battery levels

## Configuration

To also display the battery level of the dongle/central device, use the following configuration property:

```ini
CONFIG_ZMK_DONGLE_DISPLAY_DONGLE_BATTERY=y
```

If you want to use MacOS modifier symbols instead of the Windows modifier symbols, use the following configuration property:

```ini
CONFIG_ZMK_DONGLE_DISPLAY_MAC_MODIFIERS=y
```

## Smaller OLEDs, with 128x32 pixels

To allow smaller OLEDs, with 128x32 pixels, it will be necessary to exclude some widgets, like the bongo cat, active modifiers or the highest layer name. You can do it with the following config entries:

```ini
CONFIG_ZMK_DONGLE_DISPLAY_BONGO_CAT=n
CONFIG_ZMK_DONGLE_DISPLAY_MODIFIERS=n
CONFIG_ZMK_DONGLE_DISPLAY_LAYER=n
```

It is also necessary to reduce the buffer size, otherwise the I2C communication can become unstable:

```ini
CONFIG_LV_Z_VDB_SIZE=32
```

## Demo
![output](https://github.com/englmaxi/zmk-config/assets/43675074/8d268f23-1a4f-44c3-817e-c36dc96a1f8b)
![mods](https://github.com/englmaxi/zmk-config/assets/43675074/af9ec3f5-8f61-4629-abed-14ba0047f0bd)

## Dongle Designs
- [case1](/cases)
- [case2](/cases)
- [Cyberdeck](https://github.com/rafaelromao/keyboards/tree/main/stls/Dongle) by @rafaelromao
- [Dongle PCB](https://github.com/spe2/zmk_dongle_hardware) by @spe2
- [Macintosh](https://makerworld.com/en/models/403660) by @rain2813
- [Redox](https://makerworld.com/en/models/242951) by @rurounikexin
- [sai44 Dongle](https://github.com/leafflat/sai44/tree/main/STL/Dongle) by @leafflat
- [ZMK Display Dongle](https://makerworld.com/en/models/496738) by @yingeling
- [ZMK Nice Nano 128x64 OLED Dongle](https://www.printables.com/model/1207682-zmk-nice-nano-128x64-oled-dongle) by @James_909973
- [Dilemma DIY with 128x32 OLED](https://github.com/rafaelromao/keyboards/tree/main/src/keyboards/bastardkb/dilemma/boards/shields/dilemma)


## Alternatives
- [Prospector](https://github.com/carrefinho/prospector) by @carrefinho
- [YADS](https://github.com/janpfischer/zmk-dongle-screen) by @janpfischer
