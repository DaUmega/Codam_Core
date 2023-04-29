#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongCat.hpp"

int	main(void)
{
	const Animal* meta = new Animal();
	const Animal* j = new Dog();
	const Animal* i = new Cat();
	const WrongAnimal* test = new WrongCat();

	std::cout << j->getType() << " " << std::endl;
	std::cout << i->getType() << " " << std::endl;
	std::cout << test->getType() << " " << std::endl;
	j->makeSound();
	i->makeSound();
	meta->makeSound();
	test->makeSound();
	delete meta;
	delete j;
	delete i;
	delete test;
	
	return 0;
}
