#include <bits/stdc++.h>
const unsigned x = 11;
const unsigned p = 1000000007;

long long CalculateHashValue(std::string str)
{
  long long hashvalue = 0;
  for (int i = static_cast<int>(str.size()) - 1; i >= 0; --i)
    hashvalue = ((hashvalue * x + str[i])) % p;
  return hashvalue;
}

void PreComputeHash(std::vector<long long> &H, std::string str1, std::string str2)
{
  int L = str2.size() - str1.size() + 1;
  H.resize(L);

  // Calculate the initialize value
  std::string substring = str2.substr(L - 1, str1.size());
  // O(|str1|)
  H[L - 1] = CalculateHashValue(substring);

  long long y = 1;
  // O(|str1|)
  for (int i = 1; i <= str1.size(); i++)
    y = (y * x) % p;

  // O(|str2| - |str1)
  for (int i = str2.size() - str1.size() - 1; i >= 0; i--)
  {
    // Might be the negative value
    H[i] = ((x * H[i + 1] + str2[i] - y * str2[i + str1.size()]) % p + p) % p;
  }
}

// O(|str1| + |str2|)
void Rabin_Karp(std::string str1, std::string str2)
{
  std::vector<int> answer;
  std::vector<long long> Pre_Hash;

  // O(|str1|)
  long long target_hash_value = CalculateHashValue(str1);
  // O(|str1| + |str2|)
  PreComputeHash(Pre_Hash, str1, str2);

  // O(|str2| - |str1|)
  for (int i = 0; i < Pre_Hash.size(); i++)
  {
    //std::cout << "1: " << Pre_Hash[i] << std::endl;
    if (Pre_Hash[i] != target_hash_value)
      continue;
    if (Pre_Hash[i] == target_hash_value)
    {
      std::string substring = str2.substr(i, str1.size());
      if (substring == str1)
        answer.push_back(i);
    }
  }

  // Output answer
  for (int i = 0; i < answer.size(); i++)
    std::cout << answer[i] << " ";
  std::cout << std::endl;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::string str1, str2;

  std::cin >> str1 >> str2;
  Rabin_Karp(str1, str2);
}
