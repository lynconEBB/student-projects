<?php
    require_once '../Controller/PessoaController.php';
    require_once '../Controller/ValidacaoLogin.php';

    if(ValidacaoLogin::verificar()==true) {
        $pessoaControl = new PessoaController();
        $pessoa = $pessoaControl->listarPorId($_GET["id"]);
        ?>
        <meta charset="utf-8">
        <html>
        <head>
            <title>Cadastro de pessoas - Alteração </title>
        </head>
        <body>
        Cadastro de pessoas - Alteração

        <form action="../Controller/PessoaController.php" method="post">
            Nome: <input type="text" name="NomeCompleto" value="<?php echo $pessoa->getNomeCompleto() ?>"><br>
            E-mail: <input type="text" name="Email" value="<?php echo $pessoa->getEmail() ?>"><br>
            Login: <input type="text" name="Login" value="<?php echo $pessoa->getLogin() ?>"><br>
            CPF: <input type="text" name="CPF" value="<?php echo $pessoa->getCpf() ?>"><br>
            Cidade: <input type="text" name="Cidade" value="<?php echo $pessoa->getCidade() ?>"><br>
            Bairro: <input type="text" name="Bairro" value="<?php echo $pessoa->getBairro() ?>"><br>
            Rua: <input type="text" name="Rua" value="<?php echo $pessoa->getRua() ?>"><br>
            Numero: <input type="text" name="Numero" value="<?php echo $pessoa->getNumero() ?>"><br>
            Telefone: <input type="text" name="Telefone" value="<?php echo $pessoa->getTelefone() ?>"><br>
            <input type="hidden" name="TipoPessoa" value="1">
            <input type="hidden" name="acao" value="3">
            <input type="hidden" name="idPessoa" value="<?php echo $_REQUEST["id"] ?>">
            <input type="submit" value="Salvar">
        </form>
        </body>
        </html>
    <?php
    }
?>