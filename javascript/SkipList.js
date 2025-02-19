class SkipNode {
  constructor(value, level) {
    this.value = value;
    this.next = new Array(level).fill(null);
  }
}

class SkipList {
  constructor(maxLevel) {
    this.maxLevel = maxLevel;
    this.head = new SkipNode(null, maxLevel);
    this.level = 1;
  }

  randomLevel() {
    let level = 1;
    while(Math.random() < 0.5 && level < this.maxLevel) {
      level++;
    }
    return level;
  }

  insert(value) {
    const newLevel = this.randomLevel();
    const update = new Array(this.maxLevel).fill(null);

    let current = this.head;
    for(let i = this.level - 1; i >= 0; i--) {
      while(current.next[i] && current.next[i].value < value) {
        current = current.next[i];
      }
      update[i] = current;
    }
    const newNode = new SkipNode(value, newLevel);
    for(let i = 0; i < newLevel; i++) {
      newNode.next[i] = update[i].next[i];
      update[i].next[i] = newNode;
    }
    this.level = Math.max(this.level, newLevel);
  }

  search(value) {
    let current = this.head;
    for(let i = this.level - 1; i >= 0; i--) {
      while(current.next[i] && current.next[i].value < value) {
        current = current.next[i];
      }
    }
    return current.next[0] && current.next[0].value === value ? current.next[0].value : null;
  }

  delete(value) {
    const update = new Array(this.maxLevel).fill(null);
    let current = this.head;

    for(let i = this.level - 1; i >= 0; i--) {
      while(current.next[i] && current.next[i].value < value) {
        current = current.next[i];
      }
      update[i] = current;
    }
    const nodeToDelete = current.next[0];

    if(nodeToDelete && nodeToDelete.value === value) {
      for(let i = 0; i < this.level; i++) {
        if(update[i].next[i] === nodeToDelete) {
          update[i].next[i] = nodeToDelete.next[i];
        }
      }
      while(this.level > 1 && this.head.next[this.level - 1] === null) {
        this.level--;
      }
    }
  }
  print() {
    for(let i = this.level - 1; i >= 0; i--) {
      let current = this.head.next[i];
      let levelStr = 'Level ${i + 1}:';
      while(current) {
        levelStr += current.value + " -> ";
        current = current.next[i];
      }
      console.log(levelStr + "NULL");
    }
  }
}


// example usage
const skipList = new SkipList(4);

skipList.insert(10);
skipList.insert(20);
skipList.insert(30);
skipList.insert(5);
skipList.insert(15);
skipList.insert(25);
skipList.insert(35);

skipList.print();

console.log("Search 20:", skipList.search(20)); // Output: 20
console.log("Search 22:", skipList.search(22)); // Output: null

skipList.delete(20);
skipList.print();

skipList.delete(5);
skipList.print();

skipList.delete(35);
skipList.print();

