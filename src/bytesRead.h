//
//  bytesRead.h
//  bytesReadSample
//
//  Created by HisaHayashi on 2014/10/13.
//
//

#ifndef __bytesReadSample__bytesRead__
#define __bytesReadSample__bytesRead__

#include "../ofMain.h"

#include <iostream>

#define SERIAL_LEN 20

//

struct ReadData{
    bool bSetupArduino;
    float data1;
    float data2;
    float data3;
    float data4;
};


class bytesRead {
    
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    
    ReadData getReadData();
    
private:
    
    void debugTextDraw();
    void debugLineDraw();
    void setupArduino();
    void updateSerial();
    
    // debug
    bool debug = true;
    vector <float> v_data1;
    vector <float> v_data2;
    vector <float> v_data3;
    vector <float> v_data4;
    
    // serial
    ofSerial serial;
    bool bSetupArduino;
    int nBytesRead = 0;
    char bytesReadString[SERIAL_LEN];
    
    // datas
    float data1;
    float data2;
    float data3;
    float data4;
    
};


#endif /* defined(__bytesReadSample__bytesRead__) */
