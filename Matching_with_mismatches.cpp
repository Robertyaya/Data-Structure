#include <bits/stdc++.h>

// Solve with collison
long long p1 = 1000000007;
long long p2 = 1000000009;
long long x = rand() % 26;

std::vector<long long> hash_t_1;
std::vector<long long> hash_t_2;
std::vector<long long> hash_p_1;
std::vector<long long> hash_p_2;
std::vector<long long> mul_1;
std::vector<long long> mul_2;

void PreComputeHash(std::string t, std::string p)
{
  hash_t_1.resize(t.size());
  hash_t_2.resize(t.size());
  hash_p_1.resize(p.size());
  hash_p_2.resize(p.size());
  hash_t_1[0] = (int)t[0];
  hash_t_2[0] = (int)t[0];
  hash_p_1[0] = (int)p[0];
  hash_p_2[0] = (int)p[0];

  for (int i = 1; i < t.size(); i++)
  {
    hash_t_1[i] = (hash_t_1[i - 1] * x + (int)t[i]) % p1;
    hash_t_2[i] = (hash_t_2[i - 1] * x + (int)t[i]) % p2;
  }

  for (int i = 1; i < p.size(); i++)
  {
    hash_p_1[i] = (hash_p_1[i - 1] * x + (int)p[i]) % p1;
    hash_p_2[i] = (hash_p_2[i - 1] * x + (int)p[i]) % p2;
  }
}
void PreComputeMul(int max_l)
{
  mul_1.resize(max_l - 1);
  mul_2.resize(max_l - 1);
  mul_1[0] = x;
  mul_2[0] = x;
  for (int i = 1; i < max_l - 1; i++)
  {
    mul_1[i] = (mul_1[i - 1] * x) % p1;
    mul_2[i] = (mul_2[i - 1] * x) % p2;
  }
}

void FindMisMatch(int l, int r, int &k, int t_index)
{
  if (k < 0)
    return;

  long long p_hash_value_1, p_hash_value_2, t_hash_value_1, t_hash_value_2;
  // Compare the current sub string
  // string p
  if (l == 0)
  {
    p_hash_value_1 = hash_p_1[r];
    p_hash_value_2 = hash_p_2[r];
  }
  else
  {
    p_hash_value_1 = ((hash_p_1[r] - (mul_1[r - l] * hash_p_1[l - 1]) % p1) % p1 + p1) % p1;
    p_hash_value_2 = ((hash_p_2[r] - (mul_2[r - l] * hash_p_2[l - 1]) % p2) % p2 + p2) % p2;
  }
  // string t
  int l_t = t_index + l;
  int r_t = t_index + r;
  if (l_t == 0)
  {
    t_hash_value_1 = hash_t_1[r_t];
    t_hash_value_2 = hash_t_2[r_t];
  }
  else
  {
    t_hash_value_1 = ((hash_t_1[r_t] - (mul_1[r_t - l_t] * hash_t_1[l_t - 1]) % p1) % p1 + p1) % p1;
    t_hash_value_2 = ((hash_t_2[r_t] - (mul_2[r_t - l_t] * hash_t_2[l_t - 1]) % p2) % p2 + p2) % p2;
  }

  if (p_hash_value_1 == t_hash_value_1 && p_hash_value_2 == t_hash_value_2)
    return;

  if (k == 0 && (p_hash_value_1 != t_hash_value_1 || p_hash_value_2 != t_hash_value_2))
  {
    k--;
    return;
  }
  // Base case (l == r) don't need to keep search
  if (l == r && (p_hash_value_1 != t_hash_value_1 || p_hash_value_2 != t_hash_value_2))
  {
    k--;
    return;
  }

  // ========== The current string is not the same, we divide it ========== //
  long long p_hash_left_1, p_hash_left_2, p_hash_right_1, p_hash_right_2;
  int mid = l + (r - l) / 2;
  // Left: l~mid, Right: mid+1~r
  // Calculate left hash value
  if (l == 0)
  {
    p_hash_left_1 = hash_p_1[mid];
    p_hash_left_2 = hash_p_2[mid];
  }
  else
  {
    p_hash_left_1 = ((hash_p_1[mid] - (mul_1[mid - l] * hash_p_1[l - 1]) % p1) % p1 + p1) % p1;
    p_hash_left_2 = ((hash_p_2[mid] - (mul_2[mid - l] * hash_p_2[l - 1]) % p2) % p2 + p2) % p2;
  }

  p_hash_right_1 = ((hash_p_1[r] - (mul_1[r - mid] * hash_p_1[mid]) % p1) % p1 + p1) % p1;
  p_hash_right_2 = ((hash_p_2[r] - (mul_2[r - mid] * hash_p_2[mid]) % p2) % p2 + p2) % p2;

  // std::cout << "p_Left: " << p_hash_left_1 << std::endl;
  // std::cout << "p_Right: " << p_hash_right_1 << std::endl;

  // Left: (t_index) ~ (t_index+mid), Rigth: (t_index+mid+1) ~ (t_index+r)
  int mid_t = t_index + mid;
  long long t_hash_left_1, t_hash_left_2, t_hash_right_1, t_hash_right_2;

  if (l_t == 0) // t_index = 0
  {
    t_hash_left_1 = hash_t_1[mid_t];
    t_hash_left_2 = hash_t_2[mid_t];
  }
  else // t_index != 0
  {
    t_hash_left_1 = ((hash_t_1[mid_t] - (mul_1[mid_t - l_t] * hash_t_1[l_t - 1]) % p1) % p1 + p1) % p1;
    t_hash_left_2 = ((hash_t_2[mid_t] - (mul_2[mid_t - l_t] * hash_t_2[l_t - 1]) % p2) % p2 + p2) % p2;
  }
  t_hash_right_1 = ((hash_t_1[r_t] - (mul_1[r_t - mid_t] * hash_t_1[mid_t]) % p1) % p1 + p1) % p1;
  t_hash_right_2 = ((hash_t_2[r_t] - (mul_1[r_t - mid_t] * hash_t_2[mid_t]) % p2) % p2 + p2) % p2;

  // ======== Binary Search ========= //
  // Recursion to find the mismatch
  if (t_hash_left_1 != p_hash_left_1 || t_hash_left_2 != p_hash_left_2) // Left
  {
    FindMisMatch(l, mid, k, t_index);
  }
  if (t_hash_right_1 != p_hash_right_1 || t_hash_right_2 != p_hash_right_2) // Right
  {
    FindMisMatch(mid + 1, r, k, t_index);
  }
  return;
}

void Solve(int k, std::string t, std::string p)
{
  int temp_k = k;
  std::vector<int> answer;

  //O(|t|+|p|)
  PreComputeHash(t, p);
  PreComputeMul(std::max(t.size(), p.size()));

  for (int i = 0; i < t.size() - p.size() + 1; i++)
  {
    int l = 0;
    int r = p.size() - 1;

    FindMisMatch(l, r, temp_k, i);
    if (temp_k >= 0)
      answer.push_back(i);
    temp_k = k;
    std::cout << std::endl;
  }

  // Output answer
  if (answer.size() == 0)
    std::cout << answer.size() << std::endl;
  else
  {
    std::cout << answer.size() << " ";
    for (int i = 0; i < answer.size(); i++)
      std::cout << answer[i] << " ";
    std::cout << std::endl;
  }
}

int main()
{
  std::ios_base::sync_with_stdio(false), std::cin.tie(0);

  int k;
  std::string t, p;
  while (std::cin >> k >> t >> p)
  {
    Solve(k, t, p);
  }
  return 0;
}
