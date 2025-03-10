 // Pinos Analogicos
#define pinAPPS1 A4                                  
#define pinAPPS2 A3        
#define pinBrake A5
#define pinBMS A2
#define pinIMDfreq A1

//Pinos Digitais
#define pinRTD 5                                             // Pino de entrada do sinal RTD
#define pinFBair 13                                          // Pino de entrada do sinal do feedback AIR
#define pinRTDS 12                                           // Pino Sirene
#define pinShtd 11                                           // Pino comando Relé de shutdown                                * 
#define pinRSeatswitch 4                                      // Pino de saida do Seatswitch 
#define pinRFootswitch 2                   // Pino de saida do Footswitch
#define pinLedRTD 7                                           // Pino da led RTD
#define pinRAPPS 6  
#define pinBMSFault 9
#define pinIMDFault 10 

//pino Relé APPS Inversor
//#define pinLedShtd 8                                         // Pino led Shutdown

/* Código arduino Faraday Racing - 2025
 * 
 * 
 *  
 * 
 * 
 */


// Variáveis de input e output 
int APPS1   = 0;                                                  // Variável Acelerador1 (0~100%)
int APPS2   = 0;                                                  // Variável Acelerador2 (0~100%)                                             
int Freq = 0;
int SOC = 0;
int brake = 0;                                                    // Variavel freio



// Variáveis de limite
const int delayRTDS 3000
//const int totalBreak ???

//const int limitefreioSeat = 125; // valor do freio que precisa esta ativo 100~220 (medição Tav).


// Variáveis de estado
boolean feedbackAIR = 0;            // estado do FeedBack AIR
boolean estadoRTD = 0;              // estado do RTD
boolean shtd = 0;                   // Variável de controle do shutdown

// Variáveis de tempo
unsigned long tempo{0};

// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


void ImplausabilidadeAPPS(int input1,int input2){
  int count;
  float diff = (input1 + input2);
  if (abs(diff/input1) < 0.1){
  count = 0;
  }
  else{
  count++;  
  	if (count > 2 ){
  	digitalWrite(pinRAPPS, LOW);
   digitalWrite(RSeatswitch, LOW);
   estadoRTD = False;
   }
  } 
}  

void ImplausabilidadeBSE(int input1){
int count;
if (input1 > 0 || input1 < 5){
count = 0;
}
else {
count++; 
if (count > 2 ){
 	digitalWrite(pinRAPPS, LOW);
  digitalWrite(RSeatswitch, LOW);
  estadoRTD = False;
   }
 }
}  

void Shutdown(){
feedbackAIR = false; 
digitalWrite(pinFootswitch, LOW);   
digitalWrite(pinSeatswitch, LOW);  
digitalWrite(pinRAPPS, LOW);
shtd = True;
estadoRTD = False;
}

}








void setup() 
{
  //pinMode (pinRTD         ,INPUT);
  //pinMode (pinFBair       ,INPUT);
  pinMode (pinRAPPS        ,OUTPUT);
  pinMode (pinRTDS         ,OUTPUT);
  pinMode (pinShtd           ,OUTPUT);
  pinMode (pinRSeatswitch     ,OUTPUT);
  pinMode (pinRFootswitch     ,OUTPUT);
  pinMode (pinLedRTD         ,OUTPUT);
  pinMode (pinLedShtd        ,OUTPUT);

  Serial.begin(9600);                               //inicia o envio de dados pela porta serial a 9600 bits/s

  

}

void loop()
{
if(estadoRTD){
 digitalWrite(pinRAPPS, HIGH);   

 APPS1 = analogRead(pinAPPS2);
 APPS2 = analogRead(pinAPPS1); 
 ImplausabilidadeAPPS(APPS1,APPS2);
 
 brake = analogRead(brake);
 ImplausabilidadeBSE(brake);

 SOC = analogRead(pinBMS);

 if(digitalRead(pinBMSfault)){
   Shutdown();
 }

 if(digitalRead(pinIMDfault)){
   Freq = analogRead(pinIMDfreq)
   Shutdown();
 }
 
 
 delay(100);
 
}  
else{
    feedbackAIR = digitalRead(pinFBair);              // Lê estado do feedback AIR
    if(feedbackAIR == True)                           // Se feedbackAIR estiver ligado vai entrar no if
    {
      brake = analogRead(pinFreio);                  // Lê se o freio esta acionado ou não
      digitalWrite(pinSeatswitch, HIGH);              // fecha a seatswitch
      if(brake >= totalBrake && digitalRead(pinRTD) ){
        digitalWrite(pinFootswitch, HIGH);            // fecha o footswitch
        digitalWrite(pinRTDS, HIGH);                  // Liga a Sirene
        digitalWrite(pinLedRTD, HIGH);                // Acende o LED do RTD
        delay(delaySirene);
        digitalWrite(pinSirene, LOW);                 // Desliga Sirene   
        estadoRTD = True;
      };               
    }}      
}
