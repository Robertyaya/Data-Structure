#include <bits/stdc++.h>
#include <unordered_map>

// Solve with collison
long long p1 = 1000000007;
long long p2 = 1000000009;
long long x = rand() % 1000000000;

struct Answer
{
  int i, j, len;
};

struct Data
{
  int First_index;
  int Second_index;
  bool bo;
};

struct Record
{
  Record(bool flag = false, int index = -1, Record *next = nullptr) : flag(flag), index(index) {}
  bool flag;
  int index;
};

Data CompareSubString(std::string &s, std::string &t, int length, std::vector<long long> hashTable_s_1, std::vector<long long> hashTable_s_2, std::vector<long long> hashTable_t_1, std::vector<long long> hashTable_t_2, std::vector<long long> Mul_1, std::vector<long long> Mul_2)
{
  Data data;

  std::vector<long long> CompareTable_s_1;
  std::vector<long long> CompareTable_s_2;

  // Calculate the all substring in string s
  long long mul_1 = Mul_1[length - 1];
  long long mul_2 = Mul_2[length - 1];

  // Use this to record the substring of s
  std::unordered_map<long long, Record> map1;
  std::unordered_map<long long, Record> map2;

  // Calculate substring s hash table and save it
  // O(|s|)
  for (int i = 0; i <= s.size() - length; i++)
  {
    long long s_1, s_2;
    if (i == 0)
    {
      s_1 = hashTable_s_1[length - 1];
      s_2 = hashTable_s_2[length - 1];
    }
    else
    {
      s_1 = ((hashTable_s_1[i + length - 1] - (mul_1 * hashTable_s_1[i - 1]) % p1) % p1 + p1) % p1;
      s_2 = ((hashTable_s_2[i + length - 1] - (mul_2 * hashTable_s_2[i - 1]) % p2) % p2 + p2) % p2;
    }
    // Build the map
    Record temp;
    temp.flag = true;
    temp.index = i;
    map1.insert(std::make_pair(s_1, temp));
    map2.insert(std::make_pair(s_2, temp));
  }

  // Calculate the all substring in string t
  //O(|t|)
  for (int i = 0; i <= t.size() - length; i++)
  {
    long long hashValue_t_1, hashValue_t_2;
    if (i == 0)
    {
      hashValue_t_1 = hashTable_t_1[length - 1];
      hashValue_t_2 = hashTable_t_2[length - 1];
    }
    else
    {
      hashValue_t_1 = ((hashTable_t_1[i + length - 1] - (mul_1 * hashTable_t_1[i - 1]) % p1) % p1 + p1) % p1;
      hashValue_t_2 = ((hashTable_t_2[i + length - 1] - (mul_2 * hashTable_t_2[i - 1]) % p2) % p2 + p2) % p2;
    }
    std::unordered_map<long long, Record>::iterator iter1;
    std::unordered_map<long long, Record>::iterator iter2;

    // O(1)
    iter1 = map1.find(hashValue_t_1);
    iter2 = map2.find(hashValue_t_2);
    if (iter1 != map1.end() && iter2 != map2.end())
    {
      data.bo = true;
      data.First_index = iter1->second.index;
      data.Second_index = i;
      return data;
    }
  }
  data.bo = false;
  data.First_index = -1;
  data.Second_index = -1;
  return data;
}

void PreComputeHash(std::string &s, std::string &t, std::vector<long long> &hashTable_s_1, std::vector<long long> &hashTable_s_2, std::vector<long long> &hashTable_t_1, std::vector<long long> &hashTable_t_2)
{
  hashTable_s_1.resize(s.size());
  hashTable_s_2.resize(s.size());
  hashTable_t_1.resize(t.size());
  hashTable_t_2.resize(t.size());

  // Initialize
  hashTable_s_1[0] = (int)s[0];
  hashTable_s_2[0] = (int)s[0];
  hashTable_t_1[0] = (int)t[0];
  hashTable_t_2[0] = (int)t[0];

  for (int i = 1; i < s.size(); i++)
  {
    hashTable_s_1[i] = (hashTable_s_1[i - 1] * x + s[i]) % p1;
    hashTable_s_2[i] = (hashTable_s_2[i - 1] * x + s[i]) % p2;
  }
  for (int i = 1; i < t.size(); i++)
  {
    hashTable_t_1[i] = (hashTable_t_1[i - 1] * x + t[i]) % p1;
    hashTable_t_2[i] = (hashTable_t_2[i - 1] * x + t[i]) % p2;
  }
}

void PreComputeMul(std::vector<long long> &Mul_1, std::vector<long long> &Mul_2, long long max_l)
{
  Mul_1.resize(max_l - 1);
  Mul_2.resize(max_l - 1);

  // Initialize
  Mul_1[0] = x;
  Mul_2[0] = x;

  // Calculate s
  for (int i = 1; i < max_l - 1; i++)
  {
    Mul_1[i] = (Mul_1[i - 1] * x) % p1;
    Mul_2[i] = (Mul_2[i - 1] * x) % p2;
  }
}

Answer solve(std::string &s, std::string &t)
{
  std::vector<long long> hashTable_s_1;
  std::vector<long long> hashTable_s_2;
  std::vector<long long> hashTable_t_1;
  std::vector<long long> hashTable_t_2;

  // O(|s|+|t|)
  PreComputeHash(s, t, hashTable_s_1, hashTable_s_2, hashTable_t_1, hashTable_t_2);

  std::vector<long long> MulTable_1;
  std::vector<long long> MulTable_2;

  long long max_l;
  if (s.size() > t.size())
    max_l = s.size();
  else
    max_l = t.size();
  // O(|s|+|t|)
  PreComputeMul(MulTable_1, MulTable_2, max_l);

  Answer ans = {0, 0, 0};
  // Find the longest common substring
  int l = 0;
  int r = std::min(s.size(), t.size());

  Data data = {-1, -1, false};
  Data previous_data = {-1, -1, false};

  // O(logn * (|s|+|t|))
  while (l <= r && r > 0)
  {
    int mid = l + (r - l) / 2;
    // O(|s|+|t|)
    data = CompareSubString(s, t, mid, hashTable_s_1, hashTable_s_2, hashTable_t_1, hashTable_t_2, MulTable_1, MulTable_2);
    if (data.bo)
    {
      l = mid + 1;
      previous_data.bo = data.bo;
      previous_data.First_index = data.First_index;
      previous_data.Second_index = data.Second_index;
    }
    else
      r = mid - 1;
  }

  // Represent there are no substring equal
  if (previous_data.First_index < 0 || previous_data.Second_index < 0)
  {
    ans.len = 0;
    ans.i = 0;
    ans.j = 1;
  }
  else
  {
    ans.len = l - 1;
    ans.i = previous_data.First_index;
    ans.j = previous_data.Second_index;
  }
  return ans;
}

int main()
{
  std::ios_base::sync_with_stdio(false), std::cin.tie(0);
  std::string s, t;
  while (std::cin >> s >> t)
  {
    auto ans = solve(s, t);
    std::cout << ans.i << " " << ans.j << " " << ans.len << "\n";
  }
}
