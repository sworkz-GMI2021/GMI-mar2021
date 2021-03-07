//IoT Based Smart Agriculture with Remote Monitoring System
//v1-mac2021
void setup() {
  // initialize serial communication at 9600 bits per second:    
  Serial.begin(9600);
}

void loop() {
  String moist; //set moist as string
  int sensorValue = analogRead(A1); //read incoming value from analog pin 1 & put at variable named sensorValue
  moist = String(sensorValue); //convert sensorValue from int to string -> only to displya at nodeRED dashboard
  
  Serial.print("Moisture Level: "); //remark this line when displaying the value at nodeRED dashboard
  Serial.print(moist);  //will print at Serial Monitor & nodeRED: debug node & serial in node
  Serial.println(",");  //delimiter -> for nodeRED -> to differentiate new data
  delay(1000);          //pause for 1 sec
}
