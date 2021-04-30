# FilesearchUtility
Using DS &amp; C++ oops concepts, a file search utility is developed that can tell total occurrences and line numbers of the occurrences of the given word in a text file.
# Features
* FSU_bst
  1. Scans each word of text file along with complete info (line numbers and occurences in that line number) and stores it in Binary Search Tree.
      * BST class object with data members word, head pointer to linked list containing its info and BST left, right nodes pointers.
  2. Can search a word, if found
      * Prints its total occurrences. 
      * Line numbers of its occurences.
  3. Stores the complete Binary Search Tree in another file with complete info of every word.
* REFSU_bst
  1. Reconstructs the stored Binary Search Tree after retrieving the info from the stored file.
