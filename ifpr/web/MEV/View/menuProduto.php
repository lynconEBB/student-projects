<?php
require_once '../Controller/ValidacaoLogin.php';
if(ValidacaoLogin::verificar()==true) {
    echo "<a href='formCadastroProduto.php'>Cadastro de Produto</a><br>";
    echo " <a href='relatorioGeralProduto.php'>Relatório Produtos em Estoque</a>";
}
