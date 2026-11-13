## Estacionamento Inteligente

Este projeto consiste em um sistema de estacionamento inteligente desenvolvido com ESP32 e tecnologia RFID, integrado a um aplicativo para gerenciamento de veículos. O sistema realiza a leitura da identificação do veículo e verifica se a placa está cadastrada na base de dados. Quando o cadastro é validado, a cancela é aberta automaticamente, permitindo o acesso ao estacionamento; caso contrário, a entrada é bloqueada. Além do hardware, foi desenvolvido um aplicativo que permite o cadastro e o gerenciamento das placas autorizadas, garantindo a integração entre o software e o sistema físico, tornando o controle de acesso mais prático, seguro e automatizado.

* **Disciplina/Semestre:**  Microcontroladores - 1º período
* **Ano:** 2026

## Arquitetura do sistema
O sistema é composto por duas partes integradas: hardware e software. O hardware utiliza um ESP32 conectado a um leitor RFID, um servo motor, LEDs e um buzzer para controlar o acesso ao estacionamento. O software consiste em um aplicativo desenvolvido no MIT App Inventor, responsável pelo cadastro das placas autorizadas. Ao aproximar uma tag RFID (que representa a placa do veículo), o ESP32 verifica se ela está cadastrada. Se estiver, a cancela é aberta automaticamente; caso contrário, o acesso é negado, garantindo um controle de entrada automatizado e seguro.

## Requisitos

**Hardware:** ESP32 – Microcontrolador responsável por controlar todo o sistema, processando a leitura das tags RFID, acionando os LEDs, o buzzer e o servo motor.
Módulo RFID MFRC522 (RC522) – Utilizado para realizar a leitura das tags/cartões RFID e identificar se o acesso é autorizado.
Tag ou Cartão RFID – Dispositivo aproximado do leitor para autenticação e liberação da entrada.
Servo Motor (SG90 ou similar) – Simula a cancela do estacionamento, abrindo quando uma tag autorizada é identificada.
LED Verde – Indica que o acesso foi autorizado e a cancela foi aberta.
LED Vermelho – Indica que o acesso foi negado por falta de autorização.
Buzzer – Emite sinais sonoros para informar sucesso ou falha na autenticação.
2 Resistores (220 Ω ou 330 Ω) – Limitam a corrente dos LEDs para evitar danos aos componentes.
Jumpers (cabos de conexão) – Fazem a interligação entre o ESP32 e os demais componentes.
Fonte de alimentação via USB – Alimenta o ESP32 e, consequentemente, todo o circuito.

**Software:** Linguagens
C++
Blockly (programação em blocos do MIT App Inventor)
Frameworks
MIT App Inventor
Bibliotecas
SPI.h
MFRC522.h
ESP32Servo.h
Ferramentas
Arduino IDE
MIT App Inventor
Wokwi (simulação do circuito)
Git
GitHub

## Alunos integrantes da equipe
* Ana Clara Campos Paulino
* Ana Luiza Santos Mascarenhas
* Giulia Alves Sousa
* Leandro Manini Magalhães
* Leila Luiza Miguel Bicalho
* Lucas Batista Conforti

## Professores responsáveis
* Marta Dias Moreira Noronha

## Instruções de utilização
O sistema simula o controle de acesso de um estacionamento inteligente. A tag RFID representa a placa do veículo cadastrada no aplicativo. Quando a tag aproximada corresponde a uma placa autorizada, o ESP32 libera automaticamente a entrada, acionando a cancela. Caso a identificação não esteja cadastrada, o acesso é bloqueado, garantindo que apenas veículos autorizados possam entrar no estacionamento. Essa integração entre o aplicativo e o hardware torna o processo de controle de acesso mais seguro, prático e automatizado.

## Metodologia
O desenvolvimento do projeto foi realizado seguindo uma abordagem prática e incremental. Inicialmente, foram definidos os requisitos do sistema e selecionados os componentes de hardware, como o ESP32, o módulo RFID, o servo motor, os LEDs e o buzzer. Em seguida, foi desenvolvido o firmware em C++ na Arduino IDE para controlar o funcionamento do sistema e realizar a validação das tags RFID. Paralelamente, foi criado um aplicativo no MIT App Inventor para o cadastro das placas autorizadas. Antes da implementação física, o circuito foi testado no simulador Wokwi e, após os ajustes necessários, o sistema foi integrado e validado por meio de testes de funcionamento, garantindo a correta comunicação entre o hardware e o software.

## Estrutura do repositório
Links clicáveis: Simulador - https://wokwi.com/projects/468469105440983041
Video do funcionamento do projeto: https://drive.google.com/file/d/1xJFhl65YH7jLrH_dBCAHtQKiZM5JC1BD/view?usp=drivesdk

* **`/Artefatos`** — Atas, canvas e demais artefatos produzidos.
* **`/Divulgacao`** — Apresentações, vídeos e fotos do projeto.
