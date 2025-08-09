package DAO;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

import model.Funcionario;

public class TbFuncionario implements IFuncionario{
	public static final String DB_URL = "jdbc:mysql://localhost:3306/madeireira";
	public static final String DB_USUARIO = "root";
	public static final String DB_SENHA = "";
	String selectSql;
	
	private Connection abrirConexao() {
		Connection conexao = null;
		try {conexao = DriverManager
				.getConnection(DB_URL, DB_USUARIO,DB_SENHA);
			System.out.println("Conexão realizada com sucesso!");
		} catch(Exception e) {
			e.printStackTrace();
			System.out.println("==============================");
			System.out.println("Erro na conexão com o banco de dados!");
		}
		return conexao;
	}

public void listar(int id) {
	Connection conexao = abrirConexao();
	
	if(id == 0) {
		selectSql = "SELECT * FROM tbfuncionario";
		PreparedStatement preparedStatement = null;
		try {
			
			preparedStatement = conexao.prepareStatement(selectSql);
			
			ResultSet rs = preparedStatement.executeQuery();
			
			while(rs.next()) {
				int id_func = rs.getInt("id_func"); 
				String nome = rs.getString("nome_func");
				String cpf= rs.getString("CPF_func");
				String rg = rs.getString("RG_func");
				String rua = rs.getString("rua_func");
				String cidade = rs.getString("cidade_func");
				int numero = rs.getInt("numero_func"); 
				String bairro = rs.getString("bairro_func");
				String telefone = rs.getString("telefone_func");
				
				
				System.out.println("ID: " + id_func
						+ " |Nome: "+ nome
						+ " | CPF: " + cpf
						+ " | RG: " + rg
						+ " | Rua: " + rua
						+ " | Cidade: " + cidade
						+ " | Numero:  " + numero
						+ " | Bairro: " + bairro
						+ " | Telefone: " + telefone);
			}
			
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("Erro ao tentar listar funcionarios.");
		} finally {
			try {
				preparedStatement.close();
				conexao.close();
			} catch (Exception e) {
				e.printStackTrace();
				System.out.println("Erro ao tentar fechar conexões com o banco de dados!");
			}
		}
	}else {
	selectSql = "SELECT * FROM tbfuncionario where id_func = ?";
	PreparedStatement preparedStatement = null;
	try {
		
		preparedStatement = conexao.prepareStatement(selectSql);
		preparedStatement.setInt(1, id);
		
		ResultSet rs = preparedStatement.executeQuery();
		
		while(rs.next()) {
			int id_func = rs.getInt("id_func"); 
			String nome = rs.getString("nome_func");
			String cpf= rs.getString("CPF_func");
			String rg = rs.getString("RG_func");
			String rua = rs.getString("rua_func");
			String cidade = rs.getString("cidade_func");
			int numero = rs.getInt("numero_func"); 
			String bairro = rs.getString("bairro_func");
			String telefone = rs.getString("telefone_func");
			
			
			System.out.println("ID: " + id_func
					+ " |Nome: "+ nome
					+ " | CPF: " + cpf
					+ " | RG: " + rg
					+ " | Rua: " + rua
					+ " | Cidade: " + cidade
					+ " | Numero:  " + numero
					+ " | Bairro: " + bairro
					+ " | Telefone: " + telefone);
		}
		
	} catch (Exception e) {
		e.printStackTrace();
		System.out.println("Erro ao tentar listar funcionario(s).");
	} finally {
		try {
			preparedStatement.close();
			conexao.close();
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("Erro ao tentar fechar conexões "
					+ "com o banco de dados!");
		}
	}
}
	
}

public void inserir(Funcionario func) {

	Connection conexao = abrirConexao();
	PreparedStatement preparedStatement = null;
	String insertSql ="INSERT INTO tbfuncionario (nome_func,CPF_func,RG_func,rua_func,cidade_func,numero_func,bairro_func,telefone_func) VALUES (?, ?, ?,?,?,?,?,?)";
	
	try {
		preparedStatement = conexao.prepareStatement(insertSql);
		
		preparedStatement.setString(1, func.getNome());
		preparedStatement.setString(2, func.getCPF());
		preparedStatement.setString(3, func.getRG());
		preparedStatement.setString(4, func.getRua());
		preparedStatement.setString(5, func.getCidade());
		preparedStatement.setInt(6, func.getNumero());
		preparedStatement.setString(7, func.getBairro());
		preparedStatement.setString(8, func.getTelefone());
		
		
		preparedStatement.executeUpdate();
		
		System.out.println("Funcionario inserido com sucesso!");
		
	} catch(Exception e) {
		e.printStackTrace();
		System.out.println("Erro ao tentar inserir o Funcionario!");
	} finally {
		try {
			preparedStatement.close();
			conexao.close();
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("Erro ao tentar fechar conexões com o banco de dados!");
		}
	}
	
}

public void deletar(int id) {
	Connection conexao = abrirConexao();
	String deleteSql = "DELETE FROM tbfuncionario WHERE id_func = ?";
	PreparedStatement preparedStatement = null;
	try {
		preparedStatement = conexao.prepareStatement(deleteSql);
		preparedStatement.setInt(1, id); 
		preparedStatement.executeUpdate();
		
		System.out.println("funcionario deletado.");
		
	} catch (Exception e) {
		e.printStackTrace();
		System.out.println("Erro ao tentar deletar o funcionario.");
	} finally {
		try {
			preparedStatement.close();
			conexao.close();
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("Erro ao tentar fechar conexões com o banco de dados!");
		}
	}
	
}

public void atualizar(Funcionario func2,int id) {
	Connection conexao = abrirConexao();
	String updateSql = "UPDATE tbfuncionario SET nome_func = ? , CPF_func = ?, RG_func =?, rua_func=? , cidade_func=?, numero_func=?,bairro_func=?,telefone_func=? WHERE id_func = ?";
	
	PreparedStatement preparedStatement = null;
	
	try {
		preparedStatement = conexao.prepareStatement(updateSql);
		preparedStatement.setString(1, func2.getNome());
		preparedStatement.setString(2, func2.getCPF());
		preparedStatement.setString(3, func2.getRG());
		preparedStatement.setString(4, func2.getRua());
		preparedStatement.setString(5, func2.getCidade());
		preparedStatement.setInt(6, func2.getNumero());
		preparedStatement.setString(7, func2.getBairro());
		preparedStatement.setString(8, func2.getTelefone());
		preparedStatement.setInt(9, id);
		preparedStatement.executeUpdate();
		
		System.out.println("A Tabela Funcionario foi atualizado.");
		
	} catch (Exception e) {
		e.printStackTrace();
		System.out.println("Erro ao tentar atualizar o funcionario.");
	} finally {
		try {
			preparedStatement.close();
			conexao.close();
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("Erro ao tentar fechar conexões com o banco de dados!");
		}
	}
}
}
