#include <bits/stdc++.h>

const unsigned p = 1000000007;
const unsigned x = 263;

struct Query
{
  Query(std::string type = "", std::string str = "", int find_index = -1) : type(type), str(str), find_index(find_index) {}
  std::string type;
  std::string str;
  int find_index;
};

struct HashNode
{
  HashNode(std::string str = "", HashNode *next_node = nullptr, bool empty = true) : str(str), next_node(next_node), empty(empty) {}

  std::string str;
  HashNode *next_node;
  bool empty;
};

int CaculateHashIndex(std::string str, int m)
{
  long long Hash_index = 0;

  for (int i = static_cast<int>(str.size()) - 1; i >= 0; --i)
    Hash_index = (Hash_index * x + (int)str[i]) % p;
  return Hash_index % m;
}

void AddHashNode(std::vector<HashNode> &HashTable, std::string str, int m)
{
  // Calculate the h(s)
  int Hash_index = CaculateHashIndex(str, m);
  //std::cout << "index: " << Hash_index << std::endl;

  // No element in this position
  if (HashTable[Hash_index].empty)
  {
    HashTable[Hash_index].str = str;
    HashTable[Hash_index].empty = false;
    HashTable[Hash_index].next_node = nullptr;
  }
  else
  {
    // Point to the current hash node
    HashNode *current_node = &HashTable[Hash_index];
    while (current_node != nullptr)
    {
      // There are the same str in the hash table
      if (current_node->str == str)
        return;

      if (current_node->next_node == nullptr)
        break;
      current_node = current_node->next_node;
    }
    // Represent arrive the nullptr
    current_node->next_node = new HashNode(str, nullptr, false);
  }
}

std::string FindHashNode(std::vector<HashNode> &HashTable, std::string str, int m)
{
  // Calculate the h(s)
  int Hash_index = CaculateHashIndex(str, m);

  // Coner case
  if (HashTable[Hash_index].empty)
    return "no";

  HashNode *node = &(HashTable[Hash_index]);
  while (node != nullptr)
  {
    if (node->str == str)
      return "yes";
    node = node->next_node;
  }
  return "no";
}

void DelHashNode(std::vector<HashNode> &HashTable, std::string str, int m)
{
  int Hash_index = CaculateHashIndex(str, m);
  HashNode *node = &HashTable[Hash_index];

  if (node->empty)
    return;

  // The first one in chain need to remove, we can't directly remove it
  if (node->str == str)
  {
    // Only one element in this chain
    if (node->next_node == nullptr)
    {
      node->empty = true;
      node->str = "";
    }
    else
    {
      // Not only one element in this chain
      HashNode *remove_node = node->next_node;
      node->str = node->next_node->str;
      node->empty = node->next_node->empty;
      node->next_node = remove_node->next_node;

      delete remove_node;
      remove_node = nullptr;
    }
    return;
  }

  while (node != nullptr)
  {
    if (node->next_node == nullptr)
      return;
    if (node->next_node->str == str)
    {
      HashNode *remove_node = node->next_node;
      node->next_node = remove_node->next_node;

      // Release the memory
      delete remove_node;
      remove_node = nullptr;
      return;
    }
    node = node->next_node;
  }
}

std::vector<std::string> CheckHashNode(std::vector<HashNode> &HashTable, int find_index)
{
  std::vector<std::string> answer;

  if (HashTable.at(find_index).empty)
  {
    return answer;
  }

  HashNode *node = &(HashTable.at(find_index));
  while (node != nullptr)
  {
    answer.push_back(node->str);
    node = node->next_node;
  }
  return answer;
}

void Solve(std::vector<Query> &vec, int m)
{
  std::vector<HashNode> HashTable;
  if (m == 0)
    m = 1;
  HashTable.resize(m);

  for (int i = 0; i < vec.size(); i++)
  {
    if (vec[i].type == "add")
    {
      AddHashNode(HashTable, vec[i].str, m);
    }
    else if (vec[i].type == "check")
    {
      std::vector<std::string> check_ans = CheckHashNode(HashTable, vec[i].find_index);
      // Represent i-th list is empty
      if (check_ans.size() == 0)
        std::cout << "" << std::endl;
      else
      {
        for (int i = check_ans.size() - 1; i >= 0; i--)
          std::cout << check_ans[i] << " ";
        std::cout << std::endl;
      }
    }
    else if (vec[i].type == "find")
    {
      std::cout << FindHashNode(HashTable, vec[i].str, m) << std::endl;
    }
    else // del
    {
      DelHashNode(HashTable, vec[i].str, m);
    }
  }
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  int m, N;
  std::vector<Query> vec;

  std::cin >> m >> N;
  vec.resize(N);
  for (int i = 0; i < N; i++)
  {
    std::cin >> vec[i].type;
    if (vec[i].type == "check")
      std::cin >> vec[i].find_index;
    else
      std::cin >> vec[i].str;
  }

  Solve(vec, m);

  return 0;
}
