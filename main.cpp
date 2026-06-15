#include <Arduino.h>
#include <WiFi.h>
#include <time.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// WiFi credentials
const char* ssid = "CTOS";
const char* password = "200300##A67Yola##**";   // <-- CHANGE THIS

// Timezone: Egypt is currently on DST (UTC+3)
// When DST ends (end of October), change to 2*3600.
const long gmtOffset_sec = 3 * 3600;   // UTC+3 for now
const int daylightOffset_sec = 0;      // No extra DST offset

// Clock face center and size
const int cx = SCREEN_WIDTH / 2;   // 64
const int cy = SCREEN_HEIGHT / 2;  // 32
const int radius = 24;             // smaller to leave room for date

void drawHand(float angle, int length, int thickness) {
  int x = cx + cos(angle) * length;
  int y = cy + sin(angle) * length;
  display.drawLine(cx, cy, x, y, SSD1306_WHITE);
  if (thickness > 1) {
    float perp = angle + PI/2;
    int dx = cos(perp);
    int dy = sin(perp);
    display.drawLine(cx + dx, cy + dy, x + dx, y + dy, SSD1306_WHITE);
    display.drawLine(cx - dx, cy - dy, x - dx, y - dy, SSD1306_WHITE);
  }
}

void drawAnalogClock(int hour, int minute, int second) {
  display.drawCircle(cx, cy, radius, SSD1306_WHITE);
  display.drawCircle(cx, cy, radius+1, SSD1306_WHITE);
  
  // Hour ticks
  for (int i = 1; i <= 12; i++) {
    float rad = (i * 30) * PI / 180.0;
    int x1 = cx + cos(rad) * (radius - 3);
    int y1 = cy + sin(rad) * (radius - 3);
    int x2 = cx + cos(rad) * (radius + 1);
    int y2 = cy + sin(rad) * (radius + 1);
    display.drawLine(x1, y1, x2, y2, SSD1306_WHITE);
  }
  
  float hourAngle = ((hour % 12) * 30 + minute * 0.5) * PI / 180.0;
  drawHand(hourAngle, radius - 8, 2);
  float minuteAngle = (minute * 6 + second * 0.1) * PI / 180.0;
  drawHand(minuteAngle, radius - 4, 1);
  float secondAngle = (second * 6) * PI / 180.0;
  drawHand(secondAngle, radius - 1, 1);
  
  display.fillCircle(cx, cy, 2, SSD1306_WHITE);
}

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) for(;;);
  
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 20);
  display.println("Connecting WiFi...");
  display.display();

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(500);

  display.clearDisplay();
  display.setCursor(10, 20);
  display.println("Getting time...");
  display.display();

  configTime(gmtOffset_sec, daylightOffset_sec, "pool.ntp.org");
  struct tm timeinfo;
  while (!getLocalTime(&timeinfo)) delay(500);
}

void loop() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) return;
  
  int hour = timeinfo.tm_hour;
  int minute = timeinfo.tm_min;
  int second = timeinfo.tm_sec;
  int day = timeinfo.tm_mday;
  int month = timeinfo.tm_mon + 1;
  int year = timeinfo.tm_year + 1900;
  
  display.clearDisplay();
  
  // Draw analog clock (centered)
  drawAnalogClock(hour, minute, second);
  
  // Digital time – top‑right corner (leave left side for date)
  display.setTextSize(1);
  char timeStr[9];
  sprintf(timeStr, "%02d:%02d:%02d", hour, minute, second);
  int timeWidth = strlen(timeStr) * 6;
  display.setCursor(SCREEN_WIDTH - timeWidth, 2);
  display.print(timeStr);
  
  // Date – bottom‑left corner (clear of the clock)
  char dateStr[11];
  sprintf(dateStr, "%02d/%02d/%04d", day, month, year);
  display.setCursor(2, SCREEN_HEIGHT - 8);
  display.print(dateStr);
  
  display.display();
  delay(1000);
}