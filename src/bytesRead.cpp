//
//  bytesRead.cpp
//  bytesReadSample
//
//  Created by HisaHayashi on 2014/10/13.
//
//

#include "bytesRead.h"

//--------------------------------------------------------------
void bytesRead::setup(){
    
    // シリアルポートの取得
    vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();
    string deviceLine, serialID;
    
    // ポート名の取得
    for( int i = 0; i < deviceList.size(); i++ ){
        deviceLine = deviceList[i].getDeviceName().c_str();
        
        if( deviceLine.substr(0,12) == "tty.usbmodem" ){
            serialID = "/dev/" + deviceLine;
            cout << "Arduino serial = " << serialID << endl;
        }
    }
    
    // Arduinoに接続
    serial.setup(serialID, 115200);
    
    // 初期化
    bSetupArduino = false;
}


//--------------------------------------------------------------
void bytesRead::setupArduino(){
    
    ofLog() << "ofArduino Setup";
    
    // 接続の確立のフラグをtrueに
    bSetupArduino = true;
}

//--------------------------------------------------------------
void bytesRead::update(){
    
    // シリアルの初期化
    if( serial.isInitialized() && !bSetupArduino ){
        setupArduino();
    }
    
    // 接続後の処理
    if( bSetupArduino ){
        updateSerial();
    }
}

//--------------------------------------------------------------
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

//--------------------------------------------------------------
void bytesRead::draw(){
    
    if( debug ){
        debugTextDraw();
        
        // 接続後の処理
        if( bSetupArduino ){
            debugLineDraw();
        }
    }
}

//--------------------------------------------------------------
void bytesRead::debugTextDraw(){
    string msg = "DEBUG: \n";
    msg += "FPS: " + ofToString(ofGetFrameRate()) + "\n";
    msg += "bSetupArduino: " + ofToString(bSetupArduino) + "\n";
    msg += "data1: " + ofToString(data1) + "\n";
    msg += "data2: " + ofToString(data2) + "\n";
    msg += "data3: " + ofToString(data3) + "\n";
    msg += "data4: " + ofToString(data4) + "\n";
    
    ofSetColor( 255, 255 );
    ofDrawBitmapString(msg, 20, 20);
}

//--------------------------------------------------------------
void bytesRead::debugLineDraw(){
    
    v_data1.push_back(data1);
    v_data2.push_back(data2);
    v_data3.push_back(data3);
    v_data4.push_back(data4);
    
    int line_x = ofGetWidth() * 0.5;
    int line_y = ofGetHeight() * 0.5;
    float weight = 2;
    float ratio = 0.2;
    
    ofPath p1 = ofPath();
    p1.setStrokeColor( ofColor(255,0,0) );
    p1.setFilled(false);
    p1.setStrokeWidth(weight);
    for( int i = 0; i < v_data1.size(); i++ ){
        p1.lineTo(i * 1, line_y + v_data1[i]*ratio);
    }
    p1.draw();
    
    ofPath p2 = ofPath();
    p2.setStrokeColor( ofColor(0,255,0) );
    p2.setFilled(false);
    p2.setStrokeWidth(weight);
    for( int i = 0; i < v_data2.size(); i++ ){
        p2.lineTo( i * 1, line_y + v_data2[i]*ratio);
    }
    p2.draw();
    
    ofPath p3 = ofPath();
    p3.setStrokeColor( ofColor(0,0,255) );
    p3.setFilled(false);
    p3.setStrokeWidth(weight);
    for( int i = 0; i < v_data3.size(); i++ ){
        p3.lineTo( i * 1, line_y + v_data3[i]*ratio);
    }
    p3.draw();
    
    ofPath p4 = ofPath();
    p4.setStrokeColor( ofColor(255,255,0) );
    p4.setFilled(false);
    p4.setStrokeWidth(weight);
    for( int i = 0; i < v_data4.size(); i++ ){
        p4.lineTo( i * 1, line_y + v_data4[i]*ratio);
    }
    p4.draw();
    
}

//--------------------------------------------------------------
void bytesRead::keyPressed(int key){
}

//--------------------------------------------------------------
ReadData bytesRead::getReadData(){
    ReadData data = {
        bSetupArduino,
        data1,
        data2,
        data3,
        data4
    };
    return data;
}
