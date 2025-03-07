#include <Arduino.h>
#include "LoRaModule.h"
#include "LedController.h"
#include "esp_system.h"

// put function declarations here:

LoRaModule lora;
//LedController led(4);  // 使用GPIO4作为LED引脚

/* 读取ESP32的MAC地址作为唯一标识符输出到Serial */
void printDeviceID() {
    uint8_t mac[6];
    esp_read_mac(mac, ESP_MAC_WIFI_STA); // 获取 Wi-Fi MAC 地址
    Serial.print("Device ID (MAC): ");
    for (int i = 0; i < 6; i++) {
        if (i > 0) Serial.print(":");
        Serial.print(mac[i], HEX);
    }
    Serial.println();
}

void setup() {
  Serial.begin(115200);

  // 打印设备 ID

  printDeviceID;

  
  
  /* LED接线测试 *
  pinMode(4, OUTPUT);
  Serial.println("report_00: " + String(digitalRead(4)));
  digitalWrite(4, HIGH);
  Serial.println("report_01: " + String(digitalRead(4)));
  delay(1000);
  digitalWrite(4, LOW);
  Serial.println("report_02: " + String(digitalRead(4)));
  delay(1000);
  digitalWrite(4, HIGH);
  Serial.println("report_03: " + String(digitalRead(4)));
  delay(1000);
  /**
  digitalWrite(4, LOW);
  Serial.println("report_04: " + String(digitalRead(4)));
  delay(1000);
  Serial.println("report_05: " + String(digitalRead(4)));
  led.begin();
  led.turnOn();
  Serial.println("report_06: " + String(digitalRead(4)));
  delay(1000);
  led.turnOff();


  /* 初始化LED *
  led.begin();
  led.setBlinkFrequency(1000);  // 默认1秒闪烁一次
  
  /* 初始化LoRa模块 */
  lora.begin(); // 初始化LoRa模块并读取启动信息
  

  /***********以下为临时测试使用 ***********/

  /* 设置本地地址 */
  int localAddress = 15; // 要设置的本地地址
  if (lora.setLocalAddress(localAddress)) {
    Serial.println("[Debug Serial]:Local address set successfully."); // 设置成功
  } 
  else {
    Serial.println("[Debug Serial]:Failed to set local address."); // 设置失败
  }

  /* 设置目标地址 *
  int targetAddress = 12;
  if (lora.setTargetAddress(targetAddress)) {
    Serial.println("[Debug Serial]:Target address set successfully."); // 设置成功
  } 
  else {
    Serial.println("[Debug Serial]:Failed to set target address."); // 设置失败
  }

  /* 设置接收参数 */
  LoRaTransConfigStruct rxConfig;
  rxConfig.freq = 470500000;      // 设置频率
  rxConfig.dataRate = SF7;        // 设置数据速率
  rxConfig.bandwidth = BW_125KHz; // 设置带宽
  rxConfig.codeRate = CR_4_5;     // 设置编码率
  rxConfig.iqConverted = IQ_ON;   //设置IQ调制开关

  if (lora.setRxConfig(&rxConfig)) {
    Serial.println("[Debug Serial]:Rx configuration set successfully."); // 设置成功
  } 
  else {
    Serial.println("[Debug Serial]:Failed to set Rx configuration.");   // 设置失败
  }

  /* 设置发射参数 *
  LoRaTransConfigStruct txConfig;
  txConfig.freq = 470500000;      // 设置频率
  txConfig.dataRate = SF7;        // 设置数据速率
  txConfig.bandwidth = BW_125KHz; // 设置带宽
  txConfig.codeRate = CR_4_5;     // 设置编码率
  txConfig.iqConverted = IQ_ON;   // 设置IQ调制开关
  txConfig.power = 21;            // 设置发射功率

  if (lora.setTxConfig(&txConfig)) {
    Serial.println("[Debug Serial]:Tx configuration set successfully."); // 设置成功
  } 
  else {
    Serial.println("[Debug Serial]:Failed to set Tx configuration.");   // 设置失败
  }

  /* 设置发射内容 *
  String dataToSend = "1122334455 AABBCC 6677889900";
  if (lora.sendData(dataToSend)) {
        Serial.println("[Debug Serial]:Data sent successfully."); // 发送成功
    } else {
        Serial.println("[Debug Serial]:Failed to send data."); // 发送失败
    }
  
  /**********************/

}

void loop() {
  /* 以下暂定为LED测试 *
  // 更新LED状态
  led.update();
  
  

  // 检查串口命令
  if (Serial1.available()) {
    Serial.println("[Debug Serial]:Start to receive data.");
    Serial1.readStringUntil('\n');
    Serial1.readStringUntil('\n');
    String command = Serial1.readStringUntil('\n');
    command.trim();// 去除空格和换行符
    Serial.println(command);
    // 解析命令
    if (command.startsWith("freq")) {
      // 设置闪烁频率，格式：freq 1000
      int freq = command.substring(5).toInt();
      led.setBlinkFrequency(freq);
      Serial.println("[Debug Serial]:Set LED frequency to " + String(freq) + "ms");
    }
    else if (command == "on") {
      Serial.println("report_on_01: " + String(digitalRead(4)));
      led.turnOn();
      Serial.println("[Debug Serial]:LED turned on");
      Serial.println("report_on_02: " + String(digitalRead(4)));
    }
    else if (command == "off") {
      Serial.println("report_off_01: " + String(digitalRead(4)));
      led.turnOff();
      Serial.println("[Debug Serial]:LED turned off");
      Serial.println("report_off_02: " + String(digitalRead(4)));
    }
    else if (command.startsWith("bright")) {
      // 设置亮度，格式：bright 255
      int brightness = command.substring(7).toInt();
      led.setBrightness(brightness);
      Serial.println("[Debug Serial]:Set LED brightness to " + String(brightness));
    }
  }
  /**/
}

// put function definitions here:
