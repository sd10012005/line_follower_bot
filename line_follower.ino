#include<ezButton.h>
#define ir1 A4
#define ir2 A3
#define ir3 A2
#define ir4 A1
#define ir5 A0
#define ir6 A5
#define ML1 3
#define ML2 5
#define MR1 6
#define MR2 9
#define EN1 4
#define EN2 8

ezButton toggleSwitch(10);

void setup() {
  // put your setup code here, to run once:
 pinMode(ML1 , OUTPUT);
 pinMode(ML2 , OUTPUT);
 pinMode(MR1 , OUTPUT);
 pinMode(MR2 , OUTPUT);
 pinMode(EN1 , OUTPUT);
 pinMode(EN2 , OUTPUT);
 pinMode(ir1 , INPUT);
 pinMode(ir2 , INPUT);
 pinMode(ir3 , INPUT);
 pinMode(ir4 , INPUT);
 pinMode(ir5 , INPUT);
 pinMode(12,OUTPUT);
 //toggleSwitch.setDebounceTime(50);
 Serial.begin(9600);

 analogWrite(EN1, 100);
 analogWrite(EN2,100);
}


int size_arr = 0;
char arr[100]={};
int P, D, I, previousError, PIDvalue, error;
int lsp, rsp;
int lfspeed = 75;
int rfspeed =75;
 
float Kp = 32;
float Kd = 18;
float Ki = 0.00 ;

int id1, id2, id3, id4, id5 , id6 ;
void forward();
void sharpleft();
void sharpright();
void u_turn();
void turnoff();
void travelShortest(char arr[],int size_arr);
void slightleft(){
      analogWrite(ML1,0);
      analogWrite(ML2,0);
      analogWrite(MR1,50);
      analogWrite(MR2,0);
}
void noturn(){
do{
  analogWrite(ML1,75);
  analogWrite(ML2,0);
  analogWrite(MR1,75);
  analogWrite(MR2,0);
} 
  while(!((digitalRead(ir1)==1 && digitalRead(ir3)== 0 && digitalRead(ir4)==0 && digitalRead(ir6)==1  ) || (digitalRead(ir1)==1 && digitalRead(ir3)== 0  && digitalRead(ir6)==1  )||
  (digitalRead(ir1)==1 && digitalRead(ir4)== 0  && digitalRead(ir5)==1  )));
}

void slightright(){
      analogWrite(ML1,60);
      analogWrite(ML2,0);
      analogWrite(MR1,0);
      analogWrite(MR2,0);
}
void straight(){
   do{   analogWrite(ML1,75);
      analogWrite(ML2,0);
      analogWrite(MR1,75);
      analogWrite(MR2,0);
   }while(!(digitalRead(ir6)==1)); 
}

void forward(){
  P = error;
  I = I + error;
  D = error - previousError;

  PIDvalue = ((Kp * P) + (Ki * I) + (Kd * D));
  previousError = error;

  lsp = lfspeed + PIDvalue;
  rsp = lfspeed - PIDvalue;

  if (lsp > 75) {
    lsp = 75;
  }
  if (lsp < 0) {
    lsp = 0;
  }
  if (rsp > 75) {
    rsp = 75;
  }
  if (rsp < 0) {
    rsp = 0;
  }
  analogWrite(ML1,lsp);
  analogWrite(ML2,0);
  analogWrite(MR1,rsp);
  analogWrite(MR2,0);
}
void u_turn(){
  do{
      analogWrite(ML1,0);
      analogWrite(ML2,60);
      analogWrite(MR1,60);
      analogWrite(MR2,0);

 }while(!(digitalRead(ir1) == 1 && digitalRead(ir2) == 1 && digitalRead(ir3) == 0 && digitalRead(ir4)==0 && digitalRead(ir5 )== 1  && digitalRead(ir6 )== 1));
}

void sharpleft(){
 do{
      analogWrite(ML1,0);
      analogWrite(ML2,0);
      analogWrite(MR1,150);
      analogWrite(MR2,0);

 }while(!((digitalRead(ir1) == 1 && digitalRead(ir3) == 0 && digitalRead(ir4)==0 && digitalRead(ir2)==1 && digitalRead(ir5 )== 1 )||
 (digitalRead(ir1) == 1 && digitalRead(ir2) == 1 && digitalRead(ir3) == 0 && digitalRead(ir4)==0 && digitalRead(ir5 )== 0 && digitalRead(ir6 )== 0 )) );

  }

