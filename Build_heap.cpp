#include <bits/stdc++.h>

void MinHeapify(std::vector<int> &vec, int root_index, std::vector<std::pair<int, int>> &answer)
{
  int leftchild_index = 0;
  int rightchild_index = 0;

  // Calculate the rightchild_index and leftchild_index
  if (2 * root_index < vec.size())
  {
    leftchild_index = 2 * root_index;
    if (leftchild_index + 1 < vec.size())
      rightchild_index = leftchild_index + 1;
  }
  else // Arrive the leaf node, no leftchild_index directly return
  {
    return;
  }
  // std::cout << "left: " << leftchild_index << std::endl;
  // std::cout << "right: " << rightchild_index << std::endl;

  // Find the minimum index in the sub tree
  int min_index = root_index;
  if (rightchild_index == 0) // The sub tree only have leftchild
  {
    if (vec[leftchild_index] < vec[min_index])
      min_index = leftchild_index;
  }
  else // The sub tree have the leftchild and rightchild
  {
    if (vec[leftchild_index] < vec[min_index])
      min_index = leftchild_index;
    if (vec[rightchild_index] < vec[min_index])
      min_index = rightchild_index;
  }

  // Swap the root index with the min_index
  if (root_index != min_index)
  {
    std::swap(vec[root_index], vec[min_index]);
    answer.push_back(std::make_pair(root_index - 1, min_index - 1));
    MinHeapify(vec, min_index, answer);
  }

  // Debug
  // for (int i = 1; i < vec.size(); i++)
  //   std::cout << vec[i] << " ";
  // std::cout << std::endl;
  //MinHeapify(vec, min_index, answer);
}

void BuildMinHeap(std::vector<int> &_vec)
{
  std::vector<int> vec;
  std::vector<std::pair<int, int>> answer;
  vec.reserve(_vec.size() + 1);

  // Let the index 0 no element
  vec.push_back(-1);
  for (int i = 0; i < _vec.size(); i++)
    vec.push_back(_vec.at(i));

  int tree_root_index = (vec.size() - 1) / 2;

  // Tranverse every tree root
  for (int i = tree_root_index; i >= 1; i--)
  {
    // Min heap the sub tree
    MinHeapify(vec, i, answer);
  }

  if (answer.size() == 0)
    std::cout << 0 << std::endl;
  else
  {
    std::cout << answer.size() << std::endl;
    for (int i = 0; i < answer.size(); i++)
    {
      std::cout << answer[i].first << " " << answer[i].second << std::endl;
    }
  }

  // for (int i = 1; i < vec.size(); i++)
  //   std::cout << vec[i] << " ";
  // std::cout << std::endl;
}
int main()
{
  std::ios_base::sync_with_stdio(false);

  std::vector<int> vec;
  int n;
  std::cin >> n;
  for (int i = 0; i < n; i++)
  {
    int temp;
    std::cin >> temp;
    vec.push_back(temp);
  }

  BuildMinHeap(vec);
  return 0;
}
