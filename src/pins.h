#pragma once

const int digitalPins[] = {4, 5, 16, 17, 18, 19, 21, 22, 23};

const int adcPins[] = {32, 33, 34, 35, 36, 39}; //using adc1 since wifi can cause conflicts with adc2, 
const int inputOnlyPins[] = {34, 35, 36, 39};

const int touchPins[] = {4, 0, 2, 15, 13, 12, 14, 27, 33, 32};
                       //T0 T1 T2 T3  T4  T5  T6  T7  T8  T9 
const int dacPins[] = {25, 26};

const int spiPins[] = {18, 19, 23, 5};
const int i2cPins[] = {21, 22};


const int unsafePins[] = {6, 7, 8, 10, 11}; //pretty much off limits
const int cautionPins[] = {0, 2, 4, 5, 12, 15}; //strapping pins, dont pull them weird on boot and ur good

enum class PinType {
    DIGITAL,
    ADC,
    TOUCH,
    DAC,
    SPI,
    I2C
};

inline bool isValidPin(int pin, PinType type) {
    
    if(pin < 0 || pin > 39) return false;
    for (int unsafePin : unsafePins) if (unsafePin == pin) return false;

    switch (type) {
        case PinType::DIGITAL:
            for (int p : digitalPins) {
                if (p == pin) return true;
            }
            break;
        case PinType::ADC:
            for (int p : adcPins) {
                if (p == pin) return true;
            }
            break;
        case PinType::TOUCH:
            for (int p : touchPins) {
                if (p == pin) return true;
            }
            break;
        case PinType::DAC:
            for (int p : dacPins) {
                if (p == pin) return true;
            }
            break;
        case PinType::SPI:
            for (int p : spiPins) {
                if (p == pin) return true;
            }
            break;
        case PinType::I2C:
            for (int p : i2cPins) {
                if (p == pin) return true;
            }
            break;
    }
    return false;
}