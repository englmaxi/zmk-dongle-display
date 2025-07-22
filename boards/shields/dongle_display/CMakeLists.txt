if(CONFIG_ZMK_DISPLAY AND CONFIG_ZMK_DISPLAY_STATUS_SCREEN_CUSTOM AND ((NOT CONFIG_ZMK_SPLIT) OR CONFIG_ZMK_SPLIT_ROLE_CENTRAL))
  zephyr_library()
  zephyr_library_sources(${ZEPHYR_BASE}/misc/empty_file.c)
  zephyr_library_include_directories(${ZEPHYR_LVGL_MODULE_DIR})
  zephyr_library_include_directories(${ZEPHYR_BASE}/lib/gui/lvgl/)
  zephyr_library_include_directories(${ZEPHYR_BASE}/drivers)
  zephyr_library_include_directories(${CMAKE_SOURCE_DIR}/include)

  zephyr_library_sources(
    custom_status_screen.c
    widgets/bongo_cat.c
    widgets/bongo_cat_images.c
    widgets/layer_status.c
    widgets/modifiers.c
    widgets/modifiers_sym.c
    widgets/output_status_sym.c
  )

  # Only build the HID indicators widget if that feature is on:
  target_sources_ifdef(
    CONFIG_ZMK_HID_INDICATORS
    app PRIVATE widgets/hid_indicators.c
  )

  # Only build the BLE-driven output_status widget if BLE is on:
  if (CONFIG_ZMK_BLE)
    zephyr_library_sources(widgets/output_status.c)
  endif()

  # Only build the battery widget if battery support (and dongle display) is on:
  if (CONFIG_ZMK_BATTERY AND CONFIG_ZMK_DONGLE_DISPLAY_DONGLE_BATTERY)
    zephyr_library_sources(widgets/battery_status.c)
  endif()

endif()