//<App !Start!>
// FILE: [Baja.ino]
// Created by GUIslice Builder version: [0.17.b41]
//
// GUIslice Builder Generated File
//
// For the latest guides, updates and support view:
// https://github.com/ImpulseAdventure/GUIslice
//
//<App !End!>

/*
 * PROJETO: Painel Digital Veicular (Baja SAE)
 * AUTOR: Wellington Marciano
 * EQUIPE: Baja dos Reis (Cefet/RJ Angra dos Reis)
 * * Este código é de domínio público sob a licença MIT.
 * Se você utilizar este código em seu projeto, por favor, dê os créditos
 * mantendo este cabeçalho ou citando o repositório original.
 * * Repositório: https://github.com/MarcianTr/Simulacao_Codigo_TFT_BajaDosReis
 */

// ------------------------------------------------
// Headers to include
// ------------------------------------------------
#include "Baja_GSLC.h"
#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// ------------------------------------------------
// Program Globals
// ------------------------------------------------
#define ONE_WIRE_BUS 32  
#define sensorVelocidade 33   
#define SENSOR1_PIN 34  
#define SENSOR2_PIN 35  

unsigned long startMillis; 
const unsigned long delayTime = 1500; 
bool pageChanged = false; 

volatile bool sensor1Triggered = false; 
volatile bool sensor2Triggered = false; 

unsigned long lastBlinkTime = 0;
bool box9State = false;

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

int rpm_V = 0;
float velocidade = 0;
unsigned long TempoInicial_V = 0;

const int N = 15; 
float amostras_rpm[N];
float amostras_velocidade[N];
float amostras_rps[N];
int indice = 0;

unsigned int NumeroDeImas = 10;  
float RaioDaRoda = 0.265;         
float pi = 3.141592;            
unsigned long intervaloCalculo = 300;  
unsigned long tempoUltimoCalculo = 0;

volatile unsigned long lastPulseTime = 0; 
volatile unsigned long pulseInterval = 0; 
volatile int pulsos_V = 0; 

#define MAX_RPM 10.0 

// ------------------------------------------------
// Element References
// ------------------------------------------------
//<Save_References !Start!>
gslc_tsElemRef* m_pElemBox7       = NULL;
gslc_tsElemRef* m_pElemBox8       = NULL;
gslc_tsElemRef* m_pElemBox9       = NULL;
gslc_tsElemRef* m_pElemProgress1  = NULL;
gslc_tsElemRef* m_pElemRamp2      = NULL;
gslc_tsElemRef* m_pElemVal1_2     = NULL;
gslc_tsElemRef* m_pElemVal3       = NULL;
gslc_tsElemRef* m_pElemVal4       = NULL;
gslc_tsElemRef* m_pElemKeyPadNum  = NULL;
//<Save_References !End!>

// Define debug message function
static int16_t DebugOut(char ch) { if (ch == (char)'\n') Serial.println(""); else Serial.write(ch); return 0; }

// ------------------------------------------------
// Callback Methods
// ------------------------------------------------
bool CbBtnCommon(void* pvGui,void *pvElemRef,gslc_teTouch eTouch,int16_t nX,int16_t nY)
{
  gslc_tsGui* pGui     = (gslc_tsGui*)(pvGui);
  gslc_tsElemRef* pElemRef = (gslc_tsElemRef*)(pvElemRef);
  gslc_tsElem* pElem    = gslc_GetElemFromRef(pGui,pElemRef);

  if ( eTouch == GSLC_TOUCH_UP_IN ) {
    switch (pElem->nId) {
//<Button Enums !Start!>
      case E_ELEM_NUMINPUT1:
        gslc_ElemXKeyPadInputAsk(&m_gui, m_pElemKeyPadNum, E_POP_KEYPAD_NUM, m_pElemVal1_2);
        break;
      case E_ELEM_NUMINPUT3:
        gslc_ElemXKeyPadInputAsk(&m_gui, m_pElemKeyPadNum, E_POP_KEYPAD_NUM, m_pElemVal3);
        break;
      case E_ELEM_NUMINPUT4:
        gslc_ElemXKeyPadInputAsk(&m_gui, m_pElemKeyPadNum, E_POP_KEYPAD_NUM, m_pElemVal4);
        break;
//<Button Enums !End!>
      default:
        break;
    }
  }
  return true;
}

//<Checkbox Callback !Start!>
//<Checkbox Callback !End!>

