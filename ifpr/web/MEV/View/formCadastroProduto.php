<?php
require_once '../Controller/ValidacaoLogin.php';
if(ValidacaoLogin::verificar()==true) {
    ?>
    <html>
    <head>
        <meta charset="utf-8">
        <title>Cadastro de produtos</title>
    </head>
    <body>
    <h3>Cadastro de produtos</h3>
    <form action="../Controller/ProdutoController.php" method="post" enctype="multipart/form-data">
        <input type="text" name="descricao" placeholder="Descricao Produto"><br>
        <input type="text" name="preco" placeholder="Valor do Produto"><br>
        <input type="text" name="qtdestoque" placeholder="Qtd em estoque"><br>
        <input type="hidden" name="acao" value="1">
        <input type="submit" value="Salvar">
    </form>
    </body>
    </html>
    <?php
}
?>