void sharpright(){
  do{
      analogWrite(ML1,150);
      analogWrite(ML2,0);
      analogWrite(MR1,0);
      analogWrite(MR2,0);

 }while(!(digitalRead(ir1) == 1 && digitalRead(ir2)==1 && digitalRead(ir4)==0 && digitalRead(ir3) == 0  && digitalRead(ir5 )== 1 ));
  
}

void turnoff(){
      analogWrite(ML1,0);
      analogWrite(ML2,0);
      analogWrite(MR1,0); 
      analogWrite(MR2,0); 
}

void loop() {
  id1=digitalRead(ir1);
  id2=digitalRead(ir2);
  id3=digitalRead(ir3);
  id4=digitalRead(ir4);
  id5=digitalRead(ir5);
  id6=digitalRead(ir6);
 if((id1 == 1 && id2 == 1 && id3 == 0 && id4 == 0 && id5 == 1 && id6 == 1) ){
              
              error = 0;
              forward();
 }
 else if(id1 == 1 && id2 == 1 && id3 == 1 && id4 == 0 && id5 == 1 && id6 == 1 ){
                
                error = 1;
                forward();
 }
 else if(id1 == 1 && id2 == 1 && id3 == 1 && id4 == 0 && id5 == 0 && id6 == 1){
               
                error = 2;
                 forward();
 }
 else if(id1 == 1 && id2 == 0 && id3 == 0 && id4 == 1 && id5 == 0 && id6 == 1){
                
                error = 3;
                forward();
 }
 else if(id1 == 1 && id2 == 1 && id3 == 0 && id4 == 1 && id5 == 1 && id6 == 1){
               
                error = -1;
                 forward();
 }
 else if(id1 == 1 && id2 == 0 && id3 == 0 && id4 == 1 && id5 == 1 && id6 == 1){
               
                error = -2;
                 forward();
 }
 else if(id1 == 1 && id2 == 0 && id3 == 1 && id4 == 1 && id5 == 1 && id6 == 1){
               
                error = -3;
                 forward();
 }
 
  else if ((id1==0 && id3 == 1 && id4 == 1) || (id1 == 0 && id6 == 1)){
           sharpleft();
           arr[(size_arr++)]='L';
           if( digitalRead(ir5) == 0 && 
              digitalRead(ir6) ==0){
           while(1){
            toggleSwitch.loop(); 
 if (toggleSwitch.isPressed()){
 Serial.println("The switch: OFF -> ON");}
 if (toggleSwitch.isReleased()){
 Serial.println("The switch: ON -> OFF");}
 int state = toggleSwitch.getState();
 if (state == HIGH){
 Serial.println("The switch: OFF");
 turnoff();
 digitalWrite(12,HIGH);
 
 }
 else{
 Serial.println("The switch: ON");
 arr[size_arr++]='T'; 
 shortpath(arr,size_arr);
 travelShortest(arr, size_arr);}
}
 }
  
            }
           
  
  else if (id1==1 && id3==0  && id6==0){
                            straight();
                            
                            if(digitalRead(ir3)==0 || digitalRead(ir4)==0){
                               arr[(size_arr++)]='S';
                            }
                            else{
                              
                              sharpright();
                              arr[(size_arr++)]='R';
                            }
                            }
 
  else if(id1==1 && id2==1 && id3==1 && id4==1 && id5==1 && id6 == 1){
                         delay(60);
                         u_turn();
                         arr[(size_arr++)]='B';
}


  else if (id1==0  && id3==0 && id4==0 && id6==0){
              sharpleft();
              arr[(size_arr++)]='L';
            if( digitalRead(ir5)== 0 && digitalRead(ir6)==0){
            while(1){
                  toggleSwitch.loop(); // MUST call the loop() function first

               if (toggleSwitch.isPressed()){
                    Serial.println("The switch: OFF -> ON");}

             if (toggleSwitch.isReleased()){
                      Serial.println("The switch: ON -> OFF");}

           int state = toggleSwitch.getState();
         if (state == HIGH){
    
          turnoff();
          digitalWrite(12,HIGH);
   
           }
     else{
    Serial.println("The switch: ON");
        arr[size_arr++]='T';
       shortpath(arr,size_arr);
       
      travelShortest(arr, size_arr);}

            
                       }
  }
}}



