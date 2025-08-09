<?php
    require_once '../Controller/ValidacaoLogin.php';
    if(ValidacaoLogin::verificar()==true) {
        ?>
        <html>
        <head>
            <title>Cadastro de pessoas</title>
            <meta charset="utf-8">
        </head>
        <body>
        Cadastro de pessoas<br>
        <form action="../Controller/PessoaController.php" method="post" enctype="multipart/form-data">
            Nome: <input type="text" name="NomeCompleto"><br>
            E-mail: <input type="text" name="Email"><br>
            Login: <input type="text" name="Login" placeholder="Nome de Usuário"><br>
            Senha: <input type="password" name="Senha"><br>
            CPF: <input type="text" name="CPF"><br>
            Cidade: <input type="text" name="Cidade"><br>
            Bairro: <input type="text" name="Bairro"><br>
            Rua: <input type="text" name="Rua"><br>
            Numero: <input type="text" name="Numero"><br>
            Telefone: <input type="text" name="Telefone"><br>
            <input type="hidden" name="TipoPessoa" value="1">
            <input type="hidden" name="acao" value="1">
            <input type="submit" value="Salvar">
        </form>
        </body>
        </html>
        <?php
    }
    ?>