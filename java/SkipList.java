// probabilistic data structure that offers efficient search, insertion and deletion
// essentially a linked list with multiple levels where each node is linked to nodes at 
// various levels above it 
// allows for faster searches by skipping over multiple nodes at lower levels

import java.util.Random;

public class SkipList<T extends Comparable<T>> {
  private Node<T> head;
  private int maxLevel;
  private double p;                // probability of moving to next level

  public SkipList() {
    head = new Node<>(null);
    maxLevel = 0;
    p = 0.5;
  }
  private class Node<T> {
    T data;
    Node<T>[] forward;

    public Node(T data) {
      this.data = data;
      forward = new Node[maxLevel + 1];
    }
  }
  private int randomLevel() {
    int level = 0;
    while (Math.random() < p && level < maxLevel) {
      level++;
    }
    return level;
  }
  public void insert(T data) {
    Node<T> current = head;
    Node<T>[] update = new Node[maxLevel + 1];
    for(int i = maxLevel; i >= 0; i--) {
      while(current.forward[i] != null && current.forward[i].data.compareTo(data) < 0) {
        current = current.forward[i];
      }
      update[i] = current;
    }
    int level = randomLevel();
    if(level > maxLevel) {
      for(int i = maxLevel + 1; i <= level; i++) {
        update[i] = head;
      }
      maxLevel = level;
    }
    Node<T> newNode = new Node<>(data);
    for(int i = level; i >= 0; i--) {
      newNode.forward[i] = update[i].forward[i];
      update[i].forward[i] = newNode;
    }
  }
  public boolean search(T data)
  {
    Node<T> current = head;
    for(int i = maxLevel; i >= 0; i--) {
      while(current.forward[i] != null && current.forward[i].data.compareTo(data) < 0) {
        current = current.forward[i];
      }
    }
    current = current.forward[0];
    return current != null && current.data.equals(data);
  }
}
