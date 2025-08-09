package DAO;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

import model.Madeira;

public class TbMadeira implements IMadeira{

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
		selectSql = "SELECT * FROM tbmadeira";
		PreparedStatement preparedStatement = null;
		try {
			
			preparedStatement = conexao.prepareStatement(selectSql);
			
			ResultSet rs = preparedStatement.executeQuery();
			
			while(rs.next()) {
				int id_madeira = rs.getInt("id_madeira"); 
				double preco = rs.getDouble("preco_madeira");
				int tipo = rs.getInt("id_tipo");
				String nome = rs.getString("nome_madeira");
				
				System.out.println("ID: " + id_madeira
						+ " | Preco: " + preco
						+ " | Tipo: " + tipo
						+ " | Nome: " + nome);
			}
			
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("Erro ao tentar listar madeiras.");
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
	selectSql = "SELECT * FROM tbmadeira where id_madeira = ?";
	PreparedStatement preparedStatement = null;
	try {
		
		preparedStatement = conexao.prepareStatement(selectSql);
		preparedStatement.setInt(1, id);
		
		ResultSet rs = preparedStatement.executeQuery();
		
		while(rs.next()) {
			int id_madeira = rs.getInt("id_madeira"); 
			double preco = rs.getDouble("preco_madeira");
			int tipo = rs.getInt("id_tipo");
			String nome = rs.getString("nome_madeira");
			
			System.out.println("ID: " + id_madeira
					+ " | Preco: " + preco
					+ " | Tipo: " + tipo
					+ " | Nome: " + nome);
		}
		
	} catch (Exception e) {
		e.printStackTrace();
		System.out.println("Erro ao tentar listar madeiras.");
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

public void inserir(Madeira madeira) {

	Connection conexao = abrirConexao();
	PreparedStatement preparedStatement = null;
	String insertSql ="INSERT INTO tbmadeira (preco_madeira, id_tipo,nome_madeira) VALUES (?, ?, ?)";
	
	try {
		preparedStatement = conexao.prepareStatement(insertSql);
		
		preparedStatement.setDouble(1, madeira.getPreco());
		preparedStatement.setInt(2, madeira.getId_tipo());
		preparedStatement.setString(3, madeira.getNome());
		preparedStatement.executeUpdate();
		
		System.out.println("Madeira inserida com sucesso!");
		
	} catch(Exception e) {
		e.printStackTrace();
		System.out.println("Erro ao tentar inserir a madeira!");
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
	String deleteSql = "DELETE FROM tbmadeira WHERE id_madeira = ?";
	PreparedStatement preparedStatement = null;
	try {
		preparedStatement = conexao.prepareStatement(deleteSql);
		preparedStatement.setInt(1, id); 
		preparedStatement.executeUpdate();
		
		System.out.println("Madeira deletada.");
		
	} catch (Exception e) {
		e.printStackTrace();
		System.out.println("Erro ao tentar deletar a madeira.");
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

public void atualizar(Madeira madeira2,int id) {
	Connection conexao = abrirConexao();
	String updateSql = "UPDATE tbmadeira SET preco_madeira = ? , id_tipo = ?, nome_madeira =? where id_madeira=?";
	
	PreparedStatement preparedStatement = null;
	
	try {
		preparedStatement = conexao.prepareStatement(updateSql);
		preparedStatement.setDouble(1, madeira2.getPreco());
		preparedStatement.setInt(2, madeira2.getId_tipo());
		preparedStatement.setString(3, madeira2.getNome());
		preparedStatement.setInt(4, id);
		preparedStatement.executeUpdate();
		
		System.out.println("A Tabela madeira foi atualizado.");
		
	} catch (Exception e) {
		e.printStackTrace();
		System.out.println("Erro ao tentar atualizar madeira.");
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
