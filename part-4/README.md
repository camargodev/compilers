# Etapa 4 - Análise Semântica

### Requisitos

## Construir uma tabela de símbolos

No arquivo ```table.h``` estão declaradas as estruturas necessárias relacionadas à tabela de símbolos.
Primeiramente, há a ```table_line```, que corresponde a uma linha de uma tabela de símbolos.
Já a tabela em si é representada pela estrutura ```table```, que contém um conjunto de linhas.
Por fim, há a ```table_stack```, que contém um conjunto de tabelas (uma tabela por escopo aberto).
Além disso, existem algumas estruturas auxiliares, como:
- ```func_arg```, que contém os dados de um parâmetro de ums função. 
- ```user_type_field```, que contém os dados de um campo em um tipo de usuário.
Uma linha de tabela pode possuir n argumentos (se for função) ou n campos (se for um tipo de usuário).
Por fim, também foi inserido o conceito de categoria. Cada símbolo possui uma categoria, podendo ser
- ```USER_TYPE```, ```VARIABLE```, ```FUNCTION``` ou ```ARRAY```.

## Verificação de Declarações

A declaração de um identificador só pode ser dada quando aquele identificador ainda não foi declarado.
A exceção é se ele está declarado em escopos diferentes (um ```int x``` global e um local são permitidos).
No caso de dupla declaração, é disparado o erro ```ERR_DECLARED```, como mostrado abaixo:
```
int declaration_line = is_declared_on_current_table(stack, $2->value.v_string);
int param_type = get_param_type($2->value.v_string, function.args_counter, function.function_args);
if(declaration_line != NOT_DECLARED || param_type != NOT_DECLARED)
	set_error(ERR_DECLARED);
...
```
O uso de um identificador só pode ser dado se ele já foi declarado, sem exceções.
No caso de falta de declaração, é disparado ```ERR_UNDECLARED```, como abaixo:
```
...
if(is_declared(stack, $1->value.v_string) == NOT_DECLARED)
	set_error(ERR_UNDECLARED);
```


## Uso correto de identificadores

Uma função ```x()``` só pode ser usada como função. O mesmo vale para arrays, variáveis e tipos de usuário.
Para essa validação, é usada a categoria já explicada. Um exemplo de validação é:
```
if (category != id_category) {
	switch (category) {
		case FUNCTION:
			set_error(ERR_FUNCTION); break;
		case USER_TYPE:
			set_error(ERR_USER); break;
		case ARRAY:
			set_error(ERR_VECTOR); break;
		case VARIABLE:
			set_error(ERR_VARIABLE); break;
	}
}
```

## Verificação de tipo e tamanho dos nós da AST

Na estrutura do nó da árvore (declarada em ```tree.h```), foi adicionado o campo ```type```.
Quando necessário, esse campo é preenchido informando o tipo do nó.
Abaixo um exemplo de definição do tipo de uma expressão, usando inferência:
```
if ($1->type == $3->type) {
	$$->type = $1->type;
} else {
	int type = infer($1->type, $3->type);
	$$->type = type;

	if ($1->type == type) {
		$3->conversion = get_conversion(type, $3->type);
	} else {
		$1->conversion = get_conversion(type, $1->type);
	}
}
```
Acima, se o tipo dos dois operandos for igual, então o tipo da cabeça será aquele tipo.
Se não, é feita a inferência e marcada a conversão (falada abaixo).
A função infer(...) utilizada recebe dois tipos e infere o tipo da expressão.
Essa função já dispara erros quando avalia que a combinação dos dois tipos é inválida.

Quanto à tamanho, são destacados os casos não triviais:
- definição de tamanho de array = tamanho do tipo * número de elementos.
- definição de tamanho de string = feito dinamicamente com a função ```update_string_size(...)```.

## Anotação de conversão implícita

Outro campo também foi adicionado no nó da árvore: o ```conversion```, que marca a conversão feita no nodo.
Para isso, as conversões possíveis estão definidas em ```conversions.h```.
Nesse mesmo arquivo, está declarada a função ```get_conversion(...)```, que recebe dois tipos e retorna a conversão do segundo tipo para o primeiro.
O exemplo de marcação de conversão foi dado anteriormente.

## Argumentos de funções

A checagem de número e tipos dos argumentos é feita usando o auxílio da estrutura ```func_call_arg```.
Os argumentos usados são salvos e depois o número/tipos dos argumentos é comparado com o esperado pela função.

## Verificação dos tipos em comandos

Em todos os comandos, há uma checagem sobre o tipo esperado.
Além disso, caso possível/necessário, é realizada/marcada a conversão.