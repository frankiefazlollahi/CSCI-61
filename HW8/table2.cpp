#include "table2.h"
#include "node2.h"

using namespace main_savitch_6B;

namespace main_savitch_12B
{
  template <class RecordType>
  table<RecordType>::table( )
  {
    total_records = 0;
    for(int i = 0; i < TABLE_SIZE; i++)
    {
      data[i] = NULL;
    }
  }

  template <class RecordType>
  table<RecordType>::table(const table& source)
  {
    node<RecordType> *tempTail;
    for(int i = 0; i < TABLE_SIZE; i++)
    {
      list_copy(source.data[i], data[i], tempTail);
    }
    this->total_records = source.total_records;
  }

  template <class RecordType>
  table<RecordType>::~table( )
  {
    for(int i = 0; i < TABLE_SIZE; i++)
    {
      list_clear(data[i]);
    }
  }

  template <class RecordType>
  void table<RecordType>::insert(const RecordType& entry)
  {
    if(is_present(entry.key) == false)
    {
      node<RecordType> *cursor = data[hash(entry.key)];

      if(cursor == NULL)
      {
        cursor = data[hash(entry.key)] = new node<RecordType>;
        cursor->data = entry;
        cursor->link = NULL;
      }
      else
      {
        while(cursor->link != NULL && cursor->data.key != entry.key)
        {
          cursor = cursor->link;
        }

        cursor->link = new node<RecordType>;
        cursor = cursor->link;
        cursor->link = NULL;
        cursor->data = entry;
      }
      total_records++;
    }
  }

  template <class RecordType>
  void table<RecordType>::remove(int key)
  {
    node<RecordType> *cursor = data[hash(key)],
    *precursor = NULL;
    bool found = false;
    while(cursor != NULL)
    {
      if(cursor->data.key == key)
      {
        found = true;
        break;
      }
      precursor = cursor;
      cursor = cursor->link;
    }
    if(found == true)
    {
      list_remove(precursor);
      total_records--;
    }
  }

  template <class RecordType>
  void table<RecordType>::operator =(const table& source)
  {
    if(this == &source)
    return;

    for(int i = 0; i < TABLE_SIZE; i++)
    {
      list_clear(data[i]);
    }
    node<RecordType> *tempTail;
    for(int i = 0; i < TABLE_SIZE; i++)
    {
      list_copy(source.data[i], data[i], tempTail);
    }
    this->total_records = source.total_records;
  }

  template <class RecordType>
  void table<RecordType>::find(int key, bool& found, RecordType& result) const
  {
    node<RecordType> *cursor = data[hash(key)];
    found = false;
    while(cursor != NULL && cursor->data.key != key)
    {
      if(cursor->data.key == key)
      {
        found = true;
        result = cursor->data;
        break;
      }
      cursor = cursor->link;
    }
  }

  template <class RecordType>
  bool table<RecordType>::is_present(int key) const
  {
    node<RecordType> *cursor = data[hash(key)];

    bool found = false;
    while(cursor != NULL)
    {
      if(cursor->data.key == key)
      {
        found = true;
        break;
      }
      cursor = cursor->link;
    }
    return found;
  }

  template <class RecordType>
  std::size_t table<RecordType>::hash(int key) const
  {
    return (key % TABLE_SIZE);
  }
}
