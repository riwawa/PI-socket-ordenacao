# PI - Cliente/Servidor TCP com ordenação

Projeto Integrador de Estrutura de Dados 2. O cliente envia números inteiros ao servidor por TCP, o servidor os ordena com QuickSort, devolve a lista ordenada e fecha a conexão.

Integrantes: _(Beatriz Lucena; Lucas Gomes)_

## Compilar

```sh
cc -Wall -Wextra -g -o servidor servidor.c ordenacao.c
cc -Wall -Wextra -g -o cliente cliente.c
```

## Executar

```sh
./servidor    # terminal 1 (porta 9002)
./cliente     # terminal 2
```

O cliente pede o IP do servidor (`127.0.0.1` na mesma máquina) e depois os números separados por espaço. Digite `sair` para encerrar.

```
> 45 12 78 34 5
=> NUMEROS ORDENADOS: 5 12 34 45 78
```

## Em duas máquinas

Mesma rede. No servidor, veja o IP com `ipconfig getifaddr en0`, rode `./servidor` e informe esse IP no cliente.
