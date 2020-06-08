#include <bits/stdc++.h>

struct Query
{
  Query(std::string type = "", int key = -1, std::string value = "") : type(type), key(key), value(value) {}
  std::string type;
  int key;
  std::string value;
};

struct HashNode
{
  HashNode(std::string value = "", int key = -1, bool empty = true, HashNode *next_node = nullptr) : value(value), key(key), empty(empty), next_node(next_node) {}

  std::string value;
  int key;
  bool empty;
  HashNode *next_node;
};

const unsigned Prime_number = 563;
const int a = 179;
const int b = 83;
const int HashTableSize = 443;

void AddHashNode(std::vector<HashNode> &HashTable, int key, std::string value)
{
  // H(x) = ( (ax+b) mod (prime_number) ) mod HashTableSize
  int hash_index = ((a * key + b) % (Prime_number)) % HashTableSize;

  if (hash_index > HashTable.size())
  {
    std::cout << "ERROR: Add Node" << std::endl;
    return;
  }

  // No element in this position
  if (HashTable[hash_index].empty)
  {
    HashTable[hash_index].value = value;
    HashTable[hash_index].key = key;
    HashTable[hash_index].empty = false;
    HashTable[hash_index].next_node = nullptr;
  }
  else
  {
    // Point to the current hash node
    HashNode *node = &HashTable[hash_index];
    while (node != nullptr)
    {
      if (node->key == key)
      {
        node->value = value;
        return;
      }

      // the pointer arrive the leaf
      if (node->next_node == nullptr)
        break;
      node = node->next_node;
    }

    // Represent arrive the NULL
    node->next_node = new HashNode(value, key, false, nullptr);
  }
}

void DelHashNode(std::vector<HashNode> &HashTable, int key)
{
  int hash_index = ((a * key + b) % (Prime_number)) % HashTableSize;

  HashNode *node = &HashTable[hash_index];
  if (node->empty)
    return;

  // The first one in chain need to remove, we can't directly remove it
  if (node->key == key)
  {
    // only one element
    if (node->next_node == nullptr)
    {
      node->empty = true;
      node->key = -1;
      node->value = "";
    }
    else
    {
      // not only one element
      HashNode *remove_node = node->next_node;
      node->key = node->next_node->key;
      node->value = node->next_node->value;
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

    if (node->next_node->key == key)
    {
      HashNode *remove_node = node->next_node;
      node->next_node = remove_node->next_node;

      // release the momory
      delete remove_node;
      remove_node = nullptr;
      return;
    }
    node = node->next_node;
  }
}

std::string FindValue(std::vector<HashNode> &HashTable, int key)
{
  int hash_index = ((a * key + b) % (Prime_number)) % HashTableSize;
  std::string value;

  // Empty
  if (HashTable[hash_index].empty)
    return "";

  HashNode *node = &(HashTable[hash_index]);
  while (node != nullptr)
  {
    if (node->key == key)
      return node->value;
    node = node->next_node;
  }
  // Can't find the correspond value in the chain
  return "";
}

void Solve(std::vector<Query> &vec)
{
  std::vector<std::string> answer;
  std::vector<HashNode> HashTable;
  HashTable.resize(HashTableSize);
  for (int i = 0; i < vec.size(); i++)
  {
    if (vec[i].type == "add")
    {
      AddHashNode(HashTable, vec[i].key, vec[i].value);
    }
    else if (vec[i].type == "del")
    {
      DelHashNode(HashTable, vec[i].key);
    }
    else // find
    {
      std::string value = FindValue(HashTable, vec[i].key);
      if (value == "")
        answer.push_back("not found");
      else
        answer.push_back(value);
    }
  }

  // Output answer
  for (int i = 0; i < answer.size(); i++)
    std::cout << answer[i] << std::endl;
}
int main()
{
  std::ios_base::sync_with_stdio(false);
  int N;
  std::cin >> N;
  std::vector<Query> vec;
  vec.resize(N);

  // Read the data
  for (int i = 0; i < N; i++)
  {
    std::cin >> vec[i].type;
    if (vec[i].type == "add")
      std::cin >> vec[i].key >> vec[i].value;
    else
      std::cin >> vec[i].key;
  }

  Solve(vec);

  return 0;
}
