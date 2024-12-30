#include "RecipeBook.hpp"
int main (){
  RecipeBook rec = {"debug.csv"};

  RecipeBook book;
  book.preorderDisplay();
  //std:: cout << book.contains(recpie1) << std::endl;
  //std:: cout << book.contains(recpie2) << std::endl;
  //std::cout << book.findRecipe("hey") << std::endl;
  std:: cout << rec.calculateMasteryPoints("name1") << std::endl; // if recipe not in the RecipeBook
  std:: cout << rec.calculateMasteryPoints("name2") << std::endl; // if recipe is already completed
  std:: cout << rec.calculateMasteryPoints("name3") << std::endl; // if recipe is not already completed
  

} 