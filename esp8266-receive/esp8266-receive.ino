#include <ESP8266WiFi.h>
#include <espnow.h>
#include <Servo.h>
Servo servo;

#define ir_sensor 2
#define body_sensor 4

  unsigned char lock_stat;
// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
    bool e;
} struct_message;

// Create a struct_message called myData
struct_message myData;

// Callback function that will be executed when data is received
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("Bool: ");
  Serial.println(myData.e);
  Serial.println();
}

void setup() {


  // Initialize Serial Monitor
  Serial.begin(115200);
  
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(OnDataRecv);
  lock_stat = 0;//lock and door both close
  servo.attach(5); //D4
  servo.write(0);
    pinMode(ir_sensor,INPUT);
  pinMode(body_sensor,INPUT);
}
void loop()
{

  if(myData.e || digitalRead(body_sensor))
  {
    lock_stat = 1;//unlock but door close
   }    
   else
   {
    lock_stat = 0;
    }
   if(lock_stat == 1)
   {
    servo.write(90);
     while(!digitalRead(ir_sensor));//lock and door both open, wait
     delay(5000);
     servo.write(0);
     lock_stat = 0;
   }
   else
   {
    servo.write(0);
    }
  }
