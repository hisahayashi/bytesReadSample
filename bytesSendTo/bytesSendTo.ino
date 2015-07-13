
void setup(){
  Serial.begin(115200);
}

void loop(){
  sendDataString('A', 1);
  sendDataString('B', 22);
  sendDataString('C', 333);
  sendDataString('D', 4444);
  delay(20);
}

void sendDataString(char symbol, int data ){
  Serial.print(symbol);
  Serial.println(data);
}







