<?php
    require_once '../Controller/ProdutoController.php';
    require_once '../Controller/ValidacaoLogin.php';
    if(ValidacaoLogin::verificar()==true) {
        $produtoControl = new ProdutoController();
        $produtos = $produtoControl->listar();
        $num = count($produtos);

        if ($num > 0) {
            echo "<table border=1>";
            echo "<tr>";
            echo "<td>id</td>";
            echo "<td>Descrição</td>";
            echo "<td>Preço</td>";
            echo "<td>Quantidade Estoque</td>";
            echo "<td>Ações</td>";
            echo "</tr>";

            foreach ($produtos as $produto) {
                echo "<td>" . $produto->getIdProduto() . "</td>";
                echo "<td>" . $produto->getDescricao() . "</td>";
                echo "<td>" . $produto->getPreco() . "</td>";
                echo "<td>" . $produto->getQrdestoque() . "</td>";
                echo "<td><a href='../Controller/ProdutoController.php?acao=2&id=" . $produto->getIdProduto() . "'>Excluir</a>";
                echo "|<a href='formAlterarProduto.php?id=" . $produto->getIdProduto() . "'>Alterar</a>";
                echo "</td></tr>";
            }
            echo "<table>";
            echo "<hr>Foram encontrados " . $num . " registros";
        } else {
            echo "Não há registros no banco de dados";
        }
    }
?>