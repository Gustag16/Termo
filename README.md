# Termo
Wordle-like game

1) DESCRIÇÃO
Implementação de um algoritmo que simula o funcionamento do jogo “Termo”. O jogo consiste em: 
Dada uma palavra aleatória de cinco letras, o jogador deve adivinhá-la.
A adivinhação se dá por tentativa e erro. O usuário deve inserir quaisquer palavras existentes no banco de dados do jogo, verificar as letras que as compõem e a relação destas com a palavra-chave e cruzar dados para inserir a palavra correta antes que suas tentativas acabem.
Ao inserir uma palavra, o programa lê as letras que a compõe e retorna ao usuário o feedback de cada letra individualmente. Existem três estados possíveis: I) A letra não faz parte da palavra e, portanto, é prudente não utilizá-la novamente. II) A letra faz parte da palavra, mas não se encontra na posição correta e, portanto, é prudente colocá-la em outro lugar na próxima tentativa. III) A letra faz parte da palavra e se encontra na posição correta, sendo prudente mantê-la no mesmo lugar na próxima tentativa caso o usuário ainda não tenha vencido o jogo.
Se todas as cinco letras estiverem na posição correta antes das tentativas acabarem, a palavra inserida é igual à palavra-chave e, assim, o jogador vence.
Se nem todas as cinco letras estiverem na posição correta e as tentativas acabarem, o jogador perde.

2) FUNCIONAMENTO
	Um arquivo de texto irá conter o máximo de palavras com cinco letras existentes na língua portuguesa, uma palavra por linha. Uma vez iniciado, o programa abre esse arquivo e lê uma linha aleatória de acordo com a hora do sistema do usuário. Lendo a palavra, esta é armazenada como sendo a palavra-chave, que deve ser adivinhada.
	O programa pede e lê a primeira tentativa do jogador e contabiliza a entrada como uma tentativa. Ele retorna as letras digitadas, e, para letras que existem na palavra e estão na posição correta, estas são escritas na cor VERDE. Para as letras que existem na palavra e estão na posição errada, na cor AMARELA. Além disso, é mostrado ao usuário o número restante de tentativas que ele tem. Isso se repete até que o jogador vença ou perca.
	Em caso de vitória, o jogador é parabenizado e requisitado a escrever seu nome para que este seja contabilizado em um arquivo separado, servindo como um ranking de vitórias.
	Em caso de derrota, é apresentada a mensagem de derrota ao jogador e o programa encerra.



3) EXEMPLO DE PARTIDA DE TERMO SIMPLES
	Suponhamos que a palavra-chave seja “AVIAO”
	Possível primeira entrada do usuário: “AUREO”
	O programa deve retornar: A U R E O Tentativas restantes: n
	Possível segunda entrada do usuário: “ABACO”
	O programa deve retornar: A B A C O Tentativas restantes: n-1
	Possível terceira entrada do usuário: “ARPAO”
	O programa deve retornar: A R P A O Tentativas restantes: n-2
	Possível quarta entrada do usuário: “AVIAO”
	O programa deve retornar: A V I A O
Vitória! Digite aqui seu nome:
Possível nome de usuário: Jander
Fim do programa.

	Observação: em um primeiro momento, faz-se necessário o uso exclusivo de palavras maiúsculas presentes na tabela ASCII, o que impede sinais diacríticos de serem incluídos, como os acentos gráficos, o til e o cedilha (ç).
