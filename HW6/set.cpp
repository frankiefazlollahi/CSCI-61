#include <iostream>
#include <cstdlib>
#include <iomanip>

using namespace std;
using namespace main_savitch_11;

template <class Item>
set<Item>::set(){
  data_count = 0;
  child_count = 0;
}

template <class Item>
set<Item>::set(const set& source){
  make_copy(source);
}

template <class Item>
void set<Item>::operator =(const set& source){
  make_copy(source);
}

template <class Item>
void set<Item>::copy_data(const set& s)
{
  data_count = s.data_count;
  child_count = s.child_count;
  copy(s.data, s.data + s.data_count,data);
}

template <class Item>
void set<Item>::make_copy(const set& s)
{
  copy_data(s);
  child_count = s.child_count;
  for(int i = 0; i < s.child_count; i++)
  {
    subset[i] = new set();
    subset[i]->make_copy(*s.subset[i]);
  }
}

template <class Item>
void set<Item>::clear()
{
  data_count = 0;
  for(int i = 0; i < child_count; i++)
  {
    subset[i]->clear();
  }
  child_count = 0;
}

template <class Item>
std::size_t set<Item>::count(const Item& target) const
{
  size_t i = 0;
  if(empty())
  {
    return 0;
  }
  while(data[i] < target && i < data_count)
  {
    i++;
  }
  if(i < data_count && !(target < data[i]))
  {
    return 1;
  }
  else if(is_leaf())
  {
    return 0;
  }
  else
  {
    return subset[i]->count(target);
  }
}
//I used the print function on page 570 from the textbook
template <class Item>
void set<Item>::print(int indent) const
{
  const int EXTRA_INDENTATION = 4;
  size_t i;
  std::cout << std::setw(indent) << "";
  for(i = 0; i < data_count; ++i)
  {
    std::cout << data[i] << " ";
  }
  std::cout << std::endl;
  for(i = 0; i < child_count; ++i)
  {
    subset[i]->print(indent+EXTRA_INDENTATION);
  }
}

template <class Item>
bool set<Item>::insert(const Item& entry)
{
  if(!loose_insert(entry))
  {
    return false;
  }
  if(data_count > MAXIMUM)
  {
    set<Item>* newSet = new set<Item>();
    newSet->data_count = data_count;
    newSet->child_count = child_count;
    copy(data, data + data_count, newSet->data);
    copy(subset, subset + child_count, newSet->subset);
    data_count = 0;
    child_count = 1;
    subset[0] = newSet;
    fix_excess(0);
  }
  return true;
}

template <class Item>
bool set<Item>::loose_insert(const Item& entry)
{
  int i = data[0];
  int index;
  for(int index = 0; index < data_count; index++)
  {
    if(data[index] < entry)
      continue;
    else
    {
      i = index;
      break;
    }
  }
  if(index == data_count && i == data[0])
    i = data_count;
  if((i < data_count) && !(entry < data[i]))
  {
    return false;
  }
  else if(is_leaf())
  {
    for(int j = data_count; j > i; j--)
    {
      data[j] = data[j-1];
    }
    data[i] = entry;
    data_count++;
    return true;
  }
  else
  {
    bool is_entered = subset[i]->loose_insert(entry);
    if(subset[i]->data_count > MAXIMUM)
      fix_excess(i);
    return is_entered;
  }
}

template <class Item>
std::size_t set<Item>::erase(const Item& target)
{
  if(!loose_erase(target))
    return false;
  if(data_count == 0 && child_count == 1)
  {
    *this = *subset[0];
    //data_count = subset[0]->data_count;
    //child_count = subset[0]->child_count;
    copy(subset[0]->data, subset[0]->data + subset[0]->data_count, data);
    copy(subset[0]->subset, subset[0]->subset + subset[0]->child_count, subset);
  }
  return true;
}

template <class Item>
bool set<Item>::loose_erase(const Item& entry)
{
  int i = data[0];
  int index;
  for(index = 0; index < data_count; index++)
  {
    if(data[index] < entry)
      continue;
    else
    {
      i = index;
      break;
    }
  }
  if(index == data_count && i == data[0])
  {
    i = data_count;
  }
  if(is_leaf() && ((entry < data[i]) || (i == data_count)))
  {
    return false;
  }
  else if(is_leaf() && !(entry < data[i]))
  {
    if(i == data_count -1)
      data_count--;
    else
    {
      for(index = i; index < data_count; index++)
      {
        data[index] == data[index+1];
      }
      data_count--;
    }
    return true;
  }
  else if(!is_leaf() && ((entry < data[i]) || (i == data_count)))
  {
    bool is_erased = subset[i]->loose_erase(entry);
    if(subset[i]->data_count < MINIMUM)
      fix_shortage(i);
    return is_erased;
  }
  else
  {
    subset[i]->remove_biggest(data[i]);
    if(subset[i]->data_count < MINIMUM)
    {
      fix_shortage(i);
    }
    return true;
  }
}

