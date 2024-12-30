
/**
 * @file RecipeBook.hpp
 * @brief This file contains the declaration of the RecipeBook class, which represents a virtual recipe book that allows chefs to easily get the recipes and a Recipe Struct that represents Recipe
 *  There are no arritbutes in the RecipeBook Class. There are 4 arritbutes of the Recipe class such as name,difficulty level, description, mastered.
 * RecipeBook provides constructors, accessor and mutator functions, that allows the user to move around recipes in the RecipeBook, know what they need to master, and display the 
 * recipes.
 * Recipe provdies constructor and operators in order to adjust the recipe, and to compare recipes based off names
 * 
 * @date 12/12/2024 
 * @author Angela Yu
 * 
 * */
#ifndef RECIPE_BOOK
#define RECIPE_BOOK
#include <iostream>
#include "BinarySearchTree.hpp"
#include <fstream>
#include <sstream>
#include <string> 
#include <vector>
#include "BinaryNode.hpp"
struct Recipe {
    public :
    /**
    * Default constructor.
    * @post: Initializes name_ and description_ to empty strings,
    difficulty_level_ to 0, and mastered_ to false.
    */
    Recipe ();
    /**
    * Parameterized Constructor.
    * @param name The name of the recipe.
    * @param difficulty_level The difficulty level of the recipe.
    * @param description A brief description of the recipe.
    * @param mastered Indicates whether the recipe has been mastered (default is
    f alse).
    * @post: Initializes the Recipe with the provided values.
    */
    Recipe (const std::string & name,const int & difficulty_level,const std::string & description, const bool & mastered);
   /**
    * Equality operator.
    * @param other A const reference to another Recipe.
    * @return True if name_ is equal to other's name_;
    false otherwise.
    */
    bool operator== (const Recipe & other);
    /**
    * Less-than operator.
    * @param other A const reference to another Recipe.
    * @return True if difficulty_level_ is less than other's difficulty_level_;
    false otherwise.
    */

     bool operator< (const Recipe & other);

     /**
    * Greater-than operator.
    * @param other A const reference to another Recipe.
    * @return True if difficulty_level_ is greater than other's
    difficulty_level_; false otherwise.
    */

     bool operator >(const Recipe & other);


    std::string name_; //The name of the recipe.
    int difficulty_level_; //An integer representing the difficulty level of the recipe (1-10).
    std::string description_; //A brief description of the recipe
    bool mastered_; //Indicates whether the recipe has been mastered by the kitchen staff.
};
class RecipeBook : public BinarySearchTree<Recipe>{

public:
    /**
    * Default Constructor.
    * @post: Initializes an empty RecipeBook.
    */
    RecipeBook ();
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
    RecipeBook (const std::string &filename);
    /**
    * Helper Function to find the pointer 
    * @param name A const reference to the smart pointer containg a node
    * @param recipe A Recipe struct of a recipe
    * @return A pointer to the node containing the Recipe with the given
    difficulty level, or nullptr if not found.
    */

    std::shared_ptr<BinaryNode<Recipe>> findRecipehelper(const std::shared_ptr<BinaryNode<Recipe>>& node,  Recipe  recipe)const;
    /**
    * Finds a Recipe in the tree by name.
    * @param name A const reference to the name.
    * @return A pointer to the node containing the Recipe with the given
    difficulty level, or nullptr if not found.
    */
    std::shared_ptr<BinaryNode<Recipe>> findRecipe (const std::string & name) const;

    /**
    * Adds a Recipe to the tree.
    * @param recipe A const reference to a Recipe object.
    * @pre: The Recipe does not already exist in the tree (based on name).
    * @post: The Recipe is added to the tree in BST order (based on difficult
    level).
    * @return: True if the Recipe was successfully added; false if a Recipe with
    the same name already exists.
    */
    bool addRecipe (const Recipe & recipe);
    /**
    * Removes a Recipe from the tree by name.
    * @param name A const reference to a string representing the name of the
    Recipe.
    * @post: If found, the Recipe is removed from the tree.
    * @return: True if the Recipe was successfully removed; false otherwise.
    */
    bool removeRecipe (const std::string & name);
    /**
    * Clears all Recipes from the tree.
    * @post: The tree is emptied, and all nodes are deallocated.
    */
    void clear ();
    /**
    * helps calculates the number of mastery points needed to master a Recipe.
    * @param difficulty A const reference to an int representing the
    difficulty level of the Recipe.
    *@param node A const reference to a smart pointer representing the node in a binary tree
    * @note: For a Recipe to be mastered, all Recipes with lower difficulty
    levels must also be mastered.
    * @return: int of number of points needed to master the Recipe
    */
    int  caclulateMasteryHelper (const std::shared_ptr<BinaryNode<Recipe>>& node, int difficulty) const;
    /**
    * Calculates the number of mastery points needed to master a Recipe.
    * @param difficulty_level A const reference to an int representing the
    difficulty level of the Recipe.
    * @note: For a Recipe to be mastered, all Recipes with lower difficulty
    levels must also be mastered.
    * @return: An integer representing the number of mastery points needed, or
    -1 if the Recipe is not found.
    * Mastery points are calculated as the number of Recipes from the root to
    the given Recipe (inclusive).
    */
    int calculateMasteryPoints (const std::string & name ) const;
    /**
    * In order transveral function
    * @param node A smart pointer that represents the node of a binary tree
    *@param tree A vector of Recipes that represents all the recipes in binary tree
    * @post: Tree vector contains the Recipes inorder transveral form
    *
    */
    void  inorderhelp (std::shared_ptr<BinaryNode<Recipe>> node, std::vector<Recipe>  &tree );
    /**
    * Helps Build the Tree after inorder traversal in order to balance
    *@param tree A vector of Recipes that represents all the recipes in binary tree
    *@param start a int representing the start of the vector of recipes
    *@param ends a int represent the end of the vector of recipes
    * @post: The BST wll include the recipes in a balanced binary tree
    * @return a smart pointer containing the root
    *
    */
    std::shared_ptr<BinaryNode<Recipe>> buildtreehelp (const std::vector<Recipe> & tree, int start, int ends);
    /**
    * Balances the tree.
    * @post: The tree is balanced such that for any node, the heights of its
    left and right subtrees differ by no more than 1.
    * @note: You may implement this by performing an inorder traversal to get
    sorted Recipes and rebuilding the tree.
    */
    void balance ();
    /**
    * Helper Fucntion that helps Displays the tree in preorder traversal 
    *@param node a smart pointer that contains the node
    * @post: Outputs the Recipes in the tree in preorder, formatted as:
    */

    void preorderDisplayhelp ( std::shared_ptr<BinaryNode<Recipe>> node )const;
    /**
    * Displays the tree in preorder traversal.
    * @post: Outputs the Recipes in the tree in preorder, formatted as:
    * Name: [name_]
    * Difficulty Level: [difficulty_level_]
    * Description: [description_]
    * Mastered: [Yes/No]
    * (Add an empty line between Recipes)
    */
    void preorderDisplay () const;

};





#endif 