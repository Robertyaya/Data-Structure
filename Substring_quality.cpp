#include <bits/stdc++.h>

// Solve with collison
long long p1 = 1000000007;
long long p2 = 1000000009;
long long x = rand() % 1000000000;

struct Query
{
  Query(int start1 = 0, int start2 = 0, int l = 0) : start1(start1), start2(start2), l(l) {}
  int start1;
  int start2;
  int l;
};

void PreComputeHash(std::string str, std::vector<long long> &hashTable1, std::vector<long long> &hashtable2)
{
  hashTable1.resize(str.size());
  hashtable2.resize(str.size());

  // Initialize the first element
  hashTable1[0] = (int)str[0];
  hashtable2[0] = (int)str[0];

  for (int i = 1; i < str.size(); i++)
  {
    hashTable1[i] = (hashTable1[i - 1] * x + str[i]) % p1;
    hashtable2[i] = (hashtable2[i - 1] * x + str[i]) % p2;
  }
}

void PreComputeMul(std::vector<long long> &value_record1, std::vector<long long> &value_record2, long long max_l)
{
  value_record1.resize(max_l);
  value_record2.resize(max_l);
  value_record1[0] = x;
  value_record2[0] = x;
  for (int i = 1; i < max_l; i++)
  {
    value_record1[i] = (value_record1[i - 1] * x) % p1;
    value_record2[i] = (value_record2[i - 1] * x) % p2;
  }
}

void Solve(std::vector<Query> &vec, std::string str, long long max_l)
{
  std::vector<long long> hashTable1;
  std::vector<long long> hashTable2;

  // O(|str|)
  PreComputeHash(str, hashTable1, hashTable2);
  std::vector<std::string> answer;
  answer.reserve(vec.size());

  std::vector<long long> value_record1, value_record2; // Record the value of y
  PreComputeMul(value_record1, value_record2, max_l);

  // O(|str|)
  for (int i = 0; i < vec.size(); i++)
  {
    if (vec[i].l == 0)
    {
      answer.push_back("No");
      continue;
    }

    long long y1 = value_record1[vec[i].l - 1];
    long long y2 = value_record2[vec[i].l - 1];

    long long hash_value1, _hash_value1, hash_value2, _hash_value2;

    // Hash_Value1
    if (vec[i].start1 == 0)
    {
      hash_value1 = hashTable1[vec[i].start1 + vec[i].l - 1];
      _hash_value1 = hashTable2[vec[i].start1 + vec[i].l - 1];
    }
    else
    {
      hash_value1 = ((hashTable1[vec[i].start1 + vec[i].l - 1] - (y1 * hashTable1[vec[i].start1 - 1]) % p1) % p1 + p1) % p1;
      _hash_value1 = ((hashTable2[vec[i].start1 + vec[i].l - 1] - (y2 * hashTable2[vec[i].start1 - 1]) % p2) % p2 + p2) % p2;
    }

    // Hash_Value2
    if (vec[i].start2 == 0)
    {
      hash_value2 = hashTable1[vec[i].start2 + vec[i].l - 1];
      _hash_value2 = hashTable2[vec[i].start2 + vec[i].l - 1];
    }
    else
    {
      hash_value2 = ((hashTable1[vec[i].start2 + vec[i].l - 1] - (y1 * hashTable1[vec[i].start2 - 1]) % p1) % p1 + p1) % p1;
      _hash_value2 = ((hashTable2[vec[i].start2 + vec[i].l - 1] - (y2 * hashTable2[vec[i].start2 - 1]) % p2) % p2 + p2) % p2;
    }

    if ((hash_value1 == hash_value2) && (_hash_value1 == _hash_value2))
      answer.push_back("Yes");
    else
      answer.push_back("No");
  }

  for (int i = 0; i < answer.size(); i++)
    std::cout << answer[i] << std::endl;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::string str;
  std::vector<Query> vec;
  int query;
  std::cin >> str;
  std::cin >> query;
  vec.resize(query);
  long long max_l = 0;
  for (int i = 0; i < query; i++)
  {
    std::cin >> vec[i].start1 >> vec[i].start2 >> vec[i].l;
    if (vec[i].l > max_l)
      max_l = vec[i].l;
  }

  Solve(vec, str, max_l);

  return 0;
}
