package model;

public class Madeira {
	private double preco;
	private int id_tipo;
	private String nome;
	
	public Madeira(double preco, int id_tipo, String nome) {
		this.preco=preco;
		this.id_tipo=id_tipo;
		this.nome=nome;
	}

	public double getPreco() {
		return preco;
	}

	public void setPreco(double preco) {
		this.preco = preco;
	}


	public int getId_tipo() {
		return id_tipo;
	}

	public void setId_tipo(int id_tipo) {
		this.id_tipo = id_tipo;
	}

	public String getNome() {
		return nome;
	}

	public void setNome(String nome) {
		this.nome = nome;
	}
	
}
