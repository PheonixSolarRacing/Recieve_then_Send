// demo: CAN-BUS Shield, receive data
#include <mcp_can.h>
#include <SPI.h>

long unsigned int rxId;
unsigned char len = 0;
unsigned char rxBuf[8];

MCP_CAN CAN0(10);                               // Set CS to pin 10


void setup()
{
  Serial.begin(115200);
  CAN0.begin(CAN_125KBPS);                       // init can bus : baudrate = 500k 
  pinMode(0, INPUT);                            // Setting pin 2 for /INT input
  Serial.println("MCP2515 Library Receive Example...");
}

void loop()
{
    if(!digitalRead(0))                         // If pin 2 is low, read receive buffer
    {
      CAN0.readMsgBuf(&len, rxBuf);              // Read data: len = data length, buf = data byte(s)
      rxId = CAN0.getCanId();                    // Get message ID
      Serial.print("Received ID:");
      Serial.print(rxId);
      Serial.print(" Data:");
      for(int i = 0; i<len; i++)                // Print each byte of the data
      {
        Serial.print(rxBuf[i]);
        Serial.print(",");
      }
      Serial.print("  Re-sending this  ");
      CAN0.sendMsgBuf(410, 0, len, rxBuf); 
      Serial.println();
    }

    if((millis()%10000) == 0){Serial.println("--");}
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
