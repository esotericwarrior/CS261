struct hlink
{
  TYPE value;
  struct hlink *next;
};


struct hashTable
{
  struct hlink ** table;
  int tablesize;
  int count;
};


void initHashTable (struct hashTable * ht, int size)
{
  int i;

  ht->size = size; //Initialize the size
  ht->count = 0;  //Set the count equal to zero.

  ht->table = malloc(size * sizeof(struct hlink *));
  assert(ht->table != 0);

  if(i=0; i<size; i++)
  {
    ht->table[i] = 0; //Set to NULL;
  }
}

int hashTableSize (struct hashTable * ht) { return ht->count; }


void hashTableAdd (struct hashTable *ht, TYPE newValue)
{ //compute hash value to find the correct bucket
  int hashIndex = HASH(newValue) % ht->tablesize;
  if (hashIndex < 0) hashIndex += ht->tablesize;
  struct hlink * newLink = (struct hlink *) malloc(sizeof(struct hlink));
  assert(newLink);
  newLink->value = newValue;
  newLink->next = ht->table[hashIndex];
  ht->table[hashIndex] = newLink; /* add to bucket */
  ht->count++;
  if ((ht->count / (double) ht->tablesize) > 8.0) _resizeHashTable(ht);
}


int hashTableContains (struct hashTable * ht, TYPE testElement)
{
  int hashIndex = HASH(testElement) % ht->tablesize;

  struct hlink * current;
  current = ht->table[hashIndex];

  while (current != 0)
  {
    /* code */
    if(EQ(current->value, testElement))
      return 1;
      current = current->next;
  }

  return 0;
}

void hashTableRemove (struct hashTable * ht, TYPE testElement)
{
  int hashIndex = HASH(testElement) % ht->tablesize;

  struct hlink * current;
  current = ht->table[hashIndex];

  while(current != 0)
  {
    //如果找到了相同的value
    if(EQ(current->value, testElement))
    {
      ht->table[hashIndex] = current->next;
    }
    free(current);
    current = 0;
    ht->count--;

    //移动到下一个 move to next;
    else
    {
      current = current->next;
    }
  }
}

void resizeTable (struct hashTable *ht)
{
  assert(ht !=0);

  //We want to free the temp;
  struct HashTable *temp;
  temp = ht;

  struct hlink * current;
  struct hlink * rem;

  initHashTable(ht, 2 * ht->tablesize);

  for(int i=0; i<ht->tablesize; i++)
  {
    current = ht->table[i];

    while(current != 0)
    {
      hashTableAdd(ht, current->value);
      rem = current;
      current = current->next;
      free(rem);
    }
  }
  free(temp);
}