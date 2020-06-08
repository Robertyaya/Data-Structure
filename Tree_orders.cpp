#include <bits/stdc++.h>
#include <sys/resource.h>

std::vector<long long> key;
std::vector<int> left;
std::vector<int> right;

void inorder(int index)
{
  if (left[index] == -1 && right[index] == -1) // Arrive the leaf
  {
    std::cout << key[index] << " "; // print left leaf
    return;
  }
  if (left[index] != -1)
    inorder(left[index]);
  std::cout << key[index] << " ";
  if (right[index] != -1)
    inorder(right[index]);
}

void preorder(int index)
{
  if (left[index] == -1 && right[index] == -1)
  {
    std::cout << key[index] << " ";
    return;
  }

  std::cout << key[index] << " ";
  if (left[index] != -1)
    preorder(left[index]);
  if (right[index] != -1)
    preorder(right[index]);
}

void postorder(int index)
{
  if (left[index] == -1 && right[index] == -1)
  {
    std::cout << key[index] << " ";
    return;
  }

  if (left[index] != -1)
    postorder(left[index]);
  if (right[index] != -1)
    postorder(right[index]);
  std::cout << key[index] << " ";
}

void Solve()
{
  // In-order
  inorder(0);
  std::cout << std::endl;

  // Pre-order
  preorder(0);
  std::cout << std::endl;

  // Post-order
  postorder(0);
  std::cout << std::endl;
}
int main()
{
  // Allow larger stack space
  const rlim_t kStackSize = 16 * 1024 * 1024; // min stack size = 16 MB
  struct rlimit rl;
  int result;

  result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0)
  {
    if (rl.rlim_cur < kStackSize)
    {
      rl.rlim_cur = kStackSize;
      result = setrlimit(RLIMIT_STACK, &rl);
      if (result != 0)
      {
        std::cerr << "setrlimit returned result = " << result << std::endl;
      }
    }
  }

  std::ios_base::sync_with_stdio(false), std::cin.tie(0);
  int n;
  std::cin >> n;
  key.resize(n);
  left.resize(n);
  right.resize(n);
  for (int i = 0; i < n; i++)
    std::cin >> key[i] >> left[i] >> right[i];
  Solve();
}