bool CbKeypad(void* pvGui, void *pvElemRef, int16_t nState, void* pvData)
{
  gslc_tsGui* pGui     = (gslc_tsGui*)pvGui;
  gslc_tsElemRef* pElemRef = (gslc_tsElemRef*)(pvElemRef);
  gslc_tsElem* pElem    = gslc_GetElemFromRef(pGui,pElemRef);

  int16_t nTargetElemId = gslc_ElemXKeyPadDataTargetIdGet(pGui, pvData);
  if (nState == XKEYPAD_CB_STATE_DONE) {
    switch (nTargetElemId) {
//<Keypad Enums !Start!>
      case E_ELEM_NUMINPUT1:
        gslc_ElemXKeyPadInputGet(pGui, m_pElemVal1_2, pvData);
        break;
      case E_ELEM_NUMINPUT3:
        gslc_ElemXKeyPadInputGet(pGui, m_pElemVal3, pvData);
        break;
      case E_ELEM_NUMINPUT4:
        gslc_ElemXKeyPadInputGet(pGui, m_pElemVal4, pvData);
        break;
//<Keypad Enums !End!>
      default:
        break;
    }
  } else if (nState == XKEYPAD_CB_STATE_CANCEL) {
    gslc_PopupHide(&m_gui);
  }
  return true;
}

//<Spinner Callback !Start!>
//<Spinner Callback !End!>
//<Listbox Callback !Start!>
//<Listbox Callback !End!>
//<Draw Callback !Start!>
//<Draw Callback !End!>
//<Slider Callback !Start!>
//<Slider Callback !End!>
//<Tick Callback !Start!>
//<Tick Callback !End!>

// ------------------------------------------------
// FUNÇÕES AUXILIARES
// ------------------------------------------------

void updateNumericInput(float temperature) {
    char tempStr[10];
    snprintf(tempStr, sizeof(tempStr), "%.2f", temperature); 
    gslc_ElemSetTxtStr(&m_gui, m_pElemVal1_2, tempStr);
}

void IRAM_ATTR sensor1ISR() { sensor1Triggered = true; }
void IRAM_ATTR sensor2ISR() { sensor2Triggered = true; }

void IRAM_ATTR Contador_V() { 
  unsigned long currentMillis = millis();
  pulseInterval = currentMillis - lastPulseTime;
  lastPulseTime = currentMillis; 
  pulsos_V++; 
}

void Velocimetro() {
  if (rpm_V <= 30) intervaloCalculo = 1500;
  else if (rpm_V <= 160) intervaloCalculo = 700;
  else intervaloCalculo = 300;
  
  unsigned long tempoAtual = millis();

  if (tempoAtual - TempoInicial_V >= intervaloCalculo) { 
    detachInterrupt(digitalPinToInterrupt(sensorVelocidade));  

    rpm_V = (pulsos_V * 300) / (tempoAtual - TempoInicial_V);
    if(pulsos_V == 0) rpm_V = 0; 

    velocidade = 3.6 * (2 * pi * RaioDaRoda / 60) * rpm_V;
    float rps = rpm_V / 60.0;

    amostras_rpm[indice] = rpm_V;
    amostras_velocidade[indice] = velocidade;
    amostras_rps[indice] = rps;
    indice = (indice + 1) % N; 

    float rpm_media = 0, velocidade_media = 0, rps_media = 0;
    for (int i = 0; i < N; i++) {
      rpm_media += amostras_rpm[i];
      velocidade_media += amostras_velocidade[i];
      rps_media += amostras_rps[i];
    }
    rpm_media /= N; 
    velocidade_media /= N; 
    rps_media /= N; 

    char buffer[10]; 
    snprintf(buffer, sizeof(buffer), "%.2f", velocidade_media);
    gslc_ElemSetTxtStr(&m_gui, m_pElemVal3, buffer);

    snprintf(buffer, sizeof(buffer), "%.2f", rps_media);
    gslc_ElemSetTxtStr(&m_gui, m_pElemVal4, buffer);      

    int progresso = (int)(rps_media / MAX_RPM * 100.0); 
    if (progresso > 100) progresso = 100; 
    
    // Atualiza o RAMP antigo
    if(m_pElemRamp2 != NULL) gslc_ElemXRampSetVal(&m_gui, m_pElemRamp2, progresso); 

    TempoInicial_V = tempoAtual;
    pulsos_V = 0;
    attachInterrupt(digitalPinToInterrupt(sensorVelocidade), Contador_V, FALLING); 
  }
}

