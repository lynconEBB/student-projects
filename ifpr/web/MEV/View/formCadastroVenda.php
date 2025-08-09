<?php
require_once '../Controller/ValidacaoLogin.php';
if(ValidacaoLogin::verificar()==true) {
    ?>
    <meta charset="utf-8">
    <html>
    <head>
        <title>Cadastro da Venda</title>
    </head>
    <body>
    <h1> Escolha o Cliente</h1>
    <?php

    require_once '../Controller/PessoaController.php';
    $pessoaControl = new PessoaController();
    $pessoas = $pessoaControl->listar();

    echo "<form action='../Controller/VendaController.php' method='post'  enctype='multipart/form-data'>";
    echo "<table border=1>";
    echo "<tr>";
    echo "<td>id</td>";
    echo "<td>Login</td>";
    echo "<td>Nome</td>";
    echo "<td>Email</td>";
    echo "<td>Cidade</td>";
    echo "<td>Bairro</td>";
    echo "<td>Rua</td>";
    echo "<td>Numero</td>";
    echo "<td>CPF</td>";
    echo "<td>Telefone</td>";
    echo "<td>Escolha</td>";
    echo "</tr>";

    foreach ($pessoas as $pessoa) {
        echo "<tr>";
        echo "<td>" . $pessoa->getIdPessoa() . "</td>";
        echo "<td>" . $pessoa->getLogin() . "</td>";
        echo "<td>" . $pessoa->getNomeCompleto() . "</td>";
        echo "<td>" . $pessoa->getEmail() . "</td>";
        echo "<td>" . $pessoa->getCidade() . "</td>";
        echo "<td>" . $pessoa->getBairro() . "</td>";
        echo "<td>" . $pessoa->getRua() . "</td>";
        echo "<td>" . $pessoa->getNumero() . "</td>";
        echo "<td>" . $pessoa->getCPF() . "</td>";
        echo "<td>" . $pessoa->getTelefone() . "</td>";
        echo "<td><input type='radio' name='idPessoa' value='" . $pessoa->getIdPessoa() . "'></td>";
        echo "</tr>";
    }
    echo "</table><br><br><br>";

    require_once '../Controller/ProdutoController.php';
    $produtoControl = new ProdutoController();
    $produtos = $produtoControl->listar();
    echo "<h1> Escolha o Produto</h1>";
    echo "<table border=1>";
    echo "<tr>";
    echo "<td>ID</td>";
    echo "<td>Descrição</td>";
    echo "<td>Preço</td>";
    echo "<td>Quantidade Estoque</td>";
    echo "<td>Seleção</td>";
    echo "<td>Quantidade</td>";
    echo "</tr>";
    echo "<tr>";
    $pos = 0;

    foreach ($produtos as $produto) {
        echo "<td>" . $produto->getIdProduto() . "</td>";
        echo "<td>" . $produto->getDescricao() . "</td>";
        echo "<td>" . $produto->getPreco() . "</td>";
        echo "<td>" . $produto->getQrdEstoque() . "</td>";
        echo "<td><input type='checkbox' name='produtos[]' value='" . $produto->getIdProduto() . "-" . $pos . "-" . $produto->getPreco() . "-" . $produto->getQrdEstoque() . "'></td> ";
        echo "<td><input type='number' name='Quantidade[]' value='0' max='" . $produto->getQrdEstoque() . "'></td>";
        echo "</tr>";
        $pos++;
    }
    echo "<table><br>";
    echo "<h1>Dados da Venda</h1>";
    echo 'Data Venda: <INPUT type="date"  name= "dtVenda">';
    echo '<BR> Bandeira Cartão:  <INPUT type="text"  name="cartaoBand">';
    echo '<BR> Número do Cartao: <INPUT type="text"  name="cartaoNum">';
    echo "<input type='hidden' name='escolha' value='1'>";
    echo "<br><input type='submit' value='Realizar Venda'>";
    echo "</form>";
    ?>
    </body>
    </html>
    <?php
}
?>