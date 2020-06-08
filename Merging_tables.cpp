#include <bits/stdc++.h>

struct DisjointSetsElement
{
  DisjointSetsElement(long long size = 0, int parent = -1, int rank = 0) : size(size), parent(parent), rank(rank) {}
  long long size;
  int parent, rank;
};

int Find_Root(std::vector<DisjointSetsElement> &vec, int index)
{
  // while loop version
  // while (vec[index].parent != index && vec[index].parent != -1)
  // {
  //   index = vec[index].parent;
  // }
  // return index;

  // Recursive version
  if (vec[index].parent == index || vec[index].parent == -1)
    return index;
  return Find_Root(vec, vec[index].parent);
}

void Union(std::vector<DisjointSetsElement> &vec, long long &max_table_size, int index1, int index2)
{
  // Boundary case
  if (index1 == index2)
  {
    if (vec[index1].parent == -1)
      vec[index1].parent = index1;
    return;
  }

  // Get the sub tree's root index
  int root_index1 = Find_Root(vec, index1);
  if (root_index1 == index1 && vec[root_index1].parent == -1)
    vec[index1].parent = index1;

  int root_index2 = Find_Root(vec, index2);
  if (root_index2 == index2 && vec[root_index2].parent == -1)
    vec[index2].parent = index2;

  // Represent the element is already on the same tree
  if (root_index1 == root_index2)
    return;

  // index1<-index2
  if (vec[root_index1].rank > vec[root_index2].rank)
  {
    // Compression path, update the parent
    vec[root_index2].parent = root_index1;

    // Updat the size to root
    vec[root_index1].size += vec[root_index2].size;

    if (vec[root_index1].size > max_table_size)
      max_table_size = vec[root_index1].size;

    vec[index2].size = 0;
  }
  else // index2<-index1
  {
    // Update the rank
    if (vec[root_index1].rank == vec[root_index2].rank)
      vec[root_index2].rank = vec[root_index2].rank + 1;

    // Compression path, update the parent
    vec[root_index1].parent = root_index2;

    // Update the size to root
    vec[root_index2].size += vec[root_index1].size;

    if (vec[root_index2].size > max_table_size)
      max_table_size = vec[root_index2].size;

    vec[index1].size = 0;
  }
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::vector<DisjointSetsElement> disjoints_vec;
  std::vector<long long> Max_size;
  long long max_tablesize = 0;

  int n, m;
  std::cin >> n >> m;
  Max_size.reserve(m);

  for (int i = 0; i < n; i++)
  {
    DisjointSetsElement temp;
    long long table_size;
    std::cin >> table_size;

    // Update the max table size
    if (table_size > max_tablesize)
      max_tablesize = table_size;

    temp.size = table_size;
    disjoints_vec.push_back(temp);
  }

  for (int i = 0; i < m; i++)
  {
    int dest, source;
    std::cin >> dest >> source;
    Union(disjoints_vec, max_tablesize, dest - 1, source - 1);
    Max_size.push_back(max_tablesize);
  }

  // Output the answer
  for (int i = 0; i < Max_size.size(); i++)
    std::cout << Max_size[i] << std::endl;
}
