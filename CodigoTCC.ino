  // Trabalho de Conclusão de Curso em Engenharia de Controle e Automação 
  // Protótipo de Robô Doméstico para Aspiração de Pó com Rodas Omnidirecionais
  // Leonardo Cristiano Küster

  #include <Ultrasonic.h>
  #include <Servo.h>
  
  #define sensorTrig1      46                     // Sensor Ultrassônico 1, Pino do Trig
  #define sensorEcho1      47                     // Sensor Ultrassônico 1, Pino do Echo
  #define sensorTrig2      44                     // Sensor Ultrassônico 2, Pino do Trig
  #define sensorEcho2      45                     // Sensor Ultrassônico 2, Pino do Echo
  #define sensorTrig3      42                     // Sensor Ultrassônico 3, Pino do Trig
  #define sensorEcho3      43                     // Sensor Ultrassônico 3, Pino do Echo
  #define in1              29                     // Motor Esquerdo Frontal, Pino 1
  #define in2              28                     // Motor Esquerdo Frontal, Pino 2
  #define in3              26                     // Motor Esquerdo Trazeiro, Pino 1
  #define in4              27                     // Motor Esquerdo Trazeiro, Pino 2
  #define in5              25                     // Motor Direito Frontal, Pino 1
  #define in6              24                     // Motor Direito Frontal, Pino 2
  #define in7              23                     // Motor Direito Trazeiro, Pino 1
  #define in8              22                     // Motor Direito Trazeiro, Pino 2
  #define enable1          12                     // Pino PWM para controle de Velocidade Motor Esquerdo Frontal
  #define enable2          13                     // Pino PWM para controle de Velocidade Motor Esquerdo Trazeiro
  #define enable3          10                     // Pino PWM para controle de Velocidade Motor Direito Frontal
  #define enable4          11                     // Pino PWM para controle de Velocidade Motor Direito Trazeiro
  #define VelocidadeMotor  170                    // Definição da Velocidade do Motor Esquerdo Frontal (0 a 255) 
  #define VelocidadeMotor1 240                    // Definição da Velocidade do Motor Esquerdo Trazeiro (0 a 255)
  #define VelocidadeMotor2 155                    // Definição da Velocidade do Motor Direito Frontal (0 a 255)
  #define VelocidadeMotor3 160                    // Definição da Velocidade do Motor Direito Trazeiro (0 a 255)
  #define distLimite       25                     // Distância limite de 20 centímetros
  
  unsigned long pulsetime = 0;               
  unsigned long distancia = 0;                    // Armazena o valor da Distância
  
  Servo ESC;
  
  void setup() {
  
    pinMode(enable1, OUTPUT);
    pinMode(enable2, OUTPUT);
    pinMode(enable3, OUTPUT);
    pinMode(enable4, OUTPUT);
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);
    pinMode(in5, OUTPUT);
    pinMode(in6, OUTPUT);
    pinMode(in7, OUTPUT);
    pinMode(in8, OUTPUT);
  
    pinMode(sensorTrig1, OUTPUT);
    pinMode(sensorEcho1, INPUT);
    pinMode(sensorTrig2, OUTPUT);
    pinMode(sensorEcho2, INPUT);
    pinMode(sensorTrig3, OUTPUT);
    pinMode(sensorEcho3, INPUT);
    
    Serial.begin(9600);
  
    ESC.attach(8, 1000, 2000);                    
    ESC.write(0);
    
    delay(5000);                                  // Tempo de Espera antes de Inicializar
  
    ESC.write(180);                               // Potência definida para o ESC (0 a 180)
  
  }
  
  void FuncaoAleatoria();
  
  void loop() {
    
    int DistanciaFrente = 100;
    int DistanciaEsquerda = 100;
    int DistanciaDireita = 100;
    
    
    while(DistanciaFrente > distLimite && DistanciaEsquerda > distLimite && DistanciaDireita > distLimite){
      paraFrente();
      delay(10);
      DistanciaFrente = leDistancia(2);
      delay(25);
      DistanciaEsquerda = leDistancia(1);
      delay(25);
      DistanciaDireita = leDistancia(3);
      delay(25);
    }
    pararMotor();
    delay(1000);
  
    if(leDistancia(1) < distLimite){
      girarHorario(1500); 
    }
    
    else{
      if(leDistancia(3) < distLimite){
        girarAntiHorario(1500);
      }
        else{
          FuncaoAleatoria();
        }
      } 
      
    delay(500);
    
  }
  
  // Definição das funções realizadas pelo protótipo
  
  void pararMotor(){                              // Função para Parar todos os Motores
  
    analogWrite(enable1, 0); 
    analogWrite(enable2, 0); 
    analogWrite(enable3, 0); 
    analogWrite(enable4, 0);
    digitalWrite(in1,LOW);                    
    digitalWrite(in2,LOW);
    digitalWrite(in3,LOW);                   
    digitalWrite(in4,LOW);
    digitalWrite(in5,LOW);                    
    digitalWrite(in6,LOW);
    digitalWrite(in7,LOW);                   
    digitalWrite(in8,LOW);
    
  }
  
  void paraFrente(){
  
    analogWrite(enable1, 90); 
    analogWrite(enable2, 230); 
    analogWrite(enable3, 95); 
    analogWrite(enable4, 100); 
    digitalWrite(in1,LOW);                        // Motor Esquerdo Frontal Sentido Anti-Horário
    digitalWrite(in2,HIGH);
    digitalWrite(in3,LOW);                        // Motor Esquerdo Trazeiro Sentido Anti-Horário
    digitalWrite(in4,HIGH);
    digitalWrite(in5,HIGH);                       // Motor Direito Frontal Sentido Horário
    digitalWrite(in6,LOW);
    digitalWrite(in7,HIGH);                       // Motor Direito Trazeiro Sentido Horário
    digitalWrite(in8,LOW);
    
  }
  
  void paraTras(long tempo){                      // Função para o Robô andar para trás
  
    analogWrite(enable1, VelocidadeMotor); 
    analogWrite(enable2, VelocidadeMotor1); 
    analogWrite(enable3, VelocidadeMotor2); 
    analogWrite(enable4, VelocidadeMotor3); 
    digitalWrite(in1,HIGH);                       // Motor Esquerdo Frontal Sentido Horário
    digitalWrite(in2,LOW);
    digitalWrite(in3,HIGH);                       // Motor Esquerdo Trazeiro Sentido Horário
    digitalWrite(in4,LOW);
    digitalWrite(in5,LOW);                        // Motor Direito Frontal Sentido Anti-Horário
    digitalWrite(in6,HIGH);
    digitalWrite(in7,LOW);                        // Motor Direito Trazeiro Sentido Anti-Horário
    digitalWrite(in8,HIGH);
    delay(tempo);                                 // Definição do tempo para executar função
    pararMotor();
  
  }
       
  void direcaoEsquerda (long tempo){              // Função para Fazer com que o Robô vá para Esquerda por Determinado Tempo
  
    analogWrite(enable1, VelocidadeMotor); 
    analogWrite(enable2, VelocidadeMotor1); 
    analogWrite(enable3, VelocidadeMotor2); 
    analogWrite(enable4, VelocidadeMotor3); 
    digitalWrite(in1,LOW);                        // Motor Esquerdo Frontal Sentido Anti-Horário
    digitalWrite(in2,HIGH);
    digitalWrite(in3,HIGH);                       // Motor Esquerdo Trazeiro Sentido Horário
    digitalWrite(in4,LOW);
    digitalWrite(in5,LOW);                        // Motor Direito Frontal Sentido Anti-Horário
    digitalWrite(in6,HIGH);
    digitalWrite(in7,HIGH);                       // Motor Direito Trazeiro Sentido Horário
    digitalWrite(in8,LOW);
    delay(tempo);                                 // Definição do tempo para executar função
    pararMotor();
  
  }
  
  void direcaoDireita (long tempo){               // Função para Fazer com que o Robô vá para Direita por Determinado Tempo
  
    analogWrite(enable1, VelocidadeMotor); 
    analogWrite(enable2, VelocidadeMotor1); 
    analogWrite(enable3, VelocidadeMotor2); 
    analogWrite(enable4, VelocidadeMotor3); 
    digitalWrite(in1,HIGH);                       // Motor Esquerdo Frontal Sentido Horário
    digitalWrite(in2,LOW);
    digitalWrite(in3,LOW);                        // Motor Esquerdo Trazeiro Sentido Anti-Horário
    digitalWrite(in4,HIGH);
    digitalWrite(in5,HIGH);                       // Motor Direito Frontal Sentido Horário
    digitalWrite(in6,LOW);
    digitalWrite(in7,LOW);                        // Motor Direito Trazeiro Sentido Anti-Horário
    digitalWrite(in8,HIGH);
    delay(tempo);                                 // Definição do tempo para executar função
    pararMotor();
  
  }
  
  void girarHorario (long tempo){                 // Função para o Robô girar x graus no sentido Horário 
  
    analogWrite(enable1, VelocidadeMotor); 
    analogWrite(enable2, VelocidadeMotor1); 
    analogWrite(enable3, VelocidadeMotor2); 
    analogWrite(enable4, VelocidadeMotor3); 
    digitalWrite(in1,LOW);                        // Motor Esquerdo Frontal Sentido Anti-Horário
    digitalWrite(in2,HIGH);
    digitalWrite(in3,LOW);                        // Motor Esquerdo Trazeiro Sentido Anti-Horário
    digitalWrite(in4,HIGH);
    digitalWrite(in5,LOW);                        // Motor Direito Frontal Sentido Anti-Horário
    digitalWrite(in6,HIGH);
    digitalWrite(in7,LOW);                        // Motor Direito Trazeiro Sentido Anti-Horário
    digitalWrite(in8,HIGH);
    delay(tempo);                                 // Definição do tempo para executar função
    pararMotor();
    
  }
  
  void girarAntiHorario (long tempo){             // Função para o Robô girar x graus no sentido Anti-Horário 
  
    analogWrite(enable1, VelocidadeMotor); 
    analogWrite(enable2, VelocidadeMotor1); 
    analogWrite(enable3, VelocidadeMotor2); 
    analogWrite(enable4, VelocidadeMotor3); 
    digitalWrite(in1,HIGH);                       // Motor Esquerdo Frontal Sentido Horário
    digitalWrite(in2,LOW);
    digitalWrite(in3,HIGH);                       // Motor Esquerdo Trazeiro Sentido Horário
    digitalWrite(in4,LOW);
    digitalWrite(in5,HIGH);                       // Motor Direito Frontal Sentido Horário
    digitalWrite(in6,LOW);
    digitalWrite(in7,HIGH);                       // Motor Direito Trazeiro Sentido Horário
    digitalWrite(in8,LOW);
    delay(tempo);                                 // Definição do tempo para executar função
    pararMotor();
    
  }
  
  void direcaoDiagonalDireitaTras (long tempo){   // Função para Fazer com que o Robô vá para Diagonal Direita Trás por Determinado Tempo
  
    analogWrite(enable1, VelocidadeMotor); 
    analogWrite(enable2, VelocidadeMotor1); 
    analogWrite(enable3, VelocidadeMotor2); 
    analogWrite(enable4, VelocidadeMotor3); 
    digitalWrite(in1,HIGH);                       // Motor Esquerdo Frontal Sentido Horário
    digitalWrite(in2,LOW);
    digitalWrite(in7,LOW);                        // Motor Direito Trazeiro Sentido Anti-Horário
    digitalWrite(in8,HIGH);
    delay(tempo);                                 // Definição do tempo para executar função
    pararMotor();
  
  }
  
  void direcaoDiagonalEsquerdaTras(long tempo){   // Função para Fazer com que o Robô vá para Diagonal Esquerda Trás por Determinado Tempo
  
    analogWrite(enable1, VelocidadeMotor); 
    analogWrite(enable2, VelocidadeMotor1); 
    analogWrite(enable3, VelocidadeMotor2); 
    analogWrite(enable4, VelocidadeMotor3); 
    digitalWrite(in3,HIGH);                       // Motor Esquerdo Trazeiro Sentido Horário
    digitalWrite(in4,LOW);
    digitalWrite(in5,LOW);                        // Motor Direito Frontal Sentido Anti-Horário
    digitalWrite(in6,HIGH);
    delay(tempo);                                 // Definição do tempo para executar função
    pararMotor();
    
  }
  
  int leDistancia(int sensor){                    // Função para ler a distância do sensor
  
    int sensorTrig = 0;
    int sensorEcho = 0;
  
    switch(sensor){
      
            case 1: sensorTrig = sensorTrig1; 
                    sensorEcho = sensorEcho1;
                    break;
                    
            case 2: sensorTrig = sensorTrig2; 
                    sensorEcho = sensorEcho2;
                    break;
                    
            case 3: sensorTrig = sensorTrig3; 
                    sensorEcho = sensorEcho3;
                    break; 
  
            default: break;
   
    }
    digitalWrite(sensorTrig, LOW);            
    digitalWrite(sensorTrig, HIGH);           
    delayMicroseconds(10);                    
    digitalWrite(sensorTrig, LOW);
    pulsetime = pulseIn(sensorEcho, HIGH);
    return pulsetime/58;                          // Converte a distância em centímetros e retorna
  
  } 
  
  void FuncaoAleatoria(){
  
    int Numero = random(1,6);
    Serial.print("Aleatorio");
    Serial.println(Numero);
    
    switch(Numero){ 
      case 1: direcaoEsquerda(1500); break;
      case 2: direcaoDireita(1500); break;
      case 3: girarHorario(1500); break;
      case 4: girarAntiHorario(1500); break;
      case 5: direcaoDiagonalDireitaTras(1500); break;
      case 6: direcaoDiagonalEsquerdaTras(1500); break;
      default: pararMotor; break;
    };
  }
