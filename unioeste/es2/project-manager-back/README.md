# Gerenciador de projetos (Back-end)

API Back-end do primeiro projeto de Engenharia de Software 2 do curso de Ciência da Computação da UNIOESTE.

## Tecnologias
- Spring Boot
- Spring Data JPA
- Postgres Driver
- Spring Web
- Spring Boot Dev Tools

## Implementação

Este projeto se trata de uma API RESTful simples utilizando o framework Spring Boot e o mapeamento de entidades para o banco de dados com Spring Data JPA. A escolha do Spring Boot visa agilizar o desenvolvimento e a do Spring Data JPA, facilitar o acesso e a manipulação de dados.

O primeiro passo para a implementação foi mapear as entidades do domínio. As entidades representam os objetos principais da aplicação, e o Spring Boot utiliza a anotação @Entity para indicar que uma classe é uma entidade persistente. As propriedades da classe podem ser anotadas com @Column, @Id, e outras, para definir suas características no banco de dados. Todas as classes de entitidade podem ser encontradas no pacote ```entities```.

```java
@Entity
public class Profissional {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    @Column(nullable = false)
    private String nome;

    // Outras propriedades e métodos
}
```

Após realizar o mapeamento foi necessário criar os repositórios para realizar operações de persistência no banco de dados. Os repositórios são interfaces que estendem a interface JpaRepository do Spring Data. Essa abordagem proporciona métodos prontos para realizar operações comuns, como salvar, buscar e excluir registros.Todas as interfaces de repositorios podem ser encontradas no pacote ```repositories```.

```java
public interface ProfissionalRepository extends JpaRepository<Profissional, Long> {
    List<Profissional> findByNome(String nome);
}
```

Por fim, foram criados os controllers, sendo estes responsáveis por receber as requisições HTTP, processá-las e interagir com os repositórios para buscar ou modificar os dados. A anotação @RestController indica que a classe é um controlador, e os métodos são mapeados para endpoints utilizando anotações como @GetMapping, @PostMapping, entre outras.


```java
@RestController
@RequestMapping("/api/profissionais")
public class ProfissionalController {
    @Autowired
    private ProfissionalRepository profissionalRepository;

    @GetMapping
    public List<Profissional> listarProfissionais() {
        return profissionalRepository.findAll();
    }

    @PostMapping
    public ResponseEntity<Profissional> criarProfissional(@RequestBody Profissional profissional) {
        Profissional novoProfissional = profissionalRepository.save(profissional);
        return new ResponseEntity<>(novoProfissional, HttpStatus.CREATED);
    }

    // Outros métodos para atualizar, deletar, ou buscar profissionais
}
```

## Instalação e Execução

Para executar o projeto é necessário ter os seguintes programas instalados:

- JDK 19+

Para executar o progr

```bash
npm run dev
```
Também é possivel gerar a imagem docker do projeto utilizando o seguinte comando:

```bash
docker build . -t proj/back
```

O arquivo ```docker-compose.yml``` está configurado de modo a criar um container para a API back-end, um container para a aplicação front-end e um container para o banco de dados, todos se comunindo por meio de uma rede em modo bridge. Após gerar as imagens dos containers certifique-se de executar o comando:

```bash
docker-compose up -d
```

### Autores
- Felipe Asano
- Lyncon Baez
- Lucas Tomio
