<?php
    require_once '../Controller/ValidacaoLogin.php';
    if(ValidacaoLogin::verificar()==true) {
        ?>
        <html>
        <head>
            <meta charset="utf-8">
            <title>Menu Mimo e Você</title>
        </head>
        <body>
        <h3><a href="menuPessoa.php">Menu Cliente</a></h3><br>
        <h3><a href="menuProduto.php">Menu Produto</a></h3><br>
        <h3><a href="menuVenda.php">Menu Venda</a></h3><br><br>
        <a href="../Controller/ValidacaoLogin.php?action=sair">Sair</a><BR>
        </body>
        </html>
        <?php
    }
    ?>