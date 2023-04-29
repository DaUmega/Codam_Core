#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongCat.hpp"

int	main(void)
{
	const Animal* test[3] = { new Animal(), new Dog(), new Cat() };
	const WrongAnimal* bad = new WrongCat();

	for (int i = 0; i < 3; i++)
	{
		test[i]->makeSound();
		delete test[i];
	}
	delete bad;

	return 0;
}
