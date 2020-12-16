# Porjet LO21
## Opérateurs
### Implémenter un opérateur.

1) Déterminer l'arité de l'opérateur.
  On prendra ici le cas d'un opérateur binaire

2) Dans un header : Créer la classe *nomOpérateur* ici : Add. Cette classe hérite de la classe BinaryOperator.
avec un nom prédéterminé qui serivra d'identificateur.

```
class Add : public BinaryOperator {
	std::string name = "add";
	static std::shared_ptr<Add> instance;
	Add() = default;
public:
	static Add& get();
	static void free();
};
```
3) Dans un fichier source : définir les méthodes get et free de cette classe ainsi que le shared_ptr du singleton :

```
shared_ptr<Add> Add::instance = nullptr;

Add& Add::get(){
	if(instance == nullptr){
		instance = shared_ptr<Add>(new Add);
		Operator::addOperator(instance->name, instance);
	}
	return *instance;
}

void Add::free(){
	if(instance != nullptr){
		Operator::delOperator(instance->name);
		instance = nullptr;
	}
}
```

4) Dans un header : Créer la classe Abstract*nomOpérateur* ici : AbstractAdd. Cette classe hérite de la classe AbstractBinaryOperation

```
class AbstractAdd : public AbstractBinaryOperation{
public:
	AbstractAdd() = default;
	~AbstractAdd() = default;
};
```

5) Dans un fichier Header : Créer chacune des classes de l'opérateur qui implemente un comportement en fonction des types d'entrée. Ici on ne prendra que l'exemple de Add avec deux int. la classe  AddIntInt.

```
class AddIntInt : public AbstractAdd{
	LiteralType typeA = linteger;
	LiteralType typeB = linteger;
public:
	AddIntInt();
	void execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};
```

6) Implémenter le constructeur de cette classe ainsi que la méthode execution.

```
AddIntInt::AddIntInt(){
	Add::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de Add, qui permettra de trouver un objet de la classe AddIntInt si on recherche l'opérateur Add pour deux Int.
}
void AddIntInt::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un pointeur de Literal sur le shared_ptr
  Literal* litB = B.get();
	LInteger* lIntA = dynamic_cast<LInteger*>(litA); //On cast ce pointeur en LInteger
  LInteger* lIntB = dynamic_cast<LInteger*>(litB);
	int valeurA = lIntA->getValue(); //On récupère la valeur de ce Literal
  int valeurB = lIntB->getValue();
	const int newVal = valeurA + valeurB; //On effectue l'opération Add
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau int
	Stack::getInstance().push(newLit); //On pous notre Literal sur la Stack.
}
```
