package DAO;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

import model.Entregador;

public class TbEntregador implements IEntregador{
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
		selectSql = "SELECT * FROM tbentregador";
		PreparedStatement preparedStatement = null;
		try {
			
			preparedStatement = conexao.prepareStatement(selectSql);
			
			ResultSet rs = preparedStatement.executeQuery();
			
			while(rs.next()) {
				int id_func = rs.getInt("id_func"); 
				String carteira = rs.getString("carteira_de_motorista");
				String veiculo = rs.getString("veiculo_entregador");
				
				System.out.println("ID: " + id_func
						+ " | Nº Carteira de Motorita: "+ carteira 
						+ " | Veiculo: " + veiculo);
			}
			
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("Erro ao tentar listar entregadores.");
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
	selectSql = "SELECT * FROM tbentregador where id_func = ?";
	PreparedStatement preparedStatement = null;
	try {
		
		preparedStatement = conexao.prepareStatement(selectSql);
		preparedStatement.setInt(1, id);
		
		ResultSet rs = preparedStatement.executeQuery();
		
		while(rs.next()) {
			int id_func = rs.getInt("id_func"); 
			String carteira = rs.getString("carteira_de_motorista");
			String veiculo = rs.getString("veiculo_entregador");
			
			System.out.println("ID: " + id_func
					+ " | Nº Carteira de Motorita: "+ carteira 
					+ " | Veiculo: " + veiculo);
		}
		
	} catch (Exception e) {
		e.printStackTrace();
		System.out.println("Erro ao tentar listar entregadores.");
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

public void inserir(Entregador ent) {

	Connection conexao = abrirConexao();
	PreparedStatement preparedStatement = null;
	String insertSql ="INSERT INTO tbentregador (id_func,carteira_de_motorista,veiculo_entregador) VALUES (?, ?, ?)";
	
	try {
		preparedStatement = conexao.prepareStatement(insertSql);
		
		preparedStatement.setInt(1, ent.getId_func());
		preparedStatement.setString(2, ent.getCarteira());
		preparedStatement.setString(3, ent.getVeiculo());
		preparedStatement.executeUpdate();
		
		System.out.println("Entregador inserido com sucesso!");
		
	} catch(Exception e) {
		e.printStackTrace();
		System.out.println("Erro ao tentar inserir o entregador!");
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
	String deleteSql = "DELETE FROM tbentregador WHERE id_func = ?";
	PreparedStatement preparedStatement = null;
	try {
		preparedStatement = conexao.prepareStatement(deleteSql);
		preparedStatement.setInt(1, id); 
		preparedStatement.executeUpdate();
		
		System.out.println("Entregador deletado.");
		
	} catch (Exception e) {
		e.printStackTrace();
		System.out.println("Erro ao tentar deletar o entregador.");
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

public void atualizar(Entregador ent2,int id) {
	Connection conexao = abrirConexao();
	String updateSql = "UPDATE tbentregador SET carteira_de_motorista = ? , veiculo_entregador = ? where id_func = ?";
	
	PreparedStatement preparedStatement = null;
	
	try {	
		preparedStatement = conexao.prepareStatement(updateSql);
		preparedStatement.setString(1, ent2.getCarteira());
		preparedStatement.setString(2, ent2.getVeiculo());
		preparedStatement.setInt(3, id);
		preparedStatement.executeUpdate();
		
		System.out.println("A Tabela entregador foi atualizado.");
		
	} catch (Exception e) {
		e.printStackTrace();
		System.out.println("Erro ao tentar atualizar entregador.");
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
