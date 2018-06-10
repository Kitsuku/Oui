//
// EPITECH PROJECT, 2018
// Comment utiliser les unique ptr
// File description:
// 
//

#include <iostream>
#include <memory>
#include <vector>

// La classe père correspond par exemple à notre AObject
// ATTENTION : il faut définir toutes les fonctions que les fils
// peuvent utiliser dans le père en virtual et les redéfinir comme il faut dans le fils

class	Pere
{
public:
	Pere(std::string name = "Oui") { _name = name; }
	~Pere() {}
	virtual void	speak() = 0;
	void	presentation() { std::cout << "Je m'appelles " << _name << std::endl; }
	void	rename(std::string name) { _name = name; }
protected:
	std::string	_name;
};

// La classe fils peut donc correspondre à une bombe

class Fils : public Pere
{
public:
	Fils(std::string name = "Fils") { _name = name; }
	~Fils() {}
	void	speak() { std::cout << "Je suis fils." << std::endl; }
};

// La classe fille peut correspondre à un bonus

class	Fille : public Pere
{
public:
	Fille(std::string name = "Fille") { _name = name; }
	~Fille() {}
	void	speak() { std::cout << "Je suis fille." << std::endl; }
};

class	Stock
{
public:
	Stock() {}
	~Stock() {}

	void	addChild(std::unique_ptr<Pere> child) { _children.push_back(std::move(child)); }
	Pere	*getChild(int pos) {
		if (pos <= _children.size())
			return _children[pos].get();
		return nullptr;
	}
protected:
	std::vector<std::unique_ptr<Pere>>	_children;
};

int	main()
{
	// Création d'une fille et d'un fils
	std::unique_ptr<Pere>	fils(new Fils);
	std::unique_ptr<Pere>	fille(new Fille);

	// On les fait parler
	fils->speak();
	fille->speak();

	// Création du vector<Pere>
	std::vector<std::unique_ptr<Pere>>	children;

	// Insertion des enfants dans children
	// ATTENTION : les variable fils et fille sont delete après insertion
	// On ne peut plus les utiliser car la priorité est donnée au vector
	children.push_back(std::move(fils));
	children.push_back(std::move(fille));

/*
** équivalent de 
** children.push_back(std::move(std::unique_ptr<Fils/Fille>())
** qui créer un unique_ptr)
*/

	// On fait parler nos enfants dans le vector
	children[0]->speak();
	children[1]->speak();

	// Insertion du vector dans un objet le stockant
	// ATTENTION : cela va rendre le vector children INUTILISABLE
	// La propritété des unique_ptr va passer au vector les stockants
	Stock	stock;
	
	for (int it = 0; it != children.size(); it++)
		stock.addChild(std::move(children[it]));

	// Récupération d'un child stocké
	Pere	*child = stock.getChild(1);

	child->speak();
	child->presentation();

	// Modification de notre enfant
	// L'objet est donc aussi modifié dans notre vector
	child->rename("Aurélie");
	child->presentation();
	stock.getChild(1)->presentation();
	
	return 0;
}
