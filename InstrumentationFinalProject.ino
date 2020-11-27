//Jacob Pina
//ME 360L Motion Sensor Light Switch
//This switch measures a distance using the HC-SR04 ultrasonoc sensor so when an object like your hand passes
   //in front it will turn the led on and stay on until you pass in front of it again in which case the led
   //will turn off and stay off.

int trig=9;     //Port for trig sensor
int echo=10;    //Port for echo sensor
int led=13;     //Port for positive led leg
int crit=15;    //Critical distance (cm)
int state=1;    

void setup() {
  Serial.begin(9600);     
  pinMode(led,OUTPUT);
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  
}

void loop() {
  long duration, distance;        
  digitalWrite (trig,HIGH);       //send out trigger pulse
  delayMicroseconds (1000);       
  digitalWrite (trig,LOW);        
  duration=pulseIn(echo,HIGH);    //Duration is the time it takes for the echo to read the trigger
  distance=(duration/2)/29.1;     //Convert duration time to distance (cm)
  Serial.print(distance);         //Display distance on small screen
  Serial.println("cm");

  delay(100);                     //Delay helps the sensor make better readings, when there is little to no delay it often makes inaccurace readings
  if ((distance <=crit))
  {
  while (distance <=crit)
  {
    digitalWrite (trig,HIGH);     //Check distance, nothing will happen until they move away
    delayMicroseconds (1000);
    digitalWrite (trig,LOW);
    duration=pulseIn(echo,HIGH);
    distance=(duration/2)/29.1;
    delay(5);
  }

    if (state%2==0)
    {
      Serial.println("Turn Off");      //Turn led off
      digitalWrite(led,LOW);
      delay(1000);
    }
    else if (state % 2 == 1)
    {
      Serial.println("Turn On");     //Turn led on
      digitalWrite(led,HIGH);
      delay(1000);
    }
    state = state+1;      //Change the state for the next pass
    
  }
}
