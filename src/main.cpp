#include <Arduino.h>
#include <QMI8658.h>
#include <LovyanGFX.hpp>
#include <LGFX_RP2350_Touch_LCD_128_Waveshare.hpp>

QMI8658 imu;

static LGFX lcd;

void setup(void)
{ 
  Serial.begin(115200);
  imu.begin(6, 7);
  // Set accelerometer range (±8g)
  imu.setAccelRange(QMI8658_ACCEL_RANGE_8G);
  
  // Set accelerometer output data rate (1000Hz)
  imu.setAccelODR(QMI8658_ACCEL_ODR_1000HZ);
  
  // Set gyroscope range (±512dps)
  imu.setGyroRange(QMI8658_GYRO_RANGE_512DPS);
  
  // Set gyroscope output data rate (1000Hz)
  imu.setGyroODR(QMI8658_GYRO_ODR_1000HZ);

  // Set units (DEFAULT: mg for accel, dps for gyro - matches most IMU displays)
  imu.setAccelUnit_mg(true);      // Use mg (like your screen: ACC_X = -965.82)
  imu.setGyroUnit_dps(true);      // Use dps (degrees per second)
  imu.setDisplayPrecision(6);     // 6 decimal places (like your screen)

  // Enable sensors
  imu.enableSensors(QMI8658_ENABLE_ACCEL | QMI8658_ENABLE_GYRO);

  lcd.init();

  if (lcd.width() < lcd.height()) lcd.setRotation(lcd.getRotation() ^ 1);
}

void loop(void)
{ 
  static lgfx::touch_point_t prev_tp;
  static int prev_sec;
  static int fps;
  ++fps;
  int sec = millis() / 1000;
  if (prev_sec != sec)
    {
      prev_sec = sec;
      fps = 0;
    }

  // Method 1: Read all sensor data at once (recommended)
  QMI8658_Data sensorData;
  
  if (imu.readSensorData(sensorData)) {
    Serial.print(millis());
    Serial.print("\t");
    Serial.print(sensorData.accelX, 6);
    Serial.print("\t");
    Serial.print(sensorData.accelY, 6);
    Serial.print("\t");
    Serial.print(sensorData.accelZ, 6);
    Serial.print("\t");
    Serial.print(sensorData.gyroX, 6);
    Serial.print("\t");
    Serial.print(sensorData.gyroY, 6);
    Serial.print("\t");
    Serial.print(sensorData.gyroZ, 6);
    Serial.print("\t");
    Serial.println(sensorData.temperature, 1);
  } else {
    Serial.println("❌ Failed to read sensor data!");
  }
  
  lgfx::touch_point_t tp;
  lcd.getTouch(&tp, 2);
  lcd.getTouch(&tp);

  lcd.startWrite();
  //lcd.fillScreen(TFT_BLACK);
  if (tp.size > 0) 
  {
    lcd.drawSpot(tp.x, tp.y, 20, TFT_MAGENTA);
    prev_tp = tp;
    lcd.setCursor(40,40);
    lcd.printf("fps:%03d", fps);
  }
  else 
  {
    lcd.fillScreen(TFT_BLACK);
  }
  lcd.endWrite();
}

void setup1() {
  //Serial.begin(115200);
}

void loop1() {
  // Serial.println("Hello, World!");
  // delay(1000);
}