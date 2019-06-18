
int inPin[] = {A0,A1,A2,A3};
int pinval[] = {-1,-1,-1,-1};

int gcheck(){
  int i = 0;
  for(i = 0; i < 4; i++){
    if(pinval[i] == -1){
      int j=0;
      int flag = 0;
      delay(200);
      for(j = 0; j < 20; j++){
        int val=analogRead(inPin[i]);
        if(val > 600){
          flag = 1;
          break;
          delay(10);
        }
      }      
      if(flag == 0){
        pinval[i]=0;
        Serial.print("Gnd : A");
        Serial.println(inPin[i]-14);
        return i;
      }
    }
  }
  return -1;
}
int txrx(int gnd){
  int c1=0,c2=0,turn=0,p1,p2;
   for(int i = 0; i < 8; i++){    
      int j=0;
      for(j = 0; j < 4; j++){
        if(pinval[j]==-1){
        int val=analogRead(inPin[j]);
        if(turn == 0){
          p1=j;
          c1=c1+val;
        }
        else{
          p2=j;
          c2=c2+val;
        }
        turn=(turn+1)%2;
        }
      }
   }
   if(c1 < c2){
    Serial.print("Tx : A");
    Serial.println(inPin[p2]-14);
    Serial.print("Rx : A");
    Serial.println(inPin[p1]-14);
   }
   else{
    Serial.print("Tx : A");
    Serial.println(inPin[p1]-14);
    Serial.print("Rx : A");
    Serial.println(inPin[p2]-14);
   }
}

int vcheck(int gnd){
  
  int i = 0;
  for(i = 0; i < 4; i++){
    if(pinval[i] == -1){
      int j=0,flag=0;
      analogWrite(inPin[i],500);
      for(j = 0; j < 8; j++){
        int val=analogRead(inPin[gnd]);
        if(val > 80){
          flag = 1;
          break;
          delay(3);
        }
      } 
      if(flag == 1){
        pinval[i]=0;
        Serial.print("Vcc : A");
        Serial.println(inPin[i]-14);
     }
      analogWrite(inPin[i],0);
    }
    
  }
  return 0;
}

void setup() {
  Serial.begin(9600);
  delay(500);
  Serial.write("starting\n");
  int gnd=gcheck();
  analogWrite(inPin[0],0);
  analogWrite(inPin[1],0);
  analogWrite(inPin[2],0);
  analogWrite(inPin[2],0);
  int vcc=vcheck(gnd);
  txrx(gnd);
}

void loop() {

}
