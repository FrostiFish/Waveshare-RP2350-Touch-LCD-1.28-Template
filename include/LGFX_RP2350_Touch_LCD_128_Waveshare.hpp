#pragma once

#define LGFX_USE_V1

#include <LovyanGFX.hpp>

// LGFX for Waveshare RP2350-Touch-LCD-1.28
// https://www.waveshare.com/wiki/RP2350-Touch-LCD-1.28

class LGFX : public lgfx::LGFX_Device
{
  lgfx::Panel_GC9A01 _panel_instance;
  lgfx::Bus_SPI       _bus_instance;
  lgfx::Light_PWM     _light_instance;
  lgfx::Touch_CST816S _touch_instance;

  public:
  LGFX(void)
  {
    {
      auto cfg = _bus_instance.config();
      cfg.spi_host   = 1;
      cfg.spi_mode   = 0;
      cfg.freq_write = 80000000;
      cfg.pin_sclk   = 10;
      cfg.pin_miso   = 12;
      cfg.pin_mosi   = 11;
      cfg.pin_dc     = 8;
      _bus_instance.config(cfg);
      _panel_instance.setBus(&_bus_instance);
    }

    {
      auto cfg = _panel_instance.config();
      cfg.pin_cs       = 9;
      cfg.pin_rst      = 13;
      cfg.panel_width  = 240;
      cfg.panel_height = 240;
      cfg.offset_x     = 0;
      cfg.offset_y     = 0;
      cfg.invert       = true;
      cfg.rgb_order    = false;
      //cfg.offset_rotation = 0;
      _panel_instance.config(cfg);
    }

    {
      auto cfg = _light_instance.config();
      cfg.pin_bl      = 25;
      cfg.pwm_channel = 1;
      _light_instance.config(cfg);
      _panel_instance.setLight(&_light_instance);
    }

    {
      auto cfg = _touch_instance.config();
      cfg.x_min      = 0;
      cfg.y_min      = 0;
      cfg.x_max      = 240;
      cfg.y_max      = 240;
      cfg.bus_shared = false;
      cfg.offset_rotation = 0;
      // I2C接続
      cfg.i2c_port   = 1;
      cfg.pin_sda    = 6;
      cfg.pin_scl    = 7;
      cfg.pin_int    = 21;
      cfg.pin_rst    = 22;

      cfg.freq       = 400000;
      _touch_instance.config(cfg);
      _panel_instance.setTouch(&_touch_instance);
    }

    setPanel(&_panel_instance);
  }
};
