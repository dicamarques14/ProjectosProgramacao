# Projecto de Estrutura de Dados
Projeto Final – “Gestão de Caixas de um supermercado”


![Screenshot](https://github.com/dicamarques14/ProjectosProgramacao/raw/master/Estrutura%20de%20Dados/Screen.png)


A gerência de uma grande superfície “Compra Aqui Lda.” pretende desenvolver um programa que permita gerir todo o conjunto de caixas de atendimento que possui.
O sistema que se pretende servirá para a gerência poder “apreciar” o andamento das caixas de atendimento. A gerência da empresa pretende, essencialmente, gerir as caixas e verificar se será necessário introduzir/remover caixas de modo a optimizar todo o processo. Existe um programa (ED_Visual.exe) que está permanentemente a fazer a monitorização do sistema.
O tempo de atendimento de uma pessoa depende do numero de compras que trás no carrinho. Estima-se que o tempo de passagem (na caixa) de cada produto é um valor entre [2, TEMPO_ATENDIMENTO_PRODUTO]
A empresa garante que o tempo máximo de espera é MAXESPERA, se este valor for ultrapassado será “oferecido” descontado um produto do carrinho de compras do cliente.
O sistema deve guardar, quantos produtos foram “oferecidos”, pois é importante que se analise superiormente se esse processo está a dar prejuízo. Cada produto tem um dado preço aleatório (um valor entre ]0, MAXPRECO]) Os dados dos clientes devem ser escritos num ficheiro “Dados.txt” de modo a que o programa ED_Visual.exe esteja sempre a ler este ficheiro

Resumindo, o programa a implementar deve permitir diversas funcionalidades, acessíveis a partir de menus bem estruturados, nomeadamente:
1. Carregar os dados (por omissão) a partir dos ficheiros para estruturas em memória (no início do programa);
2. Gravar os dados (Historial de todo o tempo de simulação), número de clientes atendidos, número de produtos, tempo médio de espera, etc;
3. Ter um histórico (gravar em *.csv) de tudo o que o utilizador faz no programa;
4. Um dado cliente pode estar na fila de uma das caixas, mas num dado instante pode passar para outra caixa;
5. Colocar uma nova caixa em funcionamento;
6. O número máximo de pessoas que podem estar em espera numa caixa é MAXESPERA, se num dado instante for ultrapassado esse número, deve ser aberta outra caixa;
7. Se o numero total de pessoas a atender (por todas as caixas) for inferior a um dado valor, a caixa que tiver menos pessoas deve fechar (depois de atender as que tem em espera)
8. Num dado instante pode acontecer que uma caixa tenha de fechar, então as pessoas devem ser distribuídas pelas restantes caixas;
9. Pesquisar pessoa – Verificar se uma dada pessoa está em espera numa dada caixa;
10. Determinar qual a caixa que atendeu mais pessoas;
11. Determinar qual a caixa que vendeu mais produtos;
12. Listar todas as pessoas atendidas por uma caixa;
13. Determinar qual o nome do operador de caixa que atendeu menos pessoas;
