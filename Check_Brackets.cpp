#include <iostream>
#include <stack>
#include <string>

struct Element
{
  char ch;
  int index;
};

bool Match(Element &top, char &ch)
{
  if (ch == ']')
  {
    if (top.ch == '[')
      return true;
    else
      return false;
  }
  else if (ch == '}')
  {
    if (top.ch == '{')
      return true;
    else
      return false;
  }
  else if (top.ch == '(')
    return true;
  else
    return false;
}

int main()
{
  std::string text;
  std::cin >> text;
  std::stack<Element> container;

  bool success = true;

  for (int i = 0; i < text.size(); i++)
  {
    char ch = text[i];

    // Boundary condition, only one element, we can directly return answer
    if (text.size() == 1)
    {
      std::cout << i + 1 << std::endl;
      success = false;
      break;
    }

    if (ch == '[' || ch == '{' || ch == '(')
    {
      // Record the char and its index
      Element ele_temp = {ch, i + 1};
      container.push(ele_temp);
    }
    else if (ch == ']' || ch == '}' || ch == ')')
    {
      // Check whether the container is empty
      if (container.empty())
      {
        std::cout << i + 1 << std::endl;
        success = false;
        break;
      }
      else // If not empty, we check whether the char is match
      {
        // Get the top char
        Element top = container.top();
        if (Match(top, ch)) // Compare the char
        {
          success = true;
          container.pop(); // Remove the top one
        }
        else
        {
          success = false; // Not match, directly break the loop and output the answer
          std::cout << i + 1 << std::endl;
          break;
        }
      }
    }
  }

  // There are a not match char in the container
  if (container.size() != 0 && success)
  {
    std::cout << container.top().index << std::endl;
    success = false;
  }
  if (success)
    std::cout << "Success" << std::endl;
}
