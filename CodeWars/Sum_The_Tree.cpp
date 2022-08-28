 // Return the sum of all values in the tree, including the root
 int sumTheTreeValues(node* root) {
   if (root == NULL)
     return 0;
   return root->value + sumTheTreeValues(root->left) + sumTheTreeValues(root->right);   
 }
