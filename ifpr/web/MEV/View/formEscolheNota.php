<?php
    require_once '../Controller/VendaController.php';
    require_once '../Controller/ValidacaoLogin.php';
    if(ValidacaoLogin::verificar()==true) {
        $vendaControl = new VendaController();
        $vendas = $vendaControl->listar();

        $num = count($vendas);

        if ($num > 0) {
            echo "<table border=1>";
            echo "<tr>";
            echo "<td>id</td>";
            echo "<td>Preco Total</td>";
            echo "<td>Escolha</td>";
            echo "</tr>";
            foreach ($vendas as $venda) {
                echo "<tr>";
                echo "<td>" . $venda->getIdVenda() . "</td>";
                echo "<td>" . $venda->getTotal() . "</td>";
                echo "<td><a href='NotaFiscal.php?id=" . $venda->getIdVenda() . "'>Escolher</a></td>";
                echo "</tr>";
            }
            echo "</table>";
            echo "<hr>Foram encontrados " . $num . "registros";
        } else {
            echo "Não há registros no banco de dados";
        }
    }
?>