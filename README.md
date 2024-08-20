# Projeto de Redes de Computadores

Professor: Guilherme Werneck de Oliveira     
Integrantes: Beatriz R. Nahas, Rafael Correia Alves, Marjorie Ap. Cortez Daenecke, André Luiz Cecato Justus

## O Problema

  Alice tem passado por um problema diário com seu computador. Ao iniciá-lo,
sua data e seu _horário local_ aparecem todas as vezes como **01/01/2000** e **00:00:00**.
Após consultar um Técnico em Informática, foi informado que a bateria de seu
computador, auxiliar a CMOS, está sem energia e consequentemente _todas as
configurações da BIOS não são armazenadas quando seu computador é desligado_.
Além disso, todos os fornecedores para aquele modelo de placa-mãe não as
fabricam mais e por isso deverá aguardar a entrega de um novo computador.

   No entanto, Alice utiliza seu computador, que possui um _certificado de
autenticidade local_, para **assinar digitalmente seus documentos**. Uma possível saída
para esse problema, seria realizar o ajuste da data e do horário manualmente ao
ligar seu computador, mas Alice não possui o perfil de administrador para tal tarefa.
Alice te procurou e solicitou sua ajuda que prontamente se disponibilizou. A
solução proposta por você foi _desenvolver uma comunicação **cliente-servidor** entre
um computador que possui a data e a hora corretas e o computador dela, que
solicitará essas informações e **atualizará localmente**_.

### Como executar os códigos

Dentro de uma pasta com ambos os códigos `tcp.server.c` e `tcp.cliente.c`, abra um terminal para cada código para gerar os executores e o programa em si.


No primeiro terminal, digite o seguinte comando:
```
gcc -o tcp_server tcp_server.c
```
E logo em seguida, digite o próximo comando:
```
./tcp_server 8080
```
Após isso, mantenha o terminal do `tcp.server.c` reservado, e abra um novo terminal dentro da mesma pasta.


No segundo terminal, digite o seguinte comando:
```
gcc -o tcp_cliente tcp_cliente.c
```
E logo em seguuida, digite o próximo comando:
```
./tcp_cliente 127.0.0.1  8080
```
