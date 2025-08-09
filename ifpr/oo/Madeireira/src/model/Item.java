package model;

public class Item {
	private double precomad;
	private double preco;
	private int id_venda;
	private int id_madeira;
	private double comprimento;
	private int quantidade;
	
	public Item(double precomad ,double preco, int id_v, int id_m, double comp,int qtd) {
		this.precomad= precomad;
		this.preco= preco;
		this.id_venda=id_v;
		this.id_madeira=id_m;
		this.comprimento=comp;
		this.quantidade=qtd;
	}

	public double getPrecomad() {
		return precomad;
	}

	public void setPrecomad(double precomad) {
		this.precomad = precomad;
	}

	public double getPreco() {
		return preco;
	}

	public void setPreco(double preco) {
		this.preco = preco;
	}

	public int getId_venda() {
		return id_venda;
	}

	public void setId_venda(int id_venda) {
		this.id_venda = id_venda;
	}

	public int getId_madeira() {
		return id_madeira;
	}

	public void setId_madeira(int id_madeira) {
		this.id_madeira = id_madeira;
	}

	public double getComprimento() {
		return comprimento;
	}

	public void setComprimento(double comprimento) {
		this.comprimento = comprimento;
	}

	public int getQuantidade() {
		return quantidade;
	}

	public void setQuantidade(int quantidade) {
		this.quantidade = quantidade;
	}
	


}
