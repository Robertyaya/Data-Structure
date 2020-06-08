#include <bits/stdc++.h>

class Node
{
public:
  int key;
  Node *parent;                 // Point to the parent
  std::vector<Node *> children; // Point to the children

  Node()
  {
    this->parent = NULL;
  }

  void setParent(Node *theParent)
  {
    parent = theParent;
    parent->children.push_back(this);
  }
};

int MaxDepth(Node *node)
{
  // Is the tree is NULL, return zero
  if (node == NULL)
    return 0;
  // Represent arrive the leaf, therefore return 1, base condition
  if (node->children.size() == 0)
    return 1;
  else
  {
    int max_depth = 0;
    std::vector<int> depth_vec;
    depth_vec.resize(node->children.size());
    //std::cout << "size: " << node->children.size() << std::endl;

    // Compute the depth of the each subtree, tranverse the children and calculate its height
    for (int i = 0; i < node->children.size(); i++)
    {
      depth_vec[i] = MaxDepth(node->children[i]);
    }

    // Return the max element
    std::vector<int>::const_iterator iter;
    iter = std::max_element(depth_vec.begin(), depth_vec.end());
    return (*iter) + 1;
  }
}

int CalculateTreeHeight()
{
  std::ios_base::sync_with_stdio(0);

  int n;
  Node *root; // Point to the root
  std::cin >> n;
  std::vector<Node> nodes;
  nodes.resize(n);

  // Build the tree
  for (int child_index = 0; child_index < n; child_index++)
  {
    int parent_index;
    std::cin >> parent_index;
    if (parent_index >= 0)
      nodes[child_index].setParent(&nodes[parent_index]);
    else
    {
      root = &nodes[child_index];
    }
    nodes[child_index].key = child_index;
  }

  // Calculate the max height of tree
  return MaxDepth(root);

  // Replace this code with a faster implementation
  // int maxHeight = 0;
  // for (int leaf_index = 0; leaf_index < n; leaf_index++)
  // {
  //   int height = 0;
  //   for (Node *v = &nodes[leaf_index]; v != NULL; v = v->parent)
  //     height++;
  //   maxHeight = std::max(maxHeight, height);
  // }
  // return maxHeight;
  return 1;
}
int main()
{
  std::cout << CalculateTreeHeight() << std::endl;
  return 0;
}
