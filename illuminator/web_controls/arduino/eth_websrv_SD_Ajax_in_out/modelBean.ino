bool jumperVal[8];  
byte jumperValInBytes=0;
String model="Test";

byte at6es =B11111111;
byte at12es=B11111110;
byte at9ez =B11111101;  //31,33,35,37,39,41,43,45
boolean isDegree10;
boolean isDegree30;
boolean isDegree45;
boolean isDegree60;
boolean isDegree130;

void readJumperVal(){
   for(int i=0;i<sizeof(pinInArrary)/sizeof(int);i++){
     jumperVal[i]=digitalRead(pinInArrary[i]);
   }
   //convert to byte val
   for (int i=0;i<8;i++){
     jumperValInBytes=jumperValInBytes << 1;
     if(jumperVal[i]){
       jumperValInBytes |=1;
     }
   }
}

void getModel(){
  readJumperVal();
  Serial.print("jumper val in bytes ");
  Serial.println(jumperValInBytes);
  if (jumperValInBytes==at6es){
    model="AT-6ES";
    isDegree10 =true;
    isDegree30 =true;
    isDegree45 =true;
    isDegree60 =true;
    isDegree130=true;
  }else if (jumperValInBytes==at12es){
    model="AT-12ES";
    isDegree10 =true;
    isDegree30 =true;
    isDegree45 =true;
    isDegree60 =true;
    isDegree130=true;
  }else if (jumperValInBytes==at9ez){
    model="AT-9EZ";
    isDegree10 =true;
    isDegree30 =true;
    isDegree45 =false;
    isDegree60 =true;
    isDegree130=true;
  }
}


