 #include <Servo.h>

int right = 84;;
int mid = 20;

Servo servo_1;

void setup()
{
  pinMode(35,INPUT);
  servo_1.attach(4, 500, 2500);
  servo_1.write(20);
}

void loop()
{
  
    if ((digitalRead(A0) == HIGH)) {
      while(1){
      // Code for Thread 2
      //delay(3000);    //delay 3.0 seconds
      servo_1.write(85);    //servo to deploy
      delay(1000);
      servo_1.write(20);  // Reset the servo to its initial position (adjust as needed)
      delay(1000);
    }
    }
   
}