template <class Item>
void set<Item>::fix_shortage(std::size_t i)
{

  if(i > 0 && subset[i-1]->data_count > MINIMUM)
  {
    for(int index = subset[i]->data_count - 1; index > 0; index--)
    {
      subset[i]->data[index] = subset[i]->data[index - 1];
    }
    subset[i]->data[0] = data[i -1];
    subset[i]->data_count++;
    data[i - 1] = subset[i - 1]->data[subset[i - 1]->data_count - 1];
    subset[i - 1]->data_count--;
    if(!subset[i-1]->is_leaf())
    {
      for(int index = subset[i]->child_count - 1; index > 0; index--)
      {
        subset[i]->subset[index] = subset[i]->subset[index - 1];
      }
      subset[i]->subset[0] = subset[i - 1]->subset[subset[i - 1]->child_count - 1];
      subset[i - 1]->child_count--;
      subset[i]->child_count++;
    }
  }

  if(i < child_count && subset[i+1]->data_count >MINIMUM)
  {
    subset[i]->data[subset[i]->data_count++] =data[i - 1];
    data[i - 1] = subset[i + 1]->data[0];
    for(int index = 0; index < subset[i + 1]->data_count; index++)
    {
      subset[i+1]->data[index] = subset[i+1]->data[index + 1];
    }
    subset[i + 1]->data_count--;
    if(!subset[i+1]->is_leaf())
    {
      subset[i]->subset[subset[i]->child_count++] = subset[i + 1]->subset[0];
      for(int index = 0; index < subset[i + 1]->child_count; index++)
      {
        subset[i+1]->subset[index] = subset[i+1]->subset[index + 1];
      }
      subset[i + 1]->child_count--;
    }
  }

  if(i > 0 && subset[i-1]->data_count == MINIMUM)
  {
    subset[i-1]->data[subset[i-1]->data_count++] = data[i - 1];
    for(int index = i; index < data_count ; index++)
    {
      data[index] = data[index+1];
    }
    data_count--;
    for(int index = 0; index < subset[i]->data_count; index++)
    {
    subset[i-1]->data[subset[i-1]->data_count++] = subset[i]->data[index];
    }
    subset[i]->data_count = 0;
    for(int index = 0; index < subset[i]->child_count; index++)
    {
      subset[i-1]->subset[subset[i-1]->child_count++] = subset[i]->subset[index];
    }
    subset[i]->child_count = 0;
    for(int index = i; index < child_count; index++)
    {
      subset[index] = subset[index+1];
    }
    child_count--;
  }

  if(i < child_count && subset[i+1]->data_count == MINIMUM)
  {
    subset[i]->data[subset[i]->data_count++] = data[i];
    for(int index = i+1; index < data_count ; index++)
    {
      data[index] = data[index+1];
    }
    data_count--;
    for(int index = 0; index < subset[i+1]->data_count; index++)
    {
      subset[i]->data[subset[i]->data_count++] = subset[i+1]->data[index];
    }
    subset[i+1]->data_count = 0;
    for(int index = 0; index < subset[i+1]->child_count; index++)
    {
      subset[i]->subset[subset[i]->child_count++] = subset[i+1]->subset[index];
    }
    subset[i+1]->child_count = 0;
    for(int index = i+1 ; index < child_count; index++)
    {
      subset[index] = subset[index+1];
    }
    child_count--;
  }
}

template <class Item>
void set<Item>::remove_biggest(Item& removed_entry)
{
  if(is_leaf())
  {
    removed_entry = data[data_count-1];
    data_count--;
  }
  else
  {
    subset[child_count-1]->remove_biggest(removed_entry);
    if(subset[child_count-1]->data_count < MINIMUM)
    {
      fix_shortage(child_count-1);
    }
  }
}

template <class Item>
void set<Item>::fix_excess(std::size_t i)
{
  if(!(i < child_count))
  {
    return;
  }
  set<Item>* leftSet = new set<Item>();
  set<Item>* rightSet = new set<Item>();
  copy(subset[i]->data, subset[i]->data + MINIMUM, leftSet->data);
  leftSet->data_count = MINIMUM;
  copy(subset[i]->data + MINIMUM + 1, subset[i]->data + 2 * MINIMUM + 1, rightSet->data);
  rightSet->data_count = MINIMUM;
  copy(subset[i]->subset, subset[i]->subset+subset[i]->child_count / 2, leftSet->subset);
  leftSet->child_count = subset[i]->child_count / 2;
  copy(subset[i]->subset + subset[i]->child_count / 2, subset[i]->subset + subset[i]->child_count, rightSet->subset);
  rightSet->child_count = subset[i]->child_count - subset[i]->child_count / 2;
  for(int j = data_count; j > i; j--)
  {
    data[j] = data[j-1];
  }
  data[i] = subset[i]->data[MINIMUM];
  data_count++;
  for(int j = child_count; j > i; j--)
  {
    subset[j] = subset[j-1];
  }
  subset[i] = leftSet;
  subset[i+1] = rightSet;
  child_count++;
}
