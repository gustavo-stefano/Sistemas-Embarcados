# Sistemas-Embarcados
Repository for the class SEM0544 from the University of Sao Paulo (USP - EESC).

Nome do Grupo: Cabras Mancas

Membros do grupo:
  - Gustavo Stefano
  - Igor Arenales
  - Lucas Padlipskas
  - Andre Mota
  
Projeto:
Nosso grupo optou pela formiga robótica. O objetivo do projeto é programar o robô de forma que ele possa ser minimamente controlavel, em outras palavras, capaz de transladar em linha reta e fazer curvas para direita e esquerda de forma controlada. 

Arquitetura:
A arquitetura do sistema robotico pode ser vista em detalhes no esquematico a seguir:
![Arquitetura Eletronica Formiga Robotica](https://user-images.githubusercontent.com/38964186/172719800-e0dd9714-1caa-4bdd-af15-6b2b1c536a52.png)

Como o robo possiu um grnade numero de atuadores, o esquema a seguir foi desenvolvido para a nomenclatura dos mesmo e evitar confusoes ao desenvolver o código:
![Atuadores Formiga robotica](https://user-images.githubusercontent.com/38964186/172720001-e0654bee-0c1f-4032-9b64-5375e0b5d930.png)


![](https://github.com/gustavo-stefano/Sistemas-Embarcados/blob/main/ezgif-1-5fb3583126.gif)

![](https://github.com/gustavo-stefano/Sistemas-Embarcados/blob/main/ezgif-1-f1d40c770e.gif)

![](https://github.com/gustavo-stefano/Sistemas-Embarcados/blob/main/ezgif-1-bac7082c9b.gif)

O projeto é consituído por dois microcontroladores do kit de desenvolvimento mbed com o processador NXP lpc1768, nos quais possue 6 saídas PWM cada para o controle dos servo motores. Duas interfaces de comunicação de rede CAN, nas quais uma delas será usada para constituir a rede de comunicação do sistema. E ainda, os temporizadores nativos dos processadores foram inicializados para ter uma base tempo confiável e robusta para o sistema. Outro sistema importante utilizado no projeto foram os interrupts do lpc1768. Em uma das placas, uma função IRQ_Handler (Interrupt request handler) foi criada para que a execução das funções de movimento das pernas do robô sejam executadas simultâneamente. Ou seja, ao receber as intruções do linux embarcada através da rede CAN, os controladores deverão executar as rotinas de movimento de acordo com o que foi instruído. No entanto, para o melhor funcionamento do sistema, é interessante que estas rotinas sejam executadas em sincronia. Sendo assim, um dos controladores possue um comando para que o pino 5 do kit de desenvolvimento passe de estado low para high. O outro controlador tem seu interrupt configurado como borda de subida, sendo assim reagindo a variação do estado da saída do outro controlador. Outro aspecto que vale a menção são os leds que estão na mbed. Eles foram usados para podermos visualizar quais rotinas estão sendo executadas em cada placa. Se as placas estiverem em "standBy", ou seja, as pernas do robô estão paradas, todos os 4 leds estarão acesos. Se a função a ser executada é a 'foward', os leds acenderão de forma crescente (primeiramente o led1, depois o led2 e etc). De forma análoga à função 'backward', os leds acenderão de maneira decrescente (primeiro o led4 e por último o led1). 

![Pinagem do kit de desenvolvimento mbed lpc1768](lpc1768_pinout.png)

A rede CAN foi desenvolvida em meados dos anos 80 pela Bosch GmbH para proporcionar uma boa relação custo eficácia para um barramento de comunicação com aplicações automotivas. Hoje esta comunicação é utilizada também em indústrias, plantas de controle, robótica, e em dispositivos médicos. A Controller Area Network (CAN) pode ser definida como um protocolo de comunicação baseado em múltiplos mestres caracterizado pela resolução determinística da conexão, baixo custo, e implantação simples. Esta comunicação é realizado por um barramento de dois fios. O protocolo CAN opera em todas as unidades de controle, o que possibilita a continuação do funcionamento, mesmo quando uma das unidades apresente problema. A princípio, a rede CAN faz com que todos as unidades do sistema recebem a mensagem pelo barramento, no entanto, somente aquelas que o frame de identificação de mensagem estão presentes no código das unidades serão ouvidas por elas. Ou seja, a unidade envia dados com o código identificador na rede ao inicializar o processo de trânsferência de mensagens. A rede verifica quais mensagens possuem maior prioridade através do número do identificador. Após o envio do identificador, a unidade de controle envia um conjunto de dados, os quais são informações relevantes à aplicação em questão. Este conjunto de dados são constituídos por 8 frames de 8 bits cada. Porém se o identificador da mensagem não estiver definido no código fonte da unidade de controle, a mensagem será apenas lida e não será memorizada. Ainda vale ressaltar que a rede CAN é um barramento digital projetado para operar de 20 Kbit/s até 1 Mbit/s, padronizado pela norma ISO11898 para altas velocidades (500 Kbit/s) e pela norma ISO11519-2 para aplicações de baixas velocidades (até 125 Kbit/s). Para a aplicação da disciplina, a frequência utilizada foi de 500 Kbit/s.

O kit de desenvolvimento mbed possue um processador de arquitetura ARM Cortex-M3 de 32 bits, clock de 100 Mhz e 512 kB de memória flash. A interface usada para a programação destes controladores foi o próprio compilador online da propria plataforma da mbed (https://ide.mbed.com/compiler) onde há todo o suporte e documentação referentes ao kit de desenvolvimento utilizado.

Ainda falando da constituição do projeto, temos que mencionar o microprocessador embarcado no robô. Para o robô foi utilizado a BeagleBone Black. O seu processador é um Sitara AM3359, com um clock de 1GHz, memórica eMMC embarcada de capacidade de 2 GB e uma memória SDRAM de 521 MB. A versão do debian utilizada foi o Debian 9.12 gravado em um cartão SD externo. Nesta placa de linux embarcado existem dois controladores para a rede CAN (can0 e can1), nos quais somente um deles foi utilizado. Para a inicialização da rede na BBB basta apenas designar as funções dos pinos p9.24 e p9.26 como "config-pin p9.24 can" e "config-pin p9.26 can" para o controlador can1, ou analogamente para can0 "config-pin p9.19 can" e "config-pin p9.20 can". Logo após, basta dar o seguinte comando especificando quais dos controladores o usuário deseja usar assim como a frequência de operação do controlador(neste caso habilitando o can1 com 500 KHz: "sudo /sbin/ip link set can1 up type can bitrate 500000"). A linguagem de programação utilizada na BBB foi o python. Sendo assim, é visto que mesmo com arquiteturas distintas os dois hardwares podem trocar informações entre si através da rede CAN. A biblioteca utilizada para o código foi a 'python-can'. Basicamente foi definido quais dos controladores da placa será utilizado, e comandos como recieve ou send são utilizados para receber e mandar mensagens, respectivamente.

Sobre o andamento do projeto, varios testes de validação foram realizados, desde testes sobre a rotina de passos do robô, até os testes de comunição entre os hardwares. No entanto, até o momento há um problema que impossibilita o correto funcionamento do robô. Acredita-se que um (ou alguns) dos servos motores utilizados neste robô estejam defeituosos  

