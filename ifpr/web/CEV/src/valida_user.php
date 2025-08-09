<?PHP
    session_start();
    function sair (){
	    session_destroy();
	    header("Location: login.php");
	    exit();
    }

    require "tbPaciente/crudPaciente.php";
    $crudPac = new CrudPac();
    $query=$crudPac->listar();

    if($_REQUEST["action"] == "login") {
        $obj=mysqli_fetch_object($query);
        do {
            if($_REQUEST["CAMPO_USUARIO"]==$obj->Nome && $_REQUEST["CAMPO_SENHA"]==$obj->Senha){
                $_SESSION["usuario"] = $_POST["CAMPO_USUARIO"];
                $_SESSION["autenticado"] = TRUE;
                header("Location: menu.php");
            }else{
                echo "Seu nome de usuário ou senha estão incorretos.";
            }
        }while($obj=mysqli_fetch_object($query));
    }else{ 
        if (isset ($_GET["acao"])){
            sair();
        }
    }
 ?>
 <html lang="pt-br">
    <BR><BR>
    <a href="login.php"><<--Retornar ao login </a>
    <BR>
 </html>

