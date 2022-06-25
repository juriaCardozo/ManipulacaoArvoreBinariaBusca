# Manipulação de Árvores Binárias de Busca

## Especificações

Explorar implementações de árvores binárias de busca para implementar um programa que crie um
índice remissivo para um determinado texto de entrada.

O programa receberá dois arquivos texto como parâmetros de entrada:

	• Arquivo de entrada: um arquivo texto contendo o texto de entrada simulando um
	livro e o conteúdo de suas páginas. A primeira linha do arquivo é uma tag
	<termo:> contendo todos os termos (palavras) que irão compor o índice remissivo:
	          <termos:palavra1,palavra2,palavra3,· · · palavraN >
 
Da segunda linha em diante poderão haver diversas tags <page:X>, indicando o início
de uma página fictícia do livro. Estas tags possuem também o correspondente número
	
	• Arquivo de saída: é o arquivo texto onde serão impressos os correspondentes termos
	de busca, seguidos dos números de páginas onde foram encontrados, um termo por
	linha. Por exemplo, a palavra "chave"aparece nos textos das páginas 2, 3 e 4. Assim,
	deve-se imprimir no arquivo de saída (na Figura 2b) uma linha com essa informação:
            celula, 2, 3, 4
	
No arquivo de saída, o índice remissivo deverá ser impresso em ordem alfabética.
