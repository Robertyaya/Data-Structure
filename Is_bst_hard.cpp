#include <bits/stdc++.h>

std::vector<long long> key;
std::vector<int> left;
std::vector<int> right;

bool CheckBinaryTree(int index, long long max, long long min, bool right_flag)
{
  // Base case, return the leaf
  if (index == -1)
    return true;

  // In right child
  if (right_flag)
  {
    if (key[index] < min)
      return false;
    if (key[index] > max)
      return false;
  }
  else // In left child
  {
    if (key[index] < min)
      return false;
    if (key[index] >= max)
      return false;
  }

  return CheckBinaryTree(left[index], key[index], min, false) && CheckBinaryTree(right[index], max, key[index], true);
}

void Solve()
{
  long long min = std::numeric_limits<long long>::min();
  long long max = std::numeric_limits<long long>::max();
  if (CheckBinaryTree(0, max, min, false))
    std::cout << "CORRECT" << std::endl;
  else
    std::cout << "INCORRECT" << std::endl;
}

int main()
{
  std::ios_base::sync_with_stdio(false), std::cin.tie(0);
  int n;
  std::cin >> n;
  if (n == 0)
    std::cout << "CORRECT" << std::endl;
  else
  {
    key.resize(n);
    left.resize(n);
    right.resize(n);
    for (int i = 0; i < n; i++)
      std::cin >> key[i] >> left[i] >> right[i];
    Solve();
  }
  return 0;
}