// ------------------------------------------------
// SETUP
// ------------------------------------------------
void setup()
{
  Serial.begin(115200);
  gslc_InitDebug(&DebugOut);

  // Inicializa GUIslice (Gráfico)
  InitGUIslice_gen();

  // Inicialização dos Sensores
  sensors.begin();
  if (sensors.getDeviceCount() == 0) {
      Serial.println("Nenhum sensor DS18B20 encontrado!");
  }

  startMillis = millis();

  pinMode(SENSOR1_PIN, INPUT);
  pinMode(SENSOR2_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(SENSOR1_PIN), sensor1ISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(SENSOR2_PIN), sensor2ISR, FALLING);

  pinMode(sensorVelocidade, INPUT_PULLUP); 
  attachInterrupt(digitalPinToInterrupt(sensorVelocidade), Contador_V, FALLING); 

  pulsos_V = 0; rpm_V = 0; velocidade = 0; TempoInicial_V = 0;

  for (int i = 0; i < N; i++) {
    amostras_rpm[i] = 0; amostras_velocidade[i] = 0; amostras_rps[i] = 0;
  }
}

// ------------------------------------------------
// LOOP
// ------------------------------------------------
void loop()
{
  // 1. Atualiza GUIslice
  gslc_Update(&m_gui);

  // 2. Lógica de Loading (Barra de Progresso + Troca de Página)
  if (!pageChanged) {
      unsigned long currentMillis = millis();
      unsigned long elapsed = currentMillis - startMillis;

      // Calcula a porcentagem (0 a 100) baseada no tempo
      int progressoLoad = (int)((elapsed * 100UL) / delayTime);
      if (progressoLoad > 100) progressoLoad = 100;

      // Atualiza a barra VERDE de loading
      if (m_pElemProgress1 != NULL) {
          gslc_ElemXProgressSetVal(&m_gui, m_pElemProgress1, progressoLoad);
      }

      // Se o tempo acabou (1.5s), faz a troca de página
      if (elapsed >= delayTime) {
          // 1. Muda a página lógica para a Pág 2
          gslc_SetPageCur(&m_gui, E_PG2);
          
          // 2. --- O PULO DO GATO ---
          // Força o desenho da tela NOVA imediatamente!
          // Sem isso, ele tenta ler sensores antes de desenhar e trava visualmente.
          gslc_Update(&m_gui); 
          
          // 3. Marca que mudou para liberar o resto do código
          pageChanged = true;
          gslc_Update(&m_gui);
          }
      
      return; // Sai do loop enquanto carrega
        }

  // --------------------------------------------------
  // LÓGICA DO PAINEL PRINCIPAL
  // --------------------------------------------------

  // Leitura Temperatura (Lento - a cada 1s)
  static unsigned long lastTempRequest = 0;
  if (millis() - lastTempRequest > 1000) {
    sensors.requestTemperatures();
    float tempC = sensors.getTempCByIndex(0);
    if(tempC != -127) updateNumericInput(tempC);
    lastTempRequest = millis();
  }

  // Lógica de Combustível/LEDs
  bool sensor1 = digitalRead(SENSOR1_PIN);
  bool sensor2 = digitalRead(SENSOR2_PIN);

  gslc_tsColor colorBox7 = GSLC_COL_BLACK;
  gslc_tsColor colorBox8 = GSLC_COL_BLACK;
  gslc_tsColor colorBox9 = GSLC_COL_BLACK;

  if (sensor1Triggered) sensor1Triggered = false; 
  if (sensor2Triggered) sensor2Triggered = false;

  if (sensor1 == HIGH && sensor2 == HIGH) {
      if (millis() - lastBlinkTime >= 500) {
          lastBlinkTime = millis();
          box9State = !box9State;
      }
      colorBox9 = box9State ? GSLC_COL_RED : GSLC_COL_BLACK;
  } else if (sensor1 == LOW || sensor2 == LOW) {
      colorBox9 = GSLC_COL_YELLOW;
      colorBox8 = GSLC_COL_YELLOW;
  }

  if (sensor1 == LOW && sensor2 == LOW) {
      colorBox9 = GSLC_COL_GREEN;
      colorBox8 = GSLC_COL_GREEN;
      colorBox7 = GSLC_COL_GREEN; 
  }

  // Atualiza cores
  if(m_pElemBox7 != NULL) gslc_ElemSetCol(&m_gui, m_pElemBox7, colorBox7, colorBox7, colorBox7);
  if(m_pElemBox8 != NULL) gslc_ElemSetCol(&m_gui, m_pElemBox8, colorBox8, colorBox8, colorBox8);
  if(m_pElemBox9 != NULL) gslc_ElemSetCol(&m_gui, m_pElemBox9, colorBox9, colorBox9, colorBox9);

  Velocimetro(); 
}
