#include <LiquidCrystal.h>
// Define the LCD pin connections: RS, Enable, Data4, Data5, Data6, Data7
const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);  // Create an LCD object

const int DRY_THRESHOLD = 950;// Thresholds for easier calibration
const int WET_THRESHOLD = 450;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.clear();

  pinMode(2, OUTPUT);// Initializing Pump Relay Pin
  digitalWrite(2, HIGH);// Ensure pump starts OFF

  delay(1000);
  lcd.setCursor(0, 0);
  lcd.print("IRRIGATION");
  lcd.setCursor(0, 1);
  lcd.print("SYSTEM IS ON ");
    lcd.print("");
    delay(3000);
  lcd.clear();
}
 
void loop() {
  int value = analogRead(A0);// reading sensor
  Serial.println(value);

  int status = getMoistureStatus(value);// using new status function to categorize the soil moisture

  if (status == 0) {// controlling the pump based on moisture status
    togglePump(true);
  } else {
    togglePump(false);
  }
  displayMoistureLevel(status);// displaying the moisture level on the bottom row of the LCD display

  delay(1000);// 1 second delay for next reading
}
int getMoistureStatus(int val){ // Custom function #1 - categorizes the moisture levels
  if(val > DRY_THRESHOLD) return 0;
  if(val > WET_THRESHOLD) return 1;
  return 2;
}
void togglePump(bool activate){ // Custom function #2 - Handles the pump relay state and LCD row 0 status
  lcd.setCursor(0, 0);
  if (activate) {
    digitalWrite(2, LOW);
    lcd.print("Pump: ON     ");
  } else {
    digitalWrite(2, HIGH);
    lcd.print("Pump: OFF      ");
  }
}
void displayMoistureLevel(int status) { // Custom function #3 - Updates the LCD row 1 with the text description of moisture
  lcd.setCursor(0, 1);
  if (status == 0){
    lcd.print("Moisture: LOW ");
  } else if (status == 1) {
    lcd.print("Moisture: MID ");
  } else {
    lcd.print("Moisture: HIGH");
  }
  }

