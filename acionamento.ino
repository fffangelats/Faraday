#define delayRTDS 3000
#define totalBreak ??? 

/* Código arduino Faraday Racing - 2018
 * 
 * 
 *  
 * 
 * 
 */

// PINOS
// Analogico
const int pinAPPS1 = A4;                                  
const int pinAPPS2  = A3;        
const int pinBrake  = A5;                                       //testar assim que tiver montada

// Digital
const int pinRTD = 5;                                             // Pino de entrada do sinal RTD
const int pinFBair = 13;                                          // Pino de entrada do sinal do feedback AIR
const int pinRTDS = 12;                                           // Pino Sirene
const int pinShtd = 11;                                           // Pino comando Relé de shutdown                                * 
const int pinSeatswitch = 4;                                      // Pino de saida do Seatswitch 
const int pinFootswitch = 2;                                      // Pino de saida do Footswitch
const int pinLedRTD = 7;                                           // Pino da led RTD
//const int pinLedShtd = 8;                                         // Pino led Shutdown
                                                                  // Pino do sinal PWM do motor
                                                                  //Pino de Entrada que recebe o sinall de erro do IMD.


// Variáveis de input e output 
int APPS1   = 0;                                                  // Variável Acelerador1 (0~100%)
int APPS2   = 0;                                                  // Variável Acelerador2 (0~100%)                                                // variavel PWM pro motor
//int shtdout = 0;                                                  // Variável de indicação de Shutdown externo
int diferenca = 0;                                                // Variavel que ve a diferenca de Acel1 e Acel2
int brake = 0;                                                    // Variavel freio



// Variáveis de limite

//const int limitefreioSeat = 125; // valor do freio que precisa esta ativo 100~220 (medição Tav).


// Variáveis de estado
boolean feedbackAIR = 0;            // estado do FeedBack AIR
boolean estadoRTD = 0;              // estado do RTD
boolean shtdE = 0;                  // estado do sht Externo
boolean shtd = 0;                   // Variável de controle do shutdown

// Variáveis de tempo
unsigned long tempo{0};

// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void setup() 
{
  //pinMode (pinRTD         ,INPUT);
  //pinMode (pinFBair       ,INPUT);
  pinMode (pinRTDS         ,OUTPUT);
  pinMode (pinShtd           ,OUTPUT);
  pinMode (pinSeatswitch     ,OUTPUT);
  pinMode (pinFootswitch     ,OUTPUT);
  pinMode (pinLedRTD         ,OUTPUT);
  pinMode (pinLedShtd        ,OUTPUT);

  Serial.begin(9600);                               //inicia o envio de dados pela porta serial a 9600 bits/s

  

}

void loop()
{
if(estadoRTD){
      
  
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
