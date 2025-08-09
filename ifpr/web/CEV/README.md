# Carteira Eletrônica de Vacinação

Projeto para a criação de um aplicativo de controles de vacinações realizadas por um usuário, o aplicativo foi desenvolvido como forma  de aprendizado da linguagem PHP.

**Esta foi minha primeira aplicação em PHP por isso não está otimizada**

## Instação

Clone o repositório ou faça download do arquivo zip.

```bash
git clone https://github.com/lynconEBB/CEV
```

## Deploy

- Inicie um servidor web na pasta src (Exemplo com servidor imbutido do php).
```bash
php -S localhost:8000
```
- Crie uma base de dados mysql com o nome 'dbvacinacao'.
```mysql
create database dbvacinacao
```
- Navegue até o diretório raiz do projeto e importe a estrutura do banco de dados contida no arquivo db.sql.
````bash
mysql -u usuario -psenha dbvacincao < db.sql 
````
- Insira as credencias de acesso mysql no arquivo 'conexao.php'.
````php
$host="localhost";
$user="ususario";
$password="senha";
$banco="dbvacinacao";

$con = mysqli_connect($host,$user,$password,$banco);
return $con;
````
- Acesse o endereço 'localhost:8000/login.php' em seu browser para ter acesso ao sistema.


## Licença
[MIT](https://choosealicense.com/licenses/mit/)
