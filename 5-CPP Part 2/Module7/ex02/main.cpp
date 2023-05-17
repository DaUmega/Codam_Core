#include "Array.hpp"

int	main(void)
{
	try
    {
        Array<int> arr1; // Empty array
        std::cout << "arr1 size: " << arr1.size() << std::endl;

        Array<int> arr2(5); // Array of 5 elements initialized to default value (0 for int)
        std::cout << "arr2 size: " << arr2.size() << std::endl;

        arr2[0] = 10; // Accessing elements using []
        arr2[1] = 20;
        arr2[2] = 30;
        arr2[3] = 40;
        arr2[4] = 50;

        Array<int> arr3 = arr2; // Copy construction
        std::cout << "arr3 size: " << arr3.size() << std::endl;

        arr3[2] = 99; // Modifying arr3 should not affect arr2

        Array<int> arr4;
        arr4 = arr2; // Assignment operator
        std::cout << "arr4 size: " << arr4.size() << std::endl;

        arr4[1] = 77; // Modifying arr4 should not affect arr2

        std::cout << "arr2[2]: " << arr2[2] << std::endl;
        std::cout << "arr3[2]: " << arr3[2] << std::endl;
        std::cout << "arr4[1]: " << arr4[1] << std::endl;

        std::cout << "Accessing out of bounds element: ";
        std::cout << arr4[5] << std::endl; // This should throw an exception
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
}
