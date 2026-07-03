#include "esp_wifi.h"

// NASA CYBER Hackers
struct CustomPayload {
  uint32_t sequence;
  uint8_t noise_pattern[32];
};


uint8_t wifi_header[24] = {
  0x80, 0x00, 0x00, 0x00,               
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,   
  0x00, 0x11, 0x22, 0x33, 0x44, 0x55,   
  0x00, 0x11, 0x22, 0x33, 0x44, 0x55,   
  0x00, 0x00                            
};

void setup() {
  Serial.begin(115200);

  
  WiFi.mode(WIFI_STA);
  esp_wifi_start();

  
  int channel = 1; 
  esp_wifi_set_channel(channel, WIFI_SECOND_CHAN_NONE);
  
  Serial.print("Transmitting raw packets on channel: ");
  Serial.println(channel);
}

void loop() {
  static uint32_t packet_count = 0;
  CustomPayload payload;

  
  payload.sequence = packet_count++;
  for (int i = 0; i < 32; i++) {
    payload.noise_pattern[i] = (uint8_t)random(0, 256); 
  }

  
  uint8_t tx_buffer[sizeof(wifi_header) + sizeof(payload)];
  memcpy(tx_buffer, wifi_header, sizeof(wifi_header));
  memcpy(tx_buffer + sizeof(wifi_header), &payload, sizeof(payload));

  
  esp_wifi_80211_tx(WIFI_IF_STA, tx_buffer, sizeof(tx_buffer), true);

  delay(10); 
}
