#include <bits/stdc++.h>
#include <limits>

std::vector<long long> key;
std::vector<int> left;
std::vector<int> right;

// Update the min and max
bool CheckBinaryTree(int index, long long max, long long min)
{
  // Base case
  if (index == -1)
    return true;

  if (key[index] < min)
    return false;
  if (key[index] > max)
    return false;

  return CheckBinaryTree(left[index], key[index], min) && CheckBinaryTree(right[index], max, key[index]);
}
void Solve()
{
  long long min = std::numeric_limits<long long>::min();
  long long max = std::numeric_limits<long long>::max();
  if (CheckBinaryTree(0, max, min))
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
