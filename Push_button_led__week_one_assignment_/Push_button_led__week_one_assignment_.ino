int pushButton = 8;
int led = 4;
int powerState = 0;
int pushButtonState;
int pushButtonStateOld;
void setup()
{
 Serial.begin(9600);
 pinMode(pushButton,INPUT);
 pinMode(led,OUTPUT); 
}
void loop()
{
 pushButtonStateOld = pushButtonState;
 pushButtonState = digitalRead(pushButton);
 delay(5);
 switch(powerState){
   case 0:digitalWrite(led, LOW);
         if((pushButtonStateOld == 0)&&(pushButtonState == 1))
         {
           powerState = 1;
         }
         break;
   case 1:digitalWrite(led,HIGH);
          if((pushButtonStateOld == 0)&&(pushButtonState == 1)&&(powerState == 1))
         {
           powerState = 0;
         }
         break;
   default:Serial.println("ERROR:Undefined state for the LED");
         break;
 }
}

