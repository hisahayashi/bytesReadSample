# bytesReadSample

Arduino and oF's byteIO sample

# Usage

bytesSendTo.ino をArduinoに書き込み、oFのプロジェクトを実行すると、ino側で指定された値がA,B,C,Dなどの添字とともにoF側に送られます。なので、ino側でPinから取得した値を適当な添字とともにsendすれば、oF側で読み取れます。

# Notice

シリアル通信のデータ転送レートの関係でArduinoから送られる値を固定しても、値が揺れる模様。  
例えば、500を常に送るようにしても、0, 500, 0, 500 のような感じでぶれます。



# Arduino

```c++
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
```

# oF

```c++
void bytesRead::updateSerial(){
    int len = SERIAL_LEN - 1;
    nBytesRead = 0;
    int nRead = 0;
    char bytesRead[len];
    unsigned char bytesReturned[len];
    
    memset(bytesReturned, 0, len);
    memset(bytesReadString, 0, SERIAL_LEN);
    
    // シリアル通信で受け取ったデータを読み込む
    while ((nRead = serial.readBytes(bytesReturned, len)) > 0) {
        nBytesRead = nRead;
    };
    
    if (nBytesRead > 0) {
        memcpy(bytesReadString, bytesReturned, len);
        string str = bytesReadString;
        
        // Byteをパース
        vector< string > splitString = ofSplitString( str, "\n" );
        for( int i = 0; i < splitString.size(); i++ ){
            
            if( splitString[i] != "" ){
                string spStr = splitString[i];
                char spIndex = ofToChar(spStr.substr(0,1));
                int spNum = ofToInt( spStr.substr(1) );
                
                switch( spIndex ){
                    case 'A':
                        data1 = spNum;
                        break;
                    case 'B':
                        data2 = spNum;
                        break;
                    case 'C':
                        data3 = spNum;
                        break;
                    case 'D':
                        data4 = spNum;
                        break;
                    default:
                        break;
                }
                
                // ofLog() << "i: " << i << ", spNum: " << ofToString( spNum ) << ", spIndex: " << ofToString(spIndex);
            }
        }
    }
}
```
