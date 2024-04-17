#include "irManager.hpp"

bool IrManager::edgeFlag = true;

IrManager::IrManager(int irPin){
    pinMode(irPin, INPUT);
    pullUpDnControl(irPin, PUD_DOWN);
    //wiringPiISR(irPin, INT_EDGE_FALLING, &gpoiIntHandler);
}

int IrManager::waitForHeaderBits(){
    while(digitalRead(irPin) == LOW){} // wait for high signal
    while(digitalRead(irPin) == HIGH){} // wait for low signal
    auto headerStartTime = std::chrono::high_resolution_clock::now();
    
    while(digitalRead(irPin) == LOW){} // wait for high signal
    while(digitalRead(irPin) == HIGH){} // wait for low signal
    auto headerEndTime = std::chrono::high_resolution_clock::now();

    auto result = std::chrono::duration_cast<std::chrono::microseconds>(headerEndTime - headerStartTime);
    std::cout << "Header durition: " << result.count() << std::endl;
    return result.count();
}

int IrManager::readBit(){
    while(digitalRead(irPin) == LOW){} // wait for high signal
    auto dataStartTime = std::chrono::high_resolution_clock::now();
    while(digitalRead(irPin) == HIGH){} // wait for low signal
    auto dataEndTime = std::chrono::high_resolution_clock::now();
    
    auto width = std::chrono::duration_cast<std::chrono::microseconds>(dataEndTime - dataStartTime);
    if(700 < width.count() && width.count() <= 1300)
        return 0;
    else if(1700 < width.count() && width.count() < 2300)
        return 1;
    else{
        //std::cerr << "Absurd bit width: " << width.count() << std::endl; 
        return -1;
    }
}

void gpoiIntHandler(){
    IrManager::edgeFlag = false;
}

void IrManager::waitForEdge(){
    while(edgeFlag){}
    edgeFlag = true;
}

bool IrManager::checkPowerKey(int* data){
    for(int i=0; i<24; i++){
        if(data[i] != powerKey[i])
            return false;
    }
    return true;
}

IrManager::~IrManager(){
    //wiringPiISRStop(irPin);
}