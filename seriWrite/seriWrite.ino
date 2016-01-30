/*このプログラムはあさちゃんとせりが昨日の落下ドリルの制御の仕方をしっているのでそれ以外の方は手を加えることを許しません。助言はありですが、勝手な仕様変更は認めません。
 * 折角制御できたのにできなくなってしまう可能性があるからです。Unityと連動させるにはあさちゃんなら上手く組み込めるでしょう。
 * 面倒なのでまたしてもUnity側で時間は制御するようにしてください。Delayを適宜入れることによって安定するんじゃないかな？とりあえず、組み込み易いようにあえていれなかったけど。
 * １になって２になるまでの時間、落下ドリルが動く
 * ３になって４になるまでの時間、位置調整ドリルが正回転する
 * ５になって６になるまでの時間、位置調整ドリルが逆回転する
 * そんなつもりでプログラム書いたつもりやけど、疲れ＆眠気で昨日みたいなプログラムになっているかもしれん。
 * 絶対に位置調整ドリルのテストはLED以外でテストしないこと。もうさん、どらますさん監修の元テストすること。ドリルに電源を繋いでテストしてはならない！！
 * 朝バイトだし、力尽きたZE！頼んだあさちゃん。
*/


//const int pin1 = 1, pin2 = 2, pin7 = 7, pin8 = 8;
//const int testPin = 12;
const int SEITEN1 = 8,SEITEN2 = 7,GYAKUTEN1 = 3,GYAKUTEN2 = 5;  //ピンの名称をわかりやすく
char s;  //シリアル通信受信用
unsigned long safeTime = 1500;
unsigned long time_old = -1;
unsigned long time_new = 0;
boolean testFlg = false;

void setup(){
  Serial.begin(115200);
  pinMode(SEITEN1,OUTPUT);
  pinMode(SEITEN2,OUTPUT);
  pinMode(GYAKUTEN1,OUTPUT);
  pinMode(GYAKUTEN2,OUTPUT);
  //pinMode(testPin,OUTPUT);
  digitalWrite(SEITEN1,HIGH);
  digitalWrite(SEITEN2,HIGH);
  digitalWrite(GYAKUTEN1,HIGH);
  digitalWrite(GYAKUTEN2,HIGH);
  //digitalWrite(testPin,LOW);
}

void loop(){
  
  //digitalWrite(testPin,LOW);
  if(Serial.available() > 0){
      s = Serial.read(); 
      //Serial.println(s);
      Serial.flush();
    if(s == '1'){
  
      //fall(); もともとの落下プログラムが入るところ
      /*　１が１度送られてきて次に２が送られてくるまでは落下ドリルのピンが
       * Highになる仕様だったはず
       * 
       * 
       */
    }
    
    else if(s == '2'){
      //digitalWrite(DriverPin,LOW);//落下用ドリル停止
    }
    else if(s == '3'){
      //正回転ドリルモード
      drill_plus();
      /*　３が１度送られてきて次に４が送られてくるまでは位置調整ドリルのピンが
       * Low（動作状態）になる
       * 
       * 
       */
    }
    
    else if(s == '4'){
      reset();
    }
    else if(s == '5'){
      //逆回転ドリルモード
      //testFlg = true;
      drill_minus();
      /*　５が一度送られてきて次に６が送られてくるまでは位置調整ドリルのピンがLow（動作状態）になる
       * 
       * 
       */
    }
    else if(s == '6'){
      //testFlg = false;
      reset();
    }
  }

  time_new = millis();
  if(time_old != -1){
   // digitalWrite(13,HIGH);
   if( (time_new-time_old) > safeTime )
     reset();
  }
  else{
  // digitalWrite(13,LOW); 
  }
  delay(50);
}
void reset(){
  time_old = -1;
  digitalWrite(SEITEN1,HIGH);
  digitalWrite(SEITEN2,HIGH);
  digitalWrite(GYAKUTEN1,HIGH);
  digitalWrite(GYAKUTEN2,HIGH);
  //digitalWrite(testPin,HIGH);
  delay(50);
}

void drill_plus(){
  reset();
  //migi mawari is plus
  digitalWrite(SEITEN1,LOW);
  delay(5);
  digitalWrite(SEITEN2,LOW);
  time_old = millis();
}

void drill_minus(){
 //left mawari is minus
  reset();
  digitalWrite(GYAKUTEN1,LOW);
  delay(5);
  digitalWrite(GYAKUTEN2,LOW);
  time_old = millis();
 

}

