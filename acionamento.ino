 // Pinos Analogicos
#define pinAPPS1 A4                                  
#define pinAPPS2 A3        
#define pinBrake A5                                    

//Pinos Digitais
#define pinRTD 5                                             // Pino de entrada do sinal RTD
#define pinFBair 13                                          // Pino de entrada do sinal do feedback AIR
#define pinRTDS 12                                           // Pino Sirene
#define pinShtd 11                                           // Pino comando Relé de shutdown                                * 
#define pinSeatswitch 4                                      // Pino de saida do Seatswitch 
#define pinFootswitch 2                                      // Pino de saida do Footswitch
#define pinLedRTD 7                                           // Pino da led RTD
#define pinRAPPS 6                                            //pino Relé APPS Inversor
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
//int shtdout = 0;                                                  // Variável de indicação de Shutdown externo
int diferenca = 0;                                                // Variavel que ve a diferenca de Acel1 e Acel2
int brake = 0;                                                    // Variavel freio



// Variáveis de limite
const int delayRTDS 3000
//const int totalBreak ???

//const int limitefreioSeat = 125; // valor do freio que precisa esta ativo 100~220 (medição Tav).


// Variáveis de estado
boolean feedbackAIR = 0;            // estado do FeedBack AIR
boolean estadoRTD = 0;              // estado do RTD
boolean shtdE = 0;                  // estado do sht Externo
boolean shtd = 0;                   // Variável de controle do shutdown

// Variáveis de tempo
unsigned long tempo{0};

// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void ImplausabilidadeAPPS(int input1,int input2){
  int count;
  float diff = (input1 - input2);
  if (abs(diff/input1) < 0.1){
  count = 0;
  }
  else{
  count++;  
  	if (count > 2 ){
  	digitalWrite(pinRAPPS, LOW);	}
  } 
}  


void setup() 
{
  //pinMode (pinRTD         ,INPUT);
  //pinMode (pinFBair       ,INPUT);
  pinMode (pinRAPPS        ,OUTPUT);
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
 digitalWrite(pinRAPPS, HIGH);   
 APPS1 = analogRead(pinAPPS2);
 APPS2 = analogRead(pinAPPS1); 
 ImplausabilidadeAPPS(APPS1,APPS2);
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
