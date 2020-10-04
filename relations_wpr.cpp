//Ivan Stefanov, 4/6/2020
#include <iostream>
#include "KnowledgeBase.hpp"


int main()
{
    //examples with BinaryRelation
    BinaryRelation<int, double> smaller_or_equal;
    smaller_or_equal.add(1.5, 1.55555);
    smaller_or_equal.add(0, -42.5);
    smaller_or_equal.add(6, 6);

    BinaryRelation<int, double> greater_or_equal;
    greater_or_equal.add(2, 1.55555);
    greater_or_equal.add(0, 0.1);
    greater_or_equal.add(6, 6.06);

    std::cout << "Union of relations:" << std::endl;
    std::cout << (smaller_or_equal + greater_or_equal) << std::endl;
    std::cout << "Intersection of relations:" << std::endl;
    std::cout << (smaller_or_equal ^ greater_or_equal) << std::endl;
    std::cout << "Composition of relations:" << std::endl;
    std::cout << (smaller_or_equal * greater_or_equal) << std::endl;

    std::cout << "Domain of 'greater_or_equal' :" << greater_or_equal.dom();
    std::cout << "Range of 'smaller_or_equal' :" << smaller_or_equal.ran() << std::endl;

    std::cout << "Now add an ordered pair (a, b) to the relation 'greater_or_equal': ";
    std::cin >> greater_or_equal;

    std::cout << "Now the relation looks like this: " << greater_or_equal << std::endl;

    KnowledgeBase<int, String> numbers_and_language;

    BinaryRelation<int, String> bul;
    bul.add(0, "nula");
    bul.add(1, "edno");
    bul.add(2, "dve");
    numbers_and_language.add("Bulgarian", bul);

    BinaryRelation<int, String> eng;
    eng.add(0, "zero");
    eng.add(1, "one");
    eng.add(2, "two");
    numbers_and_language.add("English", eng);

    KnowledgeBase<int, String> numbers_and_language2;

    BinaryRelation<int, String> ger;
    ger.add(1, "ein");
    ger.add(2, "zwei");
    ger.add(3, "drei");
    numbers_and_language2.add("German", ger);

    BinaryRelation<int, String> bul2;
    bul2.add(0, "nula");
    bul2.add(1, "edno");
    bul2.add(2, "dve");
    bul2.add(3, "tri");
    bul2.add(4, "chetri");
    numbers_and_language2.add("Bulgarian", bul2);

    std::cout << "\nAll of the first knowledge base:" << std::endl;
    std::cout << numbers_and_language << std::endl;

    std::cout << "Union of the knowledge bases: " << std::endl;
    std::cout << (numbers_and_language + numbers_and_language2) << std::endl;
    std::cout << "Intersection of the knowledge bases: " << std::endl;
    std::cout << (numbers_and_language ^ numbers_and_language2) << std::endl;
    std::cout << "Composition of relations in the knowledge bases: " << std::endl;
    std::cout << (numbers_and_language * numbers_and_language2) << std::endl;

    std::cout << "\n Combining the two bases" << std::endl;
    numbers_and_language += numbers_and_language2;

    std::cout << "Is the pair (1, edno) a relation in the knowledge base? : " << std::boolalpha << r(1, "edno") << std::endl;
    std::cout << "All elements, which are in relation with '1':" << numbers_and_language[1];
    std::cout << "All elements which are in relation with 'zero':" << numbers_and_language("zero");

    std::cout << "Is the knowledge base function?: " << std::boolalpha << (numbers_and_language.function()) << std::endl;
    std::cout << "Is the knowledge base injection?: " << std::boolalpha << (numbers_and_language.injection()) << std::endl;

    
    std::cout << "Now add a knowledge of your choice to the knowledge base" << std::endl;
    std::cin >> numbers_and_language;
    std::cout << "Now the knowledge base looks like this: \n" << numbers_and_language << std::endl;

    return 0;
}

