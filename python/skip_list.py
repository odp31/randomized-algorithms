import random 

class Node:
  def __init__(self, key):
    self.key = key
    self.forward = []

class SkipList:
  def __init__(self):
    self.header = Node(None)
    self.level = 0

  def update(self, key, update):
    x = self.header
    for i in reversed(range(self.level)):
      while x.forward[i] and x.forward[i].key < key:
        x = x.forward[i]
      update[i] = x

  def search(self, key):
    update = [None] * (self.level + 1)
    x = self.header
    for i in reversed(range(self.level)):
      while x.forward[i] and x.forward[i].key < key:
        x = x.forward[i]
      update[i] = x
    x = x.forward[0]
    if x and x.key == key:
      return True
    else:
      return False 


  def insert(self, key):
    update = [None] * (self.level + 1)
    x = self.header
    for i in reversed(range(self.level)):
      while x.forward[i] and x.forward[i].key < key:
        x = x.forward[i]
      update[i] = x
    r = random.randint(1, self.level + 1)
    if r > self.level:
      for i in range(self.level + 1, r):
        update[i] = self.header
      self.level = r
    x = Node(key)
    for i in range(r):
      x.forward.append(update[i].forward[i])
      update[i].forward[i] = x 

def delete(self, key):
  update = [None] * (self.level + 1)
  x = self.header
  for i in reversed(range(self.level)):
    while x.forward[i] and x.forward[i].key < key:
      x = x.forward[i]
    update[i] = x
  x = x.forward[0]
  if x and x.key == key:
    for i in range(self.level):
      if update[i].forward[i] != x:
        break
      update[i].forward[i] = x.forward[i]
    while self.level > 0 and self.header.forward[self.level - 1] is None:
      self.level -= 1
