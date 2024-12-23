// Tabla de calibración (valores reales vs valores crudos del ADC)
float voltageReal[] = {0.0, 0.5, 1.0, 1.5, 3.3};
int adcRaw[] = {0, 512, 1024, 1530, 4095};
const int calibrationPoints = 5;

float calibrateADC(int adcValue) {
    for (int i = 0; i < calibrationPoints - 1; i++) {
        if (adcValue >= adcRaw[i] && adcValue <= adcRaw[i + 1]) {
            // Interpolación lineal
            return voltageReal[i] + 
                   (voltageReal[i + 1] - voltageReal[i]) * 
                   (adcValue - adcRaw[i]) / (adcRaw[i + 1] - adcRaw[i]);
        }
    }
    return 0.0; // Fuera de rango
}

void setup() {
    Serial.begin(115200);
    analogReadResolution(12); // Configura resolución del ADC (12 bits por defecto)
}

void loop() {
    int rawADC = analogRead(34); // Leer ADC del pin 34
    float calibratedVoltage = calibrateADC(rawADC);
    Serial.print("ADC Raw: ");
    Serial.print(rawADC);
    Serial.print(" -> Calibrated Voltage: ");
    Serial.println(calibratedVoltage, 3); // Mostrar voltaje calibrado con 3 decimales
    delay(500);
}
