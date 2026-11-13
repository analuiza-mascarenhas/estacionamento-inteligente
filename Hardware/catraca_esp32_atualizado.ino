#include <SPI.h>
#include <MFRC522.h>
#include <ESP32Servo.h>
#include "BluetoothSerial.h"
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled!
#endif
BluetoothSerial SerialBT;

// Definições de Pinos
#define SS_PIN    21
#define RST_PIN   22
#define SERVO_PIN 13
#define LED_VERMELHO 4
#define LED_VERDE    5
#define BUZZER       12

MFRC522 rfid(SS_PIN, RST_PIN);
Servo catraca;

// TAGS cadastradas
String tag1 = "C7 3D F2 06";
String tag2 = "8B E6 64 06";

// Estado do estacionamento (controlado pelo App Inventor)
bool estacionamentoLotado = false;

void setup() {
  Serial.begin(115200);

  SerialBT.begin("Catraca_ESP32");
  Serial.println("Bluetooth Pronto!");

  SPI.begin();
  rfid.PCD_Init();

  ESP32PWM::allocateTimer(0);
  catraca.setPeriodHertz(50);
  catraca.attach(SERVO_PIN, 500, 2400);

  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  fecharCatraca();
  Serial.println("Sistema pronto!");
}

void loop() {
  // --- FORMA 1: COMANDOS DO APP INVENTOR (BLUETOOTH) ---
  if (SerialBT.available() > 0) {
    String comandoRecebido = SerialBT.readStringUntil('\n');
    comandoRecebido.trim();

    Serial.println("Comando do App: " + comandoRecebido);

    if (comandoRecebido == "ABRIR") {
      if (!estacionamentoLotado) {
        liberarAcesso("MANUAL");
      } else {
        estacionamentoCheio("MANUAL");
      }
    }
    else if (comandoRecebido == "LOTAR") {
      estacionamentoLotado = true;
      Serial.println("Estacionamento marcado como LOTADO.");
    }
    else if (comandoRecebido == "DESBLOQUEAR") {
      estacionamentoLotado = false;
      Serial.println("Estacionamento desbloqueado.");
    }
  }

  // --- FORMA 2: LEITURA DO RFID ---
  if (!rfid.PICC_IsNewCardPresent()) return;
  if (!rfid.PICC_ReadCardSerial()) return;

  String tagLida = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    tagLida.concat(String(rfid.uid.uidByte[i] < 0x10 ? "0" : ""));
    tagLida.concat(String(rfid.uid.uidByte[i], HEX));
    if (i < rfid.uid.size - 1) tagLida.concat(" ");
  }
  tagLida.toUpperCase();
  tagLida.trim();

  Serial.println("RFID Detectado: " + tagLida);

  if (estacionamentoLotado) {
    estacionamentoCheio(tagLida);
  }
  else if (tagLida == tag1 || tagLida == tag2) {
    liberarAcesso(tagLida);
  }
  else {
    acessoNegado(tagLida);
  }

  rfid.PICC_HaltA();
}

// FUNÇÕES

void liberarAcesso(String origem) {
  Serial.println("Acesso Liberado! Origem: " + origem);
  SerialBT.println("VAGA_OCUPADA:" + origem);

  digitalWrite(LED_VERMELHO, LOW);
  digitalWrite(LED_VERDE, HIGH);

  tone(BUZZER, 1000, 200);
  catraca.write(90);

  delay(5000);

  fecharCatraca();
}

void fecharCatraca() {
  catraca.write(0);
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_VERMELHO, HIGH);
  Serial.println("Catraca fechada.");
}

void acessoNegado(String origem) {
  Serial.println("Acesso Negado! Origem: " + origem);
  SerialBT.println("ERRO_CARTAO:" + origem);

  for (int i = 0; i < 3; i++) {
    digitalWrite(LED_VERMELHO, LOW);
    tone(BUZZER, 300, 150);
    delay(150);
    digitalWrite(LED_VERMELHO, HIGH);
    delay(150);
  }
}

void estacionamentoCheio(String origem) {
  Serial.println("Estacionamento Lotado! Origem: " + origem);
  SerialBT.println("ESTACIONAMENTO_LOTADO:" + origem);

  for (int i = 0; i < 2; i++) {
    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_VERMELHO, HIGH);
    tone(BUZZER, 200, 300);
    delay(300);
  }
}
