#Projecto de Algoritmos e Programação
Robo de Limpeza – CleaningRobot

O objectivo deste projecto é desenvolver uma aplicação que simula o funcionamento de um robot de limpeza chamado CleaningRobot. De um modo geral, o programa simula o funcionamento de robots de limpeza que existem actualmente no mercado. O robot deve-se movimentar num dado piso, limpando a área por onde passa. O objectivo dessa simulação é estimar quanto tempo um robot demora a limpar a área associada a uma divisão, assumindo que existem obstáculos (móveis, mesas, etc.).
O programa deve permitir a geração de um mapa da divisão, simular o processo de limpeza por parte do robot, marcando os espaços já limpos, bem como a gravação de um ficheiro que indique o nome do robot, algumas estatísticas da simulação da limpeza e o caminho percorrido.

Funcionamento
Uma divisão é uma grelha de quadrados. Quando o robot passa por um elemento da grelha (quadrado), este deve ser marcado como limpo. O Robot deve começar numa posição arbitrária da divisão e com uma direcção aleatória de movimento.

O funcionamento do programa poderá ser resumido da seguinte forma:
1. Leitura do tamanho da divisão (número de quadrados (altura e largura));
2. Leitura dos nomes dos robots de limpeza. O nome deve ter no máximo 2 letras;
3. Simulação da limpeza da divisão: A simulação poderá ficar mais rápida ou mais lenta a pedido do utilizador (carregando nas teclas, L (Rápido), Z (Lento));
4. O mapa da divisão deverá ser actualizado para indicar os quadrados já limpos e a nova posição do robot;
5. Gravação do caminho percorrido pelo robot;

Simulação	da	Limpeza	
A divisão é rectangular com uma altura A e largura L, valores pedidos ao utilizador no início do programa, Inicialmente, toda a divisão está suja e um robot não pode atravessar as paredes da divisão, os robots não podem colidir uns com os outros e não podem colidir também com os obstáculos. Para guardar o mapa da divisão tem de ser usado um vector M, indicando quais os quadrados ocupados e sujos. O robot deve-se movimentar de acordo com as seguintes regras:
• Na divisão, cada posição do vector M tem um índice com está na figura;
• O robot tem uma posição (Xc, Yc) que identifica o quadrado da divisão que ocupa;
• O robot tem uma posição (Xt, Yt) que pretende alcançar;
• Sempre que o robot alcançar a posição (Xt, Yt) deve ser gerada aleatoriamente uma nova posição para a qual se deve deslocar. Será que deve impor uma condição na posição gerada? Experimente!
• Os robots devem continuar a tentar alcançar uma posição até que a divisão esteja toda limpa;
• A velocidade da simulação deve ser controlada através do teclado;
• Quando toda a divisão estiver limpa, os robots não se devem movimentar.

Escrita	em	Ficheiro	
No final de cada simulação é necessário gravar em ficheiro algumas estatísticas sobre os robots.
• Nome do robot;
• Número de quadrados limpos;
• Número de quadrados percorridos;
• Lista de inteiros com um índice para cada quadrado percorrido pelo robot.

