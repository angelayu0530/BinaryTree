/**
 * @file RecipeBook.cpp
 * @brief This file contains the declaration of the RecipeBook class, which represents the virtual book of different types of Recipes and a Recipe Struct that represents
 * cooking/baking recipes.
 * 
 * 
 *  The RecipeBook class is inherited from the BinarySearchTree template that includes methods to help organize recipes in a recipe book using a binary tree.
 * Recipe Struct has operators that allow the comparison of recipe names and a constructor that reads a csv file.
 *  RecipeBook  has methods that allow to add or remove recipe, finding a recipe, clearing the book, caculating how many dish in order to master, balancing the different recipes,and displaying the recipes in
 * pre order transveral. 
 * 
 *  
 * @date 12/12/2024 
 * @author Angela Yu
 */

#include "RecipeBook.hpp"
 /**
    * Default constructor.
    * @post: Initializes name_ and description_ to empty strings,
    difficulty_level_ to 0, and mastered_ to false.
    */
    Recipe::Recipe () {
          name_ = "";
          difficulty_level_ =0;
          description_ ="";
          mastered_=false;
    }
    /**
    * Parameterized Constructor.
    * @param name The name of the recipe.
    * @param difficulty_level The difficulty level of the recipe.
    * @param description A brief description of the recipe.
    * @param mastered Indicates whether the recipe has been mastered (default is
    f alse).
    * @post: Initializes the Recipe with the provided values.
    */
    Recipe :: Recipe (const std::string & name,const int & difficulty_level,const std::string & description, const bool & mastered) {
            name_ = name;
            difficulty_level_=difficulty_level;
            description_ = description;
            mastered_ = mastered;
    }
   /**
   * Equality operator.
   * @param other A const reference to another Recipe.
   * @return True if name_ is equal to other’s name_; false otherwise.
   */
    bool Recipe :: operator== (const Recipe & other) {
           return name_ == other.name_;
    }
    /**
    * Less-than operator.
    * @param other A const reference to another Recipe.
    * @return True if name_ is lexicographically less than other's name_; false
    otherwise.
    */
    bool Recipe :: operator< (const Recipe & other) {
        return name_ < other.name_;
    }

      /**
   * Greater-than operator.
    * @param other A const reference to another Recipe.
  * @return True if name_ is lexicographically greater than other's name_;
  false otherwise.
  */

    bool Recipe :: operator >(const Recipe & other) {
        return name_ > other.name_;
    }
  /**
  * Default Constructor.
  * @post: Initializes an empty RecipeBook.
  */
  RecipeBook :: RecipeBook () : BinarySearchTree<Recipe> () { // Initalized with the constructor of BinaryTree Search

  }
  /**
  * Parameterized Constructor.
  * @param filename A const reference to a string representing the name of a
  CSV file.
  * @post: The RecipeBook is populated with Recipes from the CSV file.
  * The file format is as follows:
  * name,difficulty_level,description,mastered
  * Ignore the first line. Each subsequent line represents a Recipe to be
  added to the RecipeBook.
  */
  RecipeBook :: RecipeBook (const std::string &filename){
      std:: ifstream fin(filename);
      if (fin.fail()) {
      std::cerr << "File cannot be opened for reading." << std:: endl;
      exit(1); // exit if failed to open the file
        }
      std::string junk;
      std:: getline(fin,junk); //header
      std::string start; // first line
      std:: string names,difficulty_levels,descriptions,mastereds; // creates string of names
      while(std::getline(fin,start)){ // get line
          std:: istringstream line(start); //
          std::getline(line,names,','); // gets names
          std::getline(line,difficulty_levels,','); // gets levels
          std::getline(line,descriptions,','); // get descriptions
          std::getline (line,mastereds,','); // gets mastery level
          
          bool mastered = false;
          if(mastereds == "0"){
            mastered= false;
          }
          else {
            mastered = true;
          }
          
        //std::cout << names << " "; testing 
        //std:: cout << difficulty_levels<< " ";
        //std:: cout << descriptions << " " ;
        //std:: cout << mastered << " ";
        //std :: cout << std:: endl;
        Recipe recipe = {names,stoi(difficulty_levels),descriptions,mastered};
        addRecipe(recipe);
        //std: cout << addRecipe(recipe) << std::endl; check if add works

      }
  }    
  /**
    * Helper Function to find the pointer 
    * @param name A const reference to the smart pointer containg a node
    * @param recipe A Recipe struct of a recipe
    * @return A pointer to the node containing the Recipe with the given
    difficulty level, or nullptr if not found.
    */ 
  std::shared_ptr<BinaryNode<Recipe>> RecipeBook :: findRecipehelper(const std::shared_ptr<BinaryNode<Recipe>>& node,  Recipe  recipe)const {
      if(node == nullptr){ // if not found
        return nullptr;
      }
    if( node ->getItem().name_ == recipe.name_){ // if the node is holding the same name, returns the recipe as a pointer
      return node;
    }
    if(node ->getItem().name_ > recipe.name_){ // if it is node > given recipe, checks left side
        return(findRecipehelper(node->getLeftChildPtr(),recipe)); // checks left side til finds the pointer 
    }
    
      return(findRecipehelper(node->getRightChildPtr(),recipe)); // checks right til it finds the pointer 
    
  }
  

  /**
  * Finds a Recipe in the tree by name.
  * @param name A const reference to the name.
  * @return A pointer to the node containing the Recipe with the given
  name , or nullptr if not found.
  */
  std::shared_ptr<BinaryNode<Recipe>> RecipeBook ::  findRecipe (const std::string & name) const{
      Recipe top; // recipe 
      top.name_ = name; // with name
    return(findRecipehelper(getRoot(),top)); //calls helperfucntion
    
  }


  

  /**
  * Adds a Recipe to the tree.
  * @param recipe A const reference to a Recipe object.
  * @pre: The Recipe does not already exist in the tree (based on name).
  * @post: The Recipe is added to the tree in BST order (based on difficult
  level).
  * @return: True if the Recipe was successfully added{ false if a Recipe with
  the same name already exists.
  */
  bool RecipeBook :: addRecipe (const Recipe & recipe){
      if(contains(recipe)){ // contains check if it exist, it does, returns false;
          return false;
      }
      add(recipe);// adds using the bst add function
      return true;// will always return true
      
  }
  /**
  * Removes a Recipe from the tree by name.
  * @param name A const reference to a string representing the name of the
  Recipe.
  * @post: If found, the Recipe is removed from the tree.
  * @return: True if the Recipe was successfully removed{ false otherwise.
  */
  bool RecipeBook :: removeRecipe (const std::string & name){
      Recipe recipe;
      recipe.name_= name; // sets the recipe with this name
      if(remove(recipe)){ // if removes is true;
          return true; // return true;
      }
      return false; // returns false;
  }
  /**
  * Clears all Recipes from the tree.
  * @post: The tree is emptied, and all nodes are deallocated.
  */
  void RecipeBook :: clear (){
      setRoot(nullptr);
  }
     /**
    * helps calculates the number of mastery points needed to master a Recipe.
    * @param difficulty A const reference to an int representing the
    difficulty level of the Recipe.
    *@param node A const reference to a smart pointer representing the node in a binary tree
    * @note: For a Recipe to be mastered, all Recipes with lower difficulty
    levels must also be mastered.
    * @return: int of number of points needed to master the Recipe
    */

  int  RecipeBook :: caclulateMasteryHelper (const std::shared_ptr<BinaryNode<Recipe>>& node, int difficulty) const { // pre order transveral
      int points = 0;
        if(node == nullptr){  // check if the node == nullptr
          return 0;
        }
        if(!node ->getItem().mastered_ && node ->getItem().difficulty_level_ <= difficulty){ // if recpie is not mastered, and the diffculity level < the difficulty
            points++;
        }
        points +=caclulateMasteryHelper(node ->getLeftChildPtr(),difficulty); // left side
        points +=caclulateMasteryHelper(node -> getRightChildPtr(),difficulty); // right side
        return points; // return the points

  }
    /**
    * Calculates the number of mastery points needed to master a Recipe.
    * @param difficulty_level A const reference to an string representing the
    difficulty level of the Recipe.
    * @note: For a Recipe to be mastered, all Recipes with lower difficulty
    levels must also be mastered.
    * @return: An integer representing the number of mastery points needed, or
    -1 if the Recipe is not found. If the recipe is already mastered, return 0.
    * Note: Mastery points are calculated as the number of unmastered Recipes in
    the tree with a lower difficulty level than the given Recipe. Add one if the
    Recipe is not mastered.
    */
    int RecipeBook :: calculateMasteryPoints (const std::string & name ) const{
        if(!findRecipe(name)){ // if cant find returns -1
          return -1;  
      }
      
      if(findRecipe(name) ->getItem().mastered_ == true){ // if mastered ==  true;, returns 0
          return 0;
        }
        return caclulateMasteryHelper(getRoot(),findRecipe(name)->getItem().difficulty_level_); // returns how many if condtions are met
    }

    /**
    * In order transveral function
    * @param node A smart pointer that represents the node of a binary tree
    *@param tree A vector of Recipes that represents all the recipes in binary tree
    * @post: Tree vector contains the Recipes inorder transveral form
    */

    void RecipeBook :: inorderhelp ( std::shared_ptr<BinaryNode<Recipe>> node, std::vector<Recipe> & tree){
        if(node == nullptr){ // if node == nothing, nothing wil happen
            return;
        }

        inorderhelp(node->getLeftChildPtr(),tree); // get the left side right
        tree.push_back(node->getItem());  // puts into vector
        inorderhelp(node ->getRightChildPtr(),tree); // get right

    }
    /**
    * Helps Build the Tree after inorder traversal in order to balance
    *@param tree A vector of Recipes that represents all the recipes in binary tree
    *@param start a int representing the start of the vector of recipes
    *@param ends a int represent the end of the vector of recipes
    * @post: The BST wll include the recipes in a balanced binary tree
    * @return a smart pointer containing the root
    */
    std::shared_ptr<BinaryNode<Recipe>>RecipeBook :: buildtreehelp ( const std::vector<Recipe> & tree, int start, int ends){
        if(start > ends ){ // if the start is greater than ends, it should not work out
          return nullptr; // return null
        }
        int med; // to keep the root
        med = (start+ends)/2; // will be the root
      Recipe recipe(tree[med].name_, tree[med].difficulty_level_, tree[med].description_, tree[med].mastered_); // helper to set the root with the item in the middle
        std::shared_ptr<BinaryNode<Recipe>> top = std::make_shared<BinaryNode<Recipe>>(recipe);
        top ->setLeftChildPtr(buildtreehelp(tree,start, med-1)); // builds the left side
        top -> setRightChildPtr(buildtreehelp(tree,med+1,ends)); // builds the right side
        return top; // returns root
    }
   /**
    * Balances the tree.
    * @post: The tree is balanced such that for any node, the heights of its
    left and right subtrees differ by no more than 1.
    * @note: You may implement this by performing an inorder traversal to get
    sorted Recipes and rebuilding the tree.
    */
    void RecipeBook :: balance (){
        std::vector<Recipe> tree; // vector for the tree

        inorderhelp(getRoot(),tree); // in order transveral 

      setRoot(buildtreehelp(tree,0,tree.size()-1)); // calls to build the tree and sets the root with the new root
      
    }
     /**
    * Helper Fucntion that helps Displays the tree in preorder traversal 
    *@param node a smart pointer that contains the node
    * @post: Outputs the Recipes in the tree in preorder, formatted as:
    */
    void  RecipeBook ::preorderDisplayhelp ( std::shared_ptr<BinaryNode<Recipe>>  node ) const {
    
          if(node == nullptr){ // if node is null, nothing happens
            return;
          }
          std::cout << "Name: " <<node -> getItem().name_ <<std::endl; // prints out name
          std::cout << "Difficulty Level: " <<node -> getItem().difficulty_level_ <<std::endl; // prints out difficulty level
          std::cout << "Description: " << node ->getItem().description_ << std::endl; // prints out description
          if(node->getItem().mastered_){ // mastered
              std::cout << "Mastered: " << "Yes" << std::endl; // prints yes if true
          } 
          else {
              std::cout << "Mastered: " << "No" << std::endl; // prints no if not true
          }
          std:: cout << std::endl;
          preorderDisplayhelp(node ->getLeftChildPtr()); // left side
          preorderDisplayhelp(node -> getRightChildPtr()); // right side
           
    }

        /**
        * Displays the tree in preorder traversal.
        * @post: Outputs the Recipes in the tree in preorder, formatted as:
        * Name: [name_]
        * Difficulty Level: [difficulty_level_]
        * Description: [description_]
        * Mastered: [Yes/No]
        * (Add an empty line between Recipes)
        */
        void RecipeBook :: preorderDisplay () const {
          preorderDisplayhelp(getRoot()); // starts at the root
        }

