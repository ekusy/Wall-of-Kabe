//閾値の再設定　SHIKII　８か所
//センサの値実測値sensorValuecds,seonsorValuepress
//白と黒踏むの　on と　off　on=1,off=0 siglnal[i]
//閾値の上限以上かそうでないかの方がやりやすいと思う．

const int SEITEN1 = 8,SEITEN2 = 7,GYAKUTEN1 = 3,GYAKUTEN2 = 5;  //ピンの名称をわかりやすく
const int FAN = 2;
//char c;  //シリアル通信受信用
unsigned long safeTime = 4500;
unsigned long time_old = -1;
unsigned long time_new = 0;
boolean testFlg = false;


String s="";
int DriverPin = 10;

//cds
int SHIKIIcds[4] = {
  200,450,450,400};//閾値
int borw[4] = {
  0,0,0,0}; //black left hand->1, right hand->2  left leg->3,  right leg->4
int pborw[4] = {
  
  
  0,0,0,0};
int bwcount[4] = {
  0,0,0,0};

//圧力センサ
int SHIKIIpress[4] = {
 660,520,500,800}; //閾値
int onoff[4] = {
  0,0,0,0}; //black left hand->1, right hand->2  left leg->3,  right leg->4
int ponoff[4] = {
  0,0,0,0};
int ofcount[4] = {
  0,0,0,0};


// These constants won't change.  They're used to give names
// to the pins used:
const int cdssensor[4] = {
  A0,A1,A2,A3};  // Analog input pin that the potentiometer is attached to
const int presssensor[4]={
  A4,A5,A6,A7};
const int analogOutPin = 9; // Analog output pin that the LED is attached to

int sensorValuecds[4] = {
  0,0,0,0};        // value read from the pot
int sensorValuepress[4] = {
  0,0,0,0};        // value read from the pot

int outputValue = 0;        // value output to the PWM (analog out)


void setup() {
  // initialize serial communications at 9600 bps:
  pinMode( DriverPin, OUTPUT);
digitalWrite(DriverPin,LOW);
  Serial.begin(115200);
  pinMode(SEITEN1,OUTPUT);
  pinMode(SEITEN2,OUTPUT);
  pinMode(GYAKUTEN1,OUTPUT);
  pinMode(GYAKUTEN2,OUTPUT);
  pinMode(FAN,OUTPUT);
  
  //pinMode(testPin,OUTPUT);
  digitalWrite(SEITEN1,HIGH);
  digitalWrite(SEITEN2,HIGH);
  digitalWrite(GYAKUTEN1,HIGH);
  digitalWrite(GYAKUTEN2,HIGH);
  digitalWrite(FAN,HIGH);
  
}

void loop() {

  int signal[8]={
    0,0,0,0,0,0,0,0 };

  //LED,cds
  int i=0;
  for(i=0;i<4;i++){
    // read the analog in value:
    sensorValuecds[i] = analogRead(cdssensor[i]);  
     //Serial.println(sensorValuecds[i]); //CDSの値
  }

  
  //Serial.println(sensorValuecds[0]); //CDSの値
  
  
  //閾値は1が１が黒、0が白
  
  for(i=0;i<4;i++){
    pborw[i] = borw[i];
    if(sensorValuecds[i]>SHIKIIcds[i]) {
      //borw[i] = 1; //現在のblack/whiteの0/1値　　　　　　　　　//環境が明るい時は黒に反応するよう　borw=1　暗い時はborw=0
      signal[i] = 1;  
  }
    else if(sensorValuecds[i]<SHIKIIcds[i]){
      //borw[i] = 0;                                             //環境が明るい時は白に反応するよう　borw=1　暗い時はborw=0
      signal[i] = 0;  
  }



//on(1)とoff(0) の方
    if(pborw[i] == 0 && borw[i] == 1) {
      //Serial.print(i);
      // Serial.print("white"); 
      signal[i]=1;
      // Serial.print(signal[i]); 
    }
    else if(pborw[i] == 1 && borw[i] == 0){
      //Serial.print(i);
      //Serial.print("black");
      signal[i]=0;
      //Serial.print(signal[i]); 
    }
     
    
    //map it to the range of the analog out;    //ここ４行あんま関係ない？サンプルのまま
    outputValue = map(sensorValuecds[i], 0, 1023, 0, 255);  
    // change the analog out value:
    analogWrite(analogOutPin, outputValue);           
  }


  // 圧力センサ  
  for(i=0;i<4;i++){
    // read the analog in value:
    sensorValuepress[i] = analogRead(presssensor[i]);     
    // Serial.println(sensorValuepress[i]); //圧力
  }
  for(i=0;i<4;i++){
    ponoff[i] = onoff[i];
    if(sensorValuepress[i]>SHIKIIpress[i]){
      //onoff[i+4] = 1; //現在のblack/whiteの0/1値
      signal[i+4]=1;
    }
    else if(sensorValuepress[i]<SHIKIIpress[i]){
      //onoff[i+4] = 0;
      signal[i+4]=0;
    }

    
    
    
/*
    if(ponoff[i] == 0 && onoff[i] == 1) {
      // Serial.print(i);
      //Serial.println("on"); 
      signal[i+4]=1;
    }
    else if(ponoff[i] == 1 && onoff[i] == 0){
      //Serial.print(i);
      //Serial.println("off");
      signal[i+4]=0;
    }
*/
  }
  s="";
for(int k = 0;k<8;k++){
  if(k!=0)
    s.concat(",");
  s.concat(String(signal[k]));
//Serial.print(signal[k]);
//Serial.print(",");
}

Serial.println(s);

//Serial.println(analogRead(A4));

  delay(50);       

if(Serial.available()>0){
    char  c = Serial.read();
    Serial.flush();
    judge(c);
  }
  time_new = millis();
  if(time_old != -1){
    if( (time_new-time_old) > safeTime )
      reset();
  }
              
}




void judge(char c){
  if(c == '1'){
    digitalWrite(DriverPin,HIGH);
  }
    
  else if(c == '2'){
      digitalWrite(DriverPin,LOW);//落下用ドリル停止
  }
    else if(c == '3'){
      //正回転ドリルモード
      drill_plus();
    }
    else if(c == '4'){
      reset();
    }
    else if(c == '5'){
      //逆回転ドリルモード
      drill_minus();
    }
    else if(c == '6'){
      //testFlg = false;
      reset();
      delay(50);
    }
    else if(c == '7'){
      //逆回転ドリルモード
      digitalWrite(FAN,LOW);
    }
    else if(c == '8'){
      digitalWrite(FAN,HIGH);
    }

}
void reset(){
  time_old = -1;
  digitalWrite(SEITEN1,HIGH);
  digitalWrite(SEITEN2,HIGH);
  digitalWrite(GYAKUTEN1,HIGH);
  digitalWrite(GYAKUTEN2,HIGH);
  //digitalWrite(testPin,HIGH);
  //delay(50);
}
void drill_plus(){
  reset();
  delay(50);
  //migi mawari is plus
  digitalWrite(SEITEN1,LOW);
  delay(5);
  digitalWrite(SEITEN2,LOW);
  time_old = millis();
}

void drill_minus(){
 //left mawari is minus
  reset();
  delay(50);
  digitalWrite(GYAKUTEN1,LOW);
  delay(5);
  digitalWrite(GYAKUTEN2,LOW);
  time_old = millis();
}




