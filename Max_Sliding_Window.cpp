#include <bits/stdc++.h>

std::vector<int> Solve(std::vector<int> &vec, int window_size)
{
  std::vector<int> answer;

  // Save the index
  std::deque<int> d;

  for (int i = 0; i < vec.size(); i++)
  {
    // If the d.front() == i-window_size represent the window move right one space
    if (!d.empty() && d.front() == i - window_size)
      d.pop_front();

    // Only save the biggest in the deque
    while (!d.empty() && vec[d.back()] < vec[i])
      d.pop_back();

    d.push_back(i);

    if (i >= window_size - 1)
      answer.push_back(vec[d.front()]);
  }

  return answer;
}

int main()
{
  std::ios_base::sync_with_stdio(false);

  int n = 0;
  std::cin >> n;
  std::vector<int> vec;
  for (int i = 0; i < n; i++)
  {
    int temp;
    std::cin >> temp;
    vec.push_back(temp);
  }

  int window_size;
  std::cin >> window_size;
  std::vector<int> ans = Solve(vec, window_size);

  for (int i = 0; i < ans.size(); i++)
    std::cout << ans[i] << " ";
  std::cout << std::endl;

  return 0;
}
