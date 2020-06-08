#include <bits/stdc++.h>

int main()
{
  std::ios_base::sync_with_stdio(false);

  int num_queries = 0;
  std::cin >> num_queries;

  std::string query;
  int value;

  std::stack<int> stack;
  std::stack<int> max_element;

  for (int i = 0; i < num_queries; i++)
  {
    std::cin >> query;
    if (query == "push")
    {
      std::cin >> value;

      if (max_element.size() == 0)
        max_element.push(value);
      else
      {
        int top_element = max_element.top();
        if (value >= top_element)
          max_element.push(value);
      }

      stack.push(value);
    }
    else if (query == "pop")
    {
      int top_element = stack.top();
      int max_top_element = max_element.top();
      if (top_element == max_top_element)
        max_element.pop();
      stack.pop();
    }
    else if (query == "max")
    {
      if (max_element.size() == 0)
        std::cout << "" << std::endl;
      else
      {
        int max = max_element.top();
        std::cout << max << std::endl;
      }
    }
    else
    {
      assert(0);
    }
  }

  return 0;
}
