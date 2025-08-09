<?php
require_once "conexao.php";
require_once "../Model/Pessoa.php";
class PessoaDAO{
    private $con;
    function __construct(){
            $this->con=Conexao::conectar();
    }

    function inserir(Pessoa $pessoa){
        $sql="insert into tbPessoa (NomeCompleto, Cidade,Bairro,Rua,Numero,CPF,Telefone,Login,Senha,Email,TipoPessoa) values('".$pessoa->getNomeCompleto()."','".$pessoa->getCidade()."','".$pessoa->getBairro()."','".$pessoa->getRua()."','".$pessoa->getNumero()."','".$pessoa->getCpf()."','".$pessoa->getTelefone()."','".$pessoa->getLogin()
            ."','".$pessoa->getSenha()."','".$pessoa->getEmail()."','".$pessoa->getTipoPessoa()."')";
        mysqli_query($this->con, $sql) or die (mysqli_error($this->con));
        header("Location:../View/relatorioGeralPessoa.php");
    }

    function listar(){
        $sql="select * from tbPessoa";
        $resultado = mysqli_query($this->con, $sql);

        $lista_pessoa = array();

        while ($row = mysqli_fetch_array($resultado)) {
            $pessoa = new Pessoa();
            $pessoa -> setNomeCompleto($row['NomeCompleto']);
            $pessoa -> setIdPessoa($row['idPessoa']);
            $pessoa -> setBairro($row['Bairro']);
            $pessoa -> setCidade($row['Cidade']);
            $pessoa -> setCpf($row['CPF']);
            $pessoa -> setEmail($row["Email"]);
            $pessoa -> setNumero($row['Numero']);
            $pessoa -> setRua($row['Rua']);
            $pessoa -> setLogin($row["Login"]);
            $pessoa -> setTelefone($row["Telefone"]);

            $lista_pessoa[] = $pessoa;
        }

        return $lista_pessoa;
    }

    function listarPorId($idPessoa){
        $sql = "select * from tbPessoa where idPessoa=".$idPessoa ;
        $resultado = mysqli_query($this->con, $sql);


        $row = mysqli_fetch_object($resultado);
        $pessoa = new Pessoa();
        $pessoa -> setNomeCompleto($row->NomeCompleto);
        $pessoa -> setBairro($row->Bairro);
        $pessoa -> setCidade($row->Cidade);
        $pessoa -> setCpf($row->CPF);
        $pessoa -> setEmail($row->Email);
        $pessoa -> setNumero($row->Numero);
        $pessoa -> setRua($row->Rua);
        $pessoa -> setLogin($row->Login);
        $pessoa -> setTelefone($row->Telefone);

        return $pessoa;
    }

    function alterar(Pessoa $pessoa){
        $sql="update tbPessoa set NomeCompleto='".$pessoa->getNomeCompleto()."', Cidade='".$pessoa->getCidade()."', Bairro='".$pessoa->getBairro()."', Rua='".$pessoa->getRua()."', Numero='".$pessoa->getNumero().
            "', CPF='".$pessoa->getCpf()."', Telefone='".$pessoa->getTelefone()."', Login='".$pessoa->getLogin()."', Email='".$pessoa->getEmail()."', TipoPessoa='".$pessoa->getTipoPessoa().
            "' where idPessoa ='".$pessoa->getIdPessoa()."'";
        mysqli_query($this->con, $sql) or die (mysqli_error($this->con));
        header("Location:../View/relatorioGeralPessoa.php");

    }

    function excluir($idPessoa){
        $sql="delete from tbPessoa where idPessoa=".$idPessoa;
        $msg="Erro ao excluir o registro<hr>";
        mysqli_query($this->con, $sql)or die ($msg.mysqli_error($this->con));
        header("Location:../View/relatorioGeralPessoa.php");

    }

    function listarPorIdVenda($idVenda){
        $sql = "select NomeCompleto,Login,Telefone,Email from tbPessoa inner join tbvenda on tbpessoa.idPessoa = tbvenda.idCliente where tbvenda.idVenda='".$idVenda."'";
        $resultado = mysqli_query($this->con, $sql);

        $row = mysqli_fetch_object($resultado);
        $pessoa = new Pessoa();
        $pessoa -> setNomeCompleto($row->NomeCompleto);
        $pessoa -> setEmail($row->Email);
        $pessoa -> setLogin($row->Login);
        $pessoa -> setTelefone($row->Telefone);

        return $pessoa;
    }

    function consultar($login,$senha){
        $sql="select * from tbPessoa where Login='".$login."' and Senha='".$senha."'";
        $query=mysqli_query($this->con, $sql);

        if($query!= false){
            $num=mysqli_num_rows($query) ;
        }else{
            $num=0;
        }
        if($num>0){
            return true;
        }else{
            return false;
        }
    }
}

?>
