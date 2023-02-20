// Defining the connecting ports
int portIN1 = 8;
int portIN2 = 9;
int portIN3 = 10;
int portIN4 = 11;

// defining the temporary variables
const unsigned int MAX_MESSAGE_LENGTH = 50; // arbitrary length


// Parsing variables to capture the parameters
int8_t indexA, indexB, indexC, indexD;
String motDir, motRun, motAngle, motSpeed;

// Converted final variables, used to run the motor
int motRunInt;
float motSpeedFloat, motAngleFloat;
String motDirString;
float stepsRev;
float pause;

void setup() {
  Serial.begin(9600);

  pinMode(portIN1, OUTPUT);
  pinMode(portIN2, OUTPUT);
  pinMode(portIN3, OUTPUT);
  pinMode(portIN4, OUTPUT);

}

void loop() {

  // Check to see if anything is available in the serial receive buffer

  while (Serial.available() > 0)
  {
    // Create a place to hold the incoming message
    static char motData[MAX_MESSAGE_LENGTH]; //created a character array named message, an array is a data type that could hold multiple elements; each of the characters that we received from the serial receive buffer is gonna be going into this character array
    static unsigned int index_pos = 0; //this variable will allow us to choose where in the array to put the incoming bites 

    // Read the next available byte in the serial receiver buffer
    char charData = Serial.read();

    if (charData != '\n')
    {
      motData[index_pos] = charData;
      index_pos++ ;  
    }
    else
    {
      motData[index_pos] = '\0';

      index_pos = 0;

      Parse_the_Data(motData);
      
      Serial.println(motRunInt);
      Serial.println(motSpeedFloat);
      Serial.println(motAngleFloat);
      Serial.println(motDir);
      Serial.println('\n');

      // Operating parameter conversion 
      stepsRev = motAngleFloat/0.18/4.0; // converting angle to number of steps
      pause = (60000)/(motSpeedFloat*2049); // converting motSpeed to time delay between the steps
      
      if (motDirString == "Clockwise") {stepper_Clockwise(); digitalWrite(portIN1, LOW);}
      else if (motDirString == "Anticlockwise") {stepper_Anticlockwise(); digitalWrite(portIN4, LOW);}
      else {Serial.println("Invalid Input. Try Again!");}
    }
  }
}

long Parse_the_Data(String dataIn){
  
      Serial.println(dataIn);
      indexA = dataIn.indexOf("A");
      indexB = dataIn.indexOf("B");
      indexC = dataIn.indexOf("C");
      indexD = dataIn.indexOf("D");

      motRun = dataIn.substring(0, indexA);
      motRunInt = motRun.toInt();
      motSpeed = dataIn.substring(indexA+1, indexB);
      motSpeedFloat = motSpeed.toFloat();
      motAngle = dataIn.substring(indexB+1, indexC);
      motAngleFloat = motAngle.toFloat();
      motDir = dataIn.substring(indexC+1, indexD);
      motDirString = String(motDir);
}

void stepper_Anticlockwise() {

  for (int i = 0; i < stepsRev; i++) {
    digitalWrite(portIN1, HIGH);
    digitalWrite(portIN2, LOW);
    digitalWrite(portIN3, LOW);
    digitalWrite(portIN4, LOW);
    delay(pause);
    digitalWrite(portIN1, LOW);
    digitalWrite(portIN2, HIGH);
    digitalWrite(portIN3, LOW);
    digitalWrite(portIN4, LOW);
    delay(pause);
    digitalWrite(portIN1, LOW);
    digitalWrite(portIN2, LOW);
    digitalWrite(portIN3, HIGH);
    digitalWrite(portIN4, LOW);
    delay(pause);
    digitalWrite(portIN1, LOW);
    digitalWrite(portIN2, LOW);
    digitalWrite(portIN3, LOW);
    digitalWrite(portIN4, HIGH);
    delay(pause);
}
}

void stepper_Clockwise() {
  for (int i = 0; i < stepsRev; i++) {
    digitalWrite(portIN1, LOW);
    digitalWrite(portIN2, LOW);
    digitalWrite(portIN3, LOW);
    digitalWrite(portIN4, HIGH);
    delay(pause);  
    digitalWrite(portIN1, LOW);
    digitalWrite(portIN2, LOW);
    digitalWrite(portIN3, HIGH);
    digitalWrite(portIN4, LOW);
    delay(pause);
    digitalWrite(portIN1, LOW);
    digitalWrite(portIN2, HIGH);
    digitalWrite(portIN3, LOW);
    digitalWrite(portIN4, LOW);
    delay(pause);
    digitalWrite(portIN1, HIGH);
    digitalWrite(portIN2, LOW);
    digitalWrite(portIN3, LOW);
    digitalWrite(portIN4, LOW);
    delay(pause);
}
}
