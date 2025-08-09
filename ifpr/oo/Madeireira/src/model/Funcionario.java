package model;

public class Funcionario {
	private String nome;
	private String CPF;
	private String RG;
	private String rua;                          
	private String cidade;
	private int numero;
	private String bairro;
	private String telefone;
	
	public Funcionario(String nome, String CPF, String RG,String rua, String cidade, int numero, String bairro,String telefone) {
		this.nome = nome;
		this.rua = rua;
		this.telefone= telefone;
		this.CPF =	CPF;
		this.numero = numero;
		this.bairro = bairro;
		this.cidade = cidade;
		this.RG=RG;
	}

	public String getNome() {
		return nome;
	}

	public void setNome(String nome) {
		this.nome = nome;
	}

	public String getCPF() {
		return CPF;
	}

	public void setCPF(String cPF) {
		CPF = cPF;
	}

	public String getRG() {
		return RG;
	}

	public void setRG(String rG) {
		RG = rG;
	}

	public String getRua() {
		return rua;
	}

	public void setRua(String rua) {
		this.rua = rua;
	}

	public String getCidade() {
		return cidade;
	}

	public void setCidade(String cidade) {
		this.cidade = cidade;
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

	public String getTelefone() {
		return telefone;
	}

	public void setTelefone(String telefone) {
		this.telefone = telefone;
	}
}
