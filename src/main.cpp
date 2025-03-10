#include <Arduino.h>
#include "LoRaModule.h"
#include "LedModule.h"
#include "LaserModule.h"
// put function declarations here:
void printEspId();

// LoRaModule lora;
// Led led;
Laser laser;

void setup() {
  Serial.begin(115200);
  laser.begin();
  // lora.begin(); // 初始化LoRa模块并读取启动信息
  // led.begin(4);

  /*
  // 测试设置本地地址
  int localAddress = 12; // 要设置的本地地址
  // int targetAddress = 13;
  lora.setLocalAddress(localAddress);
  // lora.setTargetAddress(targetAddress);
  // 测试设置接收配置
  LoRaTransConfigStruct rxConfig;
  rxConfig.freq = 470500000; // 设置频率
  rxConfig.dataRate = SF7; // 设置数据速率
  rxConfig.bandwidth = BW_125KHz; // 设置带宽
  rxConfig.codeRate = CR_4_5; // 设置编码率
  rxConfig.iqConverted = IQ_ON;

  // 测试设置发送配置
  LoRaTransConfigStruct txConfig;
  txConfig.freq = 470500000; // 设置频率
  txConfig.dataRate = SF7; // 设置数据速率
  txConfig.bandwidth = BW_125KHz; // 设置带宽
  txConfig.codeRate = CR_4_5; // 设置编码率
  txConfig.power = 21;
  txConfig.iqConverted = IQ_ON;

  lora.setRxConfig(&rxConfig);
  // lora.sendData("0505");
  RecvInfo test;
  lora.receiveData(test);
  Serial.println(test.message);
  Serial.println("from="+String(test.fromAddr));
  Serial.println("rssi="+String(test.rssi)+" snr="+String(test.snr));
  */


}

void loop() {
  if (Serial1.available() >= 23) { // 确保有足够的数据（22 字节）
    uint8_t buffer[25];
    Serial1.readBytes(buffer, 23); // 读取一帧数据
    uint8_t data[3];
    for (int i = 0; i < 2; i++) {
        data[i] = buffer[13 + i];
    }
    // 解析主峰质心
    uint16_t mainPeakCentroid = (data[1] << 8) | data[0]; // 低位在前，高位在后
    Serial.print("Main Peak Centroid: ");
    Serial.println(mainPeakCentroid);
  }
}

// put function definitions here:

void printEspId()
{
    // 读取芯片ID
  uint64_t chipId = ESP.getEfuseMac(); // 获取芯片 MAC 地址（作为芯片ID）
  
  // 将64位整数分成两个32位整数以便打印
  uint32_t chipId_high = (uint32_t)(chipId >> 32);
  uint32_t chipId_low = (uint32_t)chipId;
  
  // 打印芯片ID（十六进制格式）
  Serial.printf("ESP32 Chip ID = %08X%08X\n", chipId_high, chipId_low);
  
  // 也可以分别打印高32位和低32位
  Serial.printf("High = 0x%08X\n", chipId_high);
  Serial.printf("Low = 0x%08X\n", chipId_low);
}
