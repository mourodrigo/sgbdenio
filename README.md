#SGBDenio


Trabalho apresentado à disciplina de Banco de dados II para o Curso de Ciências da Computação da Universidade Federal da Fronteira Sul

----------
Implementar uma biblioteca para tratar a criação e manipulação de arquivos definidos pelo usuário. Não é necessário criar nenhuma interface apenas um arquivo de ajuda para descrever como utilizar a biblioteca. Requisitos:

- Um componente para a criação do banco de dados, este componente cria o BD lógico, ou seja, apenas indica que um banco de dados existe que tabelas serão criadas e subordinadas a este banco.

- Um componente (ou mais) onde o usuário passa como parâmetros a criação da tabela. Deve ser possível informar o nome da tabela, seus atributos (opcionais ou não) e chaves (primária e estrangeira). Os tipos de atributos devem ser, no mínimo, inteiro, ponto flutuante, caracter e data.

- Um componente que permita inserir tuplas em uma tabela existente.

- Um componente que permita excluir tuplas em uma tabela existente (garantir que seja possível informar um predicado de exclusão).

- Um componente que permita a alteração de valores de tuplas em uma tabela existente (garantir que seja possível informar um predicado de exclusão).

- Um componente que permita a consulta a tuplas de uma tabela existente. O predicado da consulta deve permitir o uso de todos os operadores relacionais (=, <>, <, >, <= e >=). A implementação de operadores lógicos será vista "com bom olhos".

A implementação dos predicados pode ser feita sem a necessidade de criar um reconhecedor de expressões, ou seja, não é necessário reconhecer "idade > 10 and idande <30". Fica a critério da equipe desenvolver uma abordagem de parâmetros que seja necessário apenas verificar se o atributo existe na tabela e os tipos envolvidos na condição sejam compatíveis.
A implementação de junçṍes será um extra.

Deve ser previsto um dicionário de dados para armazenar os metadados.
