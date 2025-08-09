package DAO;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.Scanner;
import model.Empresa;

public class TbEmpresa implements IEmpresa {
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
			selectSql = "SELECT * FROM tbempresa";
			PreparedStatement preparedStatement = null;
			try {
				
				preparedStatement = conexao.prepareStatement(selectSql);
				
				ResultSet rs = preparedStatement.executeQuery();
				
				while(rs.next()) {
					int id_empresa = rs.getInt("id_empresa"); 
					String cnpj = rs.getString("CNPJ_empresa");
					String rua = rs.getString("rua_empresa");
					String bairro = rs.getString("bairro_empresa");
					String cidade = rs.getString("cidade_empresa");
					String nome = rs.getString("nome_empresa");
					
					System.out.println("ID: " + id_empresa
							+ " | CNPJ: " + cnpj
							+ " | Rua: " + rua
							+ " | Bairro: " + bairro
							+ " | Cidade: " + cidade
							+ " | Nome:  " + nome);
				}
				
			} catch (Exception e) {
				e.printStackTrace();
				System.out.println("Erro ao tentar listar empresas.");
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
		}else {
		selectSql = "SELECT * FROM tbempresa where id_empresa = ?";
		PreparedStatement preparedStatement = null;
		try {
			
			preparedStatement = conexao.prepareStatement(selectSql);
			preparedStatement.setInt(1, id);
			
			ResultSet rs2 = preparedStatement.executeQuery();
			
			while(rs2.next()) {
				int id_empresa = rs2.getInt("id_empresa"); 
				String cnpj = rs2.getString("CNPJ_empresa");
				String rua = rs2.getString("rua_empresa");
				String bairro = rs2.getString("bairro_empresa");
				String cidade = rs2.getString("cidade_empresa");
				String nome = rs2.getString("nome_empresa");
				
				System.out.println("ID: " + id_empresa
						+ " | CNPJ: " + cnpj
						+ " | Rua: " + rua
						+ " | Bairro: " + bairro
						+ " | Cidade: " + cidade
						+ " | Nome:  " + nome);
			}
			
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("Erro ao tentar listar Empresas.");
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

	public void inserir(Empresa empresa) {

		Connection conexao = abrirConexao();
		PreparedStatement preparedStatement = null;
		String insertSql ="INSERT INTO tbempresa (CNPJ_empresa,rua_empresa,numero_empresa,bairro_empresa,cidade_empresa,nome_empresa,telefone_empresa) VALUES (?, ?, ?,?,?,?,?)";
		
		try {
			preparedStatement = conexao.prepareStatement(insertSql);
			
			preparedStatement.setString(1, empresa.getCNPJ());
			preparedStatement.setString(2, empresa.getRua());
			preparedStatement.setInt(3, empresa.getNumero());
			preparedStatement.setString(4, empresa.getBairro());
			preparedStatement.setString(5, empresa.getCidade());
			preparedStatement.setString(6, empresa.getNome());
			preparedStatement.setString(7, empresa.getTelefone());
			
			
			preparedStatement.executeUpdate();
			
			System.out.println("Empresa inserida com sucesso!");
			
		} catch(Exception e) {
			e.printStackTrace();
			System.out.println("Erro ao tentar inserir a Empresa!");
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
		String deleteSql = "DELETE FROM tbempresa WHERE id_empresa = ?";
		PreparedStatement preparedStatement = null;
		try {
			preparedStatement = conexao.prepareStatement(deleteSql);
			preparedStatement.setInt(1, id); 
			preparedStatement.executeUpdate();
			
			System.out.println("Empresa deletada.");
			
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("Erro ao tentar deletar Empresa.");
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
	
	public void atualizar(Empresa empresa2,int id) {
		Connection conexao = abrirConexao();
		String updateSql = "UPDATE tbempresa SET CNPJ_empresa = ? , rua_empresa = ?, numero_empresa =?, bairro_empresa=? , cidade_empresa=?, nome_empresa=?,telefone_empresa=? WHERE id_empresa = ?";
		
		PreparedStatement preparedStatement = null;
		
		try {
			preparedStatement = conexao.prepareStatement(updateSql);
			preparedStatement.setString(1, empresa2.getCNPJ());
			preparedStatement.setString(2, empresa2.getRua());
			preparedStatement.setInt(3, empresa2.getNumero());
			preparedStatement.setString(4, empresa2.getBairro());
			preparedStatement.setString(5, empresa2.getCidade());
			preparedStatement.setString(6, empresa2.getNome());
			preparedStatement.setString(7, empresa2.getTelefone());
			preparedStatement.setInt(8, id);
			preparedStatement.executeUpdate();
			
			System.out.println("A Tabela empresa foi atualizado.");
			
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("Erro ao tentar atualizar empresa.");
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


