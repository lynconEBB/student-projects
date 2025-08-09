<?php
    require_once '../Controller/ProdutoController.php';
    require_once '../Controller/ValidacaoLogin.php';

    if(ValidacaoLogin::verificar()==true) {
        $produtoControl = new ProdutoController();
        $produto = $produtoControl->listarPorId($_REQUEST["id"]);
        ?>
        <meta charset="utf-8">
        <html>
        <head>
            <title>Cadastro de Produtos - Alteração </title>
        </head>
        <body>
        Cadastro de Produtos - Alteração
        <form action="../Controller/ProdutoController.php" method="post">
            <input type="text" name="descricao" value="<?php echo $produto->getDescricao(); ?>"><br>
            <input type="text" name="preco" value="<?php echo $produto->getPreco(); ?>"><br>
            <input type="text" name="qtdestoque" value="<?php echo $produto->getQrdestoque(); ?>"><br>
            <input type="hidden" name="acao" value="3">
            <input type="hidden" name="idProduto" value="<?php echo $_REQUEST["id"] ?>">
            <input type="submit" value="Salvar">
        </form>
        </body>
        </html>
    <?php
}
?>
