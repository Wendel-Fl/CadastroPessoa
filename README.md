# Cadastro de Pessoa usando Árvore AVL

Este é um trabalho em C que implementa um sistema de cadastro de pessoa utilizando a estrutura de dados de Árvore AVL. A aplicação permite armazenar informações como nome, sobrenome, CEP e CPF de cada pessoa cadastrada.

## Requisitos
Antes de executar o programa, certifique-se de ter o seguinte instalado:
- Compilador C (como o GCC)
- Ambiente de desenvolvimento ou editor de texto para C (opcional)

## Estrutura de Dados
A estrutura de dados principal utilizada neste projeto é a Árvore AVL. A Árvore AVL é uma árvore de busca binária balanceada, na qual a altura das subárvores esquerda e direita de cada nó difere em, no máximo, uma unidade.

A estrutura Pessoa é utilizada para representar cada pessoa cadastrada e possui os seguintes campos:

- nome: armazena o nome da pessoa.
- primeiro sobrenome: armazena o primeiro sobrenome da pessoa.
- segundo sobrenome: armazena o segundo sobrenome da pessoa.
- cep: armazena o CEP da pessoa.
- cpf: armazena o CPF da pessoa.

## Funcionalidades
A aplicação oferece as seguintes funcionalidades:

1. Cadastrar Pessoa: Permite ao usuário inserir os dados de uma nova pessoa, como nome, sobrenome, CEP e CPF. Os dados são então adicionados à árvore AVL.

2. Buscar Pessoa: Permite ao usuário buscar uma pessoa cadastrada pelo seu nome, CPF ou CEP. A aplicação realiza uma busca na árvore AVL e exibe as informações da pessoa caso ela seja encontrada.

3. Listar Pessoas: Exibe todas as pessoas cadastradas, em ordem pre-order, inorder ou pos-order.

## Compilação e Execução
Para compilar o programa, utilize o seguinte comando:
```
make
```
Em seguida, execute o programa:
```
./projeto
```

## Contribuição
Sinta-se à vontade para contribuir com este projeto, fazendo melhorias ou adicionando novas funcionalidades. Basta fazer um fork do repositório e enviar um pull request.

Se você encontrou algum bug ou tem alguma sugestão, por favor, abra uma issue.

## Integrantes do grupo
- Carlos Eduardo Chiarella Braga
- Gabrielle Siqueira Moreira Leão
- João Victor Rosa Couto e Silva
- Robert Cardoso Cantares Martins
- Wendel Márcio de Oliveira Filho

### Observações
O arquivo input.txt é muito grande para ser colocado no repositório. Por isso, ele foi compactado em input.zip. Para executar o programa com o arquivo input.txt, basta descompactar o arquivo input.zip e executar o programa normalmente.