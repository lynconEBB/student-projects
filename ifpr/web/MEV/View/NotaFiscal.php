<?php
    require_once '../Controller/VendaController.php';
    require_once '../Controller/ItemController.php';
    require_once '../Controller/ValidacaoLogin.php';
    if(ValidacaoLogin::verificar()==true) {
        $vendaControl = new VendaController();
        $nota = $vendaControl->gerarNotaFiscal($_GET["id"]);
        $itens = $nota[0];
        $produtos = $nota[1];
        $cliente = $nota[2];
        $venda = $nota[3];
        echo "<b>Nome do Cliente: </b>" . $cliente->getNomeCompleto() . "<br>";
        echo "<b>Data da Venda: </b>" . $venda->getDtVenda() . "<br>";
        echo "<b>Numero do Cartão: </b>" . $venda->getCartaoNum() . "<br>";
        echo "<b>Bandeira do Cartão: </b>" . $venda->getCartaoBand() . "<br><br>";
        echo "<table border=1>";
        echo "<tr>";
        echo "<th>Produto</th>";
        echo "<th>Preco Unitario</th>";
        echo "<th>Quantidade</th>";
        echo "<th>Preco Parcial</th>";
        echo "</tr>";
        echo "<tr>";

        $i = 0;
        while ($i < count($produtos)) {
            echo "<td>" . $produtos[$i]->getDescricao() . "</td>";
            echo "<td>" . $produtos[$i]->getPreco() . "</td>";
            echo "<td>" . $itens[$i]->getQtd() . "</td>";
            echo "<td>" . $itens[$i]->getPrecoParcial() . "</td>";
            echo "</tr>";
            $i++;
        }
        echo "<tr>";
        echo "<th colspan=2>Total</th>";
        echo "<th colspan=2 >" . $venda->getTotal() . "</th>";
        echo "</tr>";
        echo "</table>";
    }
?>