void shortpath(char arr[],int size_arr) {
    for (int i = 0; i < size_arr; i++) {
        if (arr[i] == 'B') {
            if ((arr[i - 1] == 'L' && arr[i + 1] == 'R') || (arr[i - 1] == 'R' && arr[i + 1] == 'L') || (arr[i - 1] == 'S' && arr[i + 1] == 'S')) {
                arr[i - 1] = 'B';
                for (int j = i; j < size_arr - 2; j++) {
                    arr[j] = arr[j + 2];
                }
                size_arr -= 2;
                i -= 2; 
            } else if (arr[i - 1] == 'L' && arr[i + 1] == 'S' || arr[i - 1] == 'S' && arr[i + 1] == 'L') {
                arr[i - 1] = 'R';
                for (int j = i; j < size_arr - 2; j++) {
                    arr[j] = arr[j + 2];
                }
                size_arr -= 2;
                i -= 2; 
            } else if (arr[i - 1] == 'L' && arr[i + 1] == 'L') {
                arr[i - 1] = 'S';
                for (int j = i; j < size_arr - 2; j++) {
                    arr[j] = arr[j + 2];
                }
                size_arr -= 2;
                i -= 2; 
            }
        }
    }
    
}

void travelShortest(char arr[],int size_arr){
   int i = 0;
  
  while(1){
   if(digitalRead(ir1)==0 || digitalRead(ir6)==0){
      if(i<size_arr){
        if(arr[i]=='L'){
          sharpleft();
          i++;
        }
        else if(arr[i]=='R'){
          sharpright();
          i++;
        }
        else if(arr[i]=='S'){
          noturn();
          i++;
        }
        else if(arr[i]=='T'){
          while(1){
          turnoff();
          digitalWrite(12,HIGH);
          i++;
        }
    }
   }}
   else if(digitalRead(ir1)==1 && digitalRead(ir6)==1)
   { if((digitalRead(ir1)==1 && digitalRead(ir2)==1 && digitalRead(ir3)==0 && digitalRead(ir4)== 0 && digitalRead(ir5)== 1 && digitalRead(ir6)==1) ){
              
              error = 0;
              forward();
 }
       else if(digitalRead(ir1)==1 && digitalRead(ir2)==1 && digitalRead(ir3)==1 && digitalRead(ir4)== 0 && digitalRead(ir5)== 1 && digitalRead(ir6)==1){
                
                error = 1;
                forward();
 }
       else if(digitalRead(ir1)==1 && digitalRead(ir2)==1 && digitalRead(ir3)==1 && digitalRead(ir4)== 0 && digitalRead(ir5)== 0 && digitalRead(ir6)==1){
               
                error = 2;
                 forward();
 }
      else if(digitalRead(ir1)==1 && digitalRead(ir2)==1 && digitalRead(ir3)== 1 && digitalRead(ir4)== 1 && digitalRead(ir5)== 0 && digitalRead(ir6)==1){
                
                error = 3;
                forward();
 }
      else if(digitalRead(ir1)==1 && digitalRead(ir2)==1 && digitalRead(ir3)== 0 && digitalRead(ir4)== 1 && digitalRead(ir5)== 1 && digitalRead(ir6)==1){
                
                error = -1;
                forward();
}
      else if(digitalRead(ir1)==1 && digitalRead(ir2)== 0 && digitalRead(ir3)== 0 && digitalRead(ir4)== 1 && digitalRead(ir5)== 0 && digitalRead(ir6)==1){
                
                error = -2;
                forward();   
      }       
       else if(digitalRead(ir1) == 1 && digitalRead(ir2) == 0 && digitalRead(ir3) == 0 && digitalRead(ir4) == 0 && digitalRead(ir5) == 1){
               
                error = 31;
                 forward();
 }
   
}
  
}}
