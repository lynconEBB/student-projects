package model;

public class Empresa {
	private String nome;
	private String CNPJ;
	private int numero;
	private String bairro;
	private String cidade;
	private String telefone;
	private String rua;
	
	public Empresa(String nome, String rua, String telefone,String CNPJ, int numero, String bairro, String cidade) {
		this.nome = nome;
		this.rua = rua;
		this.telefone= telefone;
		this.CNPJ =	CNPJ;
		this.numero = numero;
		this.bairro = bairro;
		this.cidade = cidade;
	}

	public String getNome() {
		return nome;
	}

	public void setNome(String nome) {
		this.nome = nome;
	}

	public String getCNPJ() {
		return CNPJ;
	}

	public void setCNPJ(String cNPJ) {
		CNPJ = cNPJ;
	}

	public int getNumero() {
		return numero;
	}

	public void setNumero(int numero) {
		this.numero = numero;
	}

	public String getBairro() {
		return bairro;
	}

	public void setBairro(String bairro) {
		this.bairro = bairro;
	}

	public String getCidade() {
		return cidade;
	}

	public void setCidade(String cidade) {
		this.cidade = cidade;
	}

	public String getTelefone() {
		return telefone;
	}

	public void setTelefone(String telefone) {
		this.telefone = telefone;
	}

	public String getRua() {
		return rua;
	}

	public void setRua(String rua) {
		this.rua = rua;
	}
	
	

}