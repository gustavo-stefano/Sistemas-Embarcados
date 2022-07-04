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

![Pinagem do kit de desenvolvimento mbed lpc1768](lpc1768_pinout.png)

A rede CAN foi desenvolvida em meados dos anos 80 pela Bosch GmbH para proporcionar uma boa relação custo eficácia para um barramento de comunicação com aplicações automotivas. Hoje esta comunicação é utilizada também em indústrias, plantas de controle, robótica, e em dispositivos médicos. A Controller Area Network (CAN) pode ser definida como um protocolo de comunicação baseado em múltiplos mestres caracterizado pela resolução determinística da conexão, baixo custo, e implantação simples. Esta comunicação é realizado por um barramento de dois fios. O protocolo CAN opera em todas as unidades de controle, o que possibilita a continuação do funcionamento, mesmo quando uma das unidades apresente problema. A princípio, a rede CAN faz com que todos as unidades do sistema recebem a mensagem pelo barramento, no entanto, somente aquelas que o frame de identificação de mensagem estão presentes no código das unidades serão ouvidas por elas. Ou seja, a unidade envia dados com o código identificador na rede ao inicializar o processo de trânsferência de mensagens. A rede verifica quais mensagens possuem maior prioridade através do número do identificador. Após o envio do identificador, a unidade de controle envia um conjunto de dados, os quais são informações relevantes à aplicação em questão. Este conjunto de dados são constituídos por 8 frames de 8 bits cada. Porém se o identificador da mensagem não estiver definido no código fonte da unidade de controle, a mensagem será apenas lida e não será memorizada. 

A rede CAN é um barramento digital projetado para operar de 20 Kbit/s até 1 Mbit/s, padronizado pela norma ISO11898 para altas velocidades (500 Kbit/s) e pela norma ISO11519-2 para aplicações de baixas velocidades (até 125 Kbit/s).